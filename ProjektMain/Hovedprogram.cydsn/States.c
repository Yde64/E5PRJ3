#include "States.h"
#include "Stopur.h"
#include "Display.h"

states state;

#define glasvaegtp1 25 //eksempel
#define glasvaegtp2 25 //eksempel - skal testes
#define afvigelse 10 // maksimum mængde væske, der må være i glas efter spil  -  skal testes yderligere
#define delay 100

int glasvaegtWinner = 0;
int glasvaegtLoser = 0;
int pLoser = 0;
int tidWinner = 0;
int tidLoser = 0;




void Next_state_Logic(){
switch(state)
        {
            
        case IDLE:
            {
                if(BPptr.ButtonPushed == 1)                //hvis startknap 
                {                               
                    state =  EVALUATING_WEIGHT; //state -> Evaluating Weight  
                }
            
                else
                {   
                    state = IDLE;               //ellers bliv her
                }
            }
            break;
           
        case GOING_IDLE :
            {
                state = IDLE;                   //state -> Idle
            }
            break;
            
        case EVALUATING_WEIGHT :
            {
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
                }
                else 
                    state = EVALUATING_WEIGHT;
                
            }
            break;
            
        case READY :
            {
                if (timeout() == 1)
                {
                    state=ERR_NO_START;
                }
                else if (BPptr.ButtonPushed == 1 && timeout()!=1) //hvis startknap -> Countdown
                {
                    state = COUNTDOWN;
                }
                else 
                {
                    state = READY;
                }    
            }
            break;
            
        case COUNTDOWN :
            {
              
                //start timer;
                
                /*if () timer halløj (3-2-1-CHUG)
                {
                    state = CHUG 
                }
                
            
                else  if () //Hvis glasset løftes inden timer har talt ned fra 3-2-1-CHUG
                (pseudokode) -> hvis (((nuværende timer < countdown timer) && (readdata1() < fyldtglasvægt)) ||((nuværende timer < countdown timer) && (readdata2() < fyldtglasvægt)))
                {
                    state = ERR_FALSE_START    
                }
                
                */
            }
            break;
            
        case CHUG:
            {
                if(readdata1() != 0 || readdata2() != 0){
                    CyDelay(delay); //vent med at læse til efter inital impact
                    
                    if((glasvaegtp1 + afvigelse) >= readdata1()) //Her skal det erklæres hvilken af de to spillere der vinder --> sæt pLoser til enten 0(p1) eller 1(p2)
                    {
                        pLoser = 1; //player2 taber
                        glasvaegtLoser = glasvaegtp2;
                        state = WINNER_DONE; //assign glasvaegtp1/p2 til glasvaegtLoser og glasvaegtWinner
                                        
                    }
                    else if ((glasvaegtp2 + afvigelse) >= readdata2()) //hvis spiller2 vinder, sættes p1-data til Loser-data
                    {
                        pLoser = 0; //player 1 taber
                        glasvaegtLoser = glasvaegtp1;
                        state = WINNER_DONE;
                    }
                    /*else if(timeoutTimer >= 2 min)
                    {
                        state =ERR_TIMEOUT;
                    }
                    */       
                }
            }
            break;    
            
        case WINNER_DONE:
            {
                state = EVALUATING_NEW_WEIGHT;       
            }
            break;
            
        case EVALUATING_NEW_WEIGHT :
            {
                if((readdataLoser(pLoser) != 0))
                {
                    CyDelay(delay); //vent med at læse til efter inital impact
                    if (glasvaegtLoser + afvigelse < readdataLoser(pLoser))
                    {
                        state = LOSER_DONE;
                    }
                     else if (glasvaegtLoser + afvigelse > readdataLoser(pLoser))
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
                state = WEIGHT_CONFIRMED;
            }  
            break;
        case WEIGHT_CONFIRMED:
            {
                state = GAME_OVER;
            }    
        case GAME_OVER:
            {
                if (BPptr.ButtonPushed != 0){
                    state = GOING_IDLE;
                }
                else 
                state = GAME_OVER;
            }
            break;
        
            
            
            
            
            
            
            
            // ------------------------------------ERR STATES---------------------------------------------------
            
            case ERR_WEIGHT:
            {
                state = EVALUATING_WEIGHT;
            }    
            break;
            
            case ERR_NO_START:
            {
                if (BPptr.ButtonPushed == 1)
                {
                    state = GOING_IDLE;
                }
                
            }    
            break;
            
            case ERR_FALSE_START:
            {
                if (BPptr.ButtonPushed == 1)
                {
                    state = GOING_IDLE;
                }
            }    
            break;
            
            case ERR_TIMEOUT:
            {
                if (BPptr.ButtonPushed == 1)
                {
                    state = GOING_IDLE;
                }
            }    
            break;
            
            case ERR_NOCHUG:
            {
                state = WINNER_DONE;
            }    
            break;
            
            
        default :
            {
            }
            break;
            
        
       }

}

/*
void LEDinitSeq();   //Initieringssekvens
void idleSeq();      //Idle-sekvens

void loserSeq();     //Tabersekvens

void zeroCalibrateSeq(); //Kalibreringssekvens

void checkSeq();     //Tjek vægt sekvens

void weightapprovedSeq(); //Vægt godkendt sekvens

void startSeq();     //Start sekvens
void errorSeq();     //Fejl sekvens
void winnerSeq();    //Vindersekvens
*/

void Output_logic(){
switch(state)
        {
            
        case IDLE:
            {
                //idleSeq();
            }
            break;
           
        case GOING_IDLE :
            {
               //clearDisp();    
            }
            break;
            
        case EVALUATING_WEIGHT :
            {
                //checkSeq();
            }
            break;
            
        case READY :
            {
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
                //startSeq();
            }
            break;
            
        case CHUG:
            {
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
              if (pLoser == 1)
            {
              stopLCD(1);
              tidWinner = getTime();
              // afspiller vinder sekvens
            }
            else if (pLoser == 0)
            {
                stopLCD(2);
                tidWinner = getTime();
                // afspiller vinder sekvens
            }
            }
            
            break;
            
        case EVALUATING_NEW_WEIGHT :
            {
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
              clearTimer();
            }
            break;
        
            
            
            
            
            
            
            
            // ------------------------------------ERR STATES---------------------------------------------------
            
            case ERR_WEIGHT:
            {
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
                //timer if-else statement
            }    
            break;
            
            case ERR_FALSE_START:
            {
                //timer if-else statement
            }    
            break;
            
            case ERR_TIMEOUT:
            {
                //timer if-else statement
            }    
            break;
            
            case ERR_NOCHUG:
            {
                if (glasvaegtp1 < readdata1()) 
                {
                    //errorSeq(1);
                }
                else if(glasvaegtp2 < readdata2()) 
                {
                    //errorSeq(2);
                }          
            }    
            break;
            
            
        default :
            {
            }
            break;
            
        
       }
           
}
/* [] END OF FILE */
