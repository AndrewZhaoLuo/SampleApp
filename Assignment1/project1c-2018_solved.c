#include <stdio.h>
// fixed version of project1c-2018, by team AAA copyright 2018

//  function prototypes

//  get data from the user
void getData(int* aValuePtr);

int main (void)
{
	//  declare a shared variable and a pointer to it
	int myValue;
	int* myPtr = &myValue;		//  let myPtr point to myValue

	//  get data from the user
	getData(myPtr);

	//  display the data as a character
	printf("The data is: %c \n", *myPtr);
        return 0;
}

//  prompt the user for some data and return it through a shared
//  variable pointed to by valuePtr
//
//  inputs:  	pointer to a container in which to place the data
//  outputs:	none
//  function:	the routine accepts a pointer to a container in which to store data from a user,
//				it prompts for the data, accepts the data, displays it, and returns

void getData(int* valuePtr)
{
    // *******************
    // mistake: removed tmp value which overwrites proper address
    // *******************

	//  prompt for data
	printf("Please enter a single digit between 0-9 \n");

	//  get the data
	*valuePtr = getchar();

	//  display its value as a character
	printf("The data is: %c \n", *valuePtr);

	return;

}
