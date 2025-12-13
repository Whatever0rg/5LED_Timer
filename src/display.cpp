#include <Arduino.h>
#include "display.h"
#include "config.h"

void countdisplay(int *ptr_display, int counter){
  int mod = counter % 5;
  for(int i = 0; i < 5; i++){
    if ((i+1) < mod){
      ptr_display[i] = BRIGHTNESS;
    } else{
      ptr_display[i] = 0;
    }
  }
  //Serial.println("Counter");
}

void dimdisplay(int *ptr_display, int dimmer){
  for(int i = 0; i < 5; i++){
    ptr_display[i] = dimmer;
  }
  //Serial.println("Dimmer");
}

void updatedisplay(int ledBrightness[5]){
  //Serial.print("Update");
  analogWrite(LED1, ledBrightness[0]);
  analogWrite(LED2, ledBrightness[1]);
  analogWrite(LED3, ledBrightness[2]);
  analogWrite(LED4, ledBrightness[3]);
  analogWrite(LED5, ledBrightness[4]);
}
