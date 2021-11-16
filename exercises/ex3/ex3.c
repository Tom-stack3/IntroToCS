/***********************
* Name: Tommy Zaft
* Assignment: exercise 3
***********************/

#include "ex3.h"
#include <stdio.h>
#define BONUS
#define TRUE 1
#define FALSE 0
#define FAILED -1

/*
global integer for question 2
in order the save the number of combinations the recursion creates and prints we need one global variable
it is reset to zero at the start of the run when the function printAllCombinations() gets a string to work with.
the variable is added +1 each time the funcion printAllCombinationsRecursion() prints another combination
*/
int numberOfCombinations = 0;

/*
* Function Name: checkIfPalindromeRecursive
* Input: char str[], int len, int startIndex (valid values: 0 <= startIndex <= len-1)
* Output: int (TRUE(=1) or FALSE(=0))
* Function Operation: checks if a string is a palindrome using recursion
*						if string is a palindrome, returns TRUE
*						if string is not a palindrome, returns FALSE
*/
int checkIfPalindromeRecursive(char str[], int len, int startIndex) {

	/*
	means we checked all or almost all the characters and they are equal.
	if the len of the original string was odd than there is one in the middle which is just equal to itself.
	if the len of the original string was even, we compared all the characters.
	*/
	if (len - 1 <= startIndex) {
		return TRUE;
	}
	//we found two characters which are not equal but should be (in a palindrome), means it's not a palindrome.   
	else if (str[startIndex] != str[len - 1]) {
		return FALSE;
	}
	//continue checking the other characters
	else {
		return checkIfPalindromeRecursive(str, len - 1, startIndex + 1);
	}
}

/*
* Function Name: isPalindrome
* Input: char str[], int len (valid values: len = length of str[])
* Output: none
* Function Operation: prints if a string (str[]) is a palindrome.
*					it uses the recursive function checkIfPalindromeRecursive().
*/
void isPalindrome(char str[], int len) {
	const int INDEX_TO_START_CHECK = 0;

	printf("The reverse of ");
	//prints the word
	printf(str);
	//calls the recursive function that checks of the string is a palindrome
	int isPalindrome = checkIfPalindromeRecursive(str, len, INDEX_TO_START_CHECK);
	//not a palindrome
	if (isPalindrome == FALSE) {
		printf(" is not ");
	}
	//is a palindrome
	else {
		printf(" is also ");
	}
	//prints the word
	printf(str);
	printf(".\n");
}

/*
* Function Name: printAllCombinationsRecursion
* Input: char pattern[], int len, int index (valid values: len = length of pattern[], index < len.)
* Output: none
* Function Operation: using recursion, generates and prints all the combinations of the pattern.
*					starts search for '?' to replace from the int index it recieves,
*					which is it's starting index.
*					also adds +1 to global variable numberOfCombinations, whenever we print a new combination.
*/
void printAllCombinationsRecursion(char pattern[], int len, int index) {
	//if we checked the whole string and there are no more '?' found.
	if (index >= len) {
		//prints a combination of the pattern.
		printf("%s\n",pattern);
		//we add +1 to the global variable numberOfCombinations, because we printed a new combination.
		numberOfCombinations++;
		return;
	}
	//if we found a '?' in the current index.
	if (pattern[index] == '?') {
		//in order to send the function the next index to search in for '?'.
		int nextIndex = index + 1;
		//replaces the '?' with a 0.
		pattern[index] = '0';
		printAllCombinationsRecursion(pattern,len, nextIndex);
		//replaces the '?' index with a 1.
		pattern[index] = '1';
		printAllCombinationsRecursion(pattern, len, nextIndex);
		//replaces the '?' with a 2.
		pattern[index] = '2';
		printAllCombinationsRecursion(pattern, len, nextIndex);

		//puts the '?' back in the right place.
		pattern[index] = '?';
	}
	else {
		//searches in the next index for a '?'
		printAllCombinationsRecursion(pattern, len, ++index);
	}
}

/*
* Function Name: printAllCombinations
* Input: char pattern[], int len (valid values: len = length of pattern[])
* Output: none
* Function Operation: calls printAllCombinationsRecursion() to print all the combinations for the pattern.
*						at the end, prints the number of combinations printed.
*						(using the global variable numberOfCombinations)
*/
void printAllCombinations(char pattern[], int len) {
	//sends the recursive function a index to start the search for question marks.
	const int FIRST_INDEX_TO_START_SEARCH_QUESTION_MARK = 0;

	//resets the global variable to 0. because we got a new pattern.
	numberOfCombinations = 0;
	printAllCombinationsRecursion(pattern, len, FIRST_INDEX_TO_START_SEARCH_QUESTION_MARK);
	printf("Number of combinations is: %d\n", numberOfCombinations);
}

