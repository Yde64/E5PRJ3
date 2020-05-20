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
#include "VT100Terminal.h"

void delline(int numberoflines)
{
        for(int i = 0; i < numberoflines; i++) 
    {
        UART_1_PutString("\x1b[2K");
    }
}

void movecursor(char* y, char* x)
{
    UART_1_PutString("\x1b[");
    UART_1_PutString(y);
    UART_1_PutString(";");
    UART_1_PutString(x);
    UART_1_PutString("f");
}

void setcolor(char color)
{
    switch(color)
    {
        case 'r' :
        {
            UART_1_PutString("\x1b[91m");
        }
        break;
        case 'g' :
        {
            UART_1_PutString("\x1b[92m");
        }
        break;
        case 'b' :
        {
            UART_1_PutString("\x1b[94m");
        }
        break;
        case 'd' :
        {
            UART_1_PutString("\x1b[0m");
        }
        break;
        default :
        {
            UART_1_PutString("\x1b[0m");
        }
        
    }
    
}