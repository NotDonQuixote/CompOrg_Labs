CC = gcc
CFLAGS = -Wall -Wextra -I.
parser.exe: main.o build_tree.o backend.o
	$(CC) -o $@ main.o build_tree.o backend.o
main.o: main.c build_tree.h backend.h
	$(CC) $(CFLAGS) -c main.c

build_tree.o: build_tree.c build_tree.h
	$(CC) $(CFLAGS) -c build_tree.c

backend.o: backend.c backend.h build_tree.h
	$(CC) $(CFLAGS) -c backend.c