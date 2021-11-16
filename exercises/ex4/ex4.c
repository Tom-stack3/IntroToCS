#include "ex4.h"
#include <string.h>
#define TRUE 1
#define FALSE 0
#define FAILED -1
#define NUM_OF_DIGITS_BASE_10 10
#define ZERO_CHAR ('0')

/*
* Function Name: CharDigitToInt
* Input: char digitC - (valid inputs: '0','1','2','3','4','5','6','7','8' or '9')
* Output: int
* Function Operation: gets a char that represents a digit,
*					and returns the digit which is represented in the char
*/
int charDigitToInt(char digitC) {
	return (int)(digitC - ZERO_CHAR);
}

/*
* Function Name: stringToInt
* Input: char str[]
* Output: int - FAILED(=-1) - if the number in the string is too big (for current SIZE).
*				if the number in the string is ok, we use charDigitToInt(), and return the number.
* Function Operation: gets a string, check validity compared to the SIZE, returns the number.
*/
int stringToInt(char str[]) {
	//we got an empty string
	if (str == NULL) {
		return FAILED;
	}

	int result;
	//we have one char.
	if (strlen(str) == 1) {
		result = charDigitToInt(str[0]);
		//not a valid char, for the size
		if (result > SIZE * SIZE || result < 0) {
			return FAILED;
		}
		return charDigitToInt(str[0]);
	}

	/*
	the string is longer then 1 char. means the number is too big because the max SIZE is 3.
	so max int of row is 9.
	*/
	else {
		return FAILED;
	}
}

/*
* Function Name: calcNumOfSpaces
* Input: char letter
* Output: int - FAILED(=-1) - if the number of spaces represented by char is too large for the SIZE.
*				if the char was ok, we return the number of spaces represented by the char.
* Function Operation: gets a char, check validity compared to the SIZE, returns the number of spaces.
*/
int calcNumOfSpaces(char letter) {
	
	/*
	couple examples to the calculation:
	'a' - 'a' + 1 = 1
	'b' - 'a' + 1 = 2
	'e' - 'a' + 1 = 5
	*/
	int numOfSpaces = letter - 'a' + 1;
	if (0 < numOfSpaces && numOfSpaces <= SIZE * SIZE) {
		return numOfSpaces;
	}
	//the char is too large for the SIZE, which means it just represents an unknown in the sudoku.
	else {
		return FAILED;
	}
}

/*
* Function Name: putSpaces
* Input: char board[][SIZE * SIZE], int numOfSpaces, int startIndex, int row.
*		valid values: 0 <= numOfSpaces <=SIZE*SIZE, 0 <= startIndex <= SIZE*SIZE, 0 <= row <= SIZE*SIZE
* Output: none
* Function Operation: puts a number of spaces as required, in the row (int row)
*					starting from the index (int startIndex) in the column.
*/
void putSpaces(char board[][SIZE * SIZE], int numOfSpaces, int startIndex, int row) {
	if (numOfSpaces < 0) {
		return;
	}
	//runs until we put exactly as much spaces as int numOfSpaces.
	while (numOfSpaces > 0) {
		//puts the spaces in the right places
		board[row][startIndex + numOfSpaces - 1] = ' ';
		--numOfSpaces;
	}
}

/*
* Function Name: checkIfBoardStrValid
* Input: char str[].
* Output: int TRUE(=1) - if the str that represents the board is valid.
*		int FALSE(=0) if the str that represents the board is not valid.
* Function Operation: goes over the str chars, and checks if str that represents the board is valid.
*/
int checkIfBoardStrValid(char str[]) {
	int index = 0;
	int lengthOfColumn = 0;
	int numOfRows = 0;

	//goes over the chars.
	while (index < strlen(str)) {
		//the char is a regular char.
		if ('1' <= str[index] && str[index] <= ZERO_CHAR + SIZE * SIZE) {
			lengthOfColumn += 1;
		}
		//if the row ended, we check the length of it.
		else if (str[index] == '/') {
			//the row is too long.
			if (lengthOfColumn > SIZE * SIZE) {
				return FALSE;
			}
			//the row is valid, so we move on to the next row.
			else {
				lengthOfColumn = 0;
				numOfRows++;
			}
		}
		//the char represents a number of spaces.
		else if ('a' <= str[index] && str[index] <= 'z' && calcNumOfSpaces(str[index]) != FAILED) {
			lengthOfColumn += calcNumOfSpaces(str[index]);
		}
		//other char, some variable.
		else {
			lengthOfColumn += 1;
		}
		index++;
	}

	//if the last column is longer than is should be. the str is not valid.
	if (lengthOfColumn > SIZE * SIZE) {
		return FALSE;
	}

	//if there are less or more rows than should be. the str is not valid.
	if (numOfRows != SIZE * SIZE - 1) {
		return FALSE;
	}

	//the board str is valid.
	return TRUE;
}

