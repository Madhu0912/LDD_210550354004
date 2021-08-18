#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdlib.h>
int main()
{
	int fd;
	int num[2];
	int sub;
	printf("enter one number :");
	scanf("%d",&num[0]);
	printf("enter another number:");
	scanf("%d",&num[1]);
	fd=open("/dev/SubDev",O_RDWR,0777);
	if(fd<0)
	{
		printf("error opening device\n");
		exit(1);
	}
	write(fd,num,sizeof(num));
	read(fd,&sub,sizeof(sub));
	printf("subtraction of two numbers is :%d\n",(int)sub);
	close(fd);
	return 0;
}
