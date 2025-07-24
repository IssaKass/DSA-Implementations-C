CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: run

run: main.c vector/vector.c
	$(CC) $(CFLAGS) main.c vector/vector.c -o run

clean:
	rm -f run