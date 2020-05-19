/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* [] END OF FILE */
#pragma once
#include "project.h"
#include "LiquidCrystal_I2C.h"
#include "stdio.h"


void initDisp(int refreshrate);                    // Initiere display                              // 
void dispTime(int display, int tid);               // positionere og udskriver på displays
void stopLCD(int display);                         // stopper opdateringen af displayet
void StartDisp();




