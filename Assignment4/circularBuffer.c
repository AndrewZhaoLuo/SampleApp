#include "circularBuffer.h"
#include "globals.h"

// void pushBack(const int item) {
//   if(!(circBuf.empty)){
//     if (circBuf.tail == circBuf.head) {
//       circBuf.head++;
//     }
//   }
//   circBuf.buffer[circBuf.tail] = item;
//   circBuf.tail++;
//   if (circBuf.tail > circBuf.endIndex) {
//     circBuf.tail = 0;
//   }
//   circBuf.empty = FALSE;
//   batteryLevelPtr = &(circBuf.buffer[circBuf.tail]);
// }

// Replaces oldest value in buffer with data.
void pushSample (unsigned int buffer[], int data) {
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
int getNthPreviousSample (unsigned int buffer[], int n) {
  if (n < 0) {
    printf("getNthPreviousSample: n cannot be negative. Output will be bad.");
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
void initBuffer(unsigned int buffer[], int size) {
  buffer[BUFFER_SIZE_INDEX] = size;
  buffer[BUFFER_INSERT_INDEX] = size-1;
  for (int i = BUFFER_FIRST_DATA_INDEX; i < size; i++) {
    buffer[i] = 0;
  }
}

void printBuffer(unsigned int buffer[], int size) {
    printf("\n");
    for (int i = 0; i < size; i++) printf("%d ", buffer[i]);
    printf("\n");
}

// Empty buffer is defined as 0 in index 2 -> size - 1
int isBufferEmpty (unsigned int buffer[], int size) {
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
    printf("\nisBufferEmpty?: %d\n", isBufferEmpty(buffer, size));

    printf("\nInitialized\n");
    for (int i = 1; i < size * 3; i ++) {
        printf("\n\n");
        printf("Inserting Sample: %d", i);
        pushSample (buffer, i);
        printBuffer(buffer, size);
        int prev = getNthPreviousSample(buffer, n);
        int correct = prev == (i - n);
        printf("Previous Sample: %d\n", prev);
        if (!correct) {
            printf("INCORRECT PREVIOUS SAMPLE: XXXXXXXXXXXXXXXXXXXXXXXXX");
        }
    }
    printf("\nisBufferEmpty?: %d\n", isBufferEmpty(buffer, size));
   return 0;
}
