/***********************
* Name: Tommy Zaft
* Assignment: exercise 6
***********************/

#include "ex6.h"
#include "Utils.h"
#include "queue.h"

/*
* Function Name: printFullMenu
* Input: none
* Output: none
* Function Operation: prints the full menu.
*/
static void printFullMenu() {
	printf("Please select an operation:\n"
		"\t0. Exit.\n"
		"\t1. Create family.\n"
		"\t2. Add family member.\n"
		"\t3. Print Family-Tree.\n"
		"\t4. Bidud.\n"
		"\t5. Superspreader.\n"
		"\t6. Vaccine.\n"
		"\t7. Print the menu.\n");
}

/*
* Function Name: printSurvived
* Input: Trin_Ari* person : gets the person to start freeing from recursively.
*		void(*f)(Trin_Ari): a function to do with each person, after freeing him.
*							can be printing "H ID: 8 Survived!" like in mission 0 for example.
*							also can be NULL, then we don't do anything when freeing.
*		Tree* tree: a pointer to the tree.
* Output: none
* Function Operation: frees the person and all his childs recursively.
*					after freeing all his children,
*					we run on the person the func() that was revieved. (if func != NULL)
*					then we free the persons name,
*					then we NULL the pointer to the person in his fathers tree
*					and finally, we free the person himself.
*/
static void freePerson(Trin_Ari* person, void(*func)(Trin_Ari*), Tree* tree) {
	//if we got the an end of a branch.
	if (person == NULL) {
		return;
	}
	freePerson(person->left,func,tree);
	freePerson(person->middle, func, tree);
	freePerson(person->right, func, tree);
	//if there is something to do with the person before deleting him.
	if (func != NULL) {
		func(person);
	}
	free(person->name);
	//if there is a father to the person
	if (person->father != NULL) {
		//if the person is the left child of his father
		if (person->father->left == person) {
			//we NULL the pointer to that child in the father tree, because we are deleting his child.
			person->father->left = NULL;
		}
		//if the person is the middle child of his father
		else if (person->father->middle == person) {
			//we NULL the pointer to that child in the father tree, because we are deleting his child.
			person->father->middle = NULL;
		}
		//else, the person is the right child of his father
		else {
			//we NULL the pointer to that child in the father tree, because we are deleting his child.
			person->father->right = NULL;
		}
	}
	//else, it is the first person in the tree.
	else {
		tree->firstPerson = NULL;
	}
	free(person);
}

/*
* Function Name: destroyTree
* Input: Tree* tree - a pointer to the tree.
*		void(*f)(Trin_Ari) - a function to do with each person, after freeing him.
*							can be printing "H ID: 8 Survived!" like in mission 0 for example.
*							also can be NULL, then we dont do anything when freeing.
* Output: none
* Function Operation: we find the first root of the tree, then free all using recursion. 
*					before freeing each item, we run func() we got on the person (if func != NULL).
*/
static void destroyTree(Tree* tree, void(*func)(Trin_Ari*)) {
	//if the tree is empty
	if (tree->firstPerson == NULL) {
		return;
	}
	//now we free the tree using the recursion function, starting from the root.
	freePerson(tree->firstPerson, func, tree);

}

/*
* Function Name: printSurvived
* Input: Trin_Ari* person - a person from the tree.
* Output: none
* Function Operation: prints that the person survived in the right format.
*/
static void printSurvived(Trin_Ari* person) {
	printf("%s ID: %d Survived!\n",person->name,person->id);
}

/*
* Function Name: memoryAllocationFailed
* Input: Tree* tree - a pointer to the tree.
* Output: none
* Function Operation: destroyes the tree, prints "Malloc Failed!" and exits the program.
*/
void memoryAllocationFailed(Tree* tree) {
	destroyTree(tree, NULL);
	printf("Malloc Failed!");
	exit(1);
}

