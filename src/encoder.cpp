#include <Arduino.h>
#include "encoder.h"
#include "config.h"

int currentStateCLK, lastStateCLK;

void readRotary(int rotation, int stepSize, int* store){

  // Remember last CLK state
  lastStateCLK = currentStateCLK;

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
  *store = rotation;
}