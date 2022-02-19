obj-m := kernel_space_adc.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