/*
* Function Name: findPerson
* Input: int id - the id of the person we want to find.
* Output: Trin_Ari*: a pointer to the person if found.
*		NULL: if didn't find a person with such id in the tree.
* Function Operation: a recursive function to find a person in the tree by an id.
*					first checks if the current person is not the person we are looking for,
*					then checks the left branch, then the middle branch and then the right branch.
*/
static Trin_Ari* findPerson(Trin_Ari* firstPerson, int id) {
	//if got to an end of a branch.
	if (firstPerson == NULL) {
		return NULL;
	}
	//if found the person
	if (firstPerson->id == id) {
		return firstPerson;
	}
	
	Trin_Ari* person = findPerson(firstPerson->left, id);
	//if found person in the left branch
	if (person != NULL) {
		return person;
	}
	person = findPerson(firstPerson->middle, id);
	//if found person in the middle branch
	if (person != NULL) {
		return person;
	}
	person = findPerson(firstPerson->right, id);
	//if got here, means the id is either in the right brench, or the id is not in the big branch.
	return person;
	
}

/*
* Function Name: createPerson
* Input: Tree* tree - a pointer to the tree.
* Output: Trin_Ari*: a pointer to the person created in the memory.
* Function Operation: gets input from user, an id and a name,
*					if the id already exists, we ask for the user to enter again a name and id.
*					if the id is ok, we create a person in memory then returns the pointer to it.
*/
static Trin_Ari* createPerson(Tree* tree) {
	char nameEntered[MAX_NAME_LEN];
	int id;
	Trin_Ari* personTheIdBelongs = NULL;
	//we run until the user enters a person with an id which is not taken by someone in the tree.
	while(TRUE){
		printf("enter name\n");
		scanf(" %[^\n]", nameEntered);
		printf("enter ID\n");
		scanf("%d", &id);
		personTheIdBelongs = findPerson(tree->firstPerson, id);
		//if we got an id which belongs to a member of a tree.
		if (personTheIdBelongs != NULL) {
			printf("ID %d belongs to %s\n",id,personTheIdBelongs->name);
		}
		//the user entered a person with an id which is not taken by someone in the tree.
		else {
			//we exit the while loop
			break;
		}
	}
	//we create the name in the right length.
	char* name = (char*)calloc(strlen(nameEntered) + 1, sizeof(char));
	//if the memory allocation failed
	if (name == NULL) {
		memoryAllocationFailed(tree);
	}
	strcpy(name, nameEntered);
	Trin_Ari* person = (Trin_Ari*)calloc(1, sizeof(Trin_Ari));
	//if the memory allocation failed
	if (person == NULL) {
		memoryAllocationFailed(tree);
	}
	person->id = id;
	person->name = name;
	printf("Hello %s, ID: %d\n", name, id);
	return person;
}

/*
* Function Name: createFamily
* Input: Tree* tree - gets a pointer to the tree.
* Output: none
* Function Operation: if the first person in the tree is not created yet,
*					we get input from the user about the new person, (id and name)
*					and then create the person, using createPerson().
*					then puts it in the root of the tree.
*/
static void createFamily(Tree* tree) {
	//if the first person in the family was already created.
	if (tree->firstPerson != NULL) {
		printf("The family has already been created\n");
		return;
	}
	tree->firstPerson = createPerson(tree);
}

/*
* Function Name: addMeeting
* Input: Tree* tree - gets a pointer to the tree.
* Output: none
* Function Operation: if the tree hasn't been created yet we exit.
*					gets an id from the user to make an apointment with,
*					if the id doesn't exist we print that fact and exit.
*					if the id does exist, and there is place to add a new meeting,
*					we create a new person using createPerson() and put it in the right place in the tree.
*/
static void addMeeting(Tree* tree) {
	//if the tree is empty and there is no root
	if (tree->firstPerson == NULL) {
		printf("Please create the family first\n");
		return;
	}
	printf("Enter the ID of the person who wants to make an appointment?\n");
	int idOfPersonToMeet;
	scanf("%d", &idOfPersonToMeet);
	Trin_Ari* personToMeet = findPerson(tree->firstPerson, idOfPersonToMeet);
	//if the person wanted to meet with is not in the tree.
	if (personToMeet == NULL) {
		printf("There is no ID %d\n",idOfPersonToMeet);
		return;
	}
	//if all 3 meetings are booked with the person.
	if (personToMeet->left != NULL && personToMeet->middle != NULL && personToMeet->right != NULL) {
		printf("%s ID: %d can't meet more than 3 members!\n", personToMeet->name, personToMeet->id);
		return;
	}
	Trin_Ari* personAdding = createPerson(tree);
	//if the left spot is empty to meet
	if (personToMeet->left == NULL) {
		personAdding->father = personToMeet;
		personToMeet->left = personAdding;
	}
	//if the middle spot is empty to meet
	else if (personToMeet->middle == NULL) {
		personAdding->father = personToMeet;
		personToMeet->middle = personAdding;
	}
	//else, the right spot is empty to meet
	else{
		personAdding->father = personToMeet;
		personToMeet->right = personAdding;
	}
}

