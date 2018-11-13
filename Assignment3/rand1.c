#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "rand1.h"

static long seed = 1;

// taken from the EE474 website, courtesy of one James Peckol
long randomInteger(int low, int high)
{
	double randNum = 0.0;
 	long multiplier = 2743;
	long addOn = 5923;
	double max = INT_MAX + 1.0;

	long retVal = 0;

	if (low > high)
		retVal = randomInteger(high, low);
	else
	{
   		seed = seed*multiplier + addOn;
   		randNum = seed;

		if (randNum <0)
		{
			randNum = randNum + max;
		}

		randNum = randNum/max;

		retVal =  ((int)((high-low+1)*randNum))+low;
	}

	return retVal;
}