/*
* Function Name: checkIfBoardStrValid
* Input: char board[][SIZE * SIZE], char str[]
* Output: none
* Function Operation: goes over the str chars, and creates the board according to the str[].
*/
void createBoard(char board[][SIZE * SIZE], char str[]) {
	const int NUM_OF_CHARS_IN_BOARD = SIZE * SIZE * SIZE * SIZE;
	const int NUM_OF_SLASHES_IN_STR = SIZE * SIZE - 1;
	const int NUM_OF_COLUMNS_IN_ROW = SIZE * SIZE;

	//if the board str is not valid.
	if (checkIfBoardStrValid(str) == FALSE) {
		printf("Error\n");
		return;
	}
	//else, the board str is valid. so we are going to change it.
	int index = 0;
	int row = 0;
	int column = 0;
	//runs until the end of the str.
	while (index < strlen(str)) {
		//the char is a digit.
		if ('1' <= str[index] && str[index] <= ZERO_CHAR + SIZE * SIZE) {
			//we put it in the board.
			board[row][column] = str[index];
			column++;
		}
		//the char is '/', so means we ended the row, but it's too short. so put spaces until the end of it.
		else if (str[index] == '/' && column < NUM_OF_COLUMNS_IN_ROW) {
			//we put the spaces in the right places in the board.
			putSpaces(board, NUM_OF_COLUMNS_IN_ROW - column, column, row);
			column = 0;
			row++;
		}
		//the char is '/', so means a new row. we ended the row.
		else if (str[index] == '/' && column == NUM_OF_COLUMNS_IN_ROW) {
			column = 0;
			row++;
		}
		//the char represents a number of spaces. so we calculate it.
		else if ('a' <= str[index] && str[index] <= 'z' && calcNumOfSpaces(str[index]) != FAILED) {
			//we calculate  the ammount of spaces represented.
			int numOfSpaces = calcNumOfSpaces(str[index]);
			//we put the spaces in the right places in the board.
			putSpaces(board, numOfSpaces, column, row);
			column += numOfSpaces;
		}
		//other char, some variable.
		else {
			//we put it in the board.
			board[row][column] = str[index];
			column++;
		}
		index++;
	}

	//if the str ends but still needs to add spaces in the end of the board, because it's too short.
	if (column < NUM_OF_COLUMNS_IN_ROW) {
		//we calculate the num of spaces that need to be filled in the end.
		int numSpacesFilledInTheEnd = NUM_OF_COLUMNS_IN_ROW - column;
		//we add the spaces.
		putSpaces(board, numSpacesFilledInTheEnd, column, row);
	}
}

/*
* Function Name: printBoard
* Input: char board[][SIZE*SIZE].
* Output: none
* Function Operation: prints the board in the right way.
*/
void printBoard(char board[][SIZE * SIZE]) {
	//goes over the rows.
	for (int row = 0; row < SIZE*SIZE; row++)
	{
		int cubeNum = 0;
		//prints the first SIZE-1 cube parts of the column.
		for (cubeNum = 0; cubeNum < SIZE - 1; cubeNum++) {
			for (int i = 0; i < SIZE; i++) {
				printf("%c", board[row][cubeNum*SIZE + i]);
			}
			//prints the border line in the column between the cube parts.
			printf(" | ");
		}
		//prints the last cube part in the column.
		for (int i = 0; i < SIZE; i++) {
			printf("%c", board[row][cubeNum*SIZE + i]);
		}
		printf("\n");
		//if we printed another SIZE rows, we print an additional new line.
		if ((row + 1) % SIZE == 0) {
			printf("\n");
		}
	}
}

/*
* Function Name: RunReplaceAll
* Input: char board[][SIZE * SIZE], char oldChar, char newChar
* Output: none
* Function Operation: replaces all the occurences of oldChar to newChar.
*					if one of the chars (oldChar or newChar) is a special space char, a space, a slash ('/')
*					or if the oldChar wasn't found in the board, we print an error message.
*/
void RunReplaceAll(char board[][SIZE * SIZE], char oldChar, char newChar) {
	int isInTheBoard = FALSE;
	//check if one of the chars is a space special char.
	if (calcNumOfSpaces(oldChar) != FAILED || calcNumOfSpaces(newChar) != FAILED) {
		printf("Error\n");
		return;
	}
	//check if one of the chars is a '/'.
	if (oldChar == '/' || newChar == '/') {
		printf("Error\n");
		return;
	}
	//check if one of the chars is a space.
	if (oldChar == ' ' || newChar == ' ') {
		printf("Error\n");
		return;
	}
	//runs on all the rows in the board.
	for (int row = 0; row < SIZE*SIZE; row++)
	{
		//runs on all the chars in the row.
		for (int column = 0; column < SIZE*SIZE; column++) {
			//if the char is the one we are supposed to replace.
			if (board[row][column] == oldChar) {
				//if we found one, means the old char is in the board.
				isInTheBoard = TRUE;
				//we replace the char with the new char.
				board[row][column] = newChar;
			}
		}
	}
	//the char we were supposed to replace is not in the board.
	if (isInTheBoard == FALSE) {
		printf("Error\n");
		return;
	}
}

