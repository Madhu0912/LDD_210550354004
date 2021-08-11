obj-m:=char_drivers.o
KDIR=/lib/modules/$(shell uname -r)/build/
PWD=$(shell pwd)
all:
	make -C $(KDIR) M=$(PWD) modules
	gcc -o app application.c

clean:
	make -C $(KDIR) M=$(PWD) clean
	rm -rf app
