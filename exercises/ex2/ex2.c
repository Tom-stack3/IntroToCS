/***********************
* Name: Tommy Zaft
* Assignment: exercise 2
***********************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
* Function Name: DrawARhombus
* Input: int length - the length of the side of the rhombus
* Output: void
* Function Operation: prints the rhombus
*/
void drawARhombus(int length) {
	//prints the first half of the omnibus
	for (int i = 1; i <= length; i++) {
		for (int j = length - i; j >= 1; j--)
		{
			printf(" ");
		}
		printf("/");
		for (int j = 1; j < i; j++)
		{
			printf(" ");
		}
		printf("*");
		for (int x = 1; x < i; x++)
		{
			printf(" ");
		}
		printf("\\\n");
	}

	//prints the middle line
	printf("|");
	for (int i = 1; i < length;i++) {
		printf(" ");
	}
	printf("+");
	for (int i = 1; i < length; i++) {
		printf(" ");
	}
	printf("|\n");

	//prints the second half
	for (int i = length; i >= 1; i--) {
		for (int j = 1; j <= length - i; j++)
		{
			printf(" ");
		}
		printf("\\");
		for (int j = 1; j < i; j++)
		{
			printf(" ");
		}
		printf("*");
		for (int x = 1; x < i; x++)
		{
			printf(" ");
		}
		printf("/\n");
	}
}

/*
* Function Name: getInputForRhombus
* Input: none
* Output: none
* Function Operation: gets input for drawing a rhombus and calls the function that draws it
*/
void getInputForRhombus() {
	int lengthRhombus;
	printf("Enter the sides length:\n");
	scanf("%d", &lengthRhombus);
	drawARhombus(lengthRhombus);
}

/*
* Function Name: CharDigitToInt
* Input: char digitC - gets a char that represents a digit
* Output: int
* Function Operation: returns the digit which is represented in the char
*/
int charDigitToInt(char digitC) {
	const char zeroChar = '0';
	return (int)(digitC - zeroChar);
}

/*
* Function Name: MathPow
* Input: int num, int exponent 
* Output: int
* Function Operation: returns the number (int num) raised to the power of the exponent 
*/
int mathPow(int num, int exponent) {
	int result = 1;
	for (int i = 1; i <= exponent; i++) {
		result = result * num;
	}
	return result;
}

/*
* Function Name: charToIntInAnyBase
* Input: char currentChar, int base
* Output: int number
* Function Operation: gets a char and a base, if the char is valid the the base it returns the value of the char in the base, if not, returns -1
*/
int charToIntInAnyBase(char currentChar, int base) {
	enum Base20Chars
	{
		A = 10, B = 11, C = 12, D = 13, E = 14, F = 15, G = 16, H = 17, I = 18, J = 19
	};
	enum Base20Chars num = 0;
	if (currentChar == 'A' || currentChar == 'a') {
		num = A;
	}
	else if (currentChar == 'B' || currentChar == 'b') {
		num = B;
	}
	else if (currentChar == 'C' || currentChar == 'c') {
		num = C;
	}
	else if (currentChar == 'D' || currentChar == 'd') {
		num = D;
	}
	else if (currentChar == 'E' || currentChar == 'e') {
		num = E;
	}
	else if (currentChar == 'F' || currentChar == 'f') {
		num = F;
	}
	else if (currentChar == 'G' || currentChar == 'g') {
		num = G;
	}
	else if (currentChar == 'H' || currentChar == 'h') {
		num = H;
	}
	else if (currentChar == 'I' || currentChar == 'i') {
		num = I;
	}
	else if (currentChar == 'J' || currentChar == 'j') {
		num = J;
	}
	else if (currentChar >= '0' && currentChar <= '9') {
		num = charDigitToInt(currentChar);
	}
	else { //not a valid char
		num = -1;
	}
	if (num > base - 1) { //the char is not in the base
		num = -1;
	}
	return num;
}

