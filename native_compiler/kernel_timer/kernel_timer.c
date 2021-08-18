/*Explore kernel timers. Write a module program that uses the kernel timer and generates 
some output at regular intervals of time*/
#include<linux/init.h>
#include<linux/module.h>
#include<linux/timer.h>

static struct timer_list my_timer;
static void my_timer_callback(struct timer_list *timer)
{
	printk("%s called (%ld)\n",__func__,jiffies);
}
static int __init kernel_init(void)
{
	int ret;
	printk("%s: timer module loaded\n",__func__);
	timer_setup(&my_timer,my_timer_callback,0);
	printk("%s: setup timer to fire in 3sec (%ld)\n",__func__,jiffies);

	ret= mod_timer(&my_timer,jiffies+msecs_to_jiffies(3000));
	if(ret)
		printk("%s: timer firing failed\n",__func__);
	return 0;
}
static void __exit kernel_exit(void)
{
	int ret;
	ret=del_timer(&my_timer);
	if(ret)
		printk("%s:timer is still is use \n",__func__);
	printk("%s:timer unloaded\n",__func__);
	printk("Bye");
}

module_init(kernel_init);
module_exit(kernel_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("MADHU");
MODULE_DESCRIPTION("KERNEL TIMER");
