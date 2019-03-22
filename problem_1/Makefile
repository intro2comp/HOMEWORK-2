CC = gcc
CFLAGS = -std=c99 -g -Wall -Wextra -Wpedantic
LDFLAGS = -lm -lpthread


all: primes

clean:
	rm -vf primes

primes: primes.c
	$(CC) $(CFLAGS) -o primes primes.c $(LDFLAGS)

