#include "Stopur.h"
#include "Display.h"

int count = 0;

CY_ISR(isr_timer)                // interrupter hvert 100 ms
{
    if (count < 1200)            // incrementeres ved hvert interrupt
    {
        count++;
       
    }else{
        stopTimer();             // stopper vores interrupt rutine hvis count overstiger 1200 hvilket svarer til 120s eller 2 minuter
    }
}

void initTimer()                 // initiere timer_stopur
{
    isr_timer_StartEx(isr_timer);
}

void startTimer()                // starter timer_stopur 
{
   Timer_Stopur_Start();
}

void stopTimer()                 // Stopper timer_stopur
{
   Timer_Stopur_Stop();
}

int getTime()                    // Returnere vores count værdi som ms
{   
    return count*100;
}

void clearTimer()                // nulstiller vores timer ved at sætte count til 0
{
    count = 0;
}

