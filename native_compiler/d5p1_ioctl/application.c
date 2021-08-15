#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	int fd;
	char ubuff[]="hello world";
	char kbuff[100];
	fd=open("/dev/chardevice",O_RDWR,0777);
	if(fd<0)
	{
		printf("error opening device\n");
		exit(1);
	}
	write(fd,ubuff,sizeof(ubuff));
	read(fd,kbuff,50);
	printf("the data read from the kernel is :%s\n",kbuff);
	close(fd);
}
