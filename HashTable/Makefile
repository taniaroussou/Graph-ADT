MODULES = module

CFLAGS = -g -Wall -I.

PROGRAM = hash_table

# List object files needed to compile the program.
OBJS = main.o

# We use the list module, include its make.inc so that it can configure itself
include $(MODULES)/make.inc


$(PROGRAM): clean $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM) -lm

clean:
	rm -f $(PROGRAM) $(OBJS)

run: $(PROGRAM)
	./$(PROGRAM)

