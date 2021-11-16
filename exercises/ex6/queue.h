/***********************
* Name: Tommy Zaft
* Assignment: exercise 6
***********************/

#ifndef _QUEUE_H
#define _QUEUE_H

#include "ex6.h"

// A linked list (LL) node to store a queue entry 
typedef struct QNode {
	Trin_Ari* person;
	struct QNode* next;
}QNode;

// The queue, front stores the front node of LL and rear stores the last node of LL 
typedef struct Queue {
	struct QNode *front, *rear;
}Queue;


Queue* createQueue(Tree* tree);
void enQueue(Queue* q, Trin_Ari* person, Tree* tree);
void deQueue(Queue* q);
int isEmpty(Queue* q);
void destroyQueue(Queue* q);

#endif
