#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
static int add(int ,int );

static char* charvar="module";  //mdoule parameters
static int intvar1=10;
static int intvar2=20;
//module parameter macros
module_param(charvar,charp,S_IRUGO);
module_param(intvar1,int,S_IRUGO);
module_param(intvar2,int,S_IRUGO);

static int add(int a,int b)
{
	return (a+b);
}
//module init function
static int param_init(void)
{
	printk("Hello world.\n");
	printk("charvar is %s\n",charvar);
	printk("intvar1 is %d\n",intvar1);
	printk("intvar2 is %d\n",intvar2);
	printk("addition of two numbers is %d\n",add(intvar1,intvar2));
	return 0;
}
//module exit function
static void param_exit(void)
{
	printk(KERN_ALERT"Bye.\n");
}

module_init(param_init);
module_exit(param_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MADHU");
