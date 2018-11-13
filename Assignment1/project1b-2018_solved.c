#include <stdio.h>
// fixed version of project1b-2018, by team AAA copyright 2018

// mistake: diaplay --> display
//  this is a simple routine that demonstrates how to fill and display an array of characters

int main(void)
{
	int i = 0;									//  declare a working variable

	// **************************
	// mistake: size of array from 5 -> 6 to avoid out of bounds
    // **************************
	char myArray[6];							//  declare a character array

	for (i = 0; i <= 5; i++)					//  fill array with characters
	{
		//  fill with the ascii characters A..F
		//  65 is the ascii value for A

		// style change: 65 -> 'A' makes more readable
		myArray[i]= 'A'+i;
	}

	for (i = 0; i <= 5; i++)					//  display the array
	{
		printf("%c \n", myArray[i]);
	}

	printf("\n");

	return 0;
}
