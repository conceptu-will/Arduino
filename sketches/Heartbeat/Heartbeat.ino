/*
  Heartbeat
*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  beat();
  beat();
  delay(500);
}

void beat() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(125);
  digitalWrite(LED_BUILTIN, LOW);
  delay(125);
}