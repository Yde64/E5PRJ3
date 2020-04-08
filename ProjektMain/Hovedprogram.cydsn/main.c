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
//#include "project.h"
#include "WeightSensors_.h"
#include "UART.h"
#include "Display.h"
#include "Startknap.h"
#include "States.h"


#define LEDlength 21


//WeightSensors  _WSptr = {.p1 = 0, .p2 = 0}; //WeightSensor Pointer

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    // SPIM_1_Start();
    isr_button_StartEx(isr_button_handler);
    isr_uart_rx_StartEx(ISR_UART_rx_handler);
    UART_1_Start();
    
    WeightSensorsInit();
    //LEDctrl rgbstrip1[LEDlength], rgbstrip2[LEDlength];
    //addLEDstrip(LEDlength, rgbstrip1, 1);
    //addLEDstrip(LEDlength, rgbstrip2, 2);
    //initLED(60);
    
    //ringLED(100,4,87,1.0,0.7);
    //pulseLED(20,100,1,1);
    
    //states state = IDLE;
    
    for(;;)
    {
        
        Next_state_Logic();
        Output_logic();
    }
    
}


/* [] END OF FILE */
