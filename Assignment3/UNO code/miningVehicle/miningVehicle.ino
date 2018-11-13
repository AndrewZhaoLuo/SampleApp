char incomingByte;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // read incoming byte from mega
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if(incomingByte == 'f' || incomingByte == 'F' || incomingByte == 'b' || incomingByte == 'B' || incomingByte == 'l' ||
    incomingByte == 'L' || incomingByte == 'r' || incomingByte == 'R' || incomingByte == 'd' || incomingByte == 'D' ||
    incomingByte == 'h' || incomingByte == 'H'){
      Serial.write('A');
    } else {
      Serial.write('\0');
    }
  }
}
