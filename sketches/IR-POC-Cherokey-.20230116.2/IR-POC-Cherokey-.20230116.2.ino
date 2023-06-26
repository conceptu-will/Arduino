#include <LiquidCrystal_I2C.h>
#include <IRremote.h> // include the IRremote library
#include <Wire.h>

#define IR_RECEIVER_PIN 11 // define the IR receiver pin

// CHEROKEY
int SPEED_RIGHT_PIN = 5;
int SPEED_LEFT_PIN = 6;

int DIRECTION_RIGHT_PIN = 4;
int DIRECTION_LEFT_PIN = 7;

int LEFT_MOTOR_FORWARD = LOW;
int LEFT_MOTOR_REVERSE = HIGH;
int RIGHT_MOTOR_FORWARD = HIGH;
int RIGHT_MOTOR_REVERSE = LOW;

// IR
const uint32_t UP    = 0xf003d14a;
const uint32_t RIGHT = 0x82941f86;
const uint32_t DOWN  = 0xb9f72f4c;
const uint32_t LEFT  = 0x670a99e8;
const uint32_t ENTER = 0xFAE68EEA;

IRrecv receiver(IR_RECEIVER_PIN);
decode_results results;

int leftSpeed = 0;
int rightSpeed = 0;
int absoluteSpeedUnit = 25;

void setup() {
  Serial.begin(9600); // begin serial communication with a baud rate of 9600

  receiver.enableIRIn(); // enable the receiver
  receiver.blink13(true); // enable blinking of the built-in LED when an IR signal is received

  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
}

void loop() {
    // Using SAMSUNG remote.
    // DEPRECATED API?  But this API is easier to understand, pull the results.value from.  Current API example?
    if (receiver.decode(&results)) {
      handleIRValue(results.value);      

      receiver.resume(); // reset the receiver for the next code
      
      delay(50);
    }
}

void handleIRValue(uint32_t irValue) {
  switch(irValue) {
    case UP: {
      Serial.println("*** UP ***");
      handleUp();
      break;
    }
    case RIGHT: {
      Serial.println("*** RIGHT ***");
      handleRight();
      break;
    }
    case DOWN: {
      Serial.println("*** DOWN ***");
      handleDown();
      break;
    }
    case LEFT: {
      Serial.println("*** LEFT ***");
      handleLeft();
      break;
    }
    case ENTER: {
      Serial.println("*** ENTER ***");
      handleEnter();
      break;
    }
    default: {
      Serial.println(irValue, HEX);
      break;
    }
  }
}

void handleUp() {
  leftSpeed++;
  rightSpeed++;
  drive();
}

void handleRight() {
  leftSpeed++;
  rightSpeed--;
  drive();
}

void handleDown() {
  leftSpeed--;
  rightSpeed--;
  drive();
}

void handleLeft() {
  leftSpeed--;
  rightSpeed++;
  drive();
}

void handleEnter() {
  leftSpeed = 0;
  rightSpeed = 0;
  drive();
}

void drive() {
  setLeftMotors();
  setRightMotors();
}

void setLeftMotors() {
  int direction = LEFT_MOTOR_FORWARD;
  String directionText = "FORWARD";
  
  if (leftSpeed < 0) {
    direction = LEFT_MOTOR_REVERSE;
    directionText = "REVERSE";
  } 

  int absoluteSpeed = max(abs(leftSpeed), 255);
  
  Serial.println("LEFT MOTOR ===============================");
  Serial.println("SPEED: " + leftSpeed);
  Serial.println("DIRECTION: " + directionText);
  Serial.println("CALCULATED SPEED: " + absoluteSpeed);

  digitalWrite(DIRECTION_LEFT_PIN,  direction);
  digitalWrite(SPEED_LEFT_PIN,      absoluteSpeed); 
}

void setRightMotors() {
  int direction = RIGHT_MOTOR_FORWARD;
  String directionText = "FORWARD";
  
  if (leftSpeed < 0) {
    direction = RIGHT_MOTOR_REVERSE;
    directionText = "REVERSE";
  } 

  int absoluteSpeed = max(abs(rightSpeed), 255);
  
  Serial.println("RIGHT MOTOR ===============================");
  Serial.println("SPEED: " + rightSpeed);
  Serial.println("DIRECTION: " + directionText);
  Serial.println("CALCULATED SPEED: " + absoluteSpeed);

  digitalWrite(DIRECTION_RIGHT_PIN,  direction);
  digitalWrite(SPEED_RIGHT_PIN,      absoluteSpeed); 
}
