/***********************
* Name: Tommy Zaft
* Assignment: exercise 5
***********************/

#include "ex5.h"

struct Student {
	char name[MAX_LENGTH_OF_STUDENT_NAME+1];
	//grade between 0 and 100
	int grade;
	//pointer to the next student in the list.
	struct Student* next;

};

//a permanent course struct used for the adding of a student.
typedef struct {
	int grade;
	//5 digit id of the course.
	char id[LENGTH_OF_CLASS_ID+1];
}
PermanentCourse;

//a permanent student struct used for the adding of a student.
typedef struct {
	char name[MAX_LENGTH_OF_STUDENT_NAME+1];
	PermanentCourse classes[MAX_NUM_OF_CLASSES+1];
	int numberOfClasses;
} PerStudent;

/*
* Function Name: printRightMenu
* Input: int isFullMenu: TRUE - print the full menu. FALSE - prints only the one line menu.
* Output: none
* Function Operation: prints the right menu.
*/
void printRightMenu(int isFullMenu) {
	//if we need to print the full menu
	if (isFullMenu) {
		printf("Please select an operation:\n"
			"\t0. Exit.\n"
			"\t1. Insert or update a class.\n"
			"\t2. Insert or update a student.\n"
			"\t3. Remove a student from classes.\n"
			"\t4. Print a class.\n"
			"\t5. Print all classes with their computed scores.\n"
			"\t6. Print the menu.\n");
	}
	else {
		printf("Select the next operation (insert 6 for the entire menu):\n");
	}
}

/*
* Function Name: freeClass
* Input: Student* student- pointer to the first student in class.
* Output: none
* Function Operation: frees all the students in the class in the right order.
*/
void freeClass(Student* student) {
	//if already empty.
	if (student == NULL) {
		return;
	}
	//got to the last student
	if (student->next == NULL) {
		free(student);
		return;
	}
	else {
		//we continue to the next student.
		freeClass(student->next);
		//we free the curret student.
		free(student);
	}
}

/*
* Function Name: freeAllClasess
* Input: Uni* uni - the university with the classes in it..
* Output: none
* Function Operation: free's all the classes in the university. using freeClass().
*/
void freeAllClasess(Uni* uni) {
	//goes over all the classes
	for (int i = 0; i < uni->numOfClasses; i++) {
		//frees the class. we send the recursive function the first student of the class to begin with.
		freeClass(uni->classes[i].student);
	}
}

/*
* Function Name: isStringAlphaAndSpaces
* Input: char str[] - string to check.
* Output: int. FALSE - if string not all a-z,A-Z and spaces. TRUE - if string a-z,A-Z and spaces.
* Function Operation: checks if the string contains only a-z,A-Z and spaces.
*/
int isStringAlphaAndSpaces(char str[]) {
	for (int i = 0; i < strlen(str); i++) {
		//if the char is not alphabetical and not a space. a-z,A-Z,' '.
		if (!isalpha(str[i]) && !isspace(str[i])) {
			//means it is not a valid name.
			return FALSE;
		}
	}
	return TRUE;
}

/*
* Function Name: isStringNumber
* Input: char str[] - string to check if a number.
* Output: int. FALSE - if string is not a number. TRUE - if string is a number.
* Function Operation: checks if the string is a number. (all the chars are digits.)
*/
int isStringNumber(char str[]) {
	for (int i = 0; i < strlen(str); i++) {
		//if the char is not a digit. 0-9.
		if (!isdigit(str[i])) {
			//means it is not a valid number.
			return FALSE;
		}
	}
	//if we got here, means the str is indeed a number.
	return TRUE;
}

/*
* Function Name: checkIfClassNameValid
* Input: char name[] - name to check.
* Output: int: TRUE - if id valid. FALSE - if id isn't valid.
* Function Operation: checks if class name is valid.
*/
int checkIfClassNameValid(char name[]) {
	//check if class name too long or too short.
	if (strlen(name) > MAX_LEN_CLASS_NAME || strlen(name) < 1) {
		return FALSE;
	}
	//check if class name got chars which are not letters, digits or a space.
	for (int i = 0; i < strlen(name); i++) {
		//if the char is a not english letter, space or a digit.
		if (!isalpha(name[i]) && !isdigit(name[i]) && !isspace(name[i])) {
			//means it is not a valid class name.
			return FALSE;
		}
	}
	//if we got here, means the id is valid.
	return TRUE;
}

/*
* Function Name: checkIfIdValid
* Input: char id[] - id to check.
* Output: int: TRUE - if id valid. FALSE - if id isn't valid.
* Function Operation: checks if the id is valid.
*/
int checkIfIdValid(char id[]) {
	//if got null.
	if (id == NULL) {
		return FALSE;
	}
	//check if the id is in the right length
	if (strlen(id) != LENGTH_OF_CLASS_ID) {
		return FALSE;
	}
	for (int i = 0; i < strlen(id); i++) {
		//if one of the chars in the id is not a digit.
		if (!isdigit(id[i])) {
			return FALSE;
		}
	}
	//if we got here, means the id is valid.
	return TRUE;
}

/*
* Function Name: cleanSpacesAtStart
* Input: char str[], Uni* uni. 
*		str - string the clean spaces from start.
*		uni - the university with the classes.
* Output: none
* Function Operation: cleans spaces at the start of the string got.
*/
void cleanSpacesAtStart(char str[], Uni* uni) {
	int spaceCounter = 0;
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] != ' ') {
			break;
		}
		spaceCounter++;
	}
	//if there are no spaces at the start.
	if (spaceCounter == 0) {
		return;
	}
	char* newStr = (char*) calloc(strlen(str) - spaceCounter + 1, sizeof(char));
	//if the calloc failed, we free al the classes and exit the program.
	if (newStr == NULL) {
		freeAllClasess(uni);
		exit(1);
	}
	int index = 0;
	//we copy to newStr the string starting from the furst index which is not a space.
	for (int i = spaceCounter; i < strlen(str); i++) {
		newStr[index] = str[i];
		index++;
	}
	//we copy the new cleaned string to the location of the str we got.
	strcpy(str, newStr);
	free(newStr);
}

