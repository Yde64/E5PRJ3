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
#include "LEDcontrol.h"

#define LEDlength 21


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    LEDctrl rgbstrip1[LEDlength], rgbstrip2[LEDlength];
    addLEDstrip(LEDlength, rgbstrip1, 1);
    addLEDstrip(LEDlength, rgbstrip2, 2);
    initLED(120);

    setspeed(100, 20);
    ringLED(4, 87, 1.0, 0.7, rgbstrip1);
    pulseLED(200,1,1, rgbstrip2);
    for(;;)
    {
    }
}

/* [] END OF FILE */