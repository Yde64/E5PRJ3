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
#pragma once
#include "project.h"
#include "WeightSensors_.h"
#include "VT100Terminal.h"

CY_ISR_PROTO(ISR_UART_rx_handler);             // UART Interrupt Service Rutine Handler
void handleByteReceived(uint8_t byteReceived); // handles UART communication
void UARTprint(char* line, char* string);
void clearTerm(int lines);



/* [] END OF FILE */
