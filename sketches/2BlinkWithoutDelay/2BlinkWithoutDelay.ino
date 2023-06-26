/*
  Blink-ish

  Uses an LED state, interval, and timeout to independently control
  the regular blinking of two LEDs with two different intervals.

  Based on the ubiquitous "BLINK".

  modified 2023-03-23
  by Will Garnett
  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.
*/

int EXTERNAL_LED_PIN = 9;
int BAR_PIN = 10;

unsigned long externalTimeout;
int externalInterval = 300;
boolean externalState = true;

unsigned long barTimeout;
int barInterval = 750;
boolean barState = true;

unsigned long builtinTimeout;
int builtinInterval = 100;
boolean builtinState = true;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(EXTERNAL_LED_PIN, OUTPUT);
  pinMode(BAR_PIN, OUTPUT);

  externalTimeout = millis() + externalInterval;
  barTimeout = millis() + barInterval;
  builtinTimeout = millis() + builtinInterval;
}

void loop() {
  checkBar();
  checkExternal();
  checkBuiltin();
}

void checkBar() {
  unsigned long currentMillis = millis();
  if (currentMillis > barTimeout) {
    barState = !barState;
    digitalWrite(BAR_PIN, barState);
    barTimeout = millis() + barInterval;
  }
}

void checkExternal() {
  unsigned long currentMillis = millis();
  if (currentMillis > externalTimeout) {
    externalState = !externalState;
    digitalWrite(EXTERNAL_LED_PIN, externalState);
    externalTimeout = millis() + externalInterval;
  }
}

void checkBuiltin() {
  unsigned long currentMillis = millis();
  if (currentMillis > builtinTimeout) {
    builtinState = !builtinState;
    digitalWrite(LED_BUILTIN, builtinState);
    builtinTimeout = millis() + builtinInterval;
 }
}