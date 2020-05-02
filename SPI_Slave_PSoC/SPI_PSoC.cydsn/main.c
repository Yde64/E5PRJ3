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
#include "SPI_Master.h"

CY_ISR_PROTO(SPItester);

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    SPIS_initSPI();
    tester_StartEx(SPItester);
    
    
    for(;;)
    {
    }
}

CY_ISR(SPItester){
    SPIS_sendData(50,9);
}

/* [] END OF FILE */
