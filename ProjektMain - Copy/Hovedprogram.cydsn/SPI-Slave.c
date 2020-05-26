#include "SPI-Slave.h"

int rxFlag = 0;
int tx[2];

void initSPI(){         //make spi ready to work...
    SPI_int_Write(0);
    SPIS_Start();
    rx_isr_StartEx(isr_spi_rx);
}

void sendData(int sek, int ms){
    tx[0] = sek;
    tx[1] = (sek%2) == 0 ? (ms<<2) : ((ms<<2) | 0b10);        //sek parity
    tx[1] = (ms%2) == 0 ? tx[1] : (tx[1] | 0b01);             //ms parity
    
    //send interrupt to SPIM
    SPI_int_Write(255);
    //send chugtime(data) to tx ready to send
}

CY_ISR(isr_spi_rx){
    SPI_int_Write(0);
    uint8 SPIDATA = SPIS_ReadRxData();
    
    switch(SPIDATA){
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
            SPIS_WriteTxData(SPIDATA);     //echo
        }
    }
}