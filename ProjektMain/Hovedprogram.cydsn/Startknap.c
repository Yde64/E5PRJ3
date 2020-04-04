#include "Startknap.h"
#include "States.h"


CY_ISR(isr_button_handler){
    BPptr.ButtonPushed = 1;
       
    BPptr.ButtonPushed = 0;
}
    