/*
* Function Name: Base20ToDecimal
* Input: none
* Output: none
* Function Operation: gets from the user a reversed number in base 20 and prints out the decimal value of it
*/
void base20ToDecimal() {
	int isValidInput = 1;
	int exponent = 0;
	int decimalNum = 0;
	char currentChar;
	const int BASE = 20;
	printf("Enter a reversed number in base 20:\n");

	int num;

	scanf(" %c", &currentChar);
	num = charToIntInAnyBase(currentChar, BASE);
	if (num == -1) { //means the char is not valid and not a new line
		printf("Error! %c is not a valid digit in base 20\n", currentChar);
		isValidInput = 0;
		num = 0;
	}
	decimalNum += mathPow(BASE, exponent++)*num;
	while (currentChar != '\n') {
		scanf("%c", &currentChar);
		num = charToIntInAnyBase(currentChar, BASE);
		if (currentChar == '\n') { //means we are done
			break;
		}
		if (num == -1) { //means the char is not valid and not a new line
			printf("Error! %c is not a valid digit in base 20\n", currentChar);
			isValidInput = 0;
			num = 0;
		}
		decimalNum += mathPow(BASE, exponent++)*num;
	}

	//if there were no errors and the input was valid
	if(isValidInput == 1){
		printf("%d\n", decimalNum);
	}
	
}

/*
* Function Name: baseToDecimal
* Input: none
* Output: none
* Function Operation: gets from the user a base and then a reversed number in the entered base and prints out the decimal value of it
*/
void baseToDecimal() {
	int isValidInput = 1;
	int exponent = 0;
	int decimalNum = 0;
	char currentChar;
	int intChar;
	int base;

	printf("Enter a base (2-10):\n");
	scanf("%d", &base); //gets the base

	printf("Enter a reversed number in base %d:\n",base); //gets the reversed number

	int num;
	scanf(" %c", &currentChar);
	num = charToIntInAnyBase(currentChar, base);
	if (num == -1) { //means the char is not valid and not a new line
		printf("Error! %c is not a valid digit in base %d\n", currentChar, base);
		isValidInput = 0;
		num = 0;
	}
	decimalNum += mathPow(base, exponent++)*num;
	while (currentChar != '\n') {
		scanf("%c", &currentChar);
		num = charToIntInAnyBase(currentChar, base);
		if (currentChar == '\n') { //means we are done
			break;
		}
		if (num == -1) { //means the char is not valid and not a new line
			printf("Error! %c is not a valid digit in base %d\n", currentChar, base);
			isValidInput = 0;
			num = 0;
		}
		decimalNum += mathPow(base, exponent++)*num;
	}

	//if there were no errors
	if (isValidInput == 1) {
		printf("%d\n", decimalNum);
	}
}

/*
* Function Name: checkPower2
* Input: none
* Output: none
* Function Operation: gets from the user a number prints out whether the number is a power of 2 or not
*/
void checkPower2() {
	int num;
	printf("Enter a number:\n");
	scanf("%d", &num);
	int shifted = num & (num - 1);
	if (shifted == 0 && num != 0) {
		printf("%d is a power of 2\n", num);
	}
	else {
		printf("%d is not a power of 2\n", num);
	}
}

/*
* Function Name: checkDifferentBits
* Input: none
* Output: none
* Function Operation: gets from the user two numbers and prints out the number of different bits in their binary representation
*/
void checkDifferentBits() {
	printf("Enter two numbers:\n");
	int num1;
	int num2;
	int comparingNum, compare1, compare2;
	int numOfDifferentBits = 0;
	scanf("%d%d", &num1, &num2);

	//the comparing number is 2^i which in binary is 00...00100..00 with a 1 only in the i index, that is why it is easy to compare with it two numbers
	const int SIZE_OF_INT_BITS = sizeof(int) * 8; // = 32
	for (int i = 0; i < SIZE_OF_INT_BITS; i++) {
		comparingNum = mathPow(2, i);  
		compare1 = num1 & comparingNum;
		compare2 = num2 & comparingNum;

		if (compare1 != compare2) {
			numOfDifferentBits++;
		}
	}
	printf("There are %d different bits\n", numOfDifferentBits);
}

