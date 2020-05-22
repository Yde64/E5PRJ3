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
#define afvigelse 15                //Bestemmer fejlmargin for compareWeight.
#define hysmid 100
#define mVtoG1 0.004798911134528
#define mVtoG2 0.005492139213069
#define samples 500

char uart_string[50];       //Anvendes i debug
int weighthys = 0;

WeightSensors  WSptr = {.p1 = 0, .p2 = 0}; //WeightSensor Pointer

long getWeight(int player)
{
    switch(player){
        case 1: 
        {
            WSptr.p1 = 0;
            PlayerSelect_Select(0);//vælg player1
            
            for(int i = 0; i < samples; i++)
            {
                ADC_DelSig_1_StartConvert();
                
                if (ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_WAIT_FOR_RESULT)!=0)
                {
                    WSptr.p1 += ADC_DelSig_1_GetResult32();
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
                ADC_DelSig_1_StartConvert();
                
                if (ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_WAIT_FOR_RESULT)!=0)
                {
                    WSptr.p2 += ADC_DelSig_1_GetResult32();
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
            WSptr.p1cal = ADC_DelSig_1_CountsTo_uVolts(WSptr.p1cal);    
            WSptr.p1cal *= mVtoG1;
            
            return WSptr.p1cal;
            
        }
        
        break;
        
        case 2: 
        { 
            WSptr.p2cal = 0;
            WSptr.p2cal = getWeight(2);
            
            WSptr.p2cal -= (WSptr.CalibrateP2);
            WSptr.p2cal = ADC_DelSig_1_CountsTo_uVolts(WSptr.p2cal);
            WSptr.p2cal *= mVtoG2;
            
            return WSptr.p2cal;
              
        }
        break;
    
    
    }
return 0;
}


void WeightSensorsInit()
{
    ADC_DelSig_1_Start();
    PlayerSelect_Init();
}

int CompareWeight()
{

    int Weight1 = getCalWeight(1), Weight2 = getCalWeight(2);
    if (((Weight2 >= (Weight1 - afvigelse)) && (Weight2 <= Weight1 + afvigelse)) || ((Weight1 >= (Weight2 - afvigelse)) && (Weight1 <= Weight2 + afvigelse)))
    {
        if((Weight2 < hysmid) || (Weight1 < hysmid)) return 4;
        return 1;
    }
    else if (Weight2 > Weight1)//spiller 1 fejl
    { 
        if(((Weight2 < hysmid + afvigelse) && (Weight1 < hysmid + afvigelse) && (weighthys == 0)) || ((Weight2 < hysmid - afvigelse) && (Weight1 < hysmid - afvigelse) && (weighthys == 1))){
            weighthys = 0;
            return 4;
        }
        weighthys = 1;
        return 2;
    }
    else if(Weight2 < Weight1) //spiller 2 fejl
    {
        if(((Weight2 < hysmid + afvigelse) && (Weight1 < hysmid + afvigelse) && (weighthys == 0)) || ((Weight2 < hysmid - afvigelse) && (Weight1 < hysmid - afvigelse) && (weighthys == 1))){
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

long int getCalWeightDebug(int player)
{
    if(player == 1)
    {
        return WSptr.p1cal;
        
    }else if(player == 2)
    {
        return WSptr.p2cal;
    }
    return 0;
}

    //*/
/* [] END OF FILE */
