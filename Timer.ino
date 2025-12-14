#include "src/config.h"
#include "src/display.h"
#include "src/encoder.h"
#include "src/countdown.h"
#include <EEPROM.h>

int counter;
int lastCounter;
int dimmer;
int lastDimmer;
unsigned long lastButtonPress = 0;
int buttonPresses = 0;
int displayState[5]={0,0,0,0,0};
bool hasSaved = false;
int buttonMode = 0;
bool lastBtnState = HIGH;
bool timerStart = false;
unsigned long startTime, time, turnOffInterval;

void setup() {
  // Setup Serial Monitor
  Serial.begin(9600);

  //Load EEPROM
  EEPROM.get(BRIGHTNESS_EEPROM, dimmer);
  dimmer = 256 + dimmer;
  Serial.println(dimmer);
  if (dimmer < 0 || dimmer > 255) {
    dimmer = 0;
  }
  Serial.println(dimmer);


  // Encoder Pins
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);
  
  //LED-MOSFET Pins
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  

  // Turn on Display
  dimdisplay(displayState, dimmer);
}


void loop() {
  lastDimmer = dimmer;
  lastCounter = counter;
  

  // Read the button state
  bool btnState = digitalRead(SW);

if (btnState == LOW && lastBtnState == HIGH) {
  // button was JUST pressed
  unsigned long now = millis();

  if (now - lastButtonPress < DOUBLE_PRESS_DELAY) {
    Serial.println("Double");
    buttonMode = 2;
    hasSaved = false;
  } else {
    Serial.println("Single");
    buttonMode = (buttonMode == 0) ? 1 : 0;
  }

  lastButtonPress = now;
}

lastBtnState = btnState;


  switch(buttonMode){
  case 0:
    if (not timerStart){
      timerStart = true;
    }
    
    readRotary(counter, 1, &counter);
    if(counter < 1){
      counter = 1;
    }
    if(lastCounter!= counter){
      countdisplay(displayState, counter, dimmer);
    }
    if((buttonPresses % 2) == 0 && hasSaved == 0){
      EEPROM.update(BRIGHTNESS_EEPROM, dimmer);
      Serial.println("Saved to EEPROM");
      Serial.println(EEPROM.read(BRIGHTNESS_EEPROM));
      hasSaved = true;
    }
    break;
  
  case 1:
    if(timerStart){
    startTime = millis();
    countdownsetup(counter, displayState, dimmer, &time, &turnOffInterval);
    timerStart = false;
    }
    countdownincrement(time, turnOffInterval, startTime, displayState, dimmer);
    break;

  case 2:
    readRotary(dimmer, DIMMER_STEPS, &dimmer);

    if(dimmer < 0){
      dimmer = 0;
    }
    if(dimmer > 255){
      dimmer = 255;
    }

    if(lastDimmer != dimmer){
      dimdisplay(displayState, dimmer);
    }
    break;
  }
/*
  for (int i = 0; i < 5; i++) {
      Serial.print(displayState[i]);
      Serial.print(" ");
  }
  Serial.println();
*/

  updatedisplay(displayState);//updating display
  
  delay(1);
}