/*
* Function Name: sumTwoNums
* Input: int num1, int num2 - two integers
* Output: int result - the sum of the two numbers
* Function Operation: gets from the user two numbers and using while loop with the carry and the result sums the two numbers and returns the sum when the carry is zero
*/
int sumTwoNums(int num1, int num2) {
	int currentResult = num1 ^ num2;
	int carry = num1 & num2;
	carry = carry << 1;
	int result = currentResult;
	while (carry != 0) { //if carry = 0 it means we are done summing the numbers
		currentResult = carry ^ result;
		carry = carry & result;
		carry = carry << 1;
		result = currentResult;
	}
	return result;
}

/*
* Function Name: getInputAndSum
* Input: none
* Output: none
* Function Operation: gets the input for the sum function (two integers) and prints the result that returned from the sum function
*/
void getInputAndSum() { 
	printf("Enter two numbers:\n");
	int num1;
	int num2;
	scanf("%d%d", &num1, &num2);
	int sumResult = sumTwoNums(num1, num2);
	printf("%d\n", sumResult);
}

/*
* Function Name: absValue
* Input: int number
* Output: int oppositeNum
* Function Operation: returns the absolute value of a number  
*/
int absValue(int number) {
	if (number >= 0) { //if the number is a non-negative the function just returns the number itself
		return number;
	}
	int absNum = ~number+1; //using two's complement method
	return absNum;
}

/*
* Function Name: multiplyTwoNums
* Input: int num1, int num2 - two integers
* Output: the sum of the two numbers
* Function Operation: gets from the user two numbers and multiplies them
*/
int multiplyTwoNums(int num1,int num2) {
	int tempInt;
	if (num2 > 0 && num1 < 0) {
		tempInt = num2;
		num2 = num1;
		num1 = tempInt;
	}
	if (num2 < 0 && num1 < 0) {
		num2 = absValue(num2);
	}
	int positive1 = absValue(num1);
	int result = 0;
	for (int i = 0; i < positive1; i++) {
		result += num2;
	}
	return result;
}

/*
* Function Name: getInputAndMultiply
* Input: none
* Output: none
* Function Operation: gets the input for the multiply function (two integers) and prints the result that returned from the multiply function
*/
void getInputAndMultiply() {
	printf("Enter two numbers:\n");
	int num1;
	int num2;
	scanf("%d%d", &num1, &num2);
	int multiplyResult = multiplyTwoNums(num1, num2);
	printf("%d\n", multiplyResult);
}

/*
* Function Name: handleInput
* Input: char optionChosen - the char the user entered
* Output: none
* Function Operation: in charge of calling the right functions based on the option that the user chose
*/
void handleInput(char optionChosen) {

	switch (optionChosen)
	{
	case '0':
		break;
	case '1':
		getInputForRhombus();
		break;
	case '2':
		base20ToDecimal();
		break;
	case '3':
		baseToDecimal();
		break;
	case '4':
		checkPower2();
		break;
	case '5':
		checkDifferentBits();
		break;
	case '6':
		getInputAndSum();
		break;
	case '7':
		getInputAndMultiply();
		break;
	default:
		printf("Wrong option!\n");
		break;
	}
}


/*
* Function Name: main
* Input: none
* Output: 0
* Function Operation: prints the menu, gets the option that the user chose and sends it to the handleInput() function
*/
int main() {

	//prints the menu
	printf("Choose an option:\n1. Rhombus\n2. Base 20 to Decimal\n3. Base to Decimal\n4. Pow2\n5. Different bits\n6. Add\n7. Multiply\n0. Exit\n");
	char optionChosen;
	scanf(" %c", &optionChosen);
	while (optionChosen != '0') {
		handleInput(optionChosen);
		printf("Choose an option:\n1. Rhombus\n2. Base 20 to Decimal\n3. Base to Decimal\n4. Pow2\n5. Different bits\n6. Add\n7. Multiply\n0. Exit\n"); //prints the menu
		scanf(" %c", &optionChosen);
	}

	return 0;
}
