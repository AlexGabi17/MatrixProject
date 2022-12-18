#define ENTER_BUTTON_PIN 13

byte reading;
byte lastReading = LOW;
byte buttonState;       
byte lastButtonState = LOW; 
byte buttonPressed;
byte lastButtonPressed = LOW;
unsigned long lastDebounceTimePressed = 0;
unsigned long debounceDelayPressed = 50;




void buttonCheck() {
reading = digitalRead(ENTER_BUTTON_PIN);
  if (reading != lastButtonState) {
    lastDebounceTimePressed = millis();
  }
  if (millis() - lastDebounceTimePressed > debounceDelayPressed) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW ) {
        if (!buttonPressed) { // to not reset the timer if the button is pressed multiple times
            buttonPressed = 1;
        }
        else {
            buttonPressed = 0;
        }
      }
    }
  }
  lastButtonState = reading;
}