/*
* Function Name: change
* Input: char board[][SIZE * SIZE], int locationRow, int locationCol, char newChar
* Output: none
* Function Operation: changes the char in the location specified [locationRow,locationCol] for char newChar.
*					if the char (newChar) is a special space char, a space, a slash ('/')
*					or if one of the locations in not valid or too large, we print an error message.
*					also, if the char in the place to replace is a space, we print an error message.
*/
void change(char board[][SIZE * SIZE], int locationRow, int locationCol, char newChar) {
	int isValid = TRUE;
	const int LAST_INDEX_OF_ROW_OR_COL = SIZE * SIZE - 1;
	//if one of the locations in not valid. we print an Error. either empty, or more than one digit
	if (locationRow == FAILED || locationCol == FAILED) {
		isValid = FALSE;
	}
	//if one of the locations is two large for the current SIZE.
	else if (locationCol > LAST_INDEX_OF_ROW_OR_COL || locationRow > LAST_INDEX_OF_ROW_OR_COL) {
		isValid = FALSE;
	}
	//forbidden to change a location with a space.
	else if (board[locationRow][locationCol] == ' ') {
		isValid = FALSE;
	}
	//check if the char is a space special char.
	else if (calcNumOfSpaces(newChar) != FAILED) {
		isValid = FALSE;
	}
	//check if the char is a '/' or a space.
	else if (newChar == '/' || newChar == ' ') {
		isValid = FALSE;
	}

	if (isValid == FALSE) {
		printf("Error\n");
		return;
	}
	//else, everthing is valid.
	else {
		//we replace the char in the location for the new char.
		board[locationRow][locationCol] = newChar;
	}

}

/*
* Function Name: add
* Input: char board[][SIZE * SIZE], int locationRow, int locationCol, char newChar
* Output: none
* Function Operation: adds the new char in the location specified [locationRow,locationCol].
*					if the char (newChar) is a special space char, a space, a slash ('/')
*					or if one of the locations in not valid or too large, we print an error message.
*					also, if the char in the place to add is not a space, we print an error message.
*/
void add(char board[][SIZE * SIZE], int locationRow, int locationCol, char newChar) {
	int isValid = TRUE;
	const int LAST_INDEX_OF_ROW_OR_COL = SIZE * SIZE - 1;
	//if one of the locations in not valid.  we print an Error. either empty, or more than one digit.
	if (locationRow == FAILED || locationCol == FAILED) {
		isValid = FALSE;
	}
	//if one of the locations is two large for the current SIZE.
	else if (locationCol > LAST_INDEX_OF_ROW_OR_COL || locationRow > LAST_INDEX_OF_ROW_OR_COL) {
		isValid = FALSE;
	}
	//forbidden to add to a location without a space.
	else if (board[locationRow][locationCol] != ' ') {
		isValid = FALSE;
	}
	//check if the char is a space special char.
	else if (calcNumOfSpaces(newChar) != FAILED) {
		isValid = FALSE;
	}
	//check if the char is a '/'.
	else if (newChar == '/') {
		isValid = FALSE;
	}
	//check if the char is a space.
	else if (newChar == ' ') {
		isValid = FALSE;
	}

	if (isValid == FALSE) {
		printf("Error\n");
		return;
	}
	//else, everthing is valid.
	else {
		//we add the the new char in the location.
		board[locationRow][locationCol] = newChar;
	}
}

/*
* Function Name: delete
* Input: char board[][SIZE * SIZE], int locationRow, int locationCol
* Output: none
* Function Operation: deletes the char in the location specified [locationRow,locationCol].
*					if the char is a space, 
*					or if one of the locations in not valid or too large, we print an error message.
*/
void delete(char board[][SIZE * SIZE], int locationRow, int locationCol) {
	int isValid = TRUE;
	const int LAST_INDEX_OF_ROW_OR_COL = SIZE * SIZE - 1;
	//if one of the locations in not valid. we print an Error. either empty, or more than one digit.
	if (locationRow == FAILED || locationCol == FAILED) {
		isValid = FALSE;
	}
	//if one of the locations is two large for the current SIZE.
	else if (locationCol > LAST_INDEX_OF_ROW_OR_COL || locationRow > LAST_INDEX_OF_ROW_OR_COL) {
		isValid = FALSE;
	}
	//forbidden to delete a space.
	else if (board[locationRow][locationCol] == ' ') {
		isValid = FALSE;
	}

	if (isValid == FALSE) {
		printf("Error\n");
		return;
	}
	//else, everthing is valid.
	else {
		//we delete the char in the location.
		board[locationRow][locationCol] = ' ';
	}
}

/*
* Function Name: countCommas
* Input: char str[]
* Output: int - the number of commas in the string.
* Function Operation: gets a string and counts and returns the number of commas in the string.
*/
int countCommas(char str[]) {
	int counter = 0;
	//go over the string chars.
	for (int i = 0; i < strlen(str); i++) {
		//if we found a comma, up the counter.
		if (str[i] == ',')
			counter++;
	}
	return counter;
}

