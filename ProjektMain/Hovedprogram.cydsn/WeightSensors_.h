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

typedef struct WeightSensors_
{
    uint16 p1; //player1 data
    uint16 p2; //player2 data
    uint16 pLoser; //Loser data

}WeightSensors;

uint16 readdata1();
uint16 readdata2();
uint16 readdataLoser(int x);

void WeightSensorsInit();
int CompareWeight();


/* [] END OF FILE */
