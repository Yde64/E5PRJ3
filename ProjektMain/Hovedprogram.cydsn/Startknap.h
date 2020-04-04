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
#include "States.h"

typedef struct ButtonPushed{
    int ButtonPushed;
}Button;

Button BPptr; //skal gøres for at være global åbenbart

CY_ISR(isr_button_handler);

