/*Write a module program and pass 2 integer type parameters and 1 string type module parameters to it. If the string type parameter is add, the module should call a function add() and calculate the sum of the 2 integer type parameters. Similarly, sub, mul and div should be implemented through separate handler functions and perform respective operations */
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include"header.h"
static char* charvar="module";  //mdoule parameters
static int a=10;
static int b=20;
//module parameter macros
module_param(charvar,charp,S_IRUGO);
module_param(a,int,S_IRUGO);
module_param(b,int,S_IRUGO);

static int add(int a,int b)	//addition function
{
	return (a+b);
}

static int mul(int a,int b)	//multiplication function
{
	return (a*b);
}
static int div(int a,int b)	//division function
{
	return (a/b);
}
static int diff(int a,int b)	//difference function
{
	return (a-b);
}
//module init function
static int param_init(void)
{
	printk("Hello world.\n");
	printk("charvar is %s\n",charvar);
	printk("intvar1 is %d\n",a);
	printk("intvar2 is %d\n",b);

	if(strcmp(charvar,"add")==0)
	{
		printk("addition of two numbers is:%d\n",add(a,b));
	}
	else if(strcmp(charvar,"mul")==0)
        {
                printk("multiplication of two numbers is:%d\n",mul(a,b));
        }
	else if(strcmp(charvar,"div")==0)
        {
                printk("division of two numbers is:%d\n",div(a,b));
        }
	else if(strcmp(charvar,"diff")==0)
        {
                printk("difference of two numbers is:%d\n",diff(a,b));
        }
	else
	{
		printk("invalid string.\n");
	}

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
