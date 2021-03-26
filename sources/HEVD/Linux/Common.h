
#pragma once

#ifndef __COMMON_H__
#define __COMMON_H__

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/version.h>


#define BUFFER_SIZE 512

#define STATUS_SUCCESS      0x0

#define _STRINGIFY(value) #value
#define STRINGIFY(value) _STRINGIFY(value)

#define PRINTK(level, fmt, ...) printk(KERN_##level "%s: " fmt, THIS_MODULE->name, ##__VA_ARGS__)

#define ERR(fmt, ...) PRINTK(ERR, fmt, ##__VA_ARGS__)
#define INFO(fmt, ...) PRINTK(INFO, fmt, ##__VA_ARGS__)
#define WARNING(fmt, ...) PRINTK(WARNING, fmt, ##__VA_ARGS__)

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5,0,0))

#define VERIFY_READ     0
#define VERIFY_WRITE    1
#define x_access_ok(type, addr, size) access_ok(addr, size)

#else 

#define x_access_ok(type, addr, size) access_ok(type, addr, size)

#endif

typedef void (*FunctionPointer)(void);



struct hevd_io {
    void *input_buffer;
    size_t input_buffer_length;
    void *output_buffer;
    size_t output_buffer_length;
};


int buffer_overflow_stack_ioctl_handler(struct hevd_io *io);
int integer_overflow_ioctl_handler(struct hevd_io *io);
int arbitrary_write_ioctl_handler(struct hevd_io *io);
int uninitialized_memory_stack_ioctl_handler(struct hevd_io *io);

#endif 
