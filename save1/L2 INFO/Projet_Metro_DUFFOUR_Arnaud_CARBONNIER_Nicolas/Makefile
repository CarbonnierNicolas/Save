#DUFOUR Arnaud 21505093
#CARBONNIER Nicolas 21404875
compil : clean metro

metro : metro.o terminus.o trajet.o chemin.o
	gcc -o metro -g metro.o terminus.o trajet.o chemin.o
	
metro.o : metro.c
	gcc	-c -g metro.c 
		
terminus.o : terminus.c terminus.h
	gcc -c -g terminus.c
	
trajet.o : trajet.c trajet.h
	gcc -c -g trajet.c
	
chemin.o : chemin.c chemin.h
	gcc -c -g chemin.c

clean :
	rm -f metro
	rm -f metro.o
	rm -f terminus.o
	rm -f trajet.o
	rm -f chemin.o
