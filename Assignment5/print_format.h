#ifndef PRINTF_H_INCLUDED
#define PRINTF_H_INCLUDED

#define DEBUG 1 // set to 0 to turn off debugging print statements
#define PRINT_BUFF_SIZE 1024

// Allow writing to serial via a printf like function in Arduino
// but only if DEBUG is true
void print_format(char *fmt, ... );

#endif // PRINTF_H_INCLUDED
