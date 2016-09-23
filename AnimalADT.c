#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "AnimalADT.h"

// this is the max number of deleted file
#define NUM_IDS 10

/**
    Name: Hsin-Jung Wang (Cindy)
    TCSS 333 
    Assignment: #5
    NetID: 1260340
*/


// This method reset the pointer position
// to the begining of the animal.
void resetPositionInFile(FILE * fp){
    rewind(fp); 
    fseek(fp, sizeof(short int) * 11, SEEK_SET); 
}

// This method write the animal info to the csv file.
void write(FILE *fp, Animal animal){
    FILE *outputfp = fopen("rescue.csv", "w"); 
    resetPositionInFile(fp);
    // reads the file
    while(!feof(fp)){
        fread(animal, sizeof(struct animal_tag), 1, fp); 

        // make sure that the last index does not printed out twice
        if(feof(fp)) { break; }

        // make sure that the deleted (unknown) is not being written 
        // to the csv file.
        if(strcmp(animal->name,"unknown") != 0) {
        fprintf(outputfp,"%hd,%s,%s,%c,%hd\n", animal->id,animal->name,animal->species,animal->size,animal->age);
        } 
    } 
    fclose(outputfp);
}

// Extra credit
// This method decoded and printed out all the 
// info from the text file
void printInfo(FILE *fp, Animal animal) {
    short int num_Of_IDs, ids[NUM_IDS]; 
    int index; 
    rewind(fp); 
    fread(&num_Of_IDs, sizeof(num_Of_IDs), 1, fp); 

    printf("%hd\n", num_Of_IDs);
    fread(&ids, sizeof(ids), 1, fp);
    for(index = 0; index < NUM_IDS; index++){
        printf("%hd  ", ids[index]); 
    }
    printf("\n");
    while(!feof(fp)){
        fread(animal, sizeof(struct animal_tag), 1, fp); 
        if(feof(fp)) { break; }
        printf("id = %hd, ", animal->id); 
	    printf("name = %s, ", animal->name);
 	    printf("species = %s, ", animal->species);
	    printf("size = %c, ", animal->size); 
	    printf("age = %hd\n", animal->age);
    }
}

// This method searches to see whether the user-input id is
// a valid id or not. 
int searchID(FILE *fp, Animal animal, short int inputID) {
    short int targetID; 
    int index, found = 0; 
    char targetName[20];
    char targetSpecies[35];
    char targetSize;
    short int targetAge; 

    // Rewind the pointer and skip the content from the first row 
    resetPositionInFile(fp);

    fseek(fp, inputID * (sizeof(struct animal_tag)) - (sizeof(struct animal_tag)), SEEK_CUR);

    fread(&targetID, sizeof(targetID), 1, fp);
    if(inputID == targetID) {
	// read in the target name 
	    fread(&targetName, sizeof(targetName), 1, fp); 
	    if(strcmp(targetName, "unknown") != 0) {
	        fread(&targetSpecies, sizeof(targetSpecies), 1, fp);
	        fread(&targetSize, sizeof(targetSize), 1, fp);
	        fread(&targetAge, sizeof(targetAge), 1, fp);

	        animal->id = targetID;
	        strcpy(animal->name, targetName);
	        strcpy(animal->species, targetSpecies);
	        animal->size = targetSize;
	        animal->age = targetAge;
	        found = 1; 
	    }
    }
    return found; 
}

// This method searches for a particular animal info
// based on the animal id. 
void search(FILE *fp, Animal animal) {
    short int inputID; 

    printf("Please enter an animal id number for searching: ");
    scanf(" %hu", &inputID); 

    int found = 0; 
    found = searchID(fp, animal, inputID); 

    // if it is a valid id. 
    if(found == 1) {
	    printf("id = %d, ", animal->id); 
        printf("name = %s, ", animal->name);
	    printf("species = %s, ", animal->species);
	    printf("size = %c, ", animal->size); 
	    printf("age = %d\n", animal->age);
    } else {
    // if the id is invalid  or is an empty record
	// display an error message
	    printf("No such id is found\n"); 
    }
}

