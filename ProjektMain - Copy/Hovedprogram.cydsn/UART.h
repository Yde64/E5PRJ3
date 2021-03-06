#pragma once
#include "project.h"
#include "Sensor-control.h"
#include "VT100Terminal.h"

CY_ISR_PROTO(ISR_UART_rx_handler);             // UART Interrupt Service Rutine Handler
void handleByteReceived(uint8_t byteReceived); // handles UART communication
void UARTprint(char* line, char* string);
void clearTerm(int lines);