int putStringInPlace(char str[], char *destination) {
	//first we check if one of the pointers is NULL
	if (str == NULL || destination == NULL) {
		//we return FAILED (= -1) .
		return FAILED;
	}
	//now we check the length of the str[]
	if (strlen(str) > 1) {
		//we return FAILED (= -1) .
		return FAILED;
	}
	else {
		//we put the value in the destination.
		*destination = str[0];
		//everything went ok, so we return TRUE (= 1).
		return TRUE;
	}
}

/*
* Function Name: getMove
* Input: char str[], char board[][SIZE*SIZE]. 
* Output: none
* Function Operation: goes over the str chars, and creates the board according to the str[].
*/
int getMove(char str[], char board[][SIZE*SIZE]) {
	char COMMAND_DELIM[] = ",";
	int validNumOfCommasForCommand = 0;
	int numOfCommasInCommand = countCommas(str);
	char* token = strtok(str, COMMAND_DELIM);
	//if the command was replaceAll
	if (strcmp(token, "replaceAll") == 0) {
		validNumOfCommasForCommand = 2;
		//first we check if there are not too many or too few commas.
		if (numOfCommasInCommand != validNumOfCommasForCommand) {
			return FAILED;
		}
		//here we prepare the arguments and call RunReplaceAll().

		token = strtok(NULL, COMMAND_DELIM);
		char oldChar;
		//puts token in oldChar and checks if failed.
		if (putStringInPlace(token, &oldChar) == FAILED) {
			return FAILED;
		}
		token = strtok(NULL, COMMAND_DELIM);
		char newChar;
		//puts token in newChar and checks if failed.
		if (putStringInPlace(token, &newChar) == FAILED) {
			return FAILED;
		}
		RunReplaceAll(board, oldChar, newChar);
		//the command was valid in terms of commas. other problems with the input are checked in RunReplaceAll().
		return TRUE;
	}
	//if the command was change
	else if (strcmp(token, "change") == 0) {
		validNumOfCommasForCommand = 3;
		//first we check if there are not too many or too few commas.
		if (numOfCommasInCommand != validNumOfCommasForCommand) {
			return FAILED;
		}

		token = strtok(NULL, COMMAND_DELIM);
		int locationRow = stringToInt(token);
		token = strtok(NULL, COMMAND_DELIM);
		int locationCol = stringToInt(token);
		token = strtok(NULL, COMMAND_DELIM);
		char newChar;
		//puts token in newChar and checks if failed.
		if (putStringInPlace(token, &newChar) == FAILED) {
			return FAILED;
		}
		change(board, locationRow, locationCol, newChar);

		//the command was valid in terms of commas. other problems with the input are checked in change().
		return TRUE;
	}
	//if the command was add
	else if (strcmp(token, "add") == 0) {
		validNumOfCommasForCommand = 3;
		//first we check if there are not too many or too few commas.
		if (numOfCommasInCommand != validNumOfCommasForCommand) {
			return FAILED;
		}

		token = strtok(NULL, COMMAND_DELIM);
		int locationRow = stringToInt(token);
		token = strtok(NULL, COMMAND_DELIM);
		int locationCol = stringToInt(token);
		token = strtok(NULL, COMMAND_DELIM);
		char newChar;
		//puts token in newChar and checks if failed.
		if (putStringInPlace(token, &newChar) == FAILED) {
			return FAILED;
		}

		add(board, locationRow, locationCol, newChar);
		//the command was valid in terms of commas. other problems with the input are checked in add().
		return TRUE;
	}
	//if the command was delete
	else if (strcmp(token, "delete") == 0) {
		validNumOfCommasForCommand = 2;
		//first we check if there are not too many or too few commas.
		if (numOfCommasInCommand != validNumOfCommasForCommand) {
			return FAILED;
		}

		token = strtok(NULL, COMMAND_DELIM);
		int locationRow = stringToInt(token);
		token = strtok(NULL, COMMAND_DELIM);
		int locationCol = stringToInt(token);
		delete(board, locationRow, locationCol);
		//the command was valid in terms of commas. other problems with the input are checked in delete().
		return TRUE;
	}
	//if we got here, the command is not vaild. so we return FAILED.
	return FAILED;
}

/*
* Function Name: makeMove
* Input: char board[][SIZE*SIZE], char move[].
* Output: none
* Function Operation: calls getMove(). if getMove() failed (returned -1), we print an error message.
*/
void makeMove(char board[][SIZE*SIZE], char move[]) {
	int moveGot = getMove(move, board);
	//if the command was not valid.
	if (moveGot == FAILED) {
		printf("Error\n");
	}
}