/*
* Function Name: cleanSpacesAtEnd
* Input: char str[], Uni* uni.
*		str - string the clean spaces from end.
*		uni - the university with the classes.
* Output: none
* Function Operation: cleans spaces at the end of the string got.
*/
void cleanSpacesAtEnd(char str[], Uni* uni) {
	int spaceCounterAtEnd = 0;
	for (int i = strlen(str)-1; i >=0; i--) {
		if (str[i] != ' ') {
			break;
		}
		spaceCounterAtEnd++;
	}
	//if there are no spaces at the end.
	if (spaceCounterAtEnd == 0) {
		return;
	}
	char* newStr = (char*)calloc(strlen(str) - spaceCounterAtEnd + 1, sizeof(char));
	//if the calloc failed, we free al the classes and exit the program.
	if (newStr == NULL) {
		freeAllClasess(uni);
		exit(1);
	}

	//we copy to newStr the string until we get to the last index which is not a space.
	for (int i = 0; i < strlen(str)- spaceCounterAtEnd; i++) {
		newStr[i] = str[i];
	}
	//we copy the new cleaned string to the location of the str we got.
	strcpy(str, newStr);
	free(newStr);
}

/*
* Function Name: checkIfClassInputValidAndInit
* Input: char* id, char* name, Uni* uni
*		id - id of class the user wants to add
*		name - name of class the user wants to add
*		uni - the university with the classes.
* Output: int: TRUE - if input is valid. FALSE - if input is not valid.
* Function Operation: checks if the input from the user to add a class is valid.
*					if it is valid, copy the id and name got from the user to char* id, char* name.
*/
int checkIfClassInputValidAndInit(char* id, char* name, Uni* uni) {
	char idStr[MAX_LENGTH_INPUT+1];
	char nameStr[MAX_LENGTH_INPUT + 1];
	scanf("%s", idStr);
	scanf("%[^\n]", nameStr);

	if (idStr == NULL || name == NULL) {
		return FALSE;
	}
	cleanSpacesAtStart(nameStr, uni);
	cleanSpacesAtStart(idStr, uni);
	//if the input is not valid
	if (checkIfIdValid(idStr) == FALSE || checkIfClassNameValid(nameStr) == FALSE) {
		return FALSE;
	}
	//if we got here means the input was valid, so we copy it to the id and name got.
	strcpy(id,idStr);
	strcpy(name, nameStr);
	return TRUE;
}

/*
* Function Name: findClass
* Input: Uni* uni - the university with the classes in it, char* id - id of class to find.
* Output: int: FAILED(= -1) - if haven't found a class with the same id.
*				if did found, we return the index of the class in the array in the university.
* Function Operation: find the index of the class in the array in the university.
*/
int findClass(Uni* uni, char* id) {
	//if got null.
	if (id == NULL) {
		return FAILED;
	}
	//there are no classes yet
	if (uni->numOfClasses == 0) {
		return FAILED;
	}
	for (int i = 0; i < uni->numOfClasses; i++) {
		//we found a class with the same id.
		if (strcmp(uni->classes[i].id,id) == 0) {
			//means the class exists, we return his index
			return i;
		}
	}
	//we haven't found a class with the same id.
	return FAILED;
}

/*
* Function Name: findLastStudentRecursion
* Input: Student* student
*		student - when the function first called, student = first student in class.
* Output: Student* - pointer to the last student.
* Function Operation: recursive function that finds the last student in the linked list.
*/
Student* findLastStudentRecursion(Student* student) {
	//found the last student
	if (student->next == NULL) {
		return student;
	}
	else {
		//continue searching.
		findLastStudentRecursion(student->next);
	}
}

/*
* Function Name: findStudent
* Input: Uni* uni, char* id, char name[]
*		uni - the university with the classes in it.
*		id - id of class to find student in.
*		name - name of student to find in class.
* Output: NULL - if didn't found the student
*		Student* - pointer to the student that fits the search.
* Function Operation: serach for a student in class which id is the id recieved,
*					then finds the student which name == char name[] in that class.
*
*/
Student* findStudent(Uni* uni, char* id, char name[]) {
	int classIndex = findClass(uni, id);
	//if failed to find class, return NULL
	if (classIndex == FAILED) {
		return NULL;
	}
	Student* student = uni->classes[classIndex].student;
	//we go over the students in class
	while (student != NULL)
	{
		//if found the student
		if (strcmp(student->name, name) == 0) {
			return student;
		}
		student = student->next;
	}
	//got to the end and didn't find the student
	return NULL;
}

/*
* Function Name: countStudents
* Input: Class class - class to count the students in.
* Output: int- the number of students in class.
* Function Operation: function to find the number of students in class.
*/
int countStudents(Class class) {
	int counter = 0;
	Student* student = class.student;
	//we go over the students in class
	while (student != NULL)
	{
		counter++;
		student = student->next;
	}
	return counter;
}

