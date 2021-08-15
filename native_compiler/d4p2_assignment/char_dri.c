/*Write a character driver with open, read, write and close functionalities. Test the driver through a user application by reading data from the driver and writing data to the driver*/
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>

#define NAME chardevice

int NAME_open(struct inode *inode,struct file *filp);
int NAME_release(struct inode *inode,struct file *filp);
ssize_t NAME_write(struct file *filp,const char __user *ubuff,size_t count,loff_t *offp);
ssize_t NAME_read(struct file *filp,char __user *ubuff,size_t count,loff_t *offp);

struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open  = NAME_open,
	.read  = NAME_read,
	.write = NAME_write,
	.release=NAME_release,
};
dev_t mydev;
struct cdev *my_cdev;

static int __init chardevice_init(void)
{
	int result;
	int MAJOR,MINOR;
	mydev = MKDEV(255,0);
	MAJOR=MAJOR(mydev);
	MINOR=MINOR(mydev);
	printk("the major number is %d and minor number is %d\n",MAJOR,MINOR);
	result=register_chrdev_region(mydev,1,"chardevice");//static allocation of device number
	if(result<0)
	{
		printk("the region request for is not obtainable\n");
		return(-1);
	}
	my_cdev=cdev_alloc();//allocate memory to char device
	my_cdev->ops=&fops;//link file operation to the char device

	result=cdev_add(my_cdev,mydev,1);
	if(result<0)
	{
		printk("the char device has not been created\n");
		unregister_chrdev_region(mydev,1);
		return(-1);
	}
	return 0;

}

static void __exit chardevice_exit(void)
{
	unregister_chrdev_region(mydev,1);//unregister dedevice number
	cdev_del(my_cdev);
	printk("Bye");
	return;
}
//open system call
int NAME_open(struct inode *inode,struct file *filp)
{
	printk("kernel open call\n");
	return 0;
}
//close system call
int NAME_release(struct inode *inode,struct file *filp)
{
	printk("kernel close and Bye\n");
	return 0;
}
//read functionality
ssize_t NAME_read(struct file *filp,char __user *ubuff,size_t count,loff_t *offp)
{
	char kbuff[50]="hello world";
	unsigned long result;
	ssize_t retval;
	result=copy_to_user((char *)ubuff,(char *)kbuff,count);
	if(result==0)
	{
		printk("data successful read.\n");
		retval=count;
		return retval;
	}
	else if(result>0)
	{
		retval=(count-result);
		return retval;
	}
	else 
	{
		printk("error writing data.\n");
		retval=-EFAULT;
		return retval;
	}
}
//write functionality
ssize_t NAME_write(struct file *filp,const char __user *ubuff,size_t count,loff_t *offp)
{
	char kbuff[100];
	unsigned long result;
	ssize_t retval;
	result=copy_from_user((char *)kbuff,(char *)ubuff,count);
	if(result==0)
	{
		printk("received from user : %s\n",kbuff);
		retval=count;
		return retval;
	}
	else if(result>0)
	{
		printk("received from user : %s\n",kbuff);
		retval=(count-result);
		return retval;
	}
	else
	{
		printk("error in writing data.\n");
		retval=-EFAULT;
		return retval;
	}
}

module_init(chardevice_init);
module_exit(chardevice_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MADHU");

