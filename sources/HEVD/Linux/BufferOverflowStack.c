
#include "BufferOverflowStack.h"

int trigger_buffer_overflow_stack(void *user_buffer, size_t size)
{
    int status = STATUS_SUCCESS;
    unsigned long kernel_buffer[BUFFER_SIZE] = { 0 };

    INFO("[+] user_buffer: 0x%p\n", user_buffer);
    INFO("[+] user_buffer size: 0x%zX\n", size);
    INFO("[+] kernel_buffer: 0x%p\n", &kernel_buffer);
    INFO("[+] kernel_buffer size: 0x%zX\n", sizeof(kernel_buffer));

#ifdef SECURE

    copy_from_user(kernel_buffer, user_buffer, sizeof(kernel_buffer));
#else
    INFO("[+] Triggering Buffer Overflow in Stack\n");


    copy_from_user(kernel_buffer, user_buffer, size);
#endif
    
    return status;
}


int buffer_overflow_stack_ioctl_handler(struct hevd_io *io)
{
    size_t size = 0;
    void *user_buffer = NULL;
    int status = -EINVAL;

    user_buffer = io->input_buffer;
    size = io->input_buffer_length;

    if (user_buffer)
    {
        status = trigger_buffer_overflow_stack(user_buffer, size);
    }

    return status;
}
