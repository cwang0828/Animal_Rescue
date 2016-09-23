#makefile
HW5: Driver.o AnimalADT.o
	gcc -o rescuebin Driver.o AnimalADT.o

Driver.o: Driver.c
	gcc -c Driver.c

AnimalADT.o: AnimalADT.c AnimalADT.h
	gcc -c AnimalADT.c
