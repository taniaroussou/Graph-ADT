
#MODULES3 = ../list_module

CFLAGS += -I$(MODULES1)

OBJS += $(MODULES1)/GraphImplementation.o

include $(MODULES2)/make.inc