/*
* Function Name: powRecRecursion
* Input: long int firsrtNum, long int secondNum
*		(valid values: secondNum must be positive.) we take care of it in the powRec() function.
*		as explained there. if x<0: a^x = 1 / a^(-x). we calculate it in powRec().
* Output: long int, the result of: firstNum to the power of secondNum.
* Function Operation: using recursion, calculats and returns firstNum^secondNum.
*/
long int powRecRecursion(long int firsrtNum, long int secondNum) {
	if (secondNum == 1) {
		//x^1 = x
		return firsrtNum;
	}
	return firsrtNum * powRecRecursion(firsrtNum, secondNum - 1);
}

/*
* Function Name: powRec
* Input: long int firsrtNum, long int secondNum
* Output: none
* Function Operation: prints the firstNum in the power of the second num.
*						gets the result using the recursion function powRecRecursion()
*						if the input is 0 and a negative num. the function prints: "The result is nan."
*						because 1/0 is nan.
*						else, prints the result. "The result is x."
*/
void powRec(long int firsrtNum, long int secondNum) {
	double result;
	long int exponent;

	// when x < 0: 0^x = 1/0^(-x) = 1/0 is not a number, so prints nan.
	if (firsrtNum == 0 && secondNum < 0) {
		printf("The result is nan.\n");
		return;
	}

	//in addition, the special case 0^0 is also equal to 1. so that if includes it. 0^0=1.
	if (firsrtNum == 1 || secondNum == 0) {
		// 1^x = 1. x^0 = 1.
		result = 1;
	}
	else if (firsrtNum == 0) {
		// 0^x equals 0 (if x > 0)
		result = 0;
	}
	else if (secondNum < 0) {
		// x^(-y) = 1 / (x^y)
		exponent = 0 - secondNum;
		result = 1.0 / powRecRecursion(firsrtNum, exponent);
	}
	//regular calculation.
	else {
		exponent = secondNum;
		result = powRecRecursion(firsrtNum, exponent);
	}
	//prints the result in a precision of 6 digits.
	printf("The result is %.6f.\n", result);
}

/*
* Function Name: checkDivisionBy3Recursion
* Input: long long num. long long num, int reminderFrom3
*		(valid values: num should have only the digits: 1, 2, 3)
*		(reminderFrom3 can only be: 0, 1 or 2)
* Output: 1 if the number is divisible by 3. 0 if number is not divisible by 3.
* Function Operation: checks if a number is divisible by 3 or not, using recursion.
*						goes over the number's digits and checks:
*						checks the reminder of the number's digits together from division by 3.
*						in the end if:
*						the reminder of all the numbers together is = 0. the number divisible by 3.
*						the reminder of all the numbers together is = 1 or 2. the number isn't divisible by 3.
*/
int checkDivisionBy3Recursion(long long num, int reminderFrom3) {
	// num % 10 gives the units digit of the number.
	int currentLastDigit = num % 10;
	//initialized in FAILED(=-1), if not changed during the run, means something went wrong in the calculaton.
	int numToSend = FAILED;
	//we are done going over the number's digits and the number is divisible:
	if (currentLastDigit == 0 && reminderFrom3 == 0) {
		return 1;
	}
	//we are done going over the number's digits and the number is not divisible:
	else if (currentLastDigit == 0 && reminderFrom3 != 0) {
		return 0;
	}

	if (currentLastDigit == 3) {
		//(3 + (0 or 1 or 2)) % 3 = (0 or 1 or 2) in correspondence.
		numToSend = reminderFrom3;
	}
	if (currentLastDigit == 1 && reminderFrom3 == 1) {
		//(1 + 1) % 3 = 2
		numToSend = 2;
	}
	else if (currentLastDigit == 2 && reminderFrom3 == 2) {
		//(2 + 2) % 3 = 4 % 3 = 2
		numToSend = 1;
	}
	else if (currentLastDigit == 1 && reminderFrom3 == 2 || currentLastDigit == 2 && reminderFrom3 == 1) {
		//(1 + 2) % 3 = (2 + 1) % 3 = 0
		numToSend = 0;
	}
	else if (reminderFrom3 == 0 && (currentLastDigit == 1 || currentLastDigit == 2)) {
		// ((1 or 2) + 0) % 3 = 1 or 2
		numToSend = currentLastDigit;
	}

	// num / 10 gives the number without the units digit.
	return checkDivisionBy3Recursion(num / 10, numToSend);
}

