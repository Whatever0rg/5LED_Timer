#include "src/config.h"
#include "src/display.h"
#include <EEPROM.h>

// Rotary Encoder Inputs
#define CLK 2
#define DT 3
#define SW 4
#define DIMMER_STEPS 5




int counter;
int lastCounter;
int dimmer;
int lastDimmer;
int currentStateCLK, lastStateCLK;
String currentDir = "";
unsigned long lastButtonPress = 0;
int buttonPresses = 0;
int displayState[5]={0,0,0,0,0};
int hasSaved;

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
  

  // Read the initial state of CLK
  lastStateCLK = digitalRead(CLK);

  // Turn on Display
  dimdisplay(displayState, dimmer);
}

int readRotary(int rotation, int stepSize){
  currentStateCLK = digitalRead(CLK);
  if (currentStateCLK != lastStateCLK && currentStateCLK == 1){
    if (digitalRead(DT) != currentStateCLK){
      rotation += stepSize;
      Serial.println(rotation);
    } else {
      rotation -= stepSize;
      Serial.println(rotation);
    }
  }
  return rotation;
}

void loop() {
  lastDimmer = dimmer;
  lastCounter = counter;
  

  // Remember last CLK state
  lastStateCLK = currentStateCLK;

  // Read the button state
  int btnState = digitalRead(SW);

  if (btnState == LOW) {
    if (millis() - lastButtonPress > 50){ //button is pressed
      Serial.println("Press!!");
      buttonPresses += 1;
      counter = 0;
      hasSaved = 0;
    }
    lastButtonPress = millis();
  }


  if((buttonPresses % 2) == 1 && hasSaved == 0){
    EEPROM.update(BRIGHTNESS_EEPROM, dimmer);
    Serial.println("Saved to EEPROM");
    Serial.println(EEPROM.read(BRIGHTNESS_EEPROM));
    hasSaved = 1;
  }


  switch ((buttonPresses%2)) {
  case 0:
    dimmer = readRotary(dimmer,DIMMER_STEPS);

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
  
  case 1:
    counter = readRotary(counter, 1);

    if(lastCounter!= counter){
      countdisplay(displayState, counter, dimmer);
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