/*
* Function Name: testRows
* Input: char board[][SIZE*SIZE].
* Output: int - FALSE(=0) if the rows are not correct.
*		TRUE(=1) if the rows are correct.
* Function Operation: goes over the board rows, checks and returns if they are correct.
*					correct means: 1. only spaces and digits, without any unknowns.
*									2. each digit appears not more than one time in each row.
*/
int testRows(char board[][SIZE * SIZE]) {
	/*
	for every digit there is a counter.
	if the digit 0 appeared for example, we up the counter by 1 in the index 0. (numOfTimesEachNumAppeared[0]++)
	*/
	int numOfTimesEachNumAppeared[NUM_OF_DIGITS_BASE_10] = { 0 };
	for (int row = 0; row < SIZE*SIZE; row++) {
		int currentNumOfSpacesInRow = 0;
		for (int column = 0; column < SIZE*SIZE; column++) {
			char currentChar = board[row][column];
			//the char is a space, we continue
			if (currentChar == ' ') {
				continue;
			}
			//the char is a digit
			else if (currentChar >= '1' && currentChar <= ZERO_CHAR + SIZE * SIZE) {
				int currentDigit = charDigitToInt(currentChar);
				//we up the counter in the right index.
				numOfTimesEachNumAppeared[currentDigit]++;
			}
			//the char isn't a digit or a space. so the row is not correct.
			else {
				return FALSE;
			}
		}

		/*
		we are done going over the row. now we check the counter.
		if everything is ok we reset the counter back to zero. and go check the next row.
		*/
		for (int i = 0; i < 10; i++) {
			//if a digit appeared more than one time, the row is not correct.
			if (numOfTimesEachNumAppeared[i] > 1) {
				return FALSE;
			}
			//else, everything was ok with that row. so we continue checking.
			numOfTimesEachNumAppeared[i] = 0;
		}
	}
	//if we got here, means all the rows were correct. so we return TRUE.
	return TRUE;
}

/*
* Function Name: testColumns
* Input: char board[][SIZE*SIZE].
* Output: int - FALSE(=0) if the columns are not correct.
*		TRUE(=1) if the columns are correct.
* Function Operation: goes over the board columns, checks and returns if they are correct.
*					correct means: 1. only spaces and digits, without any unknowns.
*									2. each digit appears not more than one time in each column.
*/
int testColumns(char board[][SIZE * SIZE]) {

	/*
	for every digit there is a counter.
	if the digit 4 appeared for example, we up the counter by 1 in the index 4. (numOfTimesEachNumAppeared[4]++)
	*/
	int numOfTimesEachNumAppeared[NUM_OF_DIGITS_BASE_10] = { 0 };
	for (int column = 0; column < SIZE*SIZE; column++) {
		int currentNumOfSpacesInColumn = 0;
		for (int row = 0; row < SIZE*SIZE; row++) {
			char currentChar = board[row][column];
			//the char is a space, we continue
			if (currentChar == ' ') {
				continue;
			}
			//the char is a digit
			else if (currentChar >= '1' && currentChar <= ZERO_CHAR + SIZE * SIZE) {
				int currentDigit = charDigitToInt(currentChar);
				//we up the counter in the right index.
				numOfTimesEachNumAppeared[currentDigit]++;
			}
			//the char isn't a digit or a space. so the column is not correct.
			else {
				return FALSE;
			}
		}

		/*
		we are done going over the column. now we check the counter.
		if everything is ok we reset the counter back to zero. and go check the next column.
		*/
		for (int i = 0; i < 10; i++) {
			//if a digit appeared more than one time, the column is not correct.
			if (numOfTimesEachNumAppeared[i] > 1) {
				return FALSE;
			}
			//else, everything was ok with that column. so we continue checking.
			numOfTimesEachNumAppeared[i] = 0;
		}
	}
	//if we got here, means all the columns were correct. so we return TRUE.
	return TRUE;
}

/*
* Function Name: testCubes
* Input: char board[][SIZE*SIZE].
* Output: int - FALSE(=0) if the cubes are not correct.
*		TRUE(=1) if the cubes are correct.
* Function Operation: goes over the board cubes, checks and returns if they are correct.
*					correct means: 1. only spaces and digits, without any unknowns.
*									2. each digit appears not more than one time in each cube.
*/
int testCubes(char board[][SIZE * SIZE]) {

	/*
	for every digit there is a counter.
	if the digit 4 appeared for example, we up the counter by 1 in the index 4. (numOfTimesEachNumAppeared[4]++)
	*/
	int numOfTimesEachNumAppeared[NUM_OF_DIGITS_BASE_10] = { 0 };

	/*
	goes over all the rows of cubes.
	the first row of cubes is index 0, the second one is index 1 and so on..
	in total, there are SIZE rows of cubes.
	*/
	for (int cubeRow = 0; cubeRow < SIZE; cubeRow++) {
		//goes over all the cubes in the row. there are SIZE cubes in each row.
		for (int cube = 0; cube < SIZE; cube++) {
			int currentNumOfSpacesInCube = 0;

			/*
			this goes over the columns. there are SIZE columns in each cube.
			so we ran from column cube*SIZE, until column number cube*SIZE+SIZE-1. SIZE columns in total.
			*/
			for (int column = cube * SIZE; column < (cube*SIZE + SIZE); column++) {

				/*
				this goes over the rows. there are SIZE rows in each cube.
				so we ran from row number cubeRow*SIZE, until row number cubeRow*SIZE+SIZE-1. SIZE rows in total.
				*/
				for (int row = cubeRow * SIZE; row < (cubeRow*SIZE + SIZE); row++) {
					char currentChar = board[row][column];
					//the char is a space, we continue
					if (currentChar == ' ') {
						continue;
					}
					//the char is a digit
					else if (currentChar >= '1' && currentChar <= ZERO_CHAR + SIZE * SIZE) {
						int currentDigit = charDigitToInt(currentChar);
						//we up the counter in the right index.
						numOfTimesEachNumAppeared[currentDigit]++;
					}
					//the char isn't a digit or a space. so the cube is not correct.
					else {
						return FALSE;
					}
				}
			}

			/*
			we are done going over the cube. now we check the counter.
			if everything is ok we reset the counter back to zero. and go check the next cube.
			*/
			for (int i = 0; i < 10; i++) {
				//if a digit appeared more than one time, the cube is not correct.
				if (numOfTimesEachNumAppeared[i] > 1) {
					return FALSE;
				}
				//else, everything was ok with that cube. so we continue checking.
				numOfTimesEachNumAppeared[i] = 0;
			}
		}
	}
	//if we got here, means all the cubes were correct. so we return TRUE.
	return TRUE;
}