/*
* Function Name: insertUpdateClass
* Input: Uni* uni - the university with the classes in it.
* Output: none
* Function Operation: calls checkIfClassInputValidAndInit() which gets and checks user input. 
*					checks if there is room for more classes in the university.
*					checks if the class already exists and needs an update or if needs to add a new one.
*					then updates/adds the class entered from the user if everything was valid.
*/
void insertUpdateClass(Uni* uni) {
	char id[LENGTH_OF_CLASS_ID+1];
	char name[MAX_LEN_CLASS_NAME+1];
	//we check and init the id and the name.
	int isValidInput = checkIfClassInputValidAndInit(id, name, uni);
	//if the input of the user was not valid.
	if (!isValidInput) {
		printf("Error: invalid class number or name.\n");
		return;
	}

	int classIndex = findClass(uni, id);
	//if class already exists, we need to update it.
	if (classIndex != FAILED) {
		strcpy(uni->classes[classIndex].name,name);
		printf("Class \"%s %s\" updated.\n",id,name);
	}
	//if there is no room for more classes
	else if (uni->numOfClasses >= MAX_NUM_OF_CLASSES) {
		printf("Unfortunately, there is no room for more classes.\n");
		return;
	}
	else {
		//we create a new class
		strcpy(uni->classes[uni->numOfClasses].name, name);
		strcpy(uni->classes[uni->numOfClasses].id, id);
		uni->classes[uni->numOfClasses].student = NULL;
		(uni->numOfClasses)++;
		//now we print that we added the class.
		printf("Class \"%s %s\" added.\n", id, name);
	}
}

/*
* Function Name: countCharInString
* Input: char str[] - string to count in, char chr - character to count in str.
* Output: int- number of times the char appears in the string.
* Function Operation: counts the number of times the char (char chr) appears in the string (char str[]).
*/
int countCharInString(char str[], char chr) {
	int counter = 0;
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == chr) {
			counter++;
		}
	}
	return counter;
}

/*
* Function Name: checkGradeValid
* Input: char grade[] - grade to check.
* Output: int: FALSE(=0) - the grade is not valid. TRUE(=1) - the grade is valid.
* Function Operation: checks if the grade got is a valid grade.
*					valid grade = between 0 and 100, the whole string is a number, max length 3.
*/
int checkGradeValid(char grade[]) {
	//if the grade is empty, too long, or not a number (has chars which are not digits).
	if (grade == NULL || strlen(grade) > MAX_LENGTH_OF_GRADE || !isStringNumber(grade)) {
		return FALSE;
	}
	//if the number is not a grade between 0 and 100.
	if (atoi(grade) > MAX_GRADE || atoi(grade) < MIN_GRADE) {
		return FALSE;
	}
	//if we got here, means the grade is ok and valid.
	return TRUE;
}

/*
* Function Name: checkStudentName
* Input: char input[], char name[], Uni* uni
*		input - user input
*		name - address of name of student in getInputAddUpdateStudents().
* Output: int: FALSE(=0) - student name is not valid. TRUE(=1) - student name is valid.
* Function Operation: seperates the student name from the input of the user,
*					and checks if the name is a valid name.
*					if the name is valid, we save it in name[] got from getInputAddUpdateStudents().
*/
int checkStudentName(char input[], char name[], Uni* uni) {
	const int VALID_NUM_OF_COLONS = 1;
	int numOfColons = countCharInString(input, ':');
	//if the num of colons are not as needed to be, the input isn't valid.
	if (numOfColons != VALID_NUM_OF_COLONS) {
		return FALSE;
	}
	char* token = strtok(input, ":");
	if (token == NULL) {
		return FALSE;
	}
	//we clean the spaces at the start of the name.
	cleanSpacesAtStart(token, uni);
	//if the name is too long or short
	if (strlen(token) > MAX_LENGTH_OF_STUDENT_NAME || strlen(token) < MINIMUM_LENGTH_OF_NAME) {
		return FALSE;
	}
	//if the name is not alphabetical and spaces only.
	else if (!isStringAlphaAndSpaces(token)) {
		return FALSE;
	}
	//if the name is valid, we save it.
	strcpy(name, token);
	return TRUE;
}

/*
* Function Name: checkAndInitClassAndGrade
* Input: char classAndGrade[], PerStudent* student, int classIndex, Uni* uni
*		classAndGrade[] - a class id and grade entered by the user on the student:
*			example for a valid classAndGrade = "89110, 99"
*		student - the student to save new info in.
*		classIndex - index of class in the university.
*		uni - the university with the classes in it.
* Output: int: FALSE(=0) - class or grade are not valid. TRUE(=1) -  class and grade are valid.
* Function Operation: seperates the class and grade from each other and checks them,
*					if both of them are ok, we add them to the permanent student class.
*/
int checkAndInitClassAndGrade(char classAndGrade[], PerStudent* student, int classIndex, Uni* uni) {
	char id[MAX_LENGTH_INPUT+1];
	char grade[MAX_LENGTH_INPUT+1];
	char* token = strtok(classAndGrade, ",");
	if (token == NULL) {
		return FALSE;
	}
	strcpy(id, token);
	token = strtok(NULL, ",");
	if (token == NULL) {
		return FALSE;
	}
	strcpy(grade, token);
	//we clean the spaces at the start.
	cleanSpacesAtStart(id, uni);
	cleanSpacesAtStart(grade, uni);
	//if the id or grade are not valid.
	if (!checkIfIdValid(id) || !checkGradeValid(grade)) {
		//the class and grade part is not valid.
		return FALSE;
	}
	//if didn't find the class.
	if (findClass(uni, id) == FAILED) {
		//this class doens't exist
		return FALSE;
	}
	strcpy(student->classes[classIndex].id, id);
	student->classes[classIndex].grade = atoi(grade);
	student->numberOfClasses++;
	//if we got here, everything was ok.
	return TRUE;
}