/*
* Function Name: isDivisibleBy3
* Input: long long num. (valid values: the num should have only the digits: 1,2,3)
* Output: none
* Function Operation: it calls the recursive function checkDivisionBy3Recursion()
*						and then prints if the number is divisible by 3 or not.
*/
void isDivisibleBy3(long long num) {
	printf("The number %lld", num);
	const int REMINDER_ZERO = 0;
	/*
	sends zero as the first "int previousNum" to the function.
	that way it won't affect the calculations of the checkDivisionBy3Recursion() function.
	isDivisibleBy3 = TRUE => divisible. isDivisibleBy3 = FALSE => not divisible.
	*/
	int isDivisibleBy3 = checkDivisionBy3Recursion(num, REMINDER_ZERO);
	if (isDivisibleBy3 == TRUE)
		printf(" is divisible by 3");
	else
		printf(" is not divisible by 3");
	printf(".\n");
}

/*
* Function Name: countDigitRecursion
* Input: long long num, int wantedDigit (valid values: wantedDigit = one digit)
* Output: int: the number of times the digit (int wantedDigit) is in the number recieved.
* Function Operation: using recursion, returns how many times the number has the digit (int wantedDigit).
*					every show of the function checks if the last digit is equal to the digit we are searching,
*					then adds 1 if the number was found to the returned int.
*					then calls the function again on the number divided by 10, (to move on to the next digit).
*/
int countDigitRecursion(long long num, int wantedDigit) {
	//if we got to the last digit and it is the one we are looking for.
	if (num == wantedDigit)
		return 1;
	//if we got to the last digit and it is not the one we are looking for.
	if ((num < 10) && num != wantedDigit)
		return 0;
	// num % 10 gives the units digit of the number.
	if (num % 10 == wantedDigit) {
		// num / 10 gives the number without the units digit.
		return 1 + countDigitRecursion(num / 10, wantedDigit);
	}
	else {
		// num / 10 gives the number without the units digit.
		return 0 + countDigitRecursion(num / 10, wantedDigit);
	}
}

/*
* Function Name: countDigit
* Input: long long num, int digit (valid values: digit = one digit)
* Output: none
* Function Operation: prints how many times the number (long long num) has the digit (int digit) in it.
*						using the recursion function countDigitRecursion()
*/
void countDigit(long long num, int digit) {
	int numOfTimesDigitAppears = 0;
	if (num < 0) {

		/*
		in order to not send the countDigitRecursion() a negative number to search for the digit in.
		it sends the positive oposite of the number by sending countDigitRecursion() the number 0-num.
		*/
		numOfTimesDigitAppears = countDigitRecursion(0 - num, digit);
	}
	else
		numOfTimesDigitAppears = countDigitRecursion(num, digit);
	//prints how many times the number has the digit
	printf("%lld has %d times %d.\n", num, numOfTimesDigitAppears, digit);
}

/*
* Function Name: findGcdRecursion
* Input: long int num1, long int num2
* Output: long int (the gcd)
* Function Operation: finds the gcd of two numbers using the Euclidean algorithm with recursion.
*						also prints the way the algorithm calculates it.
*						for example: 2*1+0=2(a=2, b=2)
*/
long int findGcdRecursion(long int num1, long int num2) {

	long int reminder;
	long int coefficient;

	if (num2 == 0) {
		//gcd of (x,0) is always x.
		return num1;
	}
	else if (num1 == 0) {
		//gcd of (0,x) is always x.
		return num2;
	}

	reminder = num1 % num2;
	coefficient = num1 / num2;

	//prints the calculatin, for example: 2*1+0=2 (a=2, b=2)
	printf("%ld*%ld+%ld=%ld(a=%ld,b=%ld)\n", num2, coefficient, reminder, num1, num1, num2);

	return findGcdRecursion(num2, reminder);
}


/*
* Function Name: findGcdRecursion
* Input: long int num1, long int num2
* Output: none
* Function Operation: calls the recursive function findGcdRecursion() with the two numbers it got
*						and prints the gcd that the function calculated.
*/
void gcd(long int num1, long int num2) {
	long int gcd = findGcdRecursion(num1, num2);
	if (gcd < 0) {
		//the gcd should be always positive
		gcd = 0 - gcd;
	}

	printf("GCD=%ld\n", gcd);
}

