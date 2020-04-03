
#include "Display.h"
#include "Stopur.h"

#define Display1 0x26                                  // Definere adressen på display 1
#define Display2 0x27                                  // Definere adressen på display 2

int display1On = 0;                                    //Bestemmer om display1 opdateres i interrupt
int display2On = 0;                                    //Bestemmer om display2 opdateres i interrupt

CY_ISR(isr_refreshrate_LCD)
{
    int x = getTime();                                  // vores count værdi bliver lagt i variablen x
    if (display1On == 1) dispTime(1,x);                 // Kalder dispTime funktion for begge displays
    if (display2On == 1) dispTime(2,x);
}



void initDisp(int Hz)                                   // Initiere display
{
    I2C_1_Start();                                      // Initiere og klargør I2C komponenten
    isr_refreshrate_LCD_StartEx(isr_refreshrate_LCD);   // Initiere interrupt for refreshrate på displays
    Timer_LCD_WritePeriod((1/Hz)*10000);                // Omskriver Hz til ms og opdaterer refreshraten
    
    LiquidCrystal_I2C_init(Display1,16,2,0);            // Initiere vores LCD library med: adressen på LCD'en, antal characters, antal rækker og størrelsen på "dots"
    begin();                                            // positionere vores display til begin state
    clear();
    
    LCD_print("Spiller 1");
    setCursor(0,1);                                     // vælger kollene og række
    LCD_print("Tid: ");
    
    LiquidCrystal_I2C_init(Display2,16,2,0);
    begin();                                            // positionere vores display til begin state
    clear();
    
    LCD_print("Spiller 2");
    setCursor(0,1);                                     // vælger kollenne og række
    LCD_print("Tid: ");
    
    display1On = 1;
    display2On = 1;
    
    Timer_LCD_Start();                                    // starter timeren for display
}

void dispTime(int disp, int ms)                           // positionere og udskriver på displays
{
    Timer_LCD_Stop();                                     // stopper opdateringen af display
    if(ms == 0)
    {
        setCursor(9,1);
        LCD_print("     ");                               // nulstiller display tid
    }
    int seconds = 0;
    char buf[20];
    disp = disp == 1 ? 0x26 : 0x27;
   
    seconds = ms / 1000;                                  // værdien kommer som ms derfor /1000 for at få sekunder
    ms = (ms - seconds*1000);                             // sørger for at vi får vores decimal tal 
    
    setaddress(disp);
    snprintf(buf, 8, "%d,%ds", seconds, ms);              // udskriver vores sekunder og ms
    setCursor(5,1);
    LCD_print(buf);
    
    Timer_LCD_Start();                                    // starter timeren for displays 
}

void stopLCD(int disp)                                    // stopper displays enkeltvis 
{
    if (disp == 1)
    {
    display1On = 0;
    }else{
    display2On = 0;
    }
}