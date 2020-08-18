UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	CC=gcc # define the compiler to use
	TARGET=main # define the name of the executable
	SOURCES=$(wildcard *.c */*.c */*/*.c)
	CFLAGS=-Wshadow -Wall -O2 -g3 -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined -D_GLIBCXX_DEBUG -U_FORTIFY_SOURCE
	LFLAGS=-O2 -lm -g3 -I/usr/local/include -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined -D_GLIBCXX_DEBUG

else
	CC=gcc-10 # define the compiler to use
	TARGET=main # define the name of the executable
	SOURCES=$(wildcard *.c */*.c */*/*.c)
	CFLAGS=-Wshadow -Wall -O2 -g3 -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined -D_GLIBCXX_DEBUG -U_FORTIFY_SOURCE
	LFLAGS=-O2 -lm -g3 -I/usr/local/include -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined -D_GLIBCXX_DEBUG
endif

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
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
