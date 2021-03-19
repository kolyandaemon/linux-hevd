#include "IntegerOverflow.h"


int trigger_integer_overflow(void *user_buffer, size_t size)
{
    unsigned long count = 0;
    int status = STATUS_SUCCESS;
    unsigned long kernel_buffer[BUFFER_SIZE] = {0};
    unsigned long kernel_buffer_terminator = 0xBAD0B0B0;
    size_t terminator_size = sizeof(kernel_buffer_terminator);

    INFO("[+] user_buffer: 0x%p\n", user_buffer);
    INFO("[+] user_buffer size: 0x%zX\n", size);
    INFO("[+] kernel_buffer: 0x%p\n", &kernel_buffer);
    INFO("[+] kernel_buffer size: 0x%zX\n", sizeof(kernel_buffer));

#ifdef SECURE

    if (size > (sizeof(kernel_buffer) - terminator_size))
    {
        ERR("[-] Invalid user buffer size: 0x%zX\n", size);

        status = -EINVAL;
        return status;
    }

#else
    INFO("[+] Triggering Integer Overflow\n");


    if ((size + terminator_size) > sizeof(kernel_buffer))
    {
        ERR("[-] Invalid user buffer size: 0x%zX\n", size);

        status = -EINVAL;
        return status;
    }
#endif

    while (count < (size / sizeof(unsigned long)))
    {
        unsigned long n;

        copy_from_user((void *)&n, user_buffer + count, sizeof(n));
        if (n == kernel_buffer_terminator)
            break;

        kernel_buffer[count++] = n;
    }

    return status;
}


int integer_overflow_ioctl_handler(struct hevd_io *io)
{
    size_t size = 0;
    void *user_buffer = NULL;
    int status = -EINVAL;

    user_buffer = io->input_buffer;
    size = io->input_buffer_length;

    if (user_buffer)
    {
        status = trigger_integer_overflow(user_buffer, size);
    }

    return status;
}
