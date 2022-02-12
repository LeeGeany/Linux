CC = gcc
TARGET = main

CFLAGS = -c -g -O2 -Wall
C_SRCS = $(wildcard ./*.c) 
O_SRCS = $(C_SRCS:.c=.o)

main : $(C_SRCS)
	$(CC) $(CFLAGS) $(C_SRCS)

all : $(O_SRCS)
	$(CC) -o $(TARGET) $(O_SRCS)

run:
	make clean
	make all
	./main

PHONY: clean
clean:
	rm -rf $(O_SRCS) $(TARGET)
