ifneq ($(KERNELRELEASE),)

# This part of the Makefile is used when called by the kernel build system
# and defines the modules to be built.

TOP_ANDROID_ASHMEM_MODULES_DIR := $(shell dirname $(lastword $(MAKEFILE_LIST)))

ccflags-y += -I$(TOP_ANDROID_ASHMEM_MODULES_DIR)

obj-m += android-ashmem.o
android-ashmem-objs += ashmem.o deps.o

else # KERNELRELEASE

# This part of the Makefile is used when the 'make' command is runned in the
# base directory of the ashmem-linux sources. It sets some environment and
# calls the kernel build system to build the actual modules.

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all: modules

.PHONY: modules
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) V=1 modules

.PHONY: modules_install
modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

.PHONY: clean
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

endif # KERNELRELEASE
