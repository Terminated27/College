CC=gcc
CFLAGS=-lpthread -I.

test: temperature.c
	$(CC) -o test temperature.c $(CFLAGS) 

.PHONY: clean
clean:
	rm -f test