/*
* Function Name: checkClassesAndGrades
* Input: int num, char classesGrades[][MAX_LENGTH_INPUT+1], PerStudent* student, Uni* uni
*		num - num of classes and grades got from the user to add the student to.
*		classesGrades[] - the class ids and grades entered by the user on the student:
*			example for a valid classesGrades[i] = "89110, 99"
*		uni - the university with the classes in it.
*		student - the student to save new info in.
* Output: int: FALSE(=0) - class or grade are not valid. TRUE(=1) -  class and grade are valid.
* Function Operation: on each class+grade block we call checkAndInitClassAndGrade(),
*					and check if the block is valid.
*					if one block of class+grade is not valid, we return FALSE.
*					else, we return TRUE.
*/
int checkClassesAndGrades(int num, char classesGrades[][MAX_LENGTH_INPUT+1], PerStudent* student, Uni* uni) {
	for (int i = 0; i < num; i++) {
		int isValid = checkAndInitClassAndGrade(classesGrades[i], student, i, uni);
		//if one of the parts (class id or grade) is not valid.
		if (!isValid) {
			return FALSE;
		}
	}
	//if we got here, means all the parts were ok.
	return TRUE;
}

/*
* Function Name: checkSecondPartOfInput
* Input: char input[], PerStudent* student, Uni* uni
*		input - user input.
*		uni - the university with the classes in it.
*		student - the student to save new info in.
* Output: int: FALSE(=0) - the second part isn't valid. TRUE(=1) - the second part is valid.
* Function Operation: check if the second part of the user input (after the student name) is valid or not.
*					using other functions: countCharInString(), checkClassesAndGrades().
*/
int checkSecondPartOfInput(char input[], PerStudent* student, Uni* uni) {
	input = strtok(NULL, ":");
	if (input == NULL) {
		return FALSE;
	}
	int numOfSemiColons = countCharInString(input, ';');
	int numOfSemiCommas = countCharInString(input, ',');
	//if something is wrong with the format of the command with the commas and the semi-colons
	if (numOfSemiColons != numOfSemiCommas || numOfSemiColons > uni->numOfClasses || numOfSemiColons < 1) {
		//means the input of grades is not valid
		return FALSE;
	}
	char* token = strtok(input, ";");
	if (token == NULL) {
		return FALSE;
	}
	char classesAndGrades[MAX_NUM_OF_CLASSES][MAX_LENGTH_INPUT+1];
	int indexOfCourse = 0;
	while (token != NULL) {
		strcpy(classesAndGrades[indexOfCourse], token);
		indexOfCourse++;
		token = strtok(NULL, ";");
	}
	return checkClassesAndGrades(indexOfCourse, classesAndGrades, student, uni);
}

/*
* Function Name: addOrUpdateStudent
* Input: Uni* uni, PerStudent studentToAdd
*		uni - the university with the classes in it.
*		studentToAdd - the student to add.
* Output: none
* Function Operation: adds/updates the student in the right classes with his grades.
*					using the permanent student struct PerStudent.
*/
void addOrUpdateStudent(Uni* uni, PerStudent studentToAdd) {
	//we go over all the classes of the student.
	for (int i = 0; i < studentToAdd.numberOfClasses; i++) {
		char* currentId = studentToAdd.classes[i].id;
		int currentClassIndex = findClass(uni, currentId);
		int currentGrade = studentToAdd.classes[i].grade;
		Student* student = findStudent(uni, currentId, studentToAdd.name);
		//if student already exists in the class.
		if (student != NULL) {
			student->grade = currentGrade;
			printf("Student \"%s\" updated on class \"%s %s\" with grade %d.\n"
				, studentToAdd.name, currentId, uni->classes[i].name, currentGrade);
		}
		//if student doesn't exists, add the student.
		else {
			Student* newStudent = (Student*) malloc(sizeof(Student));
			//if the malloc failed, we free al the classes and exit the program.
			if (newStudent == NULL) {
				freeAllClasess(uni);
				exit(1);
			}
			strcpy(newStudent->name, studentToAdd.name);
			newStudent->grade = currentGrade;
			newStudent->next = NULL;
			//if the class is empty.
			if (uni->classes[currentClassIndex].student == NULL) {
				uni->classes[currentClassIndex].student = newStudent;
			}
			//else, the class has some students.
			else {
				//we find the last student currently in class
				Student* lastStudent = findLastStudentRecursion(uni->classes[currentClassIndex].student);
				//we add the new student.
				lastStudent->next = newStudent;
			}
			printf("Student \"%s\" added to class \"%s %s\" with grade %d.\n"
				, studentToAdd.name, currentId, uni->classes[currentClassIndex].name, currentGrade);
		}
	}
}

/*
* Function Name: getInputAddUpdateStudents
* Input: Uni* uni - the university with the classes in it.
* Output: none
* Function Operation: gets the input for a new student, 
*					checks if the input was valid using checkStudentName() and checkGradesAddUpdateStudents().
*					if everything was valid, we add/update the student using addOrUpdateStudent().
*/
void getInputAddUpdateStudents(Uni* uni) {
	char input[MAX_LENGTH_INPUT+1];
	//here we get the input from the user.
	scanf(" %[^\n]", input);
	//we clean the spaces at the end of the input
	cleanSpacesAtEnd(input, uni);
	PerStudent studentToAdd;
	studentToAdd.numberOfClasses = 0;
	int isNameValid = checkStudentName(input, studentToAdd.name, uni);
	//if students name is not valid.
	if (!isNameValid) {
		printf("Error: invalid name, class number or grade.\n");
		return;
	}
	//checks the second part of the input, after the students name.
	int areGradesValid = checkSecondPartOfInput(input,&studentToAdd,uni);
	//if one of the grades is not valid. either to a course that doesnt exist, or not valid format, etc..
	if (!areGradesValid) {
		printf("Error: invalid name, class number or grade.\n");
		return;
	}
	//if we got here, everything was ok. so we update/add the grades.
	addOrUpdateStudent(uni, studentToAdd);
}

