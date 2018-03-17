all: matrizEsparsa.o main.o
	gcc main.o matrizEsparsa.o -o main
matrizEsparsa.o: matrizEsparsa.c
	gcc -c matrizEsparsa.c -Wall
main.o: main.c
	gcc -c main.c -Wall
clean:
	rm -f *.o main
run:
	./main
val:
	clear 
	valgrind ./main