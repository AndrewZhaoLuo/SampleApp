#include "circularBuffer.h"
#include "globals.h"

void pushBack(const int item) {
  if(!(circBuf.empty)){
    if (circBuf.tail == circBuf.head) {
      circBuf.head++;
    }
  }
  circBuf.buffer[circBuf.tail] = item;
  circBuf.tail++;
  if (circBuf.tail > circBuf.endIndex) {
    circBuf.tail = 0;
  }
  circBuf.empty = FALSE;
  batteryLevelPtr = &(circBuf.buffer[circBuf.tail]);
}
