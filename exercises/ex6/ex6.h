/***********************
* Name: Tommy Zaft
* Assignment: exercise 6
***********************/

#ifndef _EX6_H_
#define _EX6_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NAME_LEN 50

struct Trin_Ari {
	int id;
	char * name;
	struct Trin_Ari *father;
	struct Trin_Ari *left;
	struct Trin_Ari *middle;
	struct Trin_Ari *right;
};
typedef struct Trin_Ari Trin_Ari;

typedef struct {
	Trin_Ari* firstPerson;
}Tree;

enum Bool { FALSE, TRUE };
typedef enum Bool Bool;
void getUserInput();
void memoryAllocationFailed(Tree*);

#endif