all: main

main: array_list.o item.o main.c
	gcc -Wall -o main main.c array_list.o item.o

item.o: item.c
	gcc -Wall -o item.o -c item.c

array_list.o: array_list.c
	gcc -Wall -o array_list.o -c array_list.c

clean:
	rm -f *.o main

run:
	./main
val:
	clear 
	valgrind ./main
