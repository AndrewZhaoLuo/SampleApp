#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H
#include "bool.h"

#define BUFFER_SIZE_INDEX 0 // Index of array that stores size
#define BUFFER_INSERT_INDEX 1 // Location to put next sample
#define BUFFER_FIRST_DATA_INDEX 2 // First valid data index
#define BUFFER_METADATA_SIZE 2 // amount of indexes for buffers

void pushSample (int buffer[], int data);
int getNthPreviousSample (int buffer[], int n);
void initBuffer(int buffer[], int size);
void printBuffer(int buffer[], int size);
int isBufferEmpty (int buffer[], int size);

#endif // CIRCULAR_BUFFER_H