/*
* Function Name: saveStudentsInArray
* Input: Student** studentsSorted, Class class, int numStudents
*		studentsSorted: a sorted array of students
*		class: the class to take students from.
*		numStudents: the number of students in class.
* Output: none
* Function Operation: saves the students from the class given in an array.
*/
void saveStudentsInArray(Student** studentsSorted, Class class, int numStudents) {
	Student* student = class.student;
	int index = 0;
	while (student != NULL)
	{
		studentsSorted[index] = student;
		student = student->next;
		index++;
	}
}

/*
* Function Name: sortStudents
* Input: Student** studentsSorted, Class class, int numStudents
*		studentsSorted: a sorted array of students
*		class: the class to take students from.
*		numStudents: the number of students in class.
* Output: none
* Function Operation: saves the students in an array with saveStudentsInArray(),
*					then sorts it using bubble sort.
*/
void sortStudents(Student** studentsSorted, Class class, int numStudents) {
	//first we save the students in the array.
	saveStudentsInArray(studentsSorted, class, numStudents);
	//now we sort it using bubble sort.
	for (int i = 0; i < numStudents-1; i++) {
		for (int j = 0; j < numStudents - i - 1; j++) {
			//if we need to switch them with one another.
			if (strcmp(studentsSorted[j]->name,studentsSorted[j + 1]->name) > 0) {
				Student* temp = studentsSorted[j];
				studentsSorted[j] = studentsSorted[j + 1];
				studentsSorted[j + 1] = temp;
			}
		}
	}
}

/*
* Function Name: printStudents
* Input: Student** studentsSorted, int numStudents
*		studentsSorted: a sorted array of students
*		numStudents: num of student in array.
* Output: none
* Function Operation: gets a sorted array of students and prints it in the right format.
*/
void printStudents(Student** studentsSorted, int numStudents) {
	for (int i = 0; i < numStudents; i++) {
		printf("%s, %d\n", studentsSorted[i]->name, studentsSorted[i]->grade);
	}
}

/*
* Function Name: printClass
* Input: Uni* uni - the university with the classes in it.
* Output: none
* Function Operation: gets from the user what class to print,
*					checks if the input is valid,
*					if valid, sorts the students by dictionary order,
*					and prints the class (finds it with id entered) students using other functions.
*/
void printClass(Uni* uni) {
	char input[MAX_LENGTH_INPUT+1];
	scanf(" %[^\n]", input);
	//we try to find the class id entered.
	int classIndex = findClass(uni, input);
	//if the class id entered is not valid, or the class doesnt exist.
	if (!checkIfIdValid(input) || classIndex == FAILED) {
		printf("Error: invalid class number.\n");
		return;
	}
	Class class = uni->classes[classIndex];
	int numStudents = 0;
	//we count the number of students in class.
	numStudents = countStudents(class);
	if (numStudents == 0) {
		printf("Class \"%s %s\" has no students.\n",class.id,class.name);
		return;
	}
	printf("Class \"%s %s\" students:\n", class.id, class.name);
	//we have a array of pointers to the students
	Student** studentsSorted = (Student**) calloc(numStudents,sizeof(Student*));
	//if the calloc failed, we free al the classes and exit the program.
	if (studentsSorted == NULL) {
		freeAllClasess(uni);
		exit(1);
	}
	//we sort the students by a dictionary order.
	sortStudents(studentsSorted, class, numStudents);
	//now we print the sorted array of students
	printStudents(studentsSorted, numStudents);
	free(studentsSorted);
}

/*
* Function Name: printAggregationMenu
* Input: none
* Output: none
* Function Operation: prints the aggregation menu.
*/
void printAggregationMenu() {
	printf("Please select the aggregation method:\n"
		"\ta. Average Grade.\n"
		"\tb. Maximal Grade.\n"
		"\tc. Minimal Grade.\n"
		"\td. Sum.\n"
		"\te. Count.\n"
		"\t0. Return to the main menu.\n");
}

/*
* Function Name: printClassInfo
* Input: Class class, int numberToPrint
*		class - the class to print his info.
*		numberToPrint - the number to print.
* Output: none
* Function Operation: prints the message in the correct format,
*					with the class name and id, and the numberToPrint.
*/
void printClassInfo(Class class, int numberToPrint) {
	printf("%s %s, %d\n", class.id, class.name, numberToPrint);
}

/*
* Function Name: maxGrade
* Input: Class class - the class to calculate on his students.
* Output: int- the maximum grade in class.
* Function Operation: returns the maximum grade in class.
*/
int maxGrade(Class class) {
	int max = MIN_GRADE;
	Student* student = class.student;
	//we go over the students in class
	while (student != NULL)
	{
		//if we found a higher grade.
		if (max < student->grade) {
			max = student->grade;
		}
		student = student->next;
	}
	return max;
}

/*
* Function Name: minGrade
* Input: Class class - the class to calculate on his students.
* Output: int- the minimum grade in class.
* Function Operation: returns the minimum grade in class.
*/
int minGrade(Class class) {
	int min = MAX_GRADE;
	Student* student = class.student;
	//we go over the students in class
	while (student != NULL)
	{
		//if we found a lower grade.
		if (min > student->grade) {
			min = student->grade;
		}
		student = student->next;
	}
	return min;
}

/*
* Function Name: sumGrades
* Input: Class class - the class to calculate on his students.
* Output: int- sum of grades in class.
* Function Operation: returns the sum of grades in class.
*/
int sumGrades(Class class) {
	int sum = 0;
	Student* student = class.student;
	//we go over the students in class
	while (student != NULL)
	{
		sum += student->grade;
		student = student->next;
	}
	return sum;
}

