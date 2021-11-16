/***********************
* Name: Tommy Zaft
* Assignment: exercise 6
***********************/

#include "queue.h"
#include <stdlib.h>

/*
* Function Name: createQueue
* Input: Tree* tree - the trinary tree.
* Output: Queue*: a pointer to the Queue created in the memory.
* Function Operation: creates a new queue in the memory, and retunrs a pointer to it.
*/
Queue* createQueue(Tree* tree) {
	Queue* queue = (Queue*)calloc(1,sizeof(Queue));
	if (queue == NULL) {
		memoryAllocationFailed(tree);
	}
	return queue;
}

/*
* Function Name: enQueue
* Input: Queue* q - the queue, Trin_Ari* person - the person to add, Tree* tree - the trinary tree.
* Output: none
* Function Operation: adds the person got to the queue, (puts him in the end).
*/
void enQueue(Queue* q, Trin_Ari* person, Tree* tree) {
	QNode* node = (QNode*)calloc(1, sizeof(QNode));
	if (node == NULL) {
		memoryAllocationFailed(tree);
	}
	node->person = person;
	//if the queue is empty.
	if (q->front == NULL && q->rear==NULL) {
		q->front = node;
		q->rear = node;
	}
	//else, we add the new node to the end.
	else {
		q->rear->next = node;
		q->rear = node;
	}
}

/*
* Function Name: deQueue
* Input: Queue* q - the queue
* Output: none
* Function Operation: free and delete the first in line in the queue.
*/
void deQueue(Queue* q) {
	QNode* nodeToFree = q->front;
	//if there is only one node in the queue.
	if (q->front == q->rear) {
		q->front = NULL;
		q->rear = NULL;
	}
	else if (q->front != NULL) {
		q->front = q->front->next;
	}
	free(nodeToFree);
}

/*
* Function Name: isEmpty
* Input: Queue* q - the queue
* Output: 1 if empty and 0 if not empty
* Function Operation: checks if queue empty.
*/
int isEmpty(Queue* q) {
	//if the queue is empty
	if (q->front == NULL && q->rear == NULL) {
		return 1;
	}
	//else, the queue is not empty.
	else {
		return 0;
	}
}

/*
* Function Name: destroyQueue
* Input: Queue* q - the queue
* Output: none
* Function Operation: destroys and deletes the queue. frees all the allocated memory left in the queue.
*/
void destroyQueue(Queue* q) {
	//while the queue is not empty from nodes, we keep going and deleting them
	while (!isEmpty(q)) {
		deQueue(q);
	}
	//after the queue is empty, we delete him from the memory.
	free(q);
}