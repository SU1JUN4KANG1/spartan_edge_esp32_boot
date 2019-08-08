// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    int c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
}

void setup() {
  Wire.begin(0x20);                // join i2c bus with address #0x20

  //Wire.onReceive(receiveEvent); // register event
  //user_onReceive = receiveEvent;
  Serial.begin(115200);           // start serial for output
}

uint8_t cnt1 =0;
int a;
void loop() {
  cnt1 = Wire.requestFrom(0x20,1);
  while (1 < Wire.available()) { // loop through all but the last
    int c = Wire.read();  // receive byte as a character
    Serial.print(c);         // print the character
    Serial.println("a"); 
  }
  
  Serial.println("cnt1"); 
  Serial.println(cnt1); 

  Serial.println(Wire.peek()); 

  delay(100);
}
