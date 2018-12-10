/*
 Example sketch for the PS4 USB library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <PS4USB.h>
#include <SoftwareSerial.h>
#define rx2Pin 6
#define tx2Pin 7

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
PS4USB PS4(&Usb);

// Create SoftwareSerial objects
SoftwareSerial softSerial(rx2Pin, tx2Pin);

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;

void setup() {
  Serial.begin(115200);  
  pinMode(rx2Pin, INPUT);
  pinMode(tx2Pin, OUTPUT);
  softSerial.begin(9600);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 USB Library Started"));
}

void loop() {
  Usb.Task();

    if (PS4.connected()) {
      // L2 && R2 Rumble
      if (PS4.getAnalogButton(L2) != oldL2Value || PS4.getAnalogButton(R2) != oldR2Value) // Only write value if it's different
        PS4.setRumbleOn(PS4.getAnalogButton(L2), PS4.getAnalogButton(R2));
      oldL2Value = PS4.getAnalogButton(L2);
      oldR2Value = PS4.getAnalogButton(R2);  
      
      if (PS4.getButtonClick(UP)) {
        Serial.print(F("\r\nUp"));
        softSerial.print(F("\r\nUp"));
        PS4.setLed(Green);
        softSerial.write("S"); // COMMAND TO SEND: START
      } 
      if (PS4.getButtonClick(DOWN)) {
        Serial.print(F("\r\nDown"));
        softSerial.print(F("\r\nDown"));
        PS4.setLed(Red);
        softSerial.write("D"); // COMMAND TO SEND

      }
      if (PS4.getButtonClick(LEFT)) {
        Serial.print(F("\r\nLEFT"));
        softSerial.print(F("\r\nLEFT"));
        softSerial.write("1"); // COMMAND TO SEND: FIRE PHASOR

      }
      if (PS4.getButtonClick(RIGHT)) {
        Serial.print(F("\r\nLEFT"));
        softSerial.print(F("\r\nLEFT"));
        softSerial.write("2"); // COMMAND TO SEND: FIRE TORPEDO
      }
      if (PS4.getButtonClick(CROSS)) {
        Serial.print(F("\r\nLEFT"));
        softSerial.print(F("\r\nLEFT"));
        softSerial.write("X"); // COMMAND TO SEND. SWITCH
      }
  }
}
