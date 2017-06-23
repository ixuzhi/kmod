CUR = $(shell uname -r)
PWD = $(shell pwd)

ifneq ($(KERNELRELEASE),)
obj-m := timedelay.o
else
KDIR := /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *.ko *.o *.mod.o modules.order  Module.symvers *.mod.c .*.cmd .tmp_versions

in:
	insmod timedelay.ko
out:
	rmmod timedelay
endif

.PHONY:all clean
