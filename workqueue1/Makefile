CUR = $(shell uname -r)
PWD = $(shell pwd)

ifneq ($(KERNELRELEASE),)
obj-m := mod.o
else
KDIR := /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *.ko *.o *.mod.o modules.order  Module.symvers *.mod.c .*.cmd .tmp_versions

in:
	insmod mod.ko
out:
	rmmod mod
endif

.PHONY:all clean
