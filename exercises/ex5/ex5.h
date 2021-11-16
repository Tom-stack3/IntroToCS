/***********************
* Name: Tommy Zaft
* Assignment: exercise 5
***********************/

#ifndef EX5_H
#define EX5_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0
#define FAILED -1
#define MAX_NUM_OF_CLASSES 5
#define MAX_LENGTH_OF_STUDENT_NAME 20
#define MAX_LEN_CLASS_NAME 30
#define MAX_LENGTH_INPUT 200
#define LENGTH_OF_CLASS_ID 5
#define MINIMUM_LENGTH_OF_NAME 1
#define MINIMUM_AMOUNT_OF_SPACES 1
#define MAX_LENGTH_OF_GRADE 3
#define MAX_VALUE_OF_GRADE 100
#define MIN_GRADE 0
#define MAX_GRADE 100

typedef struct Student Student;
typedef struct {
	//5 digit id of the course.
	char id[LENGTH_OF_CLASS_ID+1];
	//name of the course. only english letteres, digits and spaces.
	char name[MAX_LEN_CLASS_NAME +1];
	//pointer to the first student
	Student* student;
} Class;

//Uni as in university.
typedef struct {
	Class classes[MAX_NUM_OF_CLASSES];
	int numOfClasses;
} Uni;

void handleOporations(Uni* uni);

#endif
