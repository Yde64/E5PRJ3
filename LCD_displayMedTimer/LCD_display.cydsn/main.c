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
#include "project.h"
#include "LiquidCrystal_I2C.h"
#include "Display.h"
#include "Stopur.h"

int main(void)
{
    CyGlobalIntEnable; 
    initTimer();                         // Inititer timer_stopur
    initDisp(10);                        // sætter Hz værdien for displayet
    startTimer();                        // starter timer_stopur
   /*
    
        if(getTime()==20000)
        {
            stopLCD(1);
        }
    */
    return 0;
}

/* [] END OF FILE */
