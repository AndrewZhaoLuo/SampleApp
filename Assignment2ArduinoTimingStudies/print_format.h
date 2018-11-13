#ifndef PRINTF_H_INCLUDED
#define PRINTF_H_INCLUDED

#define DEBUG 0 // set to 0 to turn off debugging print statements

// Allow writing to serial via a printf like function in Arduino
void print_format(char *fmt, ... );

#endif // PRINTF_H_INCLUDED
