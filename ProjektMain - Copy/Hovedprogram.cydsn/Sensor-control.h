#pragma once

#include <stdio.h>
#include <stdint.h>
#include "project.h"
#include "UART.h"

typedef struct WeightSensors_
{
    int CalibrateP1; //buffer
    int CalibrateP2; //buffer
    
    long p1; //buffer
    long p2; //buffer
    long p1cal; //player1 data
    long p2cal; //player2 data
    long pLoser; //Loser data

}WeightSensors;

long getWeight(int Player);
int getCalWeight(int Player);
int getWeightLoser(int Player);
void CalibrateSensors();

void WeightSensorsInit();
int CompareWeight();