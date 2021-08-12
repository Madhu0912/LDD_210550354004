#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	int fd;
	char ubuff[]="this is user buffer  sending to kernel";
	char kbuff[100];
	fd=open("/dev/chardevice",O_RDWR,0777);
	if(fd<0)
	{
		printf("error opening device\n");
		exit(1);
	}
	close(fd);
}