/*
* Function Name: averageGrade
* Input: Class class - the class to calculate on his students.
* Output: int- the average grade in class.
* Function Operation: calculates and returns the average grade in class.
*					using countStudents() and sumGrades().
*/
int averageGrade(Class class) {
	//calculate the number of students
	int numStudents = countStudents(class);
	//calculate the sum of the grades
	int sumOfGrades = sumGrades(class);
	//we calculate the average. we calculate the average as float, then round it down using (int) casting.
	int average = (int)(sumOfGrades / (float)(numStudents));
	return average;
}

/*
* Function Name: handleAggregation
* Input: Uni* uni - the university with the classes in it.
* Output: none
* Function Operation: handles the aggregation operation.
*/
void handleAggregation(Uni* uni) {
	//if the systme is empty from classes.
	if (uni->numOfClasses == 0) {
		printf("Error: there are no classes.\n");
		return;
	}
	//we print the menu.
	printAggregationMenu();
	char input;
	scanf(" %c",&input);
	int(*f)(Class class);
	switch (input)
	{
		case '0':
			return;
			break;
		case 'a':
			f = averageGrade;
			break;
		case 'b':
			f = maxGrade;
			break;
		case 'c':
			f = minGrade;
			break;
		case 'd':
			f = sumGrades;
			break;
		case 'e':
			f = countStudents;
			break;
		default:
			printf("Error: you promised that the input will be ok ;)");
			return;
	}
	for (int i = 0; i < uni->numOfClasses; i++) {
		int numStudents = countStudents(uni->classes[i]);
		if (numStudents == 0) {
			printf("Class \"%s %s\" has no students.\n", uni->classes[i].id, uni->classes[i].name);
		}
		else {
			printClassInfo(uni->classes[i], f(uni->classes[i]));
		}
	}
}

/*
* Function Name: checkClasses
* Input: int numOfCommas, char ids[][LENGTH_OF_CLASS_ID + 1], Uni* uni
*		ids[][] - class ids the user wants to delete the student from.
*		uni - the university.
* Output: int: TRUE - classes are valid. FALSE - classes aren't valid.
* Function Operation: checks if the classes got from the user are valid and in the right format.
*/
int checkClasses(int numOfCommas, char ids[][LENGTH_OF_CLASS_ID + 1], Uni* uni) {
	char* token = strtok(NULL, ",");
	if (numOfCommas < 1 || numOfCommas > MAX_NUM_OF_CLASSES) {
		return FALSE;
	}
	int numOfClassIdsGot = 0;
	while(token != NULL){
		//we clean the spaces at start first.
		cleanSpacesAtStart(token, uni);
		//if the class id is not valid
		if (!checkIfIdValid(token)) {
			return FALSE;
		}
		//if class doesnt exist
		if (findClass(uni,token) == FAILED) {
			return FALSE;
		}
		strcpy(ids[numOfClassIdsGot], token);
		numOfClassIdsGot++;
		token = strtok(NULL, ",");
	}
	//if the number of class id's is not equal to the num of commas
	if (numOfClassIdsGot != numOfCommas) {
		return FALSE;
	}
	//if we got here, means everything is valid, so we return true.
	return TRUE;
}

/*
* Function Name: checkTwoCommandCharsSequenceString
* Input: char str[], char firstCommandChar, char secondCommandChar, Uni* uni
*		str - the string to check.
*		firstCommandChar - the first command char to search.
*		secondCommandChar - the second command char to search.
*		uni - the university.
* Output: int - TRUE - found a sequence.
*				FALSE - didn't find a sequence.
* Function Operation: check if there is a sequence of two of the first or the second char in the str.
*		for example, if firstCommandChar = ',' and secondCommandChar = ':'
*		then we are searching for one of the following: ",," or "::" or ":," or ",:".
*/
int checkTwoCommandCharsSequenceString(char str[], char firstCommandChar, char secondCommandChar, Uni* uni) {
	//if we got an empty str.
	if (str == NULL) {
		return FALSE;
	}
	int didFindSequence = FALSE;
	//we go over the str chars except the last one. we compare the char and the next char to the sequence we need.
	for (int i = 0; i < strlen(str)-1; i++) {
		//if we found a sequence of two command chars, like ",," "::" or ":," for example.
		if (str[i] == firstCommandChar && str[i + 1] == secondCommandChar) {
			didFindSequence = TRUE;
		}
		else if (str[i] == secondCommandChar && str[i + 1] == firstCommandChar) {
			didFindSequence = TRUE;
		}
		else if (str[i] == firstCommandChar && str[i + 1] == firstCommandChar) {
			didFindSequence = TRUE;
		}
		else if (str[i] == secondCommandChar && str[i + 1] == secondCommandChar) {
			didFindSequence = TRUE;
		}
	}
	return didFindSequence;
}

/*
* Function Name: isBasicSyntaxValid
* Input: char input[] - user input, Uni* uni - the university with the classes.
* Output: int - TRUE - the input is valid.
*				FALSE - the input isn't valid.
* Function Operation: check if the input is valid, for task 3.
*/
int isBasicSyntaxValid(char input[], Uni* uni) {
	
	/*
	calls the function with the right command chars. in the delete option, the command chars are ',' and ':'
	so the function will look for the following not valid sequences:
	1. ",,"
	2. "::"
	3. ",:"
	4. ":,"
	*/
	if (checkTwoCommandCharsSequenceString(input, ',', ':',uni)) {
		//if found such sequence, we return false because the input is not valid.
		return FALSE;
	}
	else {
		return TRUE;
	}
}

