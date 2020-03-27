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

/* [] END OF FILE */
#include "project.h"
#include "stdio.h"
#include "math.h"

//struct til at holde på data for hver enkelt LED
typedef struct LEDctrl_
{
    int red;
    int green;
    int blue;
    
    double h;
    double s;
    double v;
    
    int green1;
    int green2;
    int red1;
    int red2;
    int blue1;
    int blue2;  
    
    int LEDlength;
    int pin;
    
    int ring;
    int pulse;
}LEDctrl;

void UpdateLED(LEDctrl *rgbLEd_); //Opdater alle LED, ny farve, i ønsket LED strip
void hsv2rgb(double H, double S, double L, int LED, LEDctrl *rgbLEd_); //Konverter HSV til RGB

void setrefreshrate(int Hz); //Ændre hvor hurtigt LED opdateres
void setspeed(int ms_ring, int ms_pulse); //Bestemmer hvor hurtigt, pulse ændre lysniveau og hvor hurtigt ring flytter sig en plads
void setcolorLED(double h, double s, double v, int LED, LEDctrl *rgbLEd_); //Ændre farven på 1 LED
void fillcolor(double h, double s, double v, LEDctrl *rgbLEd_); //Ændre farven på alle LED'er
void pulseLED(double h, double s, double v, LEDctrl *rgbLEd_); //Sætter LED strip til at pulse, med ønsket farve
void initLED(int Refreshrate);
void ringLED(int pulselength, double h, double s, double v, LEDctrl *rgbLEd_); //Sætter LED strip til at køre rundt i ring
void addLEDstrip(int LEDlength_, LEDctrl *rgbLED, int strip); //Tilføjer en LED strip, OBS der kan max være 2

//Forskellige sekvenser til LED OBS ordforklaringer er i system arkitketur
void LEDinitSeq();    //Initieringssekvens
void idleSeq();      //Idle-sekvens
void loserSeq();     //Tabersekvens
void zeroCalibrateSeq(); //Kalibreringssekvens
void checkSeq(); //Tjek vægt sekvens
void weightapprovedSeq(); //Vægt godkendt sekvens
void startSeq(); //Start sekvens
void errorSeq(); //Fejl sekvens
void winnerSeq();   //Vindersekvens