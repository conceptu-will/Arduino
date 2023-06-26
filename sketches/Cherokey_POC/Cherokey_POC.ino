// M2 and M4 are the FRONT and REAR motors on the LEFT side
// M1 and M3 are the FRONT and REAR motors on the RIGHT side

int speedPin_RIGHT = 5;
int speedPin_LEFT = 6;

int directionPin_RIGHT = 4;
int directionPin_LEFT = 7;

int LEFT_MOTOR_FORWARD = LOW;
int LEFT_MOTOR_REVERSE = HIGH;
int RIGHT_MOTOR_FORWARD = HIGH;
int RIGHT_MOTOR_REVERSE = LOW;

void setup(){   
}

void loop(){
carForward(250,50);
delay(2000);
carForward(50,250);
delay(2000);
//carStop();
//delay(1000);
//carTurnLeft(250,250);
//delay(1000);
//carTurnRight(250,250);
//delay(1000);
//carStop();
//delay(5000);
}

void carStop(){
  digitalWrite(speedPin_LEFT,0); 
  digitalWrite(directionPin_RIGHT,RIGHT_MOTOR_FORWARD);
  digitalWrite(speedPin_RIGHT,0);   
  digitalWrite(directionPin_LEFT,LEFT_MOTOR_FORWARD);
}   

void carForward(int leftSpeed,int rightSpeed){   //Move forward
  analogWrite (speedPin_LEFT,leftSpeed);
  digitalWrite(directionPin_LEFT,LEFT_MOTOR_FORWARD);
  analogWrite (speedPin_RIGHT,rightSpeed);
  digitalWrite(directionPin_RIGHT,RIGHT_MOTOR_FORWARD);   
}

void carReverse(int leftSpeed,int rightSpeed){
  analogWrite (speedPin_LEFT,leftSpeed);
  digitalWrite(directionPin_LEFT,LEFT_MOTOR_REVERSE);
  analogWrite (speedPin_RIGHT,rightSpeed);
  digitalWrite(directionPin_RIGHT,RIGHT_MOTOR_REVERSE);
} 

void carTurnLeft(int leftSpeed,int rightSpeed){  //Turn Left
  analogWrite (speedPin_LEFT,leftSpeed);
  digitalWrite(directionPin_LEFT,LEFT_MOTOR_REVERSE);
  analogWrite (speedPin_RIGHT,rightSpeed);
  digitalWrite(directionPin_RIGHT,RIGHT_MOTOR_FORWARD);
}
void carTurnRight(int leftSpeed,int rightSpeed){  //Turn Right
  analogWrite (speedPin_LEFT,leftSpeed);
  digitalWrite(directionPin_LEFT,LEFT_MOTOR_FORWARD);
  analogWrite (speedPin_RIGHT,rightSpeed);
  digitalWrite(directionPin_RIGHT,RIGHT_MOTOR_REVERSE);
}
