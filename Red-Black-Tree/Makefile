CFLAGS = -Wall

all: main

main: rbtree.o item.o main.c
	gcc $(CFLAGS) main.c item.o rbtree.o -o main

rbtree.o: rbtree.c
	gcc $(CFLAGS) -c rbtree.c -o rbtree.o

item.o:
	gcc $(CFLAGS) -c item.c -o item.o

clean:
	rm -f *.o main

run:
	./main

.PHONY: clean run