/*
* Function Name: isPalindromeIter
* Input: char str[], int len. the value of len should be the length of the char array str[].
* Output: none
* Function Operation: checks and prints if the string is a polindrome or not. using iterations.
*/
void isPalindromeIter(char str[], int len) {
	int isPalindrome = TRUE;
	const int MIDDLE_OF_STRING = len / 2;
	//the loop runs until the middle of the string
	for (int i = 0; i < MIDDLE_OF_STRING; i++) {

		/*
		we found two characters which are not equal but should be (in a palindrome)
		means it's not a palindrome.
		*/
		if (str[i] != str[len - 1 - i])
			isPalindrome = FALSE;
	}
	printf("The reverse of ");
	//prints the word
	printf(str);

	//it is a palindrome
	if (isPalindrome == TRUE)
		printf(" is also ");

	//not a palindrome
	else
		printf(" is not ");

	//prints the word
	printf(str);
	printf(".\n");

}

/*
* Function Name: sumNumberDigits
* Input: long long num
* Output: long long number, the sum of the number's digits.
* Function Operation: sums the number's digits using iterations. returns the sum.
*/
long long sumNumberDigits(long long num) {
	int digit = num % 10;
	int sum = digit;

	/*
	if the num is 0, means we are done summing.
	because the number (long long num) was already a digit in the last loop, so the num / 10 = 0
	*/
	while (num != 0) {
		// num / 10 gives the number without the units digit.
		num = num / 10;
		// num % 10 gives the units digit of the number.
		digit = num % 10;
		sum = sum + digit;
	}
	return sum;
}

/*
* Function Name: IsDividedBy3Iter
* Input: long long num (valid input: positive number)
* Output: none
* Function Operation: checks and prints whether a number is divisible by 3.
*						using the iterative function sumNumberDigits() and iterations.
*/
void IsDividedBy3Iter(long long num) {
	const int LARGEST_DIGIT = 9;
	const int SMALLEST_NEGETIVE_DIGIT = -9;
	//zero is divisible by any number
	if (num == 0) {
		printf("The number 0 is divisible by 3.\n");
		return;
	}
	long long numberToCheck = num;

	long long sum = sumNumberDigits(numberToCheck);

	/*
	runs until the sum of digits is a digit itself.
	means it sums the number's digits until the smallest sum.
	1934589 => 39 => 12 => 3
	*/
	while (sum > LARGEST_DIGIT || sum < SMALLEST_NEGETIVE_DIGIT) {
		sum = sumNumberDigits(sum);
	}

	/*
	means the number in total is divisible by 3.
	because the sum of his digits, after all the summing, is divisible by 3.
	3,6,9 are the only positive  digits that are divisible by 3.
	6 = 2*3, 9 = 3*3
	and their negetive forms: -3,-6,-9
	-3 = -1*3, -6 = -2*3, -9 = -3*3
	*/
	if (sum == 3 || sum == 6 || sum == 9 || sum == -3 || sum == -6 || sum == -9)
		printf("The number %lld is divisible by 3.\n", num);
	else
		printf("The number %lld is not divisible by 3.\n", num);
}

/*
* Function Name: towerOfHanoi
* Input: int numOfDisks, char from_rod, char to_rod, char spare_rod.
* Output: none
* Function Operation: solves the tower of hanoi puzzle using recursion and prints the way.
*						example when:
*						numOfDisks = 2. from_rod='A'. to_rod='C'. spare_rod='B'. the function prints:
*						Move disk 1 from rod A to rod B.
*						Move disk 2 from rod A to rod C.
*						Move disk 1 from rod B to rod C.
*/
void towerOfHanoi(int numOfDisks, char from_rod, char to_rod, char spare_rod) {
	//means we are done transferring all the disks:
	if (numOfDisks == 0) {
		return;
	}
	//means we got only the last (smallest) disk to move:
	if (numOfDisks == 1) {
		printf("Move disk %d from rod %c to rod %c.\n", 1, from_rod, to_rod);
	}
	else {
		towerOfHanoi(numOfDisks - 1, from_rod, spare_rod, to_rod);
		printf("Move disk %d from rod %c to rod %c.\n", numOfDisks, from_rod, to_rod);
		towerOfHanoi(numOfDisks - 1, spare_rod, to_rod, from_rod);
	}
}
