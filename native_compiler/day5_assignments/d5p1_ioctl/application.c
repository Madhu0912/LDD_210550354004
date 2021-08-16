#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include"header.h"
int main()
{
	int operator;
	int fd;
	int num1,num2,value;
	fd=open("/dev/ioctl",O_RDWR,0777);
	if(fd<0)
	{
		printf("error opening device\n");
		exit(1);
	}
	printf("operations to perform\n");
	printf("enter (+) operator to addtion\n");
	printf("enter (-) operator to subtraction\n");
	printf("enter (*) operator to multiplication\n");
	printf("enter (/) operator to division\n");
	printf("enter 0 to exit while loop\n");
	
	printf("choose your operator: ");
	scanf("%c",&operator);

  		      ioctl(fd,OPERATOR,(char *)&operator);
		      printf("Enter first value :");
    		      scanf("%d",&num1);

                      printf("Enter second value :");
                      scanf("%d",&num2);
                      printf("writing value to driver\n");

                      ioctl(fd,number1,(int *) &num1);
                      ioctl(fd,number2,(int *) &num2);

                      printf("Reading value from driver \n");
                      ioctl(fd,RD_DATA,(int *)&value);
                      printf("value is:%d\n",value);
		      
	close(fd);
	return 0;
}
