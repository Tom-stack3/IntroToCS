/***********************
* Name: Tommy Zaft
* Assignment: exercise 5
***********************/

#include "ex5.h"
/*
* Function Name: main
* Input: none
* Output: 0 - if everything was ok. 1 - if something went wrong.
* Function Operation: creates a university and calls handleOporations().
*/
int main()
{
	//we create a university and zero all the variables.
	Uni uni = {0};
	handleOporations(&uni);
	return 0;
}
