#ifndef _JOYSTICKLOGIC_
#define _JOYSTICKLOGIC_

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define CHANGE_TIME_VALUE 25

const int pinX = A0; 
const int pinY = A1;
const int pinSW = 2;
int xValue = 0;
int yValue = 0;
unsigned long lastDebounceTimeMovement = 0;
const int debounceTimeMovement = 10;
const int maxHold = 700;
const int minHold = 300;
int lastDebounceValue = -1;
int debounceValue = lastDebounceValue;
int joystickPosition;

unsigned long lastChangeTime = 0;
int lastMovementPosition = -1;

// This var is needed not to allow the user to scroll infinetly without changing
// the position of the joystick. After 1 scroll, the var is false
byte changebleValueJoystick = 1; 

byte getChangebleValueJoystick(){
  return changebleValueJoystick;
}
void verifyChangeJoystick(int movementPosition){
  if(movementPosition != -1){
    if(movementPosition!=lastMovementPosition){
      changebleValueJoystick = 1;
    }
    else{
      changebleValueJoystick = 0;
    }
  }
  lastMovementPosition = movementPosition;
}


int getMovementPosition() {
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  // Serial.println("xValue=" + String(xValue) + ", yValue=" + String(yValue));
  if (millis() - lastDebounceTimeMovement > debounceTimeMovement) {
    lastDebounceTimeMovement = millis();
    lastDebounceValue = debounceValue;
    if (xValue > maxHold && (yValue < maxHold && yValue > minHold)) {
      debounceValue = DOWN;
    }
    else if (xValue < minHold && (yValue < maxHold && yValue > minHold)) {
      debounceValue = UP;
    }
    else if (yValue > maxHold && (xValue < maxHold && xValue > minHold)) {
      debounceValue = LEFT;
    }
    else if (yValue < minHold && (xValue < maxHold && xValue > minHold)) {
      debounceValue = RIGHT;
    }
    else {
      debounceValue = -1;
    }
  }
  if (lastDebounceValue == debounceValue) {
    return debounceValue;
  }
  return -1;
}

#endif