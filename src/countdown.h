#ifndef COUNTDOWN_H
#define COUNTDOWN_H

void countdownsetup(int counter, int *ptr_display, int dimmer, unsigned long *ptr_time, unsigned long*ptr_turnOffIntervall);
void countdownincrement(unsigned long time, unsigned long turnOffIntervall, unsigned long startTime, int *ptr_display, int dimmer);

#endif
