CC = gcc
CFLAGS = -Wall -Wextra -I.
OBJS = main.o build_tree.o backend.o

compile: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

main.o: main.c build_tree.h backend.h
	$(CC) $(CFLAGS) -c main.c

build_tree.o: build_tree.c build_tree.h backend.h
	$(CC) $(CFLAGS) -c build_tree.c

backend.o: backend.c backend.h build_tree.h
	$(CC) $(CFLAGS) -c backend.c