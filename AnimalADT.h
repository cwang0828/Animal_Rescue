#ifndef ANIMALADT_H
#define ANIMALADT_H

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

/**
    Name: Hsin-Jung Wang (Cindy)
    TCSS 333 
    Assignment: #5
    NetID: 1260340
*/

struct animal_tag {
    short int id;
    char name[20];
    char species[35];
    char size; 
    short int age; 

}; 

typedef struct animal_tag * Animal; 

void search(FILE *fp, Animal animal);

void delete(FILE *fp, Animal animal);

void printInfo(FILE *fp, Animal animal); 

void adding(FILE *fp, Animal animal);

void write(FILE *fp, Animal animal); 

#endif
