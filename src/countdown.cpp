#include <Arduino.h>
#include "countdown.h"
#include "config.h"

void countdownsetup(int counter, int *ptr_display, int dimmer, unsigned long *ptr_time, unsigned long*ptr_turnOffIntervall){
    *ptr_time = counter*60000;
    *ptr_turnOffIntervall = (counter*60000)/5;
    for(int i = 0; i < 5; i++){
        ptr_display[i] = dimmer;
    }
}
void countdownincrement(unsigned long time, unsigned long turnOffIntervall, unsigned long startTime, int *ptr_display, int dimmer){
    unsigned long timePassed = millis()-startTime;
    //Serial.println(time);
    for(int i = 0; i < 5 && timePassed < time; i++){
        Serial.println("is running");
        if(timePassed > (turnOffIntervall*(i+1))){
            ptr_display[i] = 0;
        }
        
    }
    if(timePassed > time){
        for(int i = 0; i < 5; i++){
            ptr_display[i] = dimmer;
        }
    }
}