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
#pragma once

#include <stdio.h>
#include <stdint.h>
#include "project.h"
#include "UART.h"

typedef struct WeightSensors_
{
    int CalibrateP1; //Kalibreringsværdi
    int CalibrateP2; //Kalibreringsværdi
    
    int p1;     //buffer
    int p2;     //buffer
    int p1cal;  //player1 data
    int p2cal;  //player2 data
    int pLoser; //Loser data

}WeightSensors;

int getWeight(int Player);
int getCalWeight(int Player);
int getWeightLoser(int x);
void CalibrateSensors();

void WeightSensorsInit();
int CompareWeight();


/* [] END OF FILE */