/*
* Function Name: printStayHome
* Input: Trin_Ari* suspect - a person from the tree.
* Output: none
* Function Operation: prints that the person that needs to stay home (quarantine).
*/
static void printStayHome(Trin_Ari* suspect) {
	printf("#StayHome! %s %d\n", suspect->name, suspect->id);
}

/*
* Function Name: printSuspectQuarantine
* Input: Trin_Ari* suspect - gets a pointer to a person in the tree who is a suspect of having corona.
* Output: none
* Function Operation: prints all the people who need quarantine because of the suspect.
*					if the father exists, we print him first,
*					then we print the suspect himself.
*					then if the left child exists, we print him,.
*					then the middle child exists, we print him.
*					and finally if the right child exists, we print him to stay home with printStayHome().
*/
static void printSuspectQuarantine(Trin_Ari* suspect) {
	//if person exists, he needs quarantine.
	if (suspect->father != NULL) {
		printStayHome(suspect->father);
	}
	//if person exists, he needs quarantine.
	if (suspect != NULL) {
		printStayHome(suspect);
	}
	//if person exists, he needs quarantine.
	if (suspect->left != NULL) {
		printStayHome(suspect->left);
	}
	//if person exists, he needs quarantine.
	if (suspect->middle != NULL) {
		printStayHome(suspect->middle);
	}
	//if person exists, he needs quarantine.
	if (suspect->right != NULL) {
		printStayHome(suspect->right);
	}
}

/*
* Function Name: quarantine
* Input: Trin_Ari* firstPerson - gets a pointer to the first person in the tree.
* Output: none
* Function Operation: if the tree hasn't been created yet we exit.
*					gets an id from the user for a suspect,
*					if the id doesn't exist we print that fact and exit.
*					if the id does exist, we call printSuspectQuarantine(),
*					to print all the people who need to be in quarantine.
*/
static void quarantine(Trin_Ari* firstPerson) {
	//if the tree is empty and there is no root
	if (firstPerson == NULL) {
		printf("Please create the family first\n");
		return;
	}
	printf("Enter the ID of the suspected member\n");
	int suspectId;
	scanf("%d", &suspectId);
	//we search for the suspect entered.
	Trin_Ari* suspect = findPerson(firstPerson, suspectId);
	//if the person suspected is not in the tree.
	if (suspect == NULL) {
		printf("ID %d does not exist\n", suspectId);
		return;
	}
	//we print the people who need to quarantine.
	printSuspectQuarantine(suspect);
}

/*
* Function Name: vacinate
* Input: Tree* tree - gets a pointer to the tree.
* Output: none
* Function Operation: if the tree hasn't been created yet we exit.
*					gets an id from the user for a person who got vaccinated,
*					if the id doesn't exist we print that fact and exit.
*					if the id does exist, we free the person and all his children using freePerson().
*					before freeing each person,
*					we print he survived by sending freePerson() the address of the function printSurvived().
*/
static void vacinate(Tree* tree) {
	//if the tree is empty and there is no root
	if (tree->firstPerson == NULL) {
		printf("Please create the family first\n");
		return;
	}
	printf("Who got vaccinated (ID)?\n");
	int id;
	scanf("%d", &id);
	//we search for the vaccinated person entered.
	Trin_Ari* vacinatedPerson = findPerson(tree->firstPerson, id);
	//if the vaccinated person is not in the tree.
	if (vacinatedPerson == NULL) {
		printf("There is no ID %d\n", id);
		return;
	}
	
	/*
	else, we delete the person and all it's children in the tree. because they are all safe.
	we also send printSurvived(), so the function prints each person survived before deleting them.
	*/
	freePerson(vacinatedPerson, &printSurvived,tree);
}

/*
* Function Name: printPrintingMenu
* Input: none
* Output: none
* Function Operation: prints the printing menu.
*/
static void printPrintingMenu() {
	printf("Please select an operation:\n"
		"\t0. Return to the main menu.\n"
		"\t1. Print Trin-Ari family.\n"
		"\t2. Print Pre-order.\n"
		"\t3. Print Left-order.\n"
		"\t4. Print BFS.\n");
}

