#include "circularBuffer.h"
#include "globals.h"
#include "print_format.h"

// Replaces oldest value in buffer with data.
void pushSample (int buffer[], int data) {
  int curIndex = buffer[BUFFER_INSERT_INDEX];

  int size = buffer[BUFFER_SIZE_INDEX];
  int nextIndex = curIndex + 1;

  // Update buffer index for next sample
  if (nextIndex > (size - 1)) {
    nextIndex = BUFFER_FIRST_DATA_INDEX;
  }
  buffer[BUFFER_INSERT_INDEX] = nextIndex;

  buffer[nextIndex] = data;
}

// Returns Nth previous sample (n >= 0). n = 0 is last sample, n = 1 is prevous sample.
int getNthPreviousSample (int buffer[], int n) {
  if (n < 0) {
    print_format("getNthPreviousSample: n cannot be negative. Output will be bad.");
  }
  int curIndex = buffer[BUFFER_INSERT_INDEX];
  int size = buffer[BUFFER_SIZE_INDEX];
  int sizeBuffer = size - BUFFER_METADATA_SIZE;
  int bufferOffset = curIndex - BUFFER_METADATA_SIZE;
  int nSafe = n % (sizeBuffer); // handles circular case

  int getIndex = BUFFER_FIRST_DATA_INDEX + ((bufferOffset + (sizeBuffer - nSafe)) % sizeBuffer);

  return buffer[getIndex];
}

// Initalizes indexes and buffer meta data. Must have size >= 4.
void initBuffer(int buffer[], int size) {
  buffer[BUFFER_SIZE_INDEX] = size;
  buffer[BUFFER_INSERT_INDEX] = size-1;
  for (int i = BUFFER_FIRST_DATA_INDEX; i < size; i++) {
    buffer[i] = 0;
  }
}

void printBuffer(int buffer[], int size) {
    print_format("\n");
    for (int i = 0; i < size; i++) print_format("%d ", buffer[i]);
    print_format("\n");
}

// Empty buffer is defined as 0 in index 2 -> size - 1
int isBufferEmpty (int buffer[], int size) {
    int isEmpty = 1;
    for (int i = BUFFER_FIRST_DATA_INDEX; i < size; i++) {
        if (buffer[i] != 0) {
            isEmpty = 0;
        }
    }
    return isEmpty;
}

// Test buffer functions on size buffer while looking at n previous values
int testBuffer(int size, int n) {
    unsigned int buffer[size];
    initBuffer(buffer, size);
    printBuffer(buffer, size);
    print_format("\nisBufferEmpty?: %d\n", isBufferEmpty(buffer, size));

    //printf("\nInitialized\n");
    for (int i = 1; i < size * 3; i ++) {
        print_format("\n\n");
        print_format("Inserting Sample: %d", i);
        pushSample (buffer, i);
        printBuffer(buffer, size);
        int prev = getNthPreviousSample(buffer, n);
        int correct = prev == (i - n % (size-2));
        print_format("Previous Sample: %d\n", prev);
        if (!correct) {
            print_format("INCORRECT PREVIOUS SAMPLE: XXXXXXXXXXXXXXXXXXXXXXXXX");
        }
    }
    print_format("\nisBufferEmpty?: %d\n", isBufferEmpty(buffer, size));
   return 0;
}
