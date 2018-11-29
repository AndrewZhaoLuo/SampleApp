#include <Arduino.h>

// because we will be using in C libraries, use C naming conventions
extern "C" {
  #include "print_format.h"
}

// Taken from article: http://playground.arduino.cc/Main/Printf
void print_format(char *fmt, ... ){
        if (!DEBUG) return;

        char buf[PRINT_BUFF_SIZE]; // resulting string limited to 1024 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(buf, PRINT_BUFF_SIZE, fmt, args);
        va_end (args);
        Serial.println(buf);
}
