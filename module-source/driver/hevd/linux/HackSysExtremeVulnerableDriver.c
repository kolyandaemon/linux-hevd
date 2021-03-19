
#include "HackSysExtremeVulnerableDriver.h"


struct file_operations hevd_fops = {
    .owner = THIS_MODULE,
    .unlocked_ioctl = hevd_ioctl
};


static struct miscdevice hevd_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "HackSysExtremeVulnerableDriver",
    .fops = &hevd_fops
};

static int __init hevd_init(void)
{
    int status = 0;


    status = misc_register(&hevd_device);

    if (status < 0)
    {
        ERR("[-] Error Initializing HackSys Extreme Vulnerable Driver\n");
        return status;
    }

    INFO(BANNER);
    INFO("[+] HackSys Extreme Vulnerable Driver Loaded\n");

    return status;
}

static void __exit hevd_exit(void)
{

    misc_deregister(&hevd_device);

    INFO("[-] HackSys Extreme Vulnerable Driver Unloaded\n");
}

static long hevd_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    int status = -EINVAL;
    void __user *arg_user = (void __user *)arg;

    switch (cmd)
    {
    case HEVD_IOCTL_BUFFER_OVERFLOW_STACK:
        INFO("****** HEVD_IOCTL_BUFFER_OVERFLOW_STACK ******\n");
        status = buffer_overflow_stack_ioctl_handler(arg_user);
        INFO("****** HEVD_IOCTL_BUFFER_OVERFLOW_STACK ******\n");
	break;
    case HEVD_IOCTL_INTEGER_OVERFLOW:
        INFO("****** HEVD_IOCTL_INTEGER_OVERFLOW ******\n");
        status = integer_overflow_ioctl_handler(arg_user);
        INFO("****** HEVD_IOCTL_INTEGER_OVERFLOW ******\n");
        break;
    case HEVD_IOCTL_ARBITRARY_WRITE:
        INFO("****** HEVD_IOCTL_ARBITRARY_WRITE ******\n");
        status = arbitrary_write_ioctl_handler(arg_user);
        INFO("****** HEVD_IOCTL_ARBITRARY_WRITE ******\n");
        break;
    case HEVD_IOCTL_UNINITIALIZED_MEMORY_STACK:
        INFO("****** HEVD_IOCTL_UNINITIALIZED_MEMORY_STACK ******\n");
        status = uninitialized_memory_stack_ioctl_handler(arg_user);
        INFO("****** HEVD_IOCTL_UNINITIALIZED_MEMORY_STACK ******\n");
        break;
    default:
        WARNING("[-] Invalid IOCTL Code: 0x%X\n", cmd);
        status = -ENOIOCTLCMD;
        break;
    }

    return status;
}


module_init(hevd_init);
module_exit(hevd_exit);


MODULE_VERSION("4.0");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ashfaq Ansari (@HackSysTeam)");
MODULE_DESCRIPTION("HackSys Extreme Vulnerable Driver");
