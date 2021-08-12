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
/*ssize_t NAME_write(struct file *filp,const char __user *buff,size_t count,loff_t *offp);
ssize_t NAME_read(struct file *filp,char __user *buff,size_t count,loff_t *offp);*/

struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open  = NAME_open,
//	.read  = NAME_read,
//	.write = NAME_write,
	.release=NAME_release,
};

struct cdev *my_cdev;

static int __init chardevice_init(void)
{
	int result;
	int MAJOR,MINOR;
	dev_t mydev;
	mydev = MKDEV(255,0);
	MAJOR=MAJOR(mydev);
	MINOR=MINOR(mydev);
	printk("the major number is %d and minor number is %d\n",MAJOR,MINOR);
	result=register_chrdev_region(mydev,1,"chardevice");
	if(result<0)
	{
		printk("the region request for is not obtainable\n");
		return(-1);
	}
	my_cdev=cdev_alloc();
	my_cdev->ops=&fops;

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
	dev_t mydev;
	int MAJOR,MINOR;
	mydev=MKDEV(255,0);
	MAJOR=MAJOR(mydev);
	MINOR=MINOR(mydev);
	printk("the major number is %d and minor number is %d\n",MAJOR,MINOR);
	unregister_chrdev_region(mydev,1);
	cdev_del(my_cdev);
	printk("Bye");
	return;
}

int NAME_open(struct inode *inode,struct file *filp)
{
	printk("kernel open call\n");
	return 0;
}
int NAME_release(struct inode *inode,struct file *filp)
{
	printk("kernel release call\n");
	return 0;
}
/*ssize_t NAME_read(struct file *filp,const char __user *buff,size_t count,loff_t *offp)
{
	printk("in kernel read\n");
	return 0;
}
ssize_t NAME_write(struct file *filp,const char __user *buff,size_t count,loff_t *offp)
{
	printk("in kernel write\n");
	return 0;
}*/

module_init(chardevice_init);
module_exit(chardevice_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MADHU");

