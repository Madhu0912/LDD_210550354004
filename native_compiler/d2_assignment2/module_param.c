#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

static char* charvar="module";
static int intvar=10;

module_param(charvar,charp,S_IRUGO);
module_param(intvar,int,S_IRUGO);

static int param_init(void)
{
	printk(KERN_ALERT"Hello world.\n");
	printk(KERN_ALERT"charvar is %s\n",charvar);

	printk(KERN_ALERT"intvar is %d\n",intvar);
	return 0;
}
static void param_exit(void)
{
	printk(KERN_ALERT"Bye.\n");
}

module_init(param_init);
module_exit(param_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MADHU");