/*
* Function Name: checkIfStudentsExistsInAllCourses
* Input: char name[], char ids[][LENGTH_OF_CLASS_ID +1], int numClasses ,Uni* uni
*		ids[][]: the classes ids the user wants to delete the student from.
*		name: the name of the student to check.
*		numClasses: num of classes the user wants to delete the student
*		uni - the university with the classes in it.
* Output: int - TRUE - the student is in all the courses from char ids[][].
*				FALSE - the student isn't in all the courses from char ids[][].
* Function Operation: check if the student is in all the courses from char ids[][].
*					if not, prints an error message.
*/
int checkIfStudentsExistsInAllCourses(char name[], char ids[][LENGTH_OF_CLASS_ID +1], int numClasses ,Uni* uni) {
	for (int i = 0; i < numClasses; i++) {
		char classId[MAX_LEN_CLASS_NAME + 1];
		strcpy(classId, ids[i]);
		//if we didn't find the student in class, we print an error message.
		if (findStudent(uni,classId,name) == NULL) {
			int classIndex = findClass(uni, classId);
			char className[MAX_LEN_CLASS_NAME + 1];
			strcpy(className, uni->classes[classIndex].name);
			printf("Error: student is not a member of class \"%s %s\".\n",classId,className);
			return FALSE;
		}
	}
	//if we got here, means everything was ok.
	return TRUE;
}

/*
* Function Name: countClassesStudentIn
* Input: char name[] - name of student, Uni* uni - university with the classes in it.
* Output: int - number of classes the student is in.
* Function Operation: counts the number of classes the student is in.
*/
int countClassesStudentIn(char name[], Uni* uni) {
	int counter = 0;
	for (int i = 0; i < uni->numOfClasses; i++) {
		Class class = uni->classes[i];
		//if found student in class
		if (findStudent(uni, class.id, name) != NULL) {
			//we add to the counter
			counter++;
		}
	}
	return counter;
}

/*
* Function Name: findStudentPreviousRec
* Input: Student* studentToFind, Student* current
*		studentToFind - pointer to the student to find.
*		current - used for the recursion to go over the students.
* Output: Student* - pointer to the student needed to find.
* Function Operation: recursive function that finds the previous student in the linked list,
*					the student is previous to the student Student* studentToFind recieved.
*/
Student* findStudentPreviousRec(Student* studentToFind, Student* current) {
	//if the current student is previous to the one we got.
	if(current->next == studentToFind){
		//means we found the student we needed, so we return the pointer to him.
		return current;
	}
	else if (current->next == NULL) {
		return NULL;
	}
	else {
		//if didn't find, continue searching on to the next student.
		findStudentPreviousRec(studentToFind, (current->next));
	}
}

/*
* Function Name: deleteStudent
* Input: Uni* uni, char classId[], char name[]
*		Uni* uni - the university with the classes in it.
*		classId - the class to delete the student from.
*		name - the name of the student to delete.
* Output: none
* Function Operation: deletes the student named char name[] from the class which id is char classId[].
*/
void deleteStudent(Uni* uni, char classId[], char name[]) {
	int classIndex = findClass(uni, classId);
	Student* currentStudent = findStudent(uni, classId, name);
	//if failed to find the student
	if (currentStudent == NULL) {
		return;
	}
	Class class = uni->classes[classIndex];
	printf("Student \"%s\" removed from class \"%s %s\".\n",name,class.id,class.name);
	//if the first student of the class is the current student
	if (class.student == currentStudent) {
		uni->classes[classIndex].student = currentStudent->next;
		//we delete the student
		free(currentStudent);
		return;
	}
	//else, the student is not the first of his class. so we find the student that comes before him.
	Student* studentBeforeCurrent = findStudentPreviousRec(currentStudent, class.student);
	if (studentBeforeCurrent != NULL) {
		studentBeforeCurrent->next = currentStudent->next;
		//we delete the student
		free(currentStudent);
	}
}

/*
* Function Name: checkIfIdExistedBefore
* Input: char ids[][LENGTH_OF_CLASS_ID + 1], char id[], int idIndex.
*		ids[][]: the classes ids to delete the student from.
*		id: the id to check if appeared before.
*		idIndex: the index to check before (in the array).
* Output: int: TRUE - the id(char id[]) exists in the array before index (int idIndex)
*				FALSE - the id doens't appear in the array from beggining to index idIndex
* Function Operation: check if id(char id[]) exists in the array before index (int idIndex)
*/
int checkIfIdExistedBefore(char ids[][LENGTH_OF_CLASS_ID + 1], char id[], int idIndex) {
	//goes over all the ids before the current one.
	for (int i = 0; i < idIndex; i++) {
		//if its a blank string,  we just continue to the next one.
		if (strcmp(ids[i],"") == 0) {
			continue;
		}
		//if we found the same id before, in the array.
		if (strcmp(ids[i], id) == 0) {
			return TRUE;
		}
	}
	//if we got here, means the id didn't appear before in the array.
	return FALSE;
}

/*
* Function Name: countAndInitDifferentCourses
* Input: char ids[][LENGTH_OF_CLASS_ID + 1], int len
*		ids[][]: the classes ids to delete the student from.
*		len: num of classes to delete from.
* Output: int: num of different ids in the array of ids.
* Function Operation: delete duplicats in the ids array and count the number of different ids in it.
*/
int countAndInitDifferentCourses(char ids[][LENGTH_OF_CLASS_ID + 1], int len) {
	int numOfDifferentCourses = 0;
	for (int i = 0; i < len; i++) {
		//if the id apeared before, in the list, we delete it.
		if (checkIfIdExistedBefore(ids, ids[i],i)) {
			strcpy(ids[i],"");
		}
		//else, the id didn't appear before, so it's a new one. we up the counter and keep it.
		else { 
			numOfDifferentCourses++; 
		}
	}
	return numOfDifferentCourses;
}

