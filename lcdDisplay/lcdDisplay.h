#include <LiquidCrystal.h>
#include <string.h>
#include "init.h"
#include "../data/data.h"
#include "../menu/menu.h"
#include "../joystickLogic/joystickLogic.h"
#include "../ledMatrix/ledMatrix.h"
short int charIndex = 0;
void writeText(char *msg, bool menuScroll, byte verifyMoveUp, byte verifyMoveDown)
{
  if (millis() - lastRefresh > REFRESH_RATE)
  {
    lcd.clear();
    if (!menuScroll)
    {
      if (strcmp(msg, "Username ") == 0)
      {
        short int movementPosition = getMovementPosition();
        // hardcoded TODO
        // verifyChangeJoystick(movementPosition);
        charIndex = menuChangeNameChars(movementPosition, charIndex);

        if (millis() - lastArrowBlink > BLINK_TIME_ARROW)
        {
          lcd.setCursor(7 + charIndex, 0);
          lcd.write(byte(0));
          lastArrowBlink = millis();
        }

        lcd.setCursor(7, 1);
        lcd.print(Player.name[0]);
        lcd.print(Player.name[1]);
        lcd.print(Player.name[2]);
      }
    }
    else
    {
      if (menuState == GAMEPLAY)
      {
        // Serial.println("suntem aici");
        lcd.setCursor(1, 0);
        lcd.print("Difficulty: ");
        lcd.print(difficulty);
        lcd.setCursor(1, 1);
        lcd.print("Score: ");
        lcd.print(Player.score);
      }
      if (menuState == LOST)
      {
        lcd.setCursor(1, 1);
        lcd.print("Score: ");
        lcd.print(lastPlayerScore);
      }

      lcd.setCursor(0, 0);
      // lcd.print(msg);

      if (menuState != GAMEPLAY)
      {
        lcd.print(msg);

        lcd.write(byte(2));
      }

      if (verifyMoveUp)
      { // verify if menu can go up
        lcd.setCursor(15, 0);
        lcd.write(byte(0));
      }
      if (verifyMoveDown)
      { //verify if menu can go
        lcd.setCursor(15, 1);
        lcd.write(byte(1));
      }
    }
    lastRefresh = millis();
  }
}