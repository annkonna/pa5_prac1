CC = gcc
CFLAGS = -g -O2 -Wall -Werror -pthread -std=c99 -D_DEFAULT_SOURCE
LDFLAGS = -pthread

barrier: barrier.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm barrier

.PHONY: barrier
