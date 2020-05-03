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


//    U A R T    E R    U D E L U K K E N D E    F O R    D E B U G G I N G  
#include "UART.h"
#include "WeightSensors_.h"


CY_ISR(ISR_UART_rx_handler)
{
    uint8_t bytesToRead = UART_1_GetRxBufferSize();
    while (bytesToRead > 0)
    {
        uint8_t byteReceived = UART_1_ReadRxData();
        
        handleByteReceived(byteReceived);
        
        bytesToRead--;
    }
}

void handleByteReceived(uint8_t byteReceived)
{
    switch(byteReceived)
    {
        case '1' :
        {
            //getWeight(1);
            getCalWeight(1);
        }
        break;
        case '2' :
        {
            //getWeight(2);
            getCalWeight(2);
        }
        break;
      
    }
}

void UARTprint(char* line, char* string)
{
    movecursor(line, "0");
    delline(1);
    movecursor(line, "0");
    UART_1_PutString(string);
}

void clearTerm(int lines)
{
    char buf[10];
        for(int i = 0;i < lines; i++)
    {
        
        snprintf(buf, 5, "%d", i);
        
        movecursor(buf, "0");
        delline(1);
    }
}
/* [] END OF FILE */
