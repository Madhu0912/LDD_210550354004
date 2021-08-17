/*Write a character driver with open, read, write and close functionalities. Test the driver through a user application by reading data from the driver and writing data to the driver*/
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/ioctl.h>
#include"header.h"

#define NAME chardevice
int a=0,b=0,value=0;
int oper=0;
int NAME_open(struct inode *inode,struct file *filp);
long NAME_ioctl(struct file *filp,unsigned int cmd,unsigned long arg);
int NAME_release(struct inode *inode,struct file *filp);
//file operations
struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = NAME_open,
	.unlocked_ioctl=NAME_ioctl,
	.release = NAME_release,
};
dev_t mydev;
//structure for char driver
struct cdev *my_cdev;
//module init function
static int __init ioctl_init(void)
{
	int result;
	int MAJOR,MINOR;
	result=alloc_chrdev_region(&mydev,0,1,"chardevice");//dynamic register region
	MAJOR=MAJOR(mydev);
	MINOR=MINOR(mydev);
	printk("the major number is : %d and minor number is %d\n",MAJOR,MINOR);
	if(result<0)
	{
		printk("the region request for is not obtainable\n");
		return(-1);
	}
	my_cdev=cdev_alloc();//allocate memory for char structure
	my_cdev->ops=&fops;//link file operations to the char device

	result=cdev_add(my_cdev,mydev,1);
	if(result<0)
	{
		printk("the char device has not been created\n");
		unregister_chrdev_region(mydev,1);
		return(-1);
	}
	return 0;

}
//module exit function
static void __exit ioctl_exit(void)
{
	unregister_chrdev_region(mydev,1);
	cdev_del(my_cdev);
	printk("Bye");
	return;
}
//open system call 
int NAME_open(struct inode *ionde,struct file *filp)
{
	printk("open system call\n");
	return 0;
}
//ioctl function
long NAME_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
	switch(cmd)
	{
		case OPERATOR:copy_from_user(&oper,(char *)arg,sizeof(oper));
				printk("oper=%c\n",oper);
			 	break;
		case number1:copy_from_user(&a,(int *)arg,sizeof(a));
			     printk("a=%d\n",a);
			     break;
		case number2:copy_from_user(&b,(int *)arg,sizeof(b));
			     printk("b=%d\n",b);
			     break;
		case RD_DATA: if(oper=='+')
			       {
				       value=a+b;
				       printk("addition of two numbers is :%d\n",value);
			       }
			       else if(oper=='-')
			       {
				       value=a-b;
					printk("subtraction of two numbers is :%d\n",value);
			       }
			       else if(oper=='*')
			       {
				       value=a*b;
					printk("multiplication of two numbers is :%d\n",value);
			       }
			       else if(oper=='/')
			       {
				       value=a/b;
					printk("division of two numbers is :%d\n",value);
			       }
			       else
				       break;
			       copy_to_user((int *)arg,&value,sizeof(value));
			       break;
	}
	return 0;
}
//close system call
int NAME_release(struct inode *inode,struct file *filp)
{
	printk("close and bye\n");
	return 0;
}
module_init(ioctl_init);
module_exit(ioctl_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MADHU");

