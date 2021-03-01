MODULES = ../HashTable/module
MODULES1 = module
MODULES2 = list_module

CFLAGS = -g -Wall -I.

PROGRAM = graph

# List object files needed to compile the program.
OBJS = main.o

# We use the list module, include its make.inc so that it can configure itself
include $(MODULES1)/make.inc
include $(MODULES)/make.inc

$(PROGRAM): clean $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM) -lm

clean:
	rm -f $(PROGRAM) $(OBJS)

run: $(PROGRAM)
	./$(PROGRAM)

