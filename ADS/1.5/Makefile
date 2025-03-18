CC = gcc

CFLAGS = -g -O2 -std=c99 -pedantic -Wall -lm

ex1.5: itemAtPosIt.c LibList.c makeList.c printList.c main.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean debug-scan

clean:
	rm -f ex1.5

debug-ex1.5: ex1.5
	cat ../@tests/1.in | valgrind ./ex1.5
