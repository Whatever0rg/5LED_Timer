#include <Arduino.h>
#include "display.h"
#include "config.h"


void display(int LEDcase) {
  switch (LEDcase)
  {
    case 0:
      analogWrite(LED1, 0);
      analogWrite(LED2, 0);
      analogWrite(LED3, 0);
      analogWrite(LED4, 0);
      analogWrite(LED5, BRIGHTNESS);
      break;

    case 1:
      analogWrite(LED1, 0);
      analogWrite(LED2, 0);
      analogWrite(LED3, 0);
      analogWrite(LED4, BRIGHTNESS);
      analogWrite(LED5, BRIGHTNESS);
      break;

    case 2:
      analogWrite(LED1, 0);
      analogWrite(LED2, 0);
      analogWrite(LED3, BRIGHTNESS);
      analogWrite(LED4, BRIGHTNESS);
      analogWrite(LED5, BRIGHTNESS);
      break;

    case 3:
      analogWrite(LED1, 0);
      analogWrite(LED2, BRIGHTNESS);
      analogWrite(LED3, BRIGHTNESS);
      analogWrite(LED4, BRIGHTNESS);
      analogWrite(LED5, BRIGHTNESS);
      break;

    case 4:
      analogWrite(LED1, BRIGHTNESS);
      analogWrite(LED2, BRIGHTNESS);
      analogWrite(LED3, BRIGHTNESS);
      analogWrite(LED4, BRIGHTNESS);
      analogWrite(LED5, BRIGHTNESS);
      break;
  }
  //Serial.println("display called!!");
}
