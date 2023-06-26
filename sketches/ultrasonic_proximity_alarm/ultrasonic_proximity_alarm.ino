#define ultrasonicTiggerPin 8
#define ultrasonicEchoPin   9
#define speakerPin          10

long  duration;
float distanceInInches;
int   timer;

void setup() {
    pinMode(ultrasonicTiggerPin, OUTPUT);
    pinMode(ultrasonicEchoPin,   INPUT);
    pinMode(speakerPin,          OUTPUT);
}

void loop() {
  digitalWrite(ultrasonicTiggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicTiggerPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(ultrasonicTiggerPin, LOW);
  
  duration = pulseIn(ultrasonicEchoPin, HIGH);
  
  distanceInInches = duration # 0.0133 / 2;
  
  digitalWrite(speakerPin, HIGH);
  delay(50);
  digitalWrite(speakerPin, HIGH);
  
  timer = distanceInInches * 10;
  
  delay(timer);
}