/*
* Function Name: testBoard
* Input: char board[][SIZE*SIZE].
* Output: int FALSE(=0) if board is not correct
*		TRUE(=1) if board is correct.
* Function Operation: checks if the board is correct, by checking the rows, columns and cubes.
*					it does that by calling testRows(),testColumns() and testCubes().
*					correct means: 1. only spaces and digits, without any unknowns.
*									2. each digit appears not more than one time in each row/column/cube.
*/
int testBoard(char board[][SIZE * SIZE]) {
	int areRowsCorrect = testRows(board);
	int areColumnsCorrect = testColumns(board);
	int areCubesCorrect = testCubes(board);
	//if the rows are not correct, the sudoku is not correct.
	if (areRowsCorrect == FALSE) {
		//FALSE == 0.
		return FALSE;
	}
	//if the columns are not correct, the sudoku is not correct.
	if (areColumnsCorrect == FALSE) {
		//FALSE == 0.
		return FALSE;
	}
	//if the cubes are not correct, the sudoku is not correct.
	if (areCubesCorrect == FALSE) {
		//FALSE == 0.
		return FALSE;
	}
	//TRUE == 1.
	return TRUE;
}

/*
* Function Name: isSameBoard
* Input: char board1[][SIZE * SIZE], char board2[][SIZE * SIZE]
* Output: int FALSE(=0) if boards are not the same.
*		TRUE(=1) if boards are the same.
* Function Operation: checks and returns if the two boards it recieved are the same.
*					also prints the first inequality it found.
*/
int isSameBoard(char board1[][SIZE * SIZE], char board2[][SIZE * SIZE]) {
	for (int row = 0; row < SIZE*SIZE; row++) {
		for (int column = 0; column < SIZE*SIZE; column++) {
			//if we found two chars in the same place but are not equal.  
			if (board1[row][column] != board2[row][column]) {
				//the boards are not the same, we print the inequality and return FALSE (FALSE == 0).
				printf("Found inequality on row %d col %d.\n", row, column);
				return FALSE;
			}
		}
	}
	//if we got here, all the chars were the same in both boards. so we return TRUE (TRUE == 1).
	return TRUE;
}

/*
* Function Name: testSpacesRows
* Input: char board[][SIZE*SIZE], int numOfSpacesAllowed.
* Output: int - FALSE(=0) if the rows got more spaces than allowed
*		TRUE(=1) if the rows are ok.
* Function Operation: goes over the board rows, checks and returns if they are ok.
*					ok means: they have as much or less spaces than allowed (int numOfSpacesAllowed).
*					(ok if: number of spaces <= numOfSpacesAllowed)
*/
int testSpacesRows(char board[][SIZE * SIZE], int numOfSpacesAllowed) {
	for (int row = 0; row < SIZE*SIZE; row++) {
		int currentNumOfSpacesInRow = 0;
		for (int column = 0; column < SIZE*SIZE; column++) {
			char currentChar = board[row][column];
			//the char is a space
			if (currentChar == ' ') {
				//we found a space, so we up the counter.
				currentNumOfSpacesInRow++;
				continue;
			}
		}

		//if we got more spaces than allowed in a row. so the rows are not ok.
		if (currentNumOfSpacesInRow > numOfSpacesAllowed) {
			return FALSE;
		}
	}
	//if we got here, means all the rows were ok. so we return TRUE.
	return TRUE;
}

