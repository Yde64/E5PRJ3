#include "States.h"
#include "Stopur.h"
#include "Display.h"

//states state = IDLE;
//
//#define glasvaegtp1 25 //eksempel
//#define glasvaegtp2 25 //eksempel - skal testes
//#define afvigelse 10   // maksimum mængde væske, der må være i glas efter spil  -  skal testes yderligere
//#define delay 100
//
//int glasvaegtWinner = 0;
//int glasvaegtLoser = 0;
//int pLoser = 0;
//int tidWinner = 0;
//int tidLoser = 0;
//
//char uart_out[50];

/*
void Next_state_Logic(){
switch(state)
        {
            
        case IDLE:
            {
               sprintf(uart_out, "\r\nNSL - IDLE");                  // convert to string
               UART_1_PutString(uart_out);                         // output string
                
                if(BPptr.ButtonPushed == 1)                //hvis startknap 
                {                               
                    state =  EVALUATING_WEIGHT; //state -> Evaluating Weight  
                    BPptr.ButtonPushed = 0;
                }
            
                else
                {   
                    state = IDLE;               //ellers bliv her
                }
            }
            break;
           
        case GOING_IDLE :
            {
                sprintf(uart_out, "\r\nNSL - GOING_IDLE");     // convert to string
                UART_1_PutString(uart_out);                         // output string
                
                state = IDLE;                   //state -> Idle
            }
            break;
            
        case EVALUATING_WEIGHT :
            {
                sprintf(uart_out, "\r\nNSL - EVALUATING_WEIGHT");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                
                if (CompareWeight() == 1)       //hvis vægten passer
                {
                    state = READY;
                }
                else if (CompareWeight() != 1)  //hvis vægten ikke passer p1>p2
                {
                    state = ERR_WEIGHT;
                }
                else if (BPptr.ButtonPushed == 1)
                {
                    state = GOING_IDLE;
                    BPptr.ButtonPushed = 0;
                }
                else 
                    state = EVALUATING_WEIGHT;
                
            }
            break;
            
        case READY :
            {
                sprintf(uart_out, "\r\nNSL - READY");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                
                if (timeout() == 1)
                {
                    state=ERR_NO_START;
                }
                else if (BPptr.ButtonPushed == 1 && timeout()!=1) //hvis startknap -> Countdown
                {
                    state = COUNTDOWN;
                    BPptr.ButtonPushed = 0;
                }
                else 
                {
                    state = READY;
                }    
            }
            break;
            
        case COUNTDOWN :
            {
                sprintf(uart_out, "\r\nNSL - COUTNDOWN");    // convert to string
                UART_1_PutString(uart_out);                         // output string
              
                //start timer;
                
              // if () timer halløj (3-2-1-CHUG)
                {
                    state = CHUG 
                }
                
            
                else  if () //Hvis glasset løftes inden timer har talt ned fra 3-2-1-CHUG
                (pseudokode) -> hvis (((nuværende timer < countdown timer) && (getWeight(1) < fyldtglasvægt)) ||((nuværende timer < countdown timer) && (getWeight(2) < fyldtglasvægt)))
                {
                    state = ERR_FALSE_START    
                }
                
               // 
            }
            break;
            
        case CHUG:
            {
                sprintf(uart_out, "\r\nNSL - CHUG");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                
                if(getWeight(1) != 0 || getWeight(2) != 0){
                    CyDelay(delay); //vent med at læse til efter inital impact
                    
                    if((glasvaegtp1 + afvigelse) >= getWeight(1)) //Her skal det erklæres hvilken af de to spillere der vinder --> sæt pLoser til enten 1(p1) eller 2(p2)
                    {
                        pLoser = 2; //player2 taber
                        glasvaegtLoser = glasvaegtp2;
                        state = WINNER_DONE; //assign glasvaegtp1/p2 til glasvaegtLoser og glasvaegtWinner
                                        
                    }
                    else if ((glasvaegtp2 + afvigelse) >= getWeight(2)) //hvis spiller2 vinder, sættes p1-data til Loser-data
                    {
                        pLoser = 1; //player 1 taber
                        glasvaegtLoser = glasvaegtp1;
                        state = WINNER_DONE;
                    }
                    //else if(timeoutTimer >= 2 min)
                    //{
                      //  state =ERR_TIMEOUT;
                    //}
                    //       
                }
            }
            break;    
            
        case WINNER_DONE:
            {
                sprintf(uart_out, "\r\nNSL - WINNER_DONE");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                
                state = EVALUATING_NEW_WEIGHT;       
            }
            break;
            
        case EVALUATING_NEW_WEIGHT:
            {
                sprintf(uart_out, "\r\nNSL - EVALUATING_NEW_WEIGHT");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                
                if((getWeightLoser(pLoser) != 0))
                {
                    CyDelay(delay); //vent med at læse til efter inital impact
                    if (glasvaegtLoser + afvigelse < getWeightLoser(pLoser))
                    {
                        state = LOSER_DONE;
                    }
                     else if (glasvaegtLoser + afvigelse > getWeightLoser(pLoser))
                    {
                        state = ERR_NOCHUG;
                    }
                }
                else 
                {
                    state = EVALUATING_NEW_WEIGHT;
                }
               
            }   
            break;
            
        case LOSER_DONE:
            {
                sprintf(uart_out, "\r\nNSL - LOSER_DONE");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                
                state = WEIGHT_CONFIRMED;
            }  
            break;
            
        case WEIGHT_CONFIRMED:
            {
                sprintf(uart_out, "\r\nNSL - WEIGHT_CONFIRMED");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                
                state = GAME_OVER;
            }    
            break;
            
        case GAME_OVER:
            {
                sprintf(uart_out, "\r\nNSL - GAME_OVER");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                
                if (BPptr.ButtonPushed != 0)
                {
                    state = GOING_IDLE;
                    BPptr.ButtonPushed = 0;
                }
                else 
                state = GAME_OVER;
            }
            break;
        
            
            
            
            
            
            
            
            // ------------------------------------ERR STATES---------------------------------------------------
            
        case ERR_WEIGHT:
            {
                sprintf(uart_out, "\r\nNSL - ERR_WEIGHT");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                
                state = EVALUATING_WEIGHT;
            }    
            break;
            
        case ERR_NO_START:
            {
                sprintf(uart_out, "\r\nNSL - ERR_NO_START");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                
                if (BPptr.ButtonPushed == 1)
                {
                    state = GOING_IDLE;
                }
                
            }    
            break;
            
        case ERR_FALSE_START:
            {
                sprintf(uart_out, "\r\nNSL - ERR_FALSE_START");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                
                if (BPptr.ButtonPushed == 1)
                {
                    state = GOING_IDLE;
                }
            }    
            break;
            
        case ERR_TIMEOUT:
            {
                sprintf(uart_out, "\r\nNSL - ERR_TIMEOUT");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                
                if (BPptr.ButtonPushed == 1)
                {
                    state = GOING_IDLE;
                }
            }    
            break;
            
        case ERR_NOCHUG:
            {
                sprintf(uart_out, "\r\nNSL - ERR_NOCHUG");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                
                state = WINNER_DONE;
            }    
            break;
            
            
        default :
            {
                sprintf(uart_out, "\r\nNSL - DEFAULT");    // convert to string
                UART_1_PutString(uart_out);                         // output string
            }
            break;
            
        
       }

}


void Output_logic(){
switch(state)
        {
            
        case IDLE:
            {
                sprintf(uart_out, "\r\nOL - IDLE");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                
                //idleSeq();
            }
            break;
           
        case GOING_IDLE :
            {
                sprintf(uart_out, "\r\nOL - GOING_IDLE");    // convert to string
                UART_1_PutString(uart_out);                         // output string
               //clearDisp();    
            }
            break;
            
        case EVALUATING_WEIGHT :
            {
                sprintf(uart_out, "\r\nOL - EVALUATING_WEIGHT");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                //checkSeq();
            }
            break;
            
        case READY :
            {
                sprintf(uart_out, "\r\nOL - READY");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                
               if (timeout()== 1)
            {
                //errorSeq(1);
                //errorSeq(2);  
            } 
            stopTimer();
            clearTimer();
            }
            break;
            
        case COUNTDOWN :
            {
                sprintf(uart_out, "\r\nOL - COUNTDOWN");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                //startSeq();
            }
            break;
            
        case CHUG:
            {
                sprintf(uart_out, "\r\nOL - CHUG");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                
                dispTime(1, getTime());
                dispTime(2, getTime());
                startTimer();
                //sekvens for spil igang 
                if (timeout()==1)
                {
                    //errorSeq(1);
                    //errorSeq(2);
                }
            }
            break;    
            
        case WINNER_DONE:
            {
                sprintf(uart_out, "\r\nOL - WINNER_DONE");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                
                if (pLoser == 2)
                {
                    stopLCD(1);
                    tidWinner = getTime();
                    // afspiller vinder sekvens
                }
                else if (pLoser == 1)
                {
                    stopLCD(2);
                    tidWinner = getTime();
                    // afspiller vinder sekvens
                }
            }
            
            break;
            
        case EVALUATING_NEW_WEIGHT :
            {
                sprintf(uart_out, "\r\nOL - EVALUATING_NEW_WEIGHT");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                
              stopLCD(1);
              stopLCD(2);
              tidLoser = getTime();
              stopTimer();
              // afspiller taber sekvens
            }
          
            break;
            
//        case LOSER_DONE:
//            {
//                
//            }  
//            break;
//        case WEIGHT_CONFIRMED:
//            {
//            
//            }    
        case GAME_OVER:
            {
                sprintf(uart_out, "\r\nOL - GAME_OVER");    // convert to string
                UART_1_PutString(uart_out);                         // output string
              clearTimer();
            }
            break;
        
            
            
            
            
            
            
            
            // ------------------------------------ERR STATES---------------------------------------------------
            
            case ERR_WEIGHT:
            {
                sprintf(uart_out, "\r\nOL - ERR_WEIGHT");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                
                if (CompareWeight() == 2)  //hvis vægten ikke passer p1>p2 -> p2 har fejlen
                {
                    //errorSeq(2);
                }
                else if (CompareWeight() == 3)  //hvis vægten ikke passer p1<p2 -> p1 har fejlen
                {
                    //errorSeq(1);
                }

            }    
            break;
            
            case ERR_NO_START:
            {
                sprintf(uart_out, "\r\nOL - ERR_NO_START");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                
                
            }    
            break;
            
            case ERR_FALSE_START:
            {
                sprintf(uart_out, "\r\nOL - ERR_FALSE_START");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                
            }    
            break;
            
            case ERR_TIMEOUT:
            {
                sprintf(uart_out, "\r\nOL - ERR_TIMEOUT");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                
            }    
            break;
            
            case ERR_NOCHUG:
            {
                sprintf(uart_out, "\r\nOL - ERR_NOCHUG");    // convert to string
                UART_1_PutString(uart_out);                         // output string
                
                if (glasvaegtp1 < getWeight(1)) 
                {
                    //errorSeq(1);
                }
                else if(glasvaegtp2 < getWeight(2)) 
                {
                    //errorSeq(2);
                }          
            }    
            break;
            
            
        default :
            {
                sprintf(uart_out, "\r\nOL - DEFAULT");    // convert to string
                UART_1_PutString(uart_out);                         // output string
            }
            break;
            
       }  
        
}
*/
/* [] END OF FILE */
