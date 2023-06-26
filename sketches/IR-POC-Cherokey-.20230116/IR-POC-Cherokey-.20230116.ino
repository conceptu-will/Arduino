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
int speedUnit = 25;

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
      handleUp();
      break;
    }
    case RIGHT: {
      handleRight();
      break;
    }
    case DOWN: {
      handleDown();
      break;
    }
    case LEFT: {
      handleLeft();
      break;
    }
    case ENTER: {
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
  dissect();

  setLeftMotors();
  setRightMotors();
}

void dissect() {
  Serial.print("Forward: ");
  Serial.println(leftSpeed);
  Serial.print("Clockwise: ");
  Serial.println(rightSpeed);
}

void setLeftMotors() {
  int direction = (leftMotorSpeed > 0) ? LEFT_MOTOR_FORWARD : LEFT_MOTOR_REVERSE;
  int speed = max(abs(leftMotorSpeed), 255);

  digitalWrite(DIRECTION_LEFT_PIN,  direction);
  digitalWrite(SPEED_LEFT_PIN,      speed); 
}

void setRightMotors() {
  int direction = (rightMotorSpeed > 0) ? RIGHT_MOTOR_FORWARD : RIGHT_MOTOR_REVERSE;
  int speed = max(abs(rightMotorSpeed), 255);

  digitalWrite(DIRECTION_RIGHT_PIN,  direction);
  digitalWrite(SPEED_RIGHT_PIN,      speed); 
}

void carStop(){
  digitalWrite(SPEED_LEFT_PIN, 0); 
  digitalWrite(DIRECTION_LEFT_PIN, LEFT_MOTOR_FORWARD);

  digitalWrite(SPEED_RIGHT_PIN, 0);   
  digitalWrite(DIRECTION_RIGHT_PIN, RIGHT_MOTOR_FORWARD);
}   

