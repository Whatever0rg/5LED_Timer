#include "src/config.h"
#include "src/display.h"


// Rotary Encoder Inputs
#define CLK 2
#define DT 3
#define SW 4
#define DIMMER_STEPS 1




int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir = "";
unsigned long lastButtonPress = 0;

void setup() {

  // Encoder Pins
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);
  
  //LED-MOFET Pins
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
      Serial.println(counter);
    } else {
      counter -= DIMMER_STEPS;
      Serial.println(counter);
    }
    if(counter < 0){
      counter = 0;
    }
  }

  // Remember last CLK state
  lastStateCLK = currentStateCLK;

  // Read the button state
  int btnState = digitalRead(SW);

  if (btnState == LOW) {
    if (millis() - lastButtonPress > 50) { //button is pressed
      Serial.println("Press!!");
    }
    lastButtonPress = millis();
  }

  display(counter%5);//updating display
  
  delay(1);
}