#pragma once
#include "project.h" 
#include "Start.h"
#include "Sensor-control.h"


typedef enum {
    IDLE, 
    GOING_IDLE,
    EVALUATING_WEIGHT,
    READY,
    COUNTDOWN,
    CHUG,
    WINNER_DONE,
    EVALUATING_NEW_WEIGHT,
    LOSER_DONE,
    WEIGHT_CONFIRMED,
    
    LOSER_P1,
    LOSER_P2,
    WINNER_P1,
    WINNER_P2,
    
    GAME_OVER,
    
    ERR_WEIGHT,
    ERR_NO_START,
    ERR_FALSE_START,
    ERR_TIMEOUT,
    ERR_NOCHUG,
    ERR_CHEATSEQ,
} states;


void Next_state_Logic();
void Output_logic();
