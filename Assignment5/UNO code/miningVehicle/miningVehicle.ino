// The software serial will be used to communicate with the ATMega2560 
// The provided serial will be used to receive commands from Putty, 
//    acting as requests from the mining and transport vehicles

#include <SoftwareSerial.h>

char incomingByte;
char requestByte;

// Define the digital pins to use as RX and TX for the software serial connection
#define rxPin 10
#define txPin 11

// Create SoftwareSerial objects
SoftwareSerial rf(rxPin, txPin);

void setup() {
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  Serial.begin(9600);
  rf.begin(9600);
}

void loop() {
  // read incoming byte from mega
  if (rf.available() > 0) {
    incomingByte = rf.read();
    
    // Fwd, Back, Left, Right, Drill down, Drill up
    if(incomingByte == 'f' || incomingByte == 'F' || incomingByte == 'b' || incomingByte == 'B' || incomingByte == 'l' ||
    incomingByte == 'L' || incomingByte == 'r' || incomingByte == 'R' || incomingByte == 'd' || incomingByte == 'D' ||
    incomingByte == 'h' || incomingByte == 'H'){
      rf.write('A');
    }

    // Start image capture
    else if (incomingByte == 's' || incomingByte == 'S') {
      rf.write('W');
    }
    
    // Send image data
    else if (incomingByte == 'i' || incomingByte == 'I') {
      rf.write('P');
    }
    
    // Receive lift off and docking response from satellite
    else if (incomingByte == 'K' || incomingByte == 'C') {
      Serial.print("Response: ");
      Serial.println(incomingByte);
      rf.write(static_cast<byte>('\0'));
    } else {
      rf.write(static_cast<byte>('\0'));
    }
  }

  // Read request byte from putty terminal
  if (Serial.available() > 0) {
    requestByte = Serial.read();
    rf.write(requestByte);
    Serial.println("SENT");
  }
}
