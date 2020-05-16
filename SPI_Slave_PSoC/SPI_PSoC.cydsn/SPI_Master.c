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
#include "SPI_Master.h"

int tx[2];

void SPIS_initSPI(){            //initialize SPI
    SPI_int_Write(0);           //drive interrupt pin low.
    SPIS_Start();               
    SPIS_ClearTxBuffer();
    SPIS_ClearFIFO();
    rx_isr_StartEx(isr_spi_rx);
}

void SPIS_sendData(int sek, int ms){
    tx[0] = sek;
    tx[1] = (sek%2) == 0 ? (ms<<2) : ((ms<<2) | 0b10);        //sek parity
    tx[1] = (ms%2) == 0 ? tx[1] : (tx[1] | 0b01);             //ms parity
    //send interrupt to SPIM
    SPI_int_Write(255);
}

void SPIS_checkData(int rxData){
    switch(rxData){
        case 0x20 :
        {
            SPIS_WriteTxData(tx[0]);    //sek
        }
        break;
        case 0x10 :
        {
            SPIS_WriteTxData(tx[1]);    //ms
        }
        break;
        default :
        {
            SPIS_WriteTxData(rxData);     //echo
        }
    }
}

CY_ISR(isr_spi_rx){
    SPI_int_Write(0);
    uint8 SPIDATA = SPIS_ReadRxData();
    SPIS_checkData(SPIDATA);
}

/* [] END OF FILE */
