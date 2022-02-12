CC = gcc
TARGET = client

CFLAGS = -c -g -O2 -Wall 
C_SRCS = $(wildcard ./*.c) 
O_SRCS = $(C_SRCS:.c=.o)

main : $(C_SRCS)
	$(CC) $(CFLAGS) $(C_SRCS) -lpthread

all : $(O_SRCS)
	$(CC) -o $(TARGET) $(O_SRCS) -lpthread

run:
	make clean
	make all
	./client

PHONY: clean
clean:
	rm -rf $(O_SRCS) $(TARGET)