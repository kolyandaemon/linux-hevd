#include "ArbitraryWrite.h"


int trigger_arbitrary_write(PWRITE_WHAT_WHERE user_write_what_where)
{
    void *what = NULL;
    void *where = NULL;
    int status = STATUS_SUCCESS;

    if (!x_access_ok(VERIFY_READ, user_write_what_where, sizeof(WRITE_WHAT_WHERE)))
    {
        ERR("[-] Invalid parameters");

        status = -EINVAL;
        return status;
    }

    what = user_write_what_where->What;
    where = user_write_what_where->Where;

    INFO("[+] user_write_what_where: 0x%p\n", user_write_what_where);
    INFO("[+] WRITE_WHAT_WHERE size: 0x%zX\n", sizeof(WRITE_WHAT_WHERE));
    INFO("[+] user_write_what_where->What: 0x%p\n", what);
    INFO("[+] user_write_what_where->Where: 0x%p\n", where);

#ifdef SECURE
    if (!x_access_ok(VERIFY_READ, what, sizeof(void *)) ||
        !x_access_ok(VERIFY_WRITE, where, sizeof(void *)))
    {
        ERR("[-] Invalid parameters");

        status = -EINVAL;
        return status;
    }

#endif

    INFO("[+] Triggering Arbitrary Write\n");

    *((void **) where) = *((void **) what);
    
    return status;
}


int arbitrary_write_ioctl_handler(struct hevd_io *io)
{
    int status = -EINVAL;
    PWRITE_WHAT_WHERE user_write_what_where = NULL;

    user_write_what_where = (PWRITE_WHAT_WHERE)io->input_buffer;

    if (user_write_what_where)
    {
        status = trigger_arbitrary_write(user_write_what_where);
    }

    return status;
}
