all:cesar
	./cesar
cesar.o:cesar.c
	gcc -c -Wall cesar.c -lpthread
cesar:cesar.o 
	gcc -o cesar cesar.o -lpthread
clean:
	rm -f cesar.o
	rm -f cesar
test:clean cesar
	./cesar cesar.txt 
