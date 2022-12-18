// Implementing the menu as a DFA
#ifndef _MENU_
#define _MENU_

#include "init.h"
#include "../data/data.h"
#define MENU_PAUSE 100

//movement MATRIX for the menu
unsigned long lastSwitch = 0;
byte verifyMoveUp(){
    if(menuMovementMatrix[menuState][1] != NO_ACTION){
        return true;
    }
    return false;
}

byte verifyMoveDown(){
    if(menuMovementMatrix[menuState][0] != NO_ACTION){
        return true;
    }
    return false;
}

void menuStateSwitching(byte changebleValueJoystick, byte lastButtonState, short int joystickMovement, byte buttonState){
    short int result;
    if(changebleValueJoystick){
        if(joystickMovement != -1 && (joystickMovement == 0 || joystickMovement == 1))
        {
            result = menuMovementMatrix[menuState][joystickMovement];
            if (result != NO_ACTION){
                menuState = result;
                lastSwitch = millis();
            }
            
        }
    }
    if(lastButtonState != buttonState){
        if(buttonState == 1){
            result = menuMovementMatrix[menuState][2];
            // Serial.println(result);
            if(result != NO_ACTION){
                menuState = result;
                lastSwitch = millis();
            }
        }   
    }

}
short int menuChangeNameChars(short int joystickMovement, short int charIndex){
    // RIGHT 3
    // LEFT 2

        if(joystickMovement != -1)
        {
            // Serial.println(joystickMovement);
            if(joystickMovement == 1){
                Player.name[charIndex] --;
            }
            else if(joystickMovement == 0){
                Player.name[charIndex] ++ ;
            }
            else if(joystickMovement == 2){
                charIndex ++;
            }
            else if(joystickMovement == 3){
                charIndex --;
            }
            

            if(charIndex == -1){
                charIndex = 2;
            }
            else if(charIndex == 3){
                charIndex = 0;
            }
            lastSwitch = millis();
            Serial.println(charIndex);
        }

    return charIndex;
}


char* getText(){
    switch (menuState)
    {
    case START_GAME:
        return "START GAME ";
        break;
    
    case SETTINGS:
        return "SETTINGS ";
        break;

    case HIGHSCORE:
        return "HIGHSCORE ";
        break;

    case ABOUT:
        return "ABOUT ";
        break;

    case HOW_TO_PLAY:
        return "HOW TO PLAY ";
        break;

    case GAMEPLAY:
        return "GAMEPLAY ";
        break;

    case LOST:
        return "You lost! ";
        break;

    case NAME:
        return "Username ";
        break;

    case DIFFICULTY:
        return "Difficulty ";
        break;

    case LCD_CONTRAST:
        return "LCD_CONTRAST ";
        break;   

    case LCD_BRIGTHNESS:
        return "LCD BRIGTHNESS ";
        break;  

     case MATRIX_BRIGHTNESS:
        return "MATRIX BRIGHT ";
        break;  
               
    default:
        return "RESTART THE ARDUINO !! ";
        break;
    }
}

#endif