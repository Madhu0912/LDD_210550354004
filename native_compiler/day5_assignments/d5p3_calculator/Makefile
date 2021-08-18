obj-m:=calculator_kern.o
KDIR=/lib/modules/$(shell uname -r)/build/
PWD=$(shell pwd)
all:
	make -C $(KDIR) M=$(PWD) modules
	gcc -o app_add app_add.c
	gcc -o app_sub app_sub.c
	gcc -o app_mul app_mul.c
	gcc -o app_div app_div.c

clean:
	make -C $(KDIR) M=$(PWD) clean
	rm -rf app_add app_sub app_mul app_div 
