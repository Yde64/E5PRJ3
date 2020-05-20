
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
//#include "project.h"
#include "WeightSensors_.h"
#include "UART.h"
#include "Display.h"
#include "Startknap.h"
#include "States.h"
#include "LEDcontrol.h"
#include "Stopur.h"
#include "VT100Terminal.h"
#include "SPI_Master.h"

#define Display1 0x26
#define Display2 0x27
#define LEDlength 15
#define LEDrefreshrate 60
#define LCDrefreshrate 20


WeightSensors  _WSptr = {.p1 = 0, .p2 = 0}; //WeightSensor Pointer


// STATES.C
#define delay 100
#define nulvaegt -200

int pLoser = 0;
int tidp1 = 0;
int tidp2 = 0;

int cycleCountIdle = 0;
int cycleCountEvaluatingWeight = 0;
int cycleCountReady = 0;
int cycleCountCountdown = 0;

int pErr = 0;

//CHUG-state
int chugp1 = 0;
int chugp2 = 0;
int chugstart = 0;


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    // SPIM_1_Start();
    isr_button_StartEx(isr_button_handler);
    isr_uart_rx_StartEx(ISR_UART_rx_handler);
    isr_timer_StartEx(isr_timer);
    UART_1_Start();
    SPIS_initSPI();
    
    WeightSensorsInit();
    
    LEDctrl rgbstrip1[LEDlength], rgbstrip2[LEDlength];
    addLEDstrip(LEDlength, rgbstrip1, 1);
    addLEDstrip(LEDlength, rgbstrip2, 2);
    initLED(LEDrefreshrate);
    initDisp(LCDrefreshrate);
    setspeed(100, 20, 500);
    
    clearTerm(40);
    
    states CURRENT_STATE = IDLE;
    states NEXT_STATE = IDLE;
    BPptr.ButtonPushed = 0;
    
    UARTprint("1", "MAIN START\r\n");
    CalibrateSensors();
    
    
    for(;;)
    {
       CURRENT_STATE = NEXT_STATE;
        
//-----------------------------------STATE LOGIC-----------------------------------//
        switch(CURRENT_STATE)
        {
        
        case IDLE:
            {
                UARTprint("3", "NSL - IDLE\r\n");
                
                if(BPptr.ButtonPushed == 1)                //hvis startknap 
                {                               
                    NEXT_STATE =  EVALUATING_WEIGHT; //state -> Evaluating Weight  
                    BPptr.ButtonPushed = 0;
                    CalibrateSensors();
                    CyDelay(100);
                }
            
                else
                {   
                    NEXT_STATE = IDLE;               //ellers bliv her
                }
            }
            break;
           
        case GOING_IDLE :
            {
                UARTprint("3", "NSL - GOING_IDLE\r\n");
                
                NEXT_STATE = IDLE;                   //state -> Idle
            }
            break;
            
        case EVALUATING_WEIGHT :
            {
                //CyDelay(100);
                UARTprint("3", "NSL - EVALUATING_WEIGHT\r\n");
               
                int Weight = CompareWeight();
                if (Weight == 1)       //hvis vægten passer
                {
                    NEXT_STATE = READY;
                }
                else if (Weight != 1)  //hvis vægten ikke passer p1>p2
                {
                    NEXT_STATE = ERR_WEIGHT;
                }
                else if (BPptr.ButtonPushed == 1)
                {
                    NEXT_STATE = GOING_IDLE;
                    BPptr.ButtonPushed = 0;
                    CyDelay(100);
                }
                else 
                    NEXT_STATE = EVALUATING_WEIGHT;
                
            }
            break;
            
        case READY :
            {
                UARTprint("3", "NSL - READY\r\n");
                
                if (timeout() == 1)
                {
                    NEXT_STATE=ERR_NO_START;
                }
                else if (BPptr.ButtonPushed == 1 && timeout()!=1) //hvis startknap -> Countdown
                {
                    NEXT_STATE = COUNTDOWN;
                    BPptr.ButtonPushed = 0;
                    CyDelay(100);
                }
                else 
                {
                    NEXT_STATE = READY;
                }    
            }
            break;
            
        case COUNTDOWN :
            {
                UARTprint("3", "NSL - COUTNDOWN\r\n");
                
                
                int startseq = startSeq(rgbstrip1,rgbstrip2);
                if (startseq == 1)
                {
                    NEXT_STATE = CHUG;
                }
                else if (/*startseq != 1 &&*/ getCalWeight(1) < _WSptr.p1cal + afvigelse2)
                {
                    pErr = 1; //player1 error
                    NEXT_STATE = ERR_FALSE_START;
                }
                else if (/*startseq != 1 && */ getCalWeight(2) < _WSptr.p2cal + afvigelse2)
                {
                    pErr = 2; //player1 error
                    NEXT_STATE = ERR_FALSE_START;
                }
                
            }
            break;
            
        case CHUG:
            {
                UARTprint("3", "NSL - CHUG\r\n");
                
                if(getCalWeight(1) < nulvaegt) //hvis spiller 1 glas er løftet
                { 
                    chugp1 = 1;
                    CyDelay(delay);
                }
                    if(chugp1 == 1)
                    {
                        if(getCalWeight(1) > nulvaegt ){
                    
                            if((afvigelse) >= getCalWeight(1)) //Her skal det erklæres hvilken af de to spillere der vinder --> sæt pLoser til enten 1(p1) eller 2(p2)
                            {
                                pLoser = 2; //player2 taber
                                NEXT_STATE = WINNER_DONE; 
                                        
                            }
                            else if((timeout()==1))
                            {
                                NEXT_STATE = ERR_TIMEOUT;
                            }
                        }
                    }
                    
                if (getCalWeight(2) < nulvaegt) //hvis spiller 2 glas er løftet
                { 
                    chugp2 = 1;  
                    CyDelay(delay);
                }
                    if(chugp2 == 1)
                    {
                        if(getCalWeight(2) > nulvaegt)
                        {
                        
                            if ((afvigelse) >= getCalWeight(2)) //hvis spiller2 vinder, sættes p1-data til Loser-data
                            {
                                pLoser = 1; //player 1 taber
                                NEXT_STATE = WINNER_DONE;
                            }
                            else if(timeout()==1)
                            {
                                NEXT_STATE = ERR_TIMEOUT;
                            }
                        }      
                    }
            }
            break;    
            
        case WINNER_DONE:
            {
                UARTprint("3", "NSL - WINNER_DONE\r\n");
                
                NEXT_STATE = EVALUATING_NEW_WEIGHT;       
            }
            break;
            
        case EVALUATING_NEW_WEIGHT:
            {
                UARTprint("3", "NSL - EVALUATING_NEW_WEIGHT\r\n");
                
                if (getCalWeight(2) < nulvaegt) //hvis spiller 2 glas er løftet
                { 
                    chugp2 = 1;   
                }
                    if(chugp2 == 1)
                    {
                        if((getCalWeight(pLoser) > nulvaegt))
                        {
                            CyDelay(delay); //vent med at læse til efter inital impact
                            if (getCalWeight(pLoser) <= afvigelse)
                            {
                                NEXT_STATE = LOSER_DONE;
                            }
                             else
                            {
                                NEXT_STATE = ERR_NOCHUG;
                            }
                        }
                        else
                        {
                            NEXT_STATE = EVALUATING_NEW_WEIGHT;
                        }
                    }
               
            }   
            break;
            
        case LOSER_DONE:
            {
                UARTprint("3", "NSL - LOSER_DONE\r\n");
                
                NEXT_STATE = WEIGHT_CONFIRMED;
            }  
            break;
            
        case WEIGHT_CONFIRMED:
            {
                UARTprint("3", "NSL - WEIGHT_CONFIRMED\r\n");
                
                NEXT_STATE = GAME_OVER;
            }    
            break;
            
        case GAME_OVER:
            {
                UARTprint("3", "NSL - GAME_OVER\r\n");
                
                if (BPptr.ButtonPushed != 0)
                {
                    NEXT_STATE = GOING_IDLE;
                    BPptr.ButtonPushed = 0;
                }
                else 
                NEXT_STATE = GAME_OVER;
            }
            break;

            // ------------------------------------ERR STATES---------------------------------------------------
            
        case ERR_WEIGHT:
            {
                UARTprint("3", "NSL - ERR_WEIGHT\r\n");
                
                NEXT_STATE = EVALUATING_WEIGHT;
            }    
            break;
            
        case ERR_NO_START:
            {
                UARTprint("3", "NSL - ERR_NO_START\r\n");
                
                if (BPptr.ButtonPushed == 1)
                {
                    NEXT_STATE = GOING_IDLE;
                }
                
            }    
            break;
            
        case ERR_FALSE_START:
            {
                UARTprint("3", "NSL - ERR_FALSE_START\r\n");
                setspeed(100, 20, 500);
                if (BPptr.ButtonPushed == 1)
                {
                    BPptr.ButtonPushed = 0;
                    NEXT_STATE = GOING_IDLE;
                }
            }    
            break;
            
        case ERR_TIMEOUT:
            {
                UARTprint("3", "NSL - ERR_TIMEOUT\r\n");
                
                if (BPptr.ButtonPushed == 1)
                {
                    NEXT_STATE = GOING_IDLE;
                }
            }    
            break;
            
        case ERR_NOCHUG:
            {
                UARTprint("3", "NSL - ERR_NOCHUG\r\n");
                
                NEXT_STATE = WINNER_DONE;
            }    
            break;
            
            
        default :
            {
                UARTprint("3", "NSL - DEFAULT\r\n");
            }
            break;
            
        
       }
        
//-----------------------------------OUTPUT LOGIC-----------------------------------//
        switch(CURRENT_STATE)
                {
                    
                case IDLE:
                    {
                        cycleCountIdle++;
                        
                         if(cycleCountIdle == 1){ //her sørger vi for, at idleSeq kun startes én gang, og ikke  hver gang vi looper gennem staten
                            idleSeq(rgbstrip1);
                            idleSeq(rgbstrip2);
                        }
                        
                        UARTprint("4", "OL - IDLE\r\n");
                        
                        //idleSeq();
                    }
                    break;
                   
                case GOING_IDLE :
                    {
                        UARTprint("4", "OL - GOING_IDLE\r\n");
                        stopTimer();
                        
                        cycleCountIdle = 0;
                        cycleCountReady = 0;
                        cycleCountCountdown = 0;
                        cycleCountEvaluatingWeight = 0;
                        initLED(LEDrefreshrate);
                        
                        setspeed(100, 20, 500);
                        StartDisp();
                        
                        
                    }
                    break;
                    
                case EVALUATING_WEIGHT :
                    {
                        cycleCountEvaluatingWeight++;
                         if(cycleCountEvaluatingWeight == 1)
                        {
                            checkSeq(rgbstrip1);
                            checkSeq(rgbstrip2);
                        }
                        //CalibrateSensors();
                        
                        UARTprint("4", "OL - EVALUATING_WEIGHT\r\n");
                        
                    }
                    break;
                    
                case READY :
                    {
                        startTimer();
                        cycleCountReady++;
                        if (cycleCountReady == 1)
                        {
                            weightapprovedSeq(rgbstrip1);
                            weightapprovedSeq(rgbstrip2);
                        }
                        
                        UARTprint("4", "OL - READY\r\n");
                        
                    
                    }
                    break;
                    
                case COUNTDOWN :
                    {
                        stopTimer();
                        clearTimer();   
                        //alt countdown foregår i LED-kode
                        UARTprint("4", "OL - COUNTDOWN\r\n");
                    }
                    break;
                   
                case CHUG:
                    {
                        startTimer();
                        //sekvens for spil igang
                        
                        UARTprint("4", "OL - CHUG\r\n");
                    }
                    break;    
                    
                case WINNER_DONE:
                    {
                                       
                        if (pLoser == 1)
                        {
                            tidp2 = getTime()/100; 
                            stopLCD(2); //hvis spiller 2 taber, stoppes LCD ved spiller 1
                            dispTime(2, tidp2);
                            
                            winnerSeq(rgbstrip1); // afspiller vinder sekvens
                        }
                        else if (pLoser == 2)
                        {
                            tidp1 = getTime()/100;
                            stopLCD(1);
                            dispTime(1, tidp1);
                            winnerSeq(rgbstrip2); // afspiller vinder sekvens
                        }
                        
                        UARTprint("4", "OL - WINNER_DONE\r\n");
                    }
                    break;
                    
                case EVALUATING_NEW_WEIGHT :
                    {                
                        UARTprint("4", "OL - EVALUATING_NEW_WEIGHT\r\n");
                    }
                    break;
                    
                case LOSER_DONE:
                    {
                        
                        if (pLoser == 2)
                        {
                            
                            loserSeq(rgbstrip2); // afspiller taber sekvens
                            tidp2 = getTime()/100;
                            stopLCD(2);
                            dispTime(2, tidp2);
                        }
                        else if (pLoser == 1)
                        {   
                            
                            loserSeq(rgbstrip1); // afspiller taber sekvens
                            tidp1 = getTime()/100;
                            stopLCD(1);
                            dispTime(1, tidp1);
                        }
                        
                        int sek;
                        int ms;
                        sek = tidp1/10;
                        ms = tidp1%10;
                        SPIS_sendData(sek, ms);
                        CyDelay(1500);
                        
                        sek = tidp2/10;
                        ms = tidp2%10;
                        SPIS_sendData(sek, ms);
                        
                        
                    }  
                    break;
        //        case WEIGHT_CONFIRMED:
        //            {
        //            
        //            }    
                case GAME_OVER:
                    {
                        UARTprint("4", "OL - GAME_OVER\r\n");
                        clearTimer();
                    }
                    break;
                    
                    // ------------------------------------ERR STATES---------------------------------------------------
                    
                    case ERR_WEIGHT:
                    {              
                        int weight = CompareWeight();
                        if (weight == 2)  //hvis vægten ikke passer p1<p2 -> p1 har fejlen
                        {
                            checkSeq(rgbstrip2);
                            errorSeq(rgbstrip1);
                        }
                        else if (weight == 3)  //hvis vægten ikke passer p1>p2 -> p2 har fejlen
                        {
                            checkSeq(rgbstrip1);
                            errorSeq(rgbstrip2);
                        }else if(weight == 4)
                        {
                            errorSeq(rgbstrip1);
                            errorSeq(rgbstrip2);
                        }
                        UARTprint("4", "OL - ERR_WEIGHT\r\n");
                    }    
                    break;
                    
                    case ERR_NO_START:
                    {               
                        stopTimer();
                        clearTimer();
                        errorSeq(rgbstrip1);
                        errorSeq(rgbstrip2);
                        
                        UARTprint("4", "OL - ERR_NO_START\r\n");
                        
                    }    
                    break;
                    
                    case ERR_FALSE_START:
                    {
                        if (pErr == 1)
                        {
                            errorSeq(rgbstrip1);
                        }
                        else if (pErr == 2)
                        {
                            errorSeq(rgbstrip2);
                        }
                        clearTimer();
                        UARTprint("4", "OL - ERR_FALSE_START\r\n");
                        
                    }    
                    break;
                    
                    case ERR_TIMEOUT:
                    {
                        errorSeq(rgbstrip1);
                        errorSeq(rgbstrip2);
                        
                        UARTprint("4", "OL - ERR_TIMEOUT\r\n");
                        
                    }    
                    break;
                    
                    case ERR_NOCHUG:
                    {
                        UARTprint("4", "OL - ERR_NOCHUG\r\n");
                        pErr = pLoser;
                        
                        if (pErr == 1)
                        {
                            errorSeq(rgbstrip1);
                        }
                        else if (pErr == 2)
                        {
                            errorSeq(rgbstrip2);
                        }
                    }    
                    break;
                    
                    
                default :
                    {
                        UARTprint("4", "OL - DEFAULT\r\n");

                    }
                    break;
                    
               }  
                
        }
}
    



/* [] END OF FILE */
