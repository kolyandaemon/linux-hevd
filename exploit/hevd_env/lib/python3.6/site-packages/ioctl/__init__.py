# SPDX-License-Identifier: MIT

import array
import fcntl

from typing import Optional, Union


__all__ = ['IOCTL']


class IOCTL(object):
    '''
    Constructs and performs ioctl(s)
    See include/asm-generic/ioctl.h
    '''
    NRBITS: int = 8
    TYPEBITS: int = 8

    SIZEBITS: int = 14
    DIRBITS: int = 2

    NRMASK: int = (1 << NRBITS) - 1
    TYPEMASK: int = (1 << TYPEBITS) - 1
    SIZEMASK: int = (1 << SIZEBITS) - 1
    DIRMASK: int = (1 << DIRBITS) - 1

    NRSHIFT: int = 0
    TYPESHIFT: int = NRSHIFT + NRBITS
    SIZESHIFT: int = TYPESHIFT + TYPEBITS
    DIRSHIFT: int = SIZESHIFT + SIZEBITS

    class Direction:
        NONE = 0
        WRITE = 1
        READ = 2

    def __init__(self, dir: int, ty: str, nr: int, size: int = 0, bad: bool = False) -> None:
        assert self.Direction.NONE <= dir <= self.Direction.READ + self.Direction.WRITE

        if dir == self.Direction.NONE:
            size = 0
        elif not bad:
            assert size, size <= self.SIZEMASK

        self.op = (
            (dir << self.DIRSHIFT) |
            (ord(ty) << self.TYPESHIFT) |
            (nr << self.NRSHIFT) |
            (size << self.SIZESHIFT)
        )

    def perform(self, fd: int, buf: Optional[Union[str, bytes, 'array.array[int]']] = None) -> bytearray:
        '''
        Performs the ioctl
        '''
        size = self.unpack_size(self.op)

        if buf is None:
            buf = (size * '\x00').encode()

        return bytearray(fcntl.ioctl(fd, self.op, buf))  # type: ignore

    @classmethod
    def unpack_dir(cls, nr: int) -> int:
        return (nr >> cls.DIRSHIFT) & cls.DIRMASK

    @classmethod
    def unpack_type(cls, nr: int) -> int:
        return (nr >> cls.TYPESHIFT) & cls.TYPEMASK

    @classmethod
    def unpack_nr(cls, nr: int) -> int:
        return (nr >> cls.NRSHIFT) & cls.NRMASK

    @classmethod
    def unpack_size(cls, nr: int) -> int:
        return (nr >> cls.SIZESHIFT) & cls.SIZEMASK

    @classmethod
    def IO(cls, ty: str, nr: int) -> 'IOCTL':
        '''
        Constructor for no direction
        '''
        return cls(cls.Direction.NONE, ty, nr)

    @classmethod
    def IOR(cls, ty: str, nr: int, size: int) -> 'IOCTL':
        '''
        Constructor for read
        '''
        return cls(cls.Direction.READ, ty, nr, size)

    @classmethod
    def IOW(cls, ty: str, nr: int, size: int) -> 'IOCTL':
        '''
        Constructor for write
        '''
        return cls(cls.Direction.WRITE, ty, nr, size)

    @classmethod
    def IORW(cls, ty: str, nr: int, size: int) -> 'IOCTL':
        '''
        Constructor for read & write
        '''
        return cls(cls.Direction.READ | cls.Direction.WRITE, ty, nr, size)
