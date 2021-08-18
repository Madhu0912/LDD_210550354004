/*Write a calculator driver in the kernel which performs the following 
*Create 4 Device Numbers – Each device number depicts a specific calculation operation like add, subtract, multiply and divide
*Implement 8 methods – Read_Add, Read_Sub, Read_Mul, Read_Div, Write_Add, Write_Sub, Write_Mul and Write_Div
*In user space, create 4 device nodes for the 4 device numbers created – /dev/AddDev, /dev/SubDev, /dev/MulDev, /dev/DivDev
*Write 4 user applications in the user space to test the above. If /dev/AddDev application is run, it should write 2 numbers to the kernel and the kernel should add it and return the sum in the subsequent read*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>


/*function declaration of add functionality*/
int open_add(struct inode *inode, struct file *file_op_add);
int release_add(struct inode *inode, struct file *file_op_add);
ssize_t write_add(struct file *file_op_add,const char __user *ubuff,size_t count,loff_t *offp );
ssize_t read_add(struct file *file_op_add,char __user *ubuff, size_t count, loff_t *offp);

static int sum; // for storing the result of addition
/*add operation structure*/
struct file_operations fop_add=
{
	.owner = THIS_MODULE,
	.open = open_add,
	.read = read_add,
	.write = write_add,
	.release = release_add,
};

/*add open function defination*/
int open_add(struct inode *inode, struct file *file_op_add)
{
	printk("AddDev is using MyCalDriver\n");
	return 0;
}

/*add read function defination that read the user data*/
ssize_t read_add(struct file *file_op_add,char __user *ubuff,size_t count,loff_t *offp)
{
	ssize_t retval;
	int result;
	const int *re  = &sum;
	result = copy_to_user(ubuff,re,sizeof(sum)); // the result of addition com=py from kernel space to user
	if(result >= 0) // condition to check whether copy operation successful or not
	{
		printk("successfully send the result\n");
		retval = sizeof(sum);
		return retval;
	}
	else
	{
		printk("sending data not done\n");
		return -1;
	}
}

/*adition write function defination*/
ssize_t write_add(struct file *file_op_add, const char __user *ubuff, size_t count, loff_t *offp)
{
	int result;
	int kbuff[2]; //initialize variable to where two integers from user space will store
	ssize_t retval;
	result = copy_from_user((char *)kbuff,ubuff,count); // copy from user
	if(result >= 0) // condition for checking whether copy from user done or not
	{
		printk("the data from user are:%d and %d\n",(int)kbuff[0],(int)kbuff[1]); // print the two integer value 
		//collecting from user withinteger type cast
		sum = (int)kbuff[0] + (int)kbuff[1]; 
		printk("the addition result is: %d and its send to user space\n",sum);
		retval = count;
		return retval; //send the amount of data cpoied
	}
	else
	{
		printk("not able to read from user\n");
		return -1;
	}
}

/*add release function defination*/
int release_add(struct inode *inode, struct file *file_op_add)
{
	printk("AddDev is logging off from MyCalDriver\n");
	return 0;
}

/*sub operation function declaration*/
int open_sub(struct inode *inode, struct file *file_op_sub);
int release_sub(struct inode *inode, struct file *file_op_sub);
ssize_t write_sub(struct file *file_op_sub,const char __user *ubuff,size_t count, loff_t *offp);
ssize_t read_sub(struct file *file_op_sub, char __user *ubuff, size_t count, loff_t *offp);

static int sub_result;
/*sub operation structure*/
struct file_operations fop_sub=
{
	.owner = THIS_MODULE,
	.open = open_sub,
	.read = read_sub,
	.write = write_sub,
	.release = release_sub,
};

/*sub open function defination*/
int open_sub(struct inode *inode, struct file *file_op_sub)
{
	printk("SubDev is using MyCalDriver\n");
	return 0;
}

