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
	int div;
	printf("enter one numbers :");
	scanf("%d",&num[0]);
	printf("enter another number :");
	scanf("%d",&num[1]);
	fd=open("/dev/DivDev",O_RDWR,0777);
	if(fd<0)
	{
		printf("error opening device\n");
		exit(1);
	}
	write(fd,num,sizeof(num));
	read(fd,&div,sizeof(div));
	printf("division of two numbers is :%d\n",(int)div);
	close(fd);
	return 0;
}
