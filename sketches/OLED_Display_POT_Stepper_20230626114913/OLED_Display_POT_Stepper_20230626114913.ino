// I2C Communication
#include <Wire.h>

// Display
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Stepper
#include <Stepper.h>

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an Arduino UNO:
//    A4(SDA)
//    A5(SCL)

#define SCREEN_WIDTH    128 // OLED display width, in pixels
#define SCREEN_HEIGHT   32  // OLED display height, in pixels
#define OLED_RESET     -1   // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int potPin = A1;
int previousPotValue = 0;
int currentPotValue = 0;

const int stepsPerRevolution = 200;

Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

#define SCREEN_ADDRESS 0x3C   ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

void setup() {
  myStepper.setSpeed(60);
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // potPin, as it's an INPUT pin, does not need to be initialized like OUTPUT pins.

}

void loop() {
  currentPotValue = analogRead(potPin);

  // if (abs(currentPotValue - previousPotValue) < 5) {
  //   return;
  // }

  previousPotValue = currentPotValue;

  int numberOfSteps = map(currentPotValue, 0, 1023, 0, 200);
  // int degreesPerStep = getDegreesPerStep(numberOfSteps);

  myStepper.step(numberOfSteps);
  report(numberOfSteps);
  delay(1000);
}

// int getDegreesPerStep(int numberOfSteps) {
//   return 360 / numberOfSteps;
// }

void report(int numberOfSteps) {
  display.clearDisplay();

  display.setCursor(0,0);

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.print("Steps: ");
  display.println(format(numberOfSteps));

  display.display();
}

String format(int value) {
  char formatted[3];
  sprintf(formatted, "%03d", value);
  return formatted;
}