/*subtraction write function defination*/
ssize_t write_sub(struct file *file_op_sub, const char __user *ubuff, size_t count,loff_t *offp)
{
	int result;
	int kbuff[2];
	ssize_t retval;
	result = copy_from_user((char *)kbuff, ubuff, count);
	if(result >= 0)
	{
		printk("data successfully received from user asr: %d and %d\n",(int)kbuff[0],(int)kbuff[1]);
		sub_result = (int)kbuff[0] - (int)kbuff[1];
		printk("the result of subtraction is: %d and the result now send to the user\n",sub_result);
		retval = count;
		return retval;
	}
	else
	{
		printk("data received not done successfully\n");
		return -1;
	}
}

/*sub read function defination*/
ssize_t read_sub(struct file *file_op_sub, char __user *ubuff, size_t count, loff_t *offp)
{
	int result;
	ssize_t retval;
	result = copy_to_user(ubuff,&sub_result,sizeof(sub_result));
	if (result >=0)
	{
		printk("The result successfully send to the user\n");
		retval = sizeof(sub_result);
		return retval;
	}
	else
	{
		printk("the send not done");
		return -1;
	}
}


/*sub release function defination*/
int release_sub(struct inode *inode, struct file *file_op_sub)
{
	printk("SubDev is logging of from MyCalDriver\n");
	return 0;
}

/*multiplication function declaration*/
int open_mul(struct inode *inode,struct file *file_op_mul);
int release_mul(struct inode *inode, struct file *file_op_mul);
ssize_t write_mul(struct file *file_op_mul, const char __user *ubuff,size_t count,loff_t *offp);
ssize_t read_mul(struct file *file_op_mul,char __user *ubuff,size_t count, loff_t *offp);

static int mul_result;

/*file operation for multiplicatio*/
struct file_operations fop_mul=
{
	.owner = THIS_MODULE,
	.open = open_mul,
	.read = read_mul,
	.write = write_mul,
	.release = release_mul,
};

/*open multiplication function defination*/
int open_mul(struct inode *inode, struct file *file_op_mul)
{
	printk("you have oprn the multiplication section\n");
	return 0;
}

/*multiplication write function defination*/
ssize_t write_mul(struct file *file_op_mul,const char __user *ubuff,size_t count, loff_t *offp)
{
	int result;
	int kbuff[2];
	ssize_t retval;
	result = copy_from_user((char *)kbuff,ubuff,count);
	if(result >= 0)
	{
		printk("the data from user get successfully\n");
		printk("the data from user: %d and %d\n",(int)kbuff[0],(int)kbuff[1]);
		mul_result = (int)kbuff[0] * (int)kbuff[1];
		printk("the result of multiplication: %d and send to user\n",mul_result);
		retval = count;
		return retval;
	}
	else
	{
		printk("error in writing data from user\n");
		return -1;
	}
}

/*multiplication read function defination*/
ssize_t read_mul(struct file *file_op_mul,char __user *ubuff,size_t count,loff_t *offp)
{
	int result;
	ssize_t retval;
	result = copy_to_user(ubuff,&mul_result,sizeof(mul_result));
	if(result >= 0)
	{
		printk("the send successfully done\n");
		retval = sizeof(mul_result);
		return retval;
	}
	else
	{
		printk("The send operation not done successfully\n");
		return -1;
	}
}

/*release multiplication function defination*/
int release_mul(struct inode *inode,struct file *file_op_mul)
{
	printk("Multiplication operation end\n");
	return 0;
}

/*division function declaration*/
int open_div(struct inode *inode,struct file *file_op_div);
int release_div(struct inode *inode,struct file *file_op_div);
ssize_t write_div(struct file *file_op_div, const char __user *ubuff,size_t count,loff_t *offp);
ssize_t read_div(struct file *file_op_div, char __user *ubuff, size_t count, loff_t *offp);

static int div_result;

/*file operation structure for division*/
struct file_operations fop_div=
{
	.owner = THIS_MODULE,
	.open = open_div,
	.read = read_div,
	.write = write_div,
	.release = release_mul,
};

/*open operation for division*/
int open_div(struct inode *inode,struct file *file_op_div)
{
	printk("you are in division module section\n");
	return 0;
}

