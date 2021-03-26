
#include "UninitializedMemoryStack.h"

void
UninitializedMemoryStackObjectCallback(void)
{
    INFO("[+] Uninitialized Memory Stack Object Callback\n");
}


int trigger_uninitialized_memory_stack(void *user_buffer, size_t size)
{
    unsigned long UserValue = 0;
    unsigned long MagicValue = 0xBAD0B0B0;
    int status = STATUS_SUCCESS;

#ifdef SECURE

    UNINITIALIZED_MEMORY_STACK UninitializedMemory = { 0 };
#else

    UNINITIALIZED_MEMORY_STACK UninitializedMemory;
#endif

    if(copy_from_user(&UserValue, user_buffer, sizeof(UserValue))) {
        ERR("Failed to copy UserValue from user space\n");

        status = -EINVAL;
        return status;
    }

    INFO("[+] UserValue: [0x%p] [0x%zX]\n", &UserValue, UserValue);
    INFO("[+] UninitializedMemory Address: 0x%p\n", &UninitializedMemory);

    if (UserValue == MagicValue) {
        UninitializedMemory.Value = UserValue;
        UninitializedMemory.Callback = &UninitializedMemoryStackObjectCallback;
    }

#ifndef SECURE
    INFO("[+] Triggering Uninitialized Memory in Stack\n");
#endif

    if (UninitializedMemory.Callback) {
        UninitializedMemory.Callback();
    }

    return status;
}


int uninitialized_memory_stack_ioctl_handler(struct hevd_io *io)
{
    size_t size = 0;
    void *user_buffer = NULL;
    int status = -EINVAL;

    user_buffer = io->input_buffer;
    size = io->input_buffer_length;

    if (user_buffer)
    {
        status = trigger_uninitialized_memory_stack(user_buffer, size);
    }

    return status;
}
