all: vector.o item.o main.c
	gcc -o main main.c vector.o item.o

item.o: item.c
	gcc -o item.o -c item.c

vector.o: vector.c
	gcc -o vector.o -c vector.c

clean:
	rm -f *.o main

run:
	./main