/*write division operation*/
ssize_t write_div(struct file *file_op_div, const char __user *ubuff,size_t count, loff_t *offp)
{
	int kbuff[2];
	int result;
	ssize_t retval;
	result = copy_from_user((char *)kbuff,ubuff,count);
	if(result >= 0)
	{
		printk("data received from user done and data are: %d and %d\n",(int)kbuff[0],(int)kbuff[1]);
		div_result = (int)kbuff[0]/(int)kbuff[1];
		printk("the division result is: %d and now send to user",div_result);
		retval = count;
		return retval;
	}
	else
	{
		printk("data read not done successfully\n");
		return -1;
	}
}

/*dividion read operation*/
ssize_t read_div(struct file *file_op_div,char __user *ubuff, size_t count,loff_t *offp)
{
	int result;
	ssize_t retval;
	result = copy_to_user(ubuff,&div_result,sizeof(div_result));
	if(result >= 0)
	{
		printk("data send to user done\n");
		retval = sizeof(div_result);
		return retval;
	}
	else
	{
		printk("data send not done successfully\n");
		return -1;
	}
}

/*division release operation*/
int release_div(struct inode *inode,struct file *file_op_div)
{
	printk("logging off fron division module\n");
	return 0;
}

//four character devices initializations
struct cdev *AddDev;
struct cdev *SubDev;
struct cdev *MulDev;
struct cdev *DivDev;
//device number variable initialization
dev_t mydev;
dev_t mydev_add;
dev_t mydev_sub;
dev_t mydev_mul;
dev_t mydev_div;
//module initialization
static int __init calculator_init(void) 
{
	int result;
	int major;
	int result_add,result_sub,result_mul,result_div;

	result = alloc_chrdev_region(&mydev, 0,4,"MyCalDriver"); // dynamically allocate device number having four indexes

	if (result < 0) // if not success
	{
		printk(KERN_ALERT "not successfully allocated region\n");
		return 0;
	}

	major = MAJOR(mydev); // finding the major number
	printk("the allocated driver having the major number: %d\n\nminor no 0: for AddDev device\nminor no 1: for SubDev device\nminor no 2: for MulDev device\nminor no 3: for DivDev device\n",major);
	
	printk("\nFor calculation purpose deiver expected the following device with its major and minor number:\naddition: AddDev\nsubtraction: SubDev\nmultiplication: MulDev\ndivision: DivDev\n");
	/*making separate device number with same major number*/
	mydev_add = MKDEV(major,0);
	mydev_sub = MKDEV(major,1);
	mydev_mul = MKDEV(major,2);
	mydev_div = MKDEV(major,3);

	AddDev = cdev_alloc(); //dynamically allocate AddDev as character driver so that kernel know about it
	AddDev->ops = &fop_add;// pointing the function pointer
	
	SubDev = cdev_alloc();
	SubDev->ops = &fop_sub;

	MulDev = cdev_alloc();
	MulDev->ops = &fop_mul;

	DivDev = cdev_alloc();
	DivDev->ops = &fop_div;
	
	result_add = cdev_add(AddDev,mydev_add,1); // add AddDev device to the kernel section
	if(result_add <0 ) // condition whether addition of device successfull or not
	{
		printk(KERN_ALERT "driver not allocated by kernel\n");
		return -1;
	}

	result_sub = cdev_add(SubDev,mydev_sub,1);
	if(result_sub <0)
	{
		printk(KERN_ALERT "driver not allocated by kernel\n");
		return -1;
	}

	result_mul = cdev_add(MulDev,mydev_mul,1);
	if(result_mul <0)
	{
		printk(KERN_ALERT "driver not allocated by kernel\n");
		return -1;
	}

	result_div = cdev_add(DivDev,mydev_div,1);
	if(result_div <0)
	{
		printk(KERN_ALERT "driver not allocated by kernel\n");
		return -1;
	}

	return 0;
}
//module exit
static void __exit calculator_exit(void)
{
	/*delete each device location separately*/
	cdev_del(AddDev);
	cdev_del(SubDev);
	cdev_del(MulDev);
	cdev_del(DivDev);
	printk("all devices are logging off\n");
	/*unregister from the kernel space*/
	unregister_chrdev_region(mydev, 4);
	printk("Bye\n");
}

module_init(calculator_init);
module_exit(calculator_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MADHU");
