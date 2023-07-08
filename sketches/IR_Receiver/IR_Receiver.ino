#include <IRremote.h>

// Testing with IRremote 4.1.2

#define IR_RECEIVE_PIN 2

void setup() {
  Serial.begin(9600);

  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

  IrReceiver.begin(IR_RECEIVE_PIN);

  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
}

void loop() {
  if (IrReceiver.decode()) {
    IrReceiver.resume();
    Serial.println(IrReceiver.decodedIRData.command);
  }
}