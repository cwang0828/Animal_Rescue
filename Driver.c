#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "AnimalADT.h"

#define NUM_IDS 10

/**
    Name: Hsin-Jung Wang (Cindy)
    TCSS 333 
    Assignment: #5
    NetID: 1260340
*/

int main(){
    FILE *fp = fopen("rescue.dat", "rb+"); 

    // initialize animal object 
    Animal animal; 
     
    int option = 0; 
    char isContinue = 'r';
    animal = malloc(sizeof(struct animal_tag)); 
    while (isContinue != 'q') {
	printf("Which operation would you like to perform?\n"); 
	printf(" (1 = Search)\n (2 = Delete)\n (3 = Add)\n (4 = write to CSV)\n (5 = print out all info): ");
	scanf(" %d", &option); 
	if (option == 1) {
	    // search for animals 
	    search(fp, animal); 
	} else if (option == 2) {
	    // delete animals
	    delete(fp, animal);
	} else if (option == 3) {
	    // adding animals 
	    adding(fp, animal);
	} else if (option == 4) {
	    // write to csv
	    write(fp,animal);
	} else if (option == 5) { 
	    // print out everything 
	    printInfo(fp, animal); 
        }

	printf("\nEnter r to repeat, q to quit: ");
        scanf(" %s", &isContinue);

    }
    free(animal); 
    close(fp);
    return 0; 
}
