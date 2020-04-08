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
#include "WeightSensors_.h"
#define afvigelse 10                //Bestemmer fejlmargin for compareWeight.
#define mVtoG 0.252

char uart_string[50];
///*
WeightSensors  WSptr = {.p1 = 0, .p2 = 0}; //WeightSensor Pointer

uint16 readdata1()
{
    PlayerSelect_Select(0);//vælg player1
    
    ADC_SAR_1_StartConvert();
    if (ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT)!=0){
    WSptr.p1 = ADC_SAR_1_GetResult16();
    WSptr.p1 = ADC_SAR_1_CountsTo_mVolts(WSptr.p1);
    WSptr.p1 /= mVtoG;                                                      // Dividerer med 0.25 for at omregne til gram.
    
    //Debugging-----------------------------
    sprintf(uart_string, "\r\ndata read from player 1: %u", WSptr.p1);     // convert to string
    UART_1_PutString(uart_string);                                         // output string
    //--------------------------------------
    
    }
    return WSptr.p1;
}

uint16 readdata2()
{
    PlayerSelect_Select(1); //vælg player2
    
    ADC_SAR_1_StartConvert();
    if (ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT)!=0){
    WSptr.p2 = ADC_SAR_1_GetResult16();
    WSptr.p2 = ADC_SAR_1_CountsTo_mVolts(WSptr.p2);
    WSptr.p2 /= mVtoG;                                                      // Dividerer med 0.25 for at omregne til gram.
    
    //Debugging-----------------------------
    sprintf(uart_string, "\r\ndata read from player 2: %u", WSptr.p2);     // convert to string
    UART_1_PutString(uart_string);                                         // output string
    //--------------------------------------
    
    }
    return WSptr.p2;
    
}

uint16 readdataLoser(int x)
{
    PlayerSelect_Select(x); //vælg player x
    
    ADC_SAR_1_StartConvert();
    if (ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT)!=0){
    WSptr.pLoser = ADC_SAR_1_GetResult16();
    WSptr.pLoser = ADC_SAR_1_CountsTo_mVolts(WSptr.pLoser);
    WSptr.pLoser /= mVtoG;
    
    //Debugging-----------------------------
    sprintf(uart_string, "\r\ndata read from player 2: %u", WSptr.pLoser);     // convert to string
    UART_1_PutString(uart_string);                                             // output string
    //--------------------------------------
    
    }
    return WSptr.p2;
}

void WeightSensorsInit()
{
    ADC_SAR_1_Start();
    PlayerSelect_Init();
}

int CompareWeight(){

    if (((readdata2() >= (readdata1() - afvigelse)) && (readdata2() <= readdata1() + afvigelse)) || ((readdata1() >= (readdata2() - afvigelse)) && (readdata1() <= readdata2() + afvigelse)))
    {
        return 1;
    }
    else if (readdata2() > readdata1())//spiller 1 fejl
    { 
        return 2;
    }
    else if(readdata2() < readdata1()) //spiller 2 fejl
    {
        return 3;
    }
    else;
    return 0;   //for error handling
}
    //*/
/* [] END OF FILE */