/*
* Function Name: printPreOrder
* Input: Trin_Ari* firstPerson - the first person in the tree to start printing from.
* Output: none
* Function Operation: prints the tree in pre-order
*/
static void printPreOrder(Trin_Ari* firstPerson) {
	//if we got to an end of a branch.
	if (firstPerson == NULL) {
		return;
	}
	printf("%s ID: %d\n",firstPerson->name,firstPerson->id);
	printPreOrder(firstPerson->left);
	printPreOrder(firstPerson->middle);
	printPreOrder(firstPerson->right);
}

/*
* Function Name: printLeftOrder
* Input: Trin_Ari* firstPerson - the first person in the tree to start printing from.
* Output: none
* Function Operation: prints the tree in left-order
*/
static void printLeftOrder(Trin_Ari* firstPerson) {
	//if we got to an end of a branch.
	if (firstPerson == NULL) {
		return;
	}
	printLeftOrder(firstPerson->left);
	printf("%s ID: %d\n", firstPerson->name, firstPerson->id);
	printLeftOrder(firstPerson->middle);
	printLeftOrder(firstPerson->right);
}

/*
* Function Name: printBFSRec
* Input: Queue* queue - pointer to the queue used for the BSF algorhitem.
*		void(*printFunc)(Trin_Ari*) - the function to do on each person to print him.
*		Tree* tree - pointer to the tree.
* Output: none
* Function Operation: a recursive function prints the tree in BSF.
*					using the queue, we pull a node from the queue (the first node in the queue), 
*					if the node is not NULL (that means we are done),
*					we print him using printFunc() recieved.
*					then we add all his children (in the right order - left, middle, right)
*					and then we dequeue him.
*/
static void printBFSRec(Queue* queue, void(*printFunc)(Trin_Ari*), Tree* tree) {
	QNode* node = queue->front;
	//if we got to the end of the queue.
	if (node == NULL) {
		return;
	}
	//if the queue is not empty.
	if (!isEmpty(queue)) {
		//we print the person in the way needed
		printFunc(queue->front->person);
	}
	if (node->person->left!= NULL) {
		enQueue(queue, node->person->left, tree);
	}
	if (node->person->middle != NULL) {
		enQueue(queue, node->person->middle, tree);
	}
	if (node->person->right != NULL) {
		enQueue(queue, node->person->right, tree);
	}
	//then we dequeue him from the queue
	deQueue(queue);
	printBFSRec(queue, printFunc, tree);
}

/*
* Function Name: printId
* Input: Trin_Ari* person - a person from the tree.
* Output: none
* Function Operation: prints that the person that recieved ( Name Id).
*/
static void printId(Trin_Ari* person) {
	printf("%s %d\n", person->name, person->id);
}

/*
* Function Name: printBFS
* Input: Trin_Ari* firstPerson - pointer to the first person to start printing in BSF algorhitem.
*		void(*printFunc)(Trin_Ari*) - the function to do on each person to print him.
*		Tree* tree - pointer to the tree.
* Output: none
* Function Operation: prints the tree in BSF starting from the person recieved (firstPerson).
*					first we create a queue using createQueue()
*					the we enqueue the first person received and call printBFSRec() 
*					all the children of the first person.
*					after we are done working with the queue we call destroyQueue() to free all the memory.
*/
static void printBFS(Trin_Ari* firstPerson, void(*printFunc)(Trin_Ari*), Tree* tree) {
	//if the tree is empty.
	if (firstPerson == NULL) {
		return;
	}
	Queue* queue = createQueue(tree);
	//we enQueue the first person.
	enQueue(queue, firstPerson,tree);
	printBFSRec(queue, printFunc, tree);
	destroyQueue(queue);
}

