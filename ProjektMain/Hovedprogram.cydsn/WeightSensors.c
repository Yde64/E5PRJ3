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
#define afvigelse 25                //Bestemmer fejlmargin for compareWeight.
#define mVtoG 0.252
#define samples 1000
#define calSamples 200
#define delay 1

char uart_string[50];
int weighthys = 0;

WeightSensors  WSptr = {.p1 = 0, .p2 = 0}; //WeightSensor Pointer

int getWeight(int player)
{
    
    switch(player){
        case 1: 
        {
            WSptr.p1 = 0;
            PlayerSelect_Select(0);//vælg player1
            
            for(int i = 0; i < samples; i++)
            {
                ADC_SAR_1_StartConvert();
                CyDelayUs(delay); //delay indsat, så måling ikke trailer med 1 måling
                
                if (ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT)!=0)
                {
                    WSptr.p1 += ADC_SAR_1_GetResult16();
                }
            }
        return (WSptr.p1/samples);
        }
        break;
        
        case 2: 
        {
            WSptr.p2 = 0;
            PlayerSelect_Select(1);//vælg player2
            for(int i = 0; i < samples; i++)
            {
                ADC_SAR_1_StartConvert();
                CyDelayUs(delay); //delay indsat, så måling ikke trailer med 1 måling
                
                if (ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT)!=0)
                {
                    WSptr.p2 += ADC_SAR_1_GetResult16();
                }
            }    
        return (WSptr.p2/samples);
        }
        break;
    }
    
return 0;
}

int getCalWeight(int player)
{
    
    switch(player){
        case 1: 
        {
            WSptr.p1cal = 0;
            WSptr.p1cal = getWeight(1);
        

            WSptr.p1cal -= (WSptr.CalibrateP1);
            WSptr.p1cal = ADC_SAR_1_CountsTo_mVolts(WSptr.p1cal);    
            WSptr.p1cal /= mVtoG;
            
           //Debugging-----------------------------
            sprintf(uart_string, "Calibrated Weight from player 1: %i \r\n", WSptr.p1cal);     // convert to string
            UARTprint("5", uart_string);                                         // output string
            //--------------------------------------
            return WSptr.p1cal;
            
        }
        
        break;
        
        case 2: 
        { 
            WSptr.p2cal = 0;
            WSptr.p2cal = getWeight(2);
            
            WSptr.p2cal -= (WSptr.CalibrateP2);
            WSptr.p2cal = ADC_SAR_1_CountsTo_mVolts(WSptr.p2cal);
            WSptr.p2cal /= mVtoG;
            
            //Debugging-----------------------------
            sprintf(uart_string, "Calibrated Weight from player 2: %i \r\n", WSptr.p2cal);     // convert to string
            UARTprint("6", uart_string);                                         // output string
            //--------------------------------------
            return WSptr.p2cal;
              
        }
        break;
    
    
    }
return 0;
}

int getWeightLoser(int x)
{
    WSptr.pLoser = getWeight(x);
        
        if(x == 1)
        {
            WSptr.pLoser -= (WSptr.CalibrateP1);
        }
        else if(x == 2)
        {
            WSptr.pLoser -= (WSptr.CalibrateP2);
        }
        
        
        WSptr.pLoser = ADC_SAR_1_CountsTo_mVolts(WSptr.pLoser);
        WSptr.pLoser /= mVtoG;

        return WSptr.pLoser;
        
return 0;    
}

void WeightSensorsInit()
{
    ADC_SAR_1_Start();
    PlayerSelect_Init();
}

int CompareWeight()
{

    int Weight1 = getCalWeight(1), Weight2 = getCalWeight(2);
    if (((Weight2 >= (Weight1 - afvigelse)) && (Weight2 <= Weight1 + afvigelse)) || ((Weight1 >= (Weight2 - afvigelse)) && (Weight1 <= Weight2 + afvigelse)))
    {
        if((Weight2 < 100) || (Weight1 < 100)) return 4;
        return 1;
    }
    else if (Weight2 > Weight1)//spiller 1 fejl
    { 
        if(((Weight2 < 100 + afvigelse) && (Weight1 < 100 + afvigelse) && (weighthys == 0)) || ((Weight2 < 100 - afvigelse) && (Weight1 < 100 - afvigelse) && (weighthys == 1))){
            weighthys = 0;
            return 4;
        }
        weighthys = 1;
        return 2;
    }
    else if(Weight2 < Weight1) //spiller 2 fejl
    {
        if(((Weight2 < 100 + afvigelse) && (Weight1 < 100 + afvigelse) && (weighthys == 0)) || ((Weight2 < 100 - afvigelse) && (Weight1 < 100 - afvigelse) && (weighthys == 1))){
            weighthys = 0;
            return 4;
        }
        weighthys = 1;
        return 3;
    }
    
    return 0;   //for error handling
}   

void CalibrateSensors()
{
    UARTprint("2", "Calibrating WeightSensors\r\n");
    
    WSptr.CalibrateP1 = getWeight(1);
    WSptr.CalibrateP2 = getWeight(2);
}


/* [] END OF FILE */
