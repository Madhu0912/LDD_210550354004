#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include"header.h"
struct module_data
{
	int num1;
	int num2;
	char operator;
};
struct module_data data;
int main()
{
	int fd;
	int value;
	fd=open("/dev/ioctl",O_RDWR,0777);
	if(fd<0)
	{
		printf("error opening device\n");
		exit(1);
	}
	printf("operations to perform\n");
	printf("enter (+) operator to addition\n"); 
	printf("enter (-) operator to subtraction\n");
        printf("enter (*) operator to multiplication\n");
        printf("enter (/) operator to division\n");
	
	printf("choose your operator: ");
	scanf("%c",&data.operator);

		      printf("Enter first value :");
    		      scanf("%d",&data.num1);

                      printf("Enter second value :");
                      scanf("%d",&data.num2);
                      printf("writing value to driver\n");

                      ioctl(fd,module,&data);
		      
	close(fd);
	return 0;
}