/*
* Function Name: deleteFromClasses
* Input: char name[], char ids[][LENGTH_OF_CLASS_ID + 1], int length, Uni* uni.
*		name[]: students name.
*		ids[][]: the classes ids to delete the student from.
*		length: num of classes to delete from.
*		Uni* uni - the university with the classes in it.
* Output: none
* Function Operation: check if the student is indeed in every course,
*					checks if user wants to delete the student from all the classes he is taking.
*					if everything was ok, we delete the student from all the classes requested.
*/
void deleteFromClasses(char name[], char ids[][LENGTH_OF_CLASS_ID + 1], int length, Uni* uni) {
	//first we go over the courses to check if the student is in every one of them.
	int isStudentInEveryCourse = checkIfStudentsExistsInAllCourses(name, ids, length, uni);
	//if the student is not in one of the courses, we exit the function and dont delete from any course.
	if (!isStudentInEveryCourse) {
		return;
	}
	int numCoursesStudentIn = countClassesStudentIn(name, uni);
	int numOfDifferentCourses = countAndInitDifferentCourses(ids, length);
	//if the user wants to delete a student from all the courses he is in.
	if (numCoursesStudentIn == numOfDifferentCourses) {
		printf("Error: student cannot be removed from all classes.\n");
		return;
	}
	//if we got here, everything is fine. so we will delete him from the classes now.
	for (int i = 0; i < length; i++) {
		//if its a blank string (means there was a duplicate here before), we continue to the next one.
		if (strcmp(ids[i], "") == 0) {
			continue;
		}
		//if the class exists and everything is ok, we delete the student from the class.
		deleteStudent(uni,ids[i],name);
	}
}

/*
* Function Name: handleDeleteStudent
* Input: Uni* uni - the university with the classes in it.
* Output: none
* Function Operation: handles the delete student operation.
*					first we check if the basic syntax of the input is valid, using isBasicSyntaxValid()
*					then we check is the studnet name entered is valid, using checkStudentName()
*					then we check if classes entered are valid, using checkClasses()
*					if everything was ok we call deleteFromClasses() to proceed.
*/
void handleDeleteStudent(Uni* uni) {
	char input[MAX_LENGTH_INPUT + 1];
	//here we get the input from the user.
	scanf(" %[^\n]", input);
	//we clean the spaces at the end of the input
	cleanSpacesAtEnd(input, uni);
	int numOfCommas = countCharInString(input, ',');
	char studentName[MAX_LENGTH_OF_STUDENT_NAME + 1];
	//if the command is not valid (we have ":," or ",," for example. which is not valid.)
	if (!isBasicSyntaxValid(input, uni)) {
		printf("Error: invalid name or class number.\n");
		return;
	}
	int isNameVaild = checkStudentName(input, studentName, uni);
	//if the name is not valid.
	if (!isNameVaild) {
		printf("Error: invalid name or class number.\n");
		return;
	}
	char classesIds[MAX_NUM_OF_CLASSES][LENGTH_OF_CLASS_ID + 1] = { {0} };
	int areClassesValid = checkClasses(numOfCommas, classesIds, uni);
	//if the classes are not valid.
	if (!areClassesValid) {
		printf("Error: invalid name or class number.\n");
		return;
	}
	//if we got here, means the input is valid and the classes in the classesIds are valid.
	deleteFromClasses(studentName, classesIds, numOfCommas, uni);
}

/*
* Function Name: chooseWhoToCall
* Input: char option - the char the user entered, Uni* uni - the university with the classes in it.
* Output: int: TRUE - need to exit the program, FALSE - don't need to exit the program.
* Function Operation: gets the input (in char option) and chooses who to call,
*						based on the option entered from the user.
*/
int chooseWhoToCall(char option, Uni* uni) {
	int didPrintMenu = FALSE;
	void(*func)(Uni*);
	switch (option)
	{
		case '0':
			//we free the alocated memory before we exit the program.
			freeAllClasess(uni);
			//we need to exit the program, so we return TRUE.
			return TRUE;
		case '1':
			func = insertUpdateClass;
			break;
		case '2':
			func = getInputAddUpdateStudents;
			break;
		case '3':
			func = handleDeleteStudent;
			break;
		case '4':
			func = printClass;
			break;
		case '5':
			func = handleAggregation;
			break;
		case '6':
			printRightMenu(TRUE);
			didPrintMenu = TRUE;
			func = NULL;
			break;
		default:
			printf("Error: unrecognized operation.\n");
			func = NULL;
	}
	//if didn't print the menu again, and didn't have problems with the input.
	if(func != NULL){
		func(uni);
	}
	//if didn't print the menu, print it.
	if (!didPrintMenu) {
		printRightMenu(FALSE);
	}
	//dont need to exit.
	return FALSE;
}

/*
* Function Name: handleOporations
* Input: Uni* uni - the university with the classes in it.
* Output: none
* Function Operation: runs the whole program and handles all the stuff.
*					calls the function to print the menu when needed,
*					gets input from the user and calls chooseWhoToCall().
*/
void handleOporations(Uni* uni) {
	char option;
	//the first time, it prints the full menu.
	printRightMenu(TRUE);
	//we are going to exit anyway when the user enters 0.
	while(TRUE)
	{
		scanf(" %c", &option);
		//the function chooseWhoToCall() returns TRUE if the user asked to exit the program.
		int needToExit = chooseWhoToCall(option, uni);
		if (needToExit)
			return;
	}
}
