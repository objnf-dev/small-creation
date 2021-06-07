obj-m = module1.o

KDIR:= /lib/modules/$(shell uname -r)/build
PWD:= $(shell pwd) 

CONFIG_MODULE_SIG = n


default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
