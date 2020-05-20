#include "Startknap.h"
#include "States.h"
#include "UART.h"

char uart_string1[50];

CY_ISR(isr_button_handler){
    BPptr.ButtonPushed = 1;
}
    