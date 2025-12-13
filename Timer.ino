#include "src/config.h"
#include "src/display.h"
#include <EEPROM.h>

// Rotary Encoder Inputs
#define CLK 2
#define DT 3
#define SW 4
#define DIMMER_STEPS 1




int counter = 0 , dimmer = 0;
int currentStateCLK, lastStateCLK;
String currentDir = "";
unsigned long lastButtonPress = 0;
int buttonPresses = 0;
int displayState[5]={0,0,0,0,0};

void setup() {

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
  // Setup Serial Monitor
  Serial.begin(9600);

  // Read the initial state of CLK
  lastStateCLK = digitalRead(CLK);
}


void loop() {
  currentStateCLK = digitalRead(CLK);
  if (currentStateCLK != lastStateCLK && currentStateCLK == 1) {
    if (digitalRead(DT) != currentStateCLK) {
      counter += DIMMER_STEPS;
      dimmer += DIMMER_STEPS;
      Serial.println(counter);
    } else {
      counter -= DIMMER_STEPS;
      dimmer -= DIMMER_STEPS;
      Serial.println(counter);
    }
    if(dimmer < 0){
      dimmer = 0;
    }
    if(dimmer > BRIGHTNESS){
      dimmer = BRIGHTNESS;
    }
  }

  // Remember last CLK state
  lastStateCLK = currentStateCLK;

  // Read the button state
  int btnState = digitalRead(SW);

  if (btnState == LOW) {
    if (millis() - lastButtonPress > 50) { //button is pressed
      Serial.println("Press!!");
      buttonPresses += 1;
    }
    lastButtonPress = millis();
  }

  switch ((buttonPresses%2)) {
  case 0:
    dimdisplay(displayState, dimmer);
    break;
  
  case 1:
    countdisplay(displayState, counter);
    break;
  }


    for (int i = 0; i < 5; i++) {
        Serial.print(displayState[i]);
        Serial.print(" ");
    }
    Serial.println();

  updatedisplay(displayState);//updating display
  
  delay(1);
}