/*
* Function Name: testSpacesColumns
* Input: char board[][SIZE*SIZE], int numOfSpacesAllowed.
* Output: int - FALSE(=0) if the columns got more spaces than allowed
*		TRUE(=1) if the columns are ok.
* Function Operation: goes over the board columns, checks and returns if they are ok.
*					ok means: they have as much or less spaces than allowed (int numOfSpacesAllowed).
*					(ok if: number of spaces <= numOfSpacesAllowed)
*/
int testSpacesColumns(char board[][SIZE * SIZE], int numOfSpacesAllowed) {
	for (int column = 0; column < SIZE*SIZE; column++) {
		int currentNumOfSpacesInRow = 0;
		for (int row = 0; row < SIZE*SIZE; row++) {
			char currentChar = board[row][column];
			//the char is a space
			if (currentChar == ' ') {
				//we found a space, so we up the counter.
				currentNumOfSpacesInRow++;
				continue;
			}
		}

		//if we got more spaces than allowed in a column. so the columns are not ok.
		if (currentNumOfSpacesInRow > numOfSpacesAllowed) {
			return FALSE;
		}
	}
	//if we got here, means all the columns were ok. so we return TRUE.
	return TRUE;
}

/*
* Function Name: testSpacesCubes
* Input: char board[][SIZE*SIZE], int numOfSpacesAllowed.
* Output: int - FALSE(=0) if the cubes got more spaces than allowed
*		TRUE(=1) if the cubes are ok.
* Function Operation: goes over the board cubes, checks and returns if they are ok.
*					ok means: they have as much or less spaces than allowed (int numOfSpacesAllowed).
*					(ok if: number of spaces <= numOfSpacesAllowed)
*/
int testSpacesCubes(char board[][SIZE * SIZE], int numOfSpacesAllowed) {

	/*
	goes over all the rows of cubes.
	the first row of cubes is index 0, the second one is index 1 and so on..
	in total, there are SIZE rows of cubes.
	*/
	for (int cubeRow = 0; cubeRow < SIZE; cubeRow++) {
		//goes over all the cubes in the row. there are SIZE cubes in each row.
		for (int cube = 0; cube < SIZE; cube++) {
			int currentNumOfSpacesInCube = 0;

			/*
			this goes over the columns. there are SIZE columns in each cube.
			so we ran from column cube*SIZE, until column number cube*SIZE+SIZE-1. SIZE columns in total.
			*/
			for (int column = cube * SIZE; column < (cube*SIZE + SIZE); column++) {

				/*
				this goes over the rows. there are SIZE rows in each cube.
				so we ran from row number cubeRow*SIZE, 
				until row number cubeRow*SIZE+SIZE-1. SIZE rows in total.
				*/
				for (int row = cubeRow * SIZE; row < (cubeRow*SIZE + SIZE); row++) {
					char currentChar = board[row][column];
					//the char is a space
					if (currentChar == ' ') {
						//we found a space, so we up the counter.
						currentNumOfSpacesInCube++;
					}
				}
			}

			//if we got more spaces than allowed in a cube. so the cubes are not ok.
			if (currentNumOfSpacesInCube > numOfSpacesAllowed) {
				return FALSE;
			}
		}
	}
	//if we got here, means all the cubes were ok. so we return TRUE.
	return TRUE;
}

/*
* Function Name: checkSpacesBoard
* Input: char board[][SIZE*SIZE], int numOfSpacesAllowed.
* Output: int - FALSE(=0) if the board got more spaces than allowed
*		TRUE(=1) if the board is ok.
* Function Operation: checks if the board is ok, by checking the rows, columns and cubes.
*					it does that by calling testSpacesRows(),testSpacesColumns() and testSpacesCubes().
*					ok means: each row,column,cube have as much or less spaces than allowed (numOfSpacesAllowed).
*					(ok if: number of spaces <= numOfSpacesAllowed)
*/
int checkSpacesBoard(char board[][SIZE * SIZE], int numOfSpacesAllowed) {
	int areSpacesRowsCorrect = testSpacesRows(board, numOfSpacesAllowed);
	int areSpacesColumnsCorrect = testSpacesColumns(board, numOfSpacesAllowed);
	int areSpacesCubesCorrect = testSpacesCubes(board, numOfSpacesAllowed);
	//if the rows have too many spaces, the sudoku has too many spaces.
	if (areSpacesRowsCorrect == FALSE) {
		//FALSE == 0.
		return FALSE;
	}
	//if the columns have too many spaces, the sudoku has too many spaces.
	if (areSpacesColumnsCorrect == FALSE) {
		//FALSE == 0.
		return FALSE;
	}
	//if the cubes have too many spaces, the sudoku has too many spaces.
	if (areSpacesCubesCorrect == FALSE) {
		//FALSE == 0.
		return FALSE;
	}
	//TRUE == 1.
	return TRUE;
}

