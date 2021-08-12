#include<linux/init.h>
#include<linux/module.h>
#include "header.h"

static int add_init(void)
{
	printk("hello\n");
	return 0;
}

static int add(int a,int b)
{
	return (a+b);
}

EXPORT_SYMBOL_GPL(add);

static void add_exit(void)
{
	printk("bye\n");
}

module_init(add_init);
module_exit(add_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MADHU");

