#include "LedControl.h"
#include "joystickLogic/joystickLogic.h"
#include "menu/menu.h"
#include "button/button.h"
#include "lcdDisplay/lcdDisplay.h"
#include "data/data.h"
#include "ledMatrix/ledMatrix.h"
#include "deque/deque.h"
long randNumber;
void setup()
{
  pinMode(ENTER_BUTTON_PIN, INPUT);
  pinMode(contrastPin, OUTPUT);
  analogWrite(contrastPin, 130);

  lcd.begin(16, 2);

  lcd.createChar(0, arrowUp);
  lcd.createChar(1, arrowDown);
  lcd.createChar(2, clickArrow);
  ledMatrixSetup();
  Serial.begin(9600);
}
bool menuScroll = 1;
unsigned long lastMenuScrollChange = 0;
void loop()
{
  buttonCheck();

  short int movementPosition = getMovementPosition();

  if (menuState == NAME && (millis() - lastSwitch > MENU_PAUSE))
  {
    if (buttonState == 1 && lastButtonState != buttonState)
    {
      if (millis() - lastMenuScrollChange > 100)
      {
        menuScroll = !menuScroll;
        lastMenuScrollChange = millis();
      }
    }
  }
  else if (menuState == GAMEPLAY)
  {
    updateMatrix();
  }

  // Menu State Switching
  if (menuScroll)
  {
    verifyChangeJoystick(movementPosition);
    menuStateSwitching(changebleValueJoystick, lastButtonState, movementPosition, buttonState);
  }
  writeText(getText(), menuScroll, verifyMoveUp(), verifyMoveDown());
  //  Serial.println("Sizeof datasys=" + String(sizeof(dataHighscores)));
}
