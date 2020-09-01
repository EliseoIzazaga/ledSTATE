/*
   This is a simple project to demonstrate the
   state machine concept with LEDs that are controlled by
   a Joy stick, The point was to be able to adjust the brightness
   of the 3 LEDs individually with the Joystick, tilting the joystick
   in the negative direction would make the LED dimmer and tilting
   it in the positive direction would make the LED brighter,
   pressing down on the joystick would cycle through the 3
   RED, GREEN, BLUE, if the joystick is tilted at a particular point
   and clicked the brighness of the LED will stay the same as the next
   one to cycle would be adjusted.
*/

const int BLUE = 5;
const int GREEN = 3;
const int RED = 6;
const int joyX = A6;
const int joyY = A5;
const int aSwitch = 7;
const int sDepressed = 0;
const int sNotDepressed = 1;
int currentState = 0;
int currentBrightnessBlue;
int currentBrightnessRed;
int currentBrightnessGreen;
int buttonState;
enum colors {REDstate, GREENstate, BLUEstate};  // We set up an enuerator to add particular states for our switch down in the code
int getConverted()
{ // this function was created to return a value that was within range of 0 and 255 to adjust our LED brightness,
  int ret;
  ret = analogRead(joyX) / 4;
  return ret;
}
void setup()
{
  pinMode(aSwitch, INPUT); // button for joystick
  //pinMode(aSwitch, INPUT_PULLUP);
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  digitalWrite(aSwitch, HIGH);
  Serial.begin(9600);
}
void loop()
{
  switch (currentState)
  { // this is a switch to handle all the states in the enumerator, we must ensure that if we are going to use a switch in
    case REDstate:         // this particular way we have to end all cases with a break statement or else it will roll into the next case and
      Serial.println(buttonState); // execute the code if the conditions are met.
      while (currentState == REDstate) { // the switch is very useful since we can just add more cases and reference to the variables we made in the enumerator
        do {                              // without having to change the code's structure.
          buttonState = digitalRead(aSwitch);
          Serial.println(buttonState);
        } while (sDepressed == digitalRead(aSwitch));
        if (buttonState == 0)
        {
          buttonState = 1;
          currentState = GREENstate;
          break;
        }
        currentBrightnessRed = getConverted();
        analogWrite(RED, currentBrightnessRed);
      }
    case GREENstate:
      Serial.println(buttonState);
      while (currentState == GREENstate)
      {
        do {     // this do while is in place to prevent the next set of the program from being executed until the button is released.
          buttonState = digitalRead(aSwitch);
          Serial.println(buttonState);
        } while (sDepressed == digitalRead(aSwitch));
        if (buttonState == 0)
        {
          buttonState = 1;
          currentState = BLUEstate;
          break;
        }
        currentBrightnessGreen = getConverted();
        analogWrite(GREEN, currentBrightnessGreen);
      }
    case BLUEstate:
      Serial.println(buttonState);
      while (currentState == BLUEstate)
      {
        do {
          buttonState = digitalRead(aSwitch);
          Serial.println(buttonState);
        } while (sDepressed == digitalRead(aSwitch));
        if (buttonState == 0)
        {
          buttonState = 1;
          currentState = REDstate;
          break;
        }
        currentBrightnessBlue = getConverted();
        analogWrite(BLUE, currentBrightnessBlue);
      }
  }
}

/* Need to add serial print statements to control logic flow */
