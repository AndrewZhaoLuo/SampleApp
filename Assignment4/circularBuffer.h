#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H
#include "bool.h"

typedef struct circular_buf {
  int buffer[16];
  int head;
  int tail;
  int endIndex;
  Bool empty;
} circularBuffer;

void pushBack(circularBuffer* circBuf, const int item);

#endif // CIRCULAR_BUFFER_H
