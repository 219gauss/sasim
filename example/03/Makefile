##
# file : Makefile  
# owner: wuchengbing
# data : 20190125 
##

obj-m += raw-chain-notifier.o            # geneate modules ko file 
CURRENT_PATH := $(shell pwd)             # current core path
LINUX_KERNEL := $(shell uname -r)        # kernel version

# kernel core path
LINUX_KERNEL_PATH := /usr/src/linux-headers-$(LINUX_KERNEL)

# make or make all
all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules

# make clean
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean



