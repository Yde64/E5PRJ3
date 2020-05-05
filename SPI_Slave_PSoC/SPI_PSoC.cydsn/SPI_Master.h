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
#include <project.h>

CY_ISR_PROTO(isr_spi_rx);

void SPIS_initSPI();
void SPIS_sendData(int sek,int ms);
void SPIS_checkData(int rxData);

/* [] END OF FILE */