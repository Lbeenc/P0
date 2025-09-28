
CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -O2
OBJS=P0.o tree.o

all: P0

P0: $(OBJS)
	$(CC) $(CFLAGS) -o P0 $(OBJS)

P0.o: P0.c tree.h node.h
	$(CC) $(CFLAGS) -c P0.c

tree.o: tree.c tree.h node.h
	$(CC) $(CFLAGS) -c tree.c

clean:
	rm -f $(OBJS) P0 out.preorder out.inorder out.postorder
