#include <Arduino.h>

// because we will be using in C libraries, use C naming conventions
extern "C" {
  #include "print_format.h"
}

// Taken from article: http://playground.arduino.cc/Main/Printf
void print_format(char *fmt, ... ){
        if (!DEBUG) return;
  
        char buf[1024]; // resulting string limited to 1024 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(buf, 1024, fmt, args);
        va_end (args);
        Serial.print(buf);
}
