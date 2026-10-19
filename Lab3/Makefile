CC = gcc
CFLAGS = -Wall -Wextra -I.
parser.exe: main.o build_tree.o
	$(CC) -o $@ main.o build_tree.o
main.o: main.c build_tree.h
	$(CC) $(CFLAGS) -c main.c

build_tree.o: build_tree.c build_tree.h
	$(CC) $(CFLAGS) -c build_tree.c
