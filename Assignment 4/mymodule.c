/*
 *    hello.c - Simple example Loadable Kernel Module that prints
 *              output to the syslog
 *
 *    
 *
 *    Background: http://tldp.org/HOWTO/Module-HOWTO/x73.html
 */

// Defining __KERNEL__ and MODULE allows us to access kernel-level code not usually available to userspace programs.
#undef __KERNEL__
#define __KERNEL__

#undef MODULE
#define MODULE

// Linux Kernel/LKM headers: module.h is needed by all modules and kernel.h is needed for KERN_INFO.
#include <linux/module.h>	// included for all kernel modules
#include <linux/kernel.h>	// included for KERN_INFO
#include <linux/init.h>		// included for __init and __exit macros


static int __init mymodule_init(void)
{
    printk(KERN_INFO "LOADING module, which was written by krishna\n");
    return 0;	
}

static void __exit mymodule_cleanup(void)
{
    printk(KERN_INFO "UNLOADING module, which was written by krishna\n");
}

module_init(mymodule_init);
module_exit(mymodule_cleanup);

/*
Output:-
krishna@krishna:~/assignment4$ sudo insmod mymodule.ko
krishna@krishna:~/assignment4$ dmesg | grep "was writtern by krishna"
krishna@krishna:~/assignment4$ dmesg | grep "was written by krishna"
[ 1287.278024] LOADING module, which was written by krishna
krishna@krishna:~/assignment4$ sudo lsmod | grep "mymodule"
mymodule               16384  0
krishna@krishna:~/assignment4$ sudo rmmod mymodule
krishna@krishna:~/assignment4$ dmesg | grep "was written by krishna"
[ 1182.435026] LOADING module, which was written by krishna
[ 1240.545109] UNLOADING module, which was written by krishna

*/
