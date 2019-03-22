CC = gcc
CFLAGS = -std=c99 -g -Wall -Wextra -Wpedantic
LDFLAGS = -lpthread


all: fib

clean:
	rm -vf fib

fib: fib.c
	$(CC) $(CFLAGS) -o fib fib.c $(LDFLAGS)

