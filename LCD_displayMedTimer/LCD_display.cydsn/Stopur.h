#include "project.h"
#include "LiquidCrystal_I2C.h"
#include "stdio.h"



void initTimer();          // initiere timer 
void startTimer();         // startet timer_stopur
void stopTimer();          // stopper timer_stopur
int getTime();             // retunerer count værdien som ms
void clearTimer();         // nulstiller timer_stopur
