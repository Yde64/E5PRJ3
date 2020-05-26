#pragma once
#include "project.h"
#include "States.h"

typedef struct ButtonPushed{
    int ButtonPushed;
}Button;

Button BPptr; //skal gøres for at være global åbenbart

CY_ISR_PROTO(isr_button_handler);