/*
* Function Name: findRowSolution
* Input: char board[][SIZE*SIZE], int row
*		(valid values: 0 <= row <= SIZE*SIZE -1).
* Output: char solution - the solution to the row.
* Function Operation: goes over the row and finds the solution (the char to complete with sudoku rules).
*						after found, we return the char that we found as the solution.
*/
char findRowSolution(char board[][SIZE * SIZE], int row) {
	//if no solution was found to the row, we return the ZERO_CHAR, because something failed in the proccess.
	char solution = ZERO_CHAR;

	/*
	for every digit there is a counter. if it is a solution or not.
	if the digit 4 appeared in the row for example, we change the counter in index 4-1=3 to TRUE.
	because it appeared in the row already. so it is true that it's not a solution to the row.
	numIsNotSolution[3] = TRUE.
	*/
	int numIsNotSolution[SIZE*SIZE] = { FALSE };
	for (int column = 0; column < SIZE*SIZE; column++) {
		char currentChar = board[row][column];
		//the char is a space, so we continue to the next char.
		if (currentChar == ' ') {
			continue;
		}
		//the char is a digit, so that digit is not a solution to the row.
		else if (currentChar >= '1' && currentChar <= (ZERO_CHAR + SIZE * SIZE)) {
			int currentDigit = charDigitToInt(currentChar);
			numIsNotSolution[currentDigit - 1] = TRUE;
		}
	}
	int counterOfSolutions = 0;
	for (int num = 0; num < SIZE*SIZE; num++) {
		//if the number num is a solution to the row
		if (numIsNotSolution[num] == FALSE) {
			// 2=>'2'. 2+ZERO_CHAR = 2+'0' = '2'
			solution = num + 1 + ZERO_CHAR;
		}
	}
	return solution;
}

/*
* Function Name: findAllSpaces
* Input: char board[][SIZE*SIZE], int spaceIndexes[SIZE*SIZE][2].
* Output: int - the number of spaces we found.
* Function Operation: finds all the spaces in the board and puts their indexes in the array.
*					the first dimension of the array is SIZE*SIZE long,
*					because there can be only SIZE*SIZE spaces in an almost done board.
*					the function also returns the number of spaces we found.
*/
int findAllSpaces(char board[][SIZE * SIZE], int spaceIndexes[SIZE*SIZE][2]) {
	int indexInSpacesArray = 0;
	for (int row = 0; row < SIZE*SIZE; row++) {
		for (int column = 0; column < SIZE*SIZE; column++) {
			char currentChar = board[row][column];
			//the char is a space
			if (currentChar == ' ') {
				//we found a space,so we save the indexes, and up the counter of the index.
				spaceIndexes[indexInSpacesArray][0] = row;
				spaceIndexes[indexInSpacesArray][1] = column;
				indexInSpacesArray++;
				continue;
			}
			//the char isn't a space. so we go to the next one.
			else {
				continue;
			}
		}
	}
	//we return the number of spaces we found.
	return indexInSpacesArray;
}

/*
* Function Name: checkCharsOfBoard
* Input: char board[][SIZE*SIZE].
* Output: int - FALSE(=0) if board is ok.
*		TRUE(=1) if board is not ok.
* Function Operation: goes over the board chars and checks if there are no chars which are not digits or spaces.
*					if there are chars who are not digits or spaces, we return FALSE(=0)
*					else, the board is ok, so we return TRUE(=1).
*/
int checkCharsOfBoard(char board[][SIZE * SIZE]) {
	for (int column = 0; column < SIZE*SIZE; column++) {
		for (int row = 0; row < SIZE*SIZE; row++) {
			char currentChar = board[row][column];
			//the char is not space, and not a valid digit.
			if (currentChar != ' ' && (currentChar < '0' || currentChar > ZERO_CHAR + SIZE * SIZE)) {
				return FALSE;
			}
		}
	}
	//if we got here, means all the chars in the board were ok. so we return TRUE.
	return TRUE;
}

/*
* Function Name: completeBoard
* Input: char board[][SIZE*SIZE].
* Output: none
* Function Operation: checks if board is valid and almost done.
*					if not, prints Error.
*					if yes, completes the board using findRowSolution().
*/
void completeBoard(char board[][SIZE * SIZE]) {
	const int NUM_OF_SPACES_ALLOWED = 1;

	//check if board only has valid digits and spaces.
	int isBoardHasVaildChars = checkCharsOfBoard(board);
	//if the board has a not valid char (not only spaces and digits), we print an Error and exit the function.
	if (isBoardHasVaildChars == FALSE) {
		printf("Error\n");
		return;
	}

	//check if the board only has 1 space in each cube, row, column. and that he has only numbers and spaces.
	int isBoardAlmostDone = checkSpacesBoard(board, NUM_OF_SPACES_ALLOWED);
	//if the board is not almost done. we print an Error and exit the function.
	if (isBoardAlmostDone == FALSE) {
		printf("Error\n");
		return;
	}

	/*
	there can be at max, SIZE*SIZE spaces in the sudoku, because it is almost done.
	every space has 2 coordinates, row and column. so we save the indexes in the array.
	*/
	int spaceIndexes[SIZE*SIZE][2];
	int numOfSpacesFound = findAllSpaces(board, spaceIndexes);
	//if the board is already complete. so we don't change it.
	if (numOfSpacesFound == 0) {
		return;
	}
	for (int spaceIndex = 0; spaceIndex < numOfSpacesFound; spaceIndex++) {
		int currentRow = spaceIndexes[spaceIndex][0];
		int currentCol = spaceIndexes[spaceIndex][1];
		char solution = findRowSolution(board, currentRow);
		//we replace the solution in place of the space
		board[currentRow][currentCol] = solution;
	}
}
