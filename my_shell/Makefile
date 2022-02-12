CC = gcc
CFLAGS = -Wall -O2
OBJS = history.o input.o my_shell.o

history.o : history.h history.c
	$(CC) $(CFLAGS) -c history.c

input.o : input.h input.c
	$(CC) $(CFLAGS) -c input.c

my_shell.o : header.h history.h input.h history.c input.c
	$(CC) $(CFLAGS) -c my_shell.c

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o my_shell 

PHONY: clean
clean: 
	rm -f $(OBJS) my_shell