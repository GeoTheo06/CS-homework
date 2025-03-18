CC = gcc

CFLAGS = -O2 -std=c99 -pedantic -Wall -o -lm

scan: tries.c
	$(CC) $(CFLAGS) $^ -o $@

recog: mainRecog.c scanner.c recognizeEq.c
	$(CC) $(CFLAGS) $^ -o $@

eval: scanner.c recognizeEq.c evalEq.c mainEvalEq.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean debug-scan

clean:
	rm -f eval recog scan

debug-scan: scan
	cat input.in | valgrind --track-origins=yes ./scan
