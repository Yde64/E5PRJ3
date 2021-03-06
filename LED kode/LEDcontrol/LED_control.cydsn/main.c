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

#define LEDlength 10


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    LEDctrl rgbstrip1[LEDlength], rgbstrip2[LEDlength];
    addLEDstrip(LEDlength, rgbstrip1, 1);
    addLEDstrip(LEDlength, rgbstrip2, 2);
    initLED(60);

    setspeed(100, 20, 300);
    //weightapprovedSeq(rgbstrip1);
    //checkSeq(rgbstrip2);
    //idleSeq(rgbstrip2);
    fillcolor(240, 0.001, 1, rgbstrip2);
    //checkSeq(rgbstrip2);
    //zeroCalibrateSeq(rgbstrip1);
    
    
    //checkSeq(rgbstrip1);
    //checkSeq(rgbstrip2);
    for(;;)
    {
        //while(startSeq(rgbstrip1, rgbstrip2) == 0);
    }
}

/* [] END OF FILE */
