#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

int init_module(void)
{
	printk(KERN_INFO "Group Members:\n1- Ouldouz Neysari\n2- Ali Padyav\n3- Kasra Haji Heydari\n");
	return 0;
}

void cleanup_module(void) {}