// This method delete animal info based on the id. 
void delete(FILE *fp, Animal animal) {

    short int num_Of_IDs, ids[NUM_IDS]; 
    short int inputID,num_Of_avail_IDs; 
    int found  = 0; 
    char arrPerID[2];
    char tempIDArr[20]; 

    printf("Please enter an animal id number for delete: ");
    scanf(" %hu", &inputID); 

    rewind(fp); 
    fread(&num_Of_avail_IDs, 2,1,fp);      

    
    found = searchID(fp, animal, inputID); 

  
    if(found == 1) {

        //1. update the number of available id
        num_Of_avail_IDs++;
        printf("\nIn delete method number of avail_IDs is %d", num_Of_avail_IDs);

        rewind(fp); 
        fwrite(&num_Of_avail_IDs,sizeof(num_Of_avail_IDs), 1, fp); 
    
        //2. update the array id
        fread(ids,sizeof(ids),1,fp);
        ids[num_Of_avail_IDs -1] = inputID; 
        fseek(fp, sizeof(num_Of_avail_IDs), SEEK_SET); 
        fwrite(ids, sizeof(ids), 1, fp); 

        // 3. update the animal info
        resetPositionInFile(fp); 
        fseek(fp, sizeof(struct animal_tag) * (inputID-1), SEEK_CUR);
        fread(animal, sizeof(struct animal_tag), 1, fp); 
        strcpy(animal->name, "unknown");

        resetPositionInFile(fp); 
        fseek(fp, sizeof(struct animal_tag) * (inputID-1), SEEK_CUR);
        fwrite(animal, sizeof(struct animal_tag), 1, fp); 
    } else {
        // if the id is invalid
	    printf("The id is invalid and therefore cannot be deleted\n"); 
    }
}

// This method add a new animal info by asking the 
// user to enter name, species, size, and age, and
// store the info in the file in the correct spot
void adding(FILE *fp, Animal animal) {

    short int num_Of_avail_IDs, ids[NUM_IDS], newID, lastID;
    char tempName[20]; 
    char tempSpecies[35];
    char tempSize; 
    short int tempAge;

    // ask for animal info
     printf("\nPlease enter an animal's name: ");
     scanf(" %s", tempName);
     printf("the temp name is : %s", tempName); 

     printf("\nPlease enter an animal's species: ");
     scanf(" %[^\n]s", tempSpecies);
     printf("the temp species is : %s", tempSpecies); 

     printf("\nPlease enter an animal's size: ");
     scanf(" %c", &tempSize);
     printf("the temp size is : %c", tempSize); 

     printf("\nPlease enter an animal's age: ");

     scanf("%hd", &tempAge);
     printf("the temp age is : %hd", tempAge); 






        //1. num of available id (reduce by 1)
        rewind(fp); 
        fread(&num_Of_avail_IDs, sizeof(num_Of_avail_IDs),1,fp); 
         
    
        //2. READ ID ARRAY
        fread(ids,sizeof(ids),1,fp);

        if(num_Of_avail_IDs != 0) {
            // fill any existing holes
            num_Of_avail_IDs--;
            printf("\nIn Add method number of avail_IDs is %d", num_Of_avail_IDs);

            rewind(fp); 
            fwrite(&num_Of_avail_IDs,sizeof(num_Of_avail_IDs), 1, fp);
            newID = ids[0];
            // update directory
            // shift everything left one index
            int index;
            for(index = 1; index <9; index++) {
                ids[index-1] = ids[index];
            }
            // update the last index to 0
            ids[9] = 0; 
            fseek(fp, sizeof(num_Of_avail_IDs), SEEK_SET); 
            fwrite(ids, sizeof(ids), 1, fp); 

            //3. update animal info
            resetPositionInFile(fp); 
            fseek(fp, sizeof(struct animal_tag) * (newID-1), SEEK_CUR);
            fread(animal, sizeof(struct animal_tag), 1, fp);
            printf("here id %d\n", animal->id);

            strcpy(animal->name, tempName);
            strcpy(animal->species, tempSpecies);
            animal->size = tempSize;
            animal->age = tempAge;

            resetPositionInFile(fp); 
            fseek(fp, sizeof(struct animal_tag) * (newID-1), SEEK_CUR);
            fwrite(animal, sizeof(struct animal_tag),1,fp); 


        } else {
            // If there are no holes in the id sequence, 
            // then the new animal info should be appended to
            // the end of the database.
            resetPositionInFile(fp); 
            fseek(fp, -sizeof(struct animal_tag), SEEK_END);
            fread(animal, sizeof(struct animal_tag), 1, fp);
            newID = (animal->id)+1;
            printf("the last id is %hd", newID);
            strcpy(animal->name, tempName);
            strcpy(animal->species, tempSpecies);
            animal->size = tempSize;
            animal->age = tempAge;
            animal->id = newID; 
            fwrite(animal, sizeof(struct animal_tag),1,fp); 
        }
}




