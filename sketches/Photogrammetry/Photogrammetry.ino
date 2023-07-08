#include <Wire.h>
#include <Adafruit_SSD1306.h>

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1     // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define SCREEN_ADDRESS 0x3C   ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

int SNAPSHOT_LED_PIN = 5;

void setup() {
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SNAPSHOT_LED_PIN, OUTPUT);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

}

void loop() {
  takeSnapshot();
  rotate();
}

void takeSnapshot() {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(SNAPSHOT_LED_PIN, HIGH);
  
  report("CLICK", "Took a picture.");
  
  delay(1000);

  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(SNAPSHOT_LED_PIN, LOW);
}

void rotate() {
  report("SPIN", "New position...");
  delay(2000);
}

void report(String text, String subtext) {
  display.clearDisplay();

  display.setCursor(0,0);             // Start at top-left corner

  display.setTextSize(3);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text

  display.println(text);

  display.setTextSize(1);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.println(subtext);

  display.display();
}
