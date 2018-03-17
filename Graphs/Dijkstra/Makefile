all: 
	gcc -std=c99 Item.c HeapEstatica.c grafo.c main.c -o main
run:
	./main

teste: clear comp exec
clear:
	clear
comp:
	gcc -std=c99 Item.c HeapEstatica.c grafo.c main.c -o  main 
exec:
	valgrind ./main <in.txt