/*
* Function Name: handlePrinting
* Input: Tree* tree - pointer to the tree.
* Output: none
* Function Operation: prints the printing menu by calling printPrintingMenu()
*					then gets from the user to chosen option.
*					until the user doesn't enter a valid option, it does it in a loop.
*					then calls the right printing method function chosen by the user.
*					uf the user chose 0, we exit back the the main menu.
*/
static void handlePrinting(Tree* tree) {
	const int NUM_OF_SPACES = 3;
	char optinChosen;
	int isValidInput = TRUE;
	//runs until the user input a valid option.
	do {
		isValidInput = TRUE;
		printPrintingMenu();
		scanf(" %c", &optinChosen);
		switch (optinChosen)
		{
			//if the user chose to exit the printing menu.
			case '0':
				printFullMenu();
				return;
			case '1':
				print2DUtil(tree->firstPerson, NUM_OF_SPACES);
				break;
			case '2':
				printPreOrder(tree->firstPerson);
				break;
			case '3':
				printLeftOrder(tree->firstPerson);
				break;
			case '4':
				printBFS(tree->firstPerson, &printId, tree);
				break;
			default:
				printf("Error: unrecognized operation.\n");
				isValidInput = FALSE;
		}
	}while (!isValidInput);
	//after the printing of the tree, we print the full menu. (if the user didn't enter 0)
	printFullMenu();
}

/*
* Function Name: superSpreader
* Input: Tree* tree - pointer to the tree.
* Output: none
* Function Operation: if the tree hasn't been created yet we exit.
*					gets an id from the user for a suspect,
*					if the id doesn't exist we print that fact and exit.
*					if the id does exist, we call printBFS(),
*					to print all the people who need to be in quarantine.
*/
static void superSpreader(Tree* tree) {
	//if the tree is empty and there is no root
	if (tree->firstPerson == NULL) {
		printf("Please create the family first\n");
		return;
	}
	printf("Enter the ID of the suspected Superspreader\n");
	int superSpreaderId;
	scanf("%d", &superSpreaderId);
	//we search for the suspect entered.
	Trin_Ari* superSpreader = findPerson(tree->firstPerson, superSpreaderId);
	//if the person suspected is not in the tree.
	if (superSpreader == NULL) {
		printf("ID %d does not exist\n", superSpreaderId);
		return;
	}
	//we print the people who need to quarantine.
	if (superSpreader->father != NULL) {
		//if the father of the suspect exists, we print that we needs quarantine.
		printStayHome(superSpreader->father);
	}
	printBFS(superSpreader,&printStayHome,tree);
}

/*
* Function Name: chooseWhoToCall
* Input: char option - the option the user entered.
*		Tree* tree - pointer to the tree.
*		Bool* didPrint - (TRUE/FALSE) if printed the menu or not.
* Output: none
* Function Operation: based on the input of the user, we choose what operation to call.
*					if entered 0, we destroy the tree.
*					if entered 1-6 we call the function that is responsable on the operation.
*					in operation 3 we already print the menu in the funcioon handlePrinting(),
*					so we change the value of didPrint to TRUE.
*					the same in operation 7, we print the full menu,
*					so we change the value of didPrint to TRUE.
*					if user entered something else, (not '0'-'7') we print an error.
*/
static void chooseWhoToCall(char option, Tree* tree, Bool* didPrint){
	//check the option the user entered.
	switch (option)
	{
		case '0':
			*didPrint = TRUE;
			//we free the alocated memory before we exit the program.
			destroyTree(tree,&printSurvived);
			return;
		case '1':
			createFamily(tree);
			break;
		case '2':
			addMeeting(tree);
			break;
		case '3':
			*didPrint = TRUE;
			handlePrinting(tree);
			break;
		case '4':
			quarantine(tree->firstPerson);
			break;
		case '5':
			superSpreader(tree);
			break;
		case '6':
			vacinate(tree);
			break;
		case '7':
			*didPrint = TRUE;
			printFullMenu();
			break;
		default:
			printf("Error: unrecognized operation.\n");
	}
}

/*
* Function Name: getUserInput
* Input: none
* Output: none
* Function Operation: hosts the whole program.
*					called once from the main, and the whole program runs here.
*					we create the tree here, print the menu for the first time,
*					and then get from the user input and call chooseWhoToCall() each time.
*					the function runs for the last time when user enters 0.
*/
void getUserInput() {
	char option = 0;
	Tree tree;
	tree.firstPerson = NULL;
	Bool didPrint = FALSE;
	//prints the full menu for the first time
	printFullMenu();
	while (option != '0') {
		didPrint = FALSE;
		scanf(" %c", &option);
		chooseWhoToCall(option,&tree,&didPrint);
		//if didn't print the full menu already in chooseWhoToCall().
		if (!didPrint) {
			printf("Select the next operation (insert 7 for the entire menu):\n");
		}
	}
}