CC=gcc # define the compiler to use
TARGET=main # define the name of the executable
SOURCES=$(wildcard *.c */*.c */*/*.c)
CFLAGS=
LFLAGS=-lm

#gdb main

################################################################################
### DO NOT EDIT THE FOLLOWING LINES ############################################

# define list of objects
OBJS=$(SOURCES:.c=.o)

# the target is obtained linking all .o files
all: $(SOURCES) $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)
