#pragma once
#include "project.h"
#include "LiquidCrystal_I2C.h"
#include "stdio.h"


void initDisp(int refreshrate);                    // Initiere display                              // 
void dispTime(int display, int time);               // positionere og udskriver på displays
void stopDisp(int display);                         // stopper opdateringen af displayet
void StartDisp();