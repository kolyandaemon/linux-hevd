#pragma once

#ifndef __HACKSYS_EXTREME_VULNERABLE_DRIVER_H__
#define __HACKSYS_EXTREME_VULNERABLE_DRIVER_H__

#include "Common.h"


#define BANNER \
         "                                        \n" \
         " ##     ## ######## ##     ## ########  \n" \
         " ##     ## ##       ##     ## ##     ## \n" \
         " ##     ## ##       ##     ## ##     ## \n" \
         " ######### ######   ##     ## ##     ## \n" \
         " ##     ## ##        ##   ##  ##     ## \n" \
         " ##     ## ##         ## ##   ##     ## \n" \
         " ##     ## ########    ###    ########  \n" \
         "   HackSys Extreme Vulnerable Driver    \n" \
         "             Version: 4.00              \n"

#define IOCTL(NUM) _IOWR('h', NUM, struct hevd_io)



#define HEVD_IOCTL_BUFFER_OVERFLOW_STACK                IOCTL(0)
#define HEVD_IOCTL_ARBITRARY_WRITE                      IOCTL(1)
#define HEVD_IOCTL_INTEGER_OVERFLOW                     IOCTL(2)
#define HEVD_IOCTL_UNINITIALIZED_MEMORY_STACK           IOCTL(3)

static int __init hevd_init(void);
static void __exit hevd_exit(void);
static long hevd_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

#endif  
