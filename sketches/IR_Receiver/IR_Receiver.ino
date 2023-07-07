#include <IRremote.h>

// Testing with IRremote 4.1.2

#define IR_RECEIVE_PIN 11

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
}

void loop() {
  if (IrReceiver.decode()) {
    IrReceiver.resume();
    Serial.println(IrReceiver.decodedIRData.command);
  }
}