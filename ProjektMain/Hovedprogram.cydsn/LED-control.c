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


#define MAXLEDINTENSE 0.5
#include "LED-control.h"

static int pulselength_ = 0;
static int index_ = 0;
static float index2 = MAXLEDINTENSE;
static int count = 0;
static int count2 = 0;
static int count3 = 0;

LEDctrl *rgbLED1 = NULL;
LEDctrl *rgbLED2 = NULL;


CY_ISR(isr_refreshrate)
{
    Timer1_Stop();     //Timer stoppes, så der sendes for at sikre stabilitet
    isr_refreshrate_LCD_Disable();
    if (rgbLED1 != NULL)
    {
    UpdateLED(rgbLED1); //Opdater LED-strip med nye farver
    }
    CyDelayUs(100);     //Delay for at sikre stabilitet
    if (rgbLED2 != NULL)
    {
    UpdateLED(rgbLED2); //Opdater LED-strip med nye farver
    }
    CyDelayUs(100);
    isr_refreshrate_LCD_Enable();
    Timer1_Start();
}

CY_ISR(isr_LED_ring)
{
    if((rgbLED1->ring == 0) && (rgbLED2->ring == 0)) return;    //Gør intet hvis ring sekvens ikke er til
    if(rgbLED1->ring == 1) fillcolor(0,0,0,rgbLED1);            //Slukker alle LED'er på LED-strip
    if(rgbLED2->ring == 1) fillcolor(0,0,0,rgbLED2);
    
        for(int i2 = index_; i2 < pulselength_+index_; i2++)    //Bestemmer hvilke LED'er der skal tændes
        {
            if(rgbLED1->ring == 1)
            {
                int x = i2 >= rgbLED1->LEDlength ? i2 - rgbLED1->LEDlength : i2; //Starter forfra hvis i2 er større end lEDlength
                setcolorLED((rgbLED1 + x)->h, (rgbLED1 + x)->s, (rgbLED1 + x)->v, x, rgbLED1);
            }
            if(rgbLED2->ring == 1)
            {
                int x = i2 >= rgbLED2->LEDlength ? i2 - rgbLED2->LEDlength : i2;
                setcolorLED((rgbLED2 + x)->h, (rgbLED2 + x)->s, (rgbLED2 + x)->v, x, rgbLED2);  
            }
        }
    if (rgbLED1 != NULL)
    {
        index_ = index_ < (rgbLED1->LEDlength-1) ? index_ + 1 : 0; //Øger index_ med 1 hvis den er under LEDlength-1
        return;
    }else if (rgbLED2 != NULL){
        index_ = index_ < (rgbLED2->LEDlength-1) ? index_ + 1 : 0;
    }
}

CY_ISR(isr_LED_pulse)
{
    
    if(count == 0) //Mindsker lysstyrke på LED-strip
    {
        if (rgbLED1->pulse == 1)fillcolor(rgbLED1->h,rgbLED1->s,index2, rgbLED1);
        if (rgbLED2->pulse == 1)fillcolor(rgbLED2->h,rgbLED2->s,index2, rgbLED2);
        index2 = index2-0.01;
        if (index2 < 0)count = 1;
    }else if(count == 1){ //Øger lysstyrke på LED-strip
        if (rgbLED1->pulse == 1)fillcolor(rgbLED1->h,rgbLED1->s,index2, rgbLED1);
        if (rgbLED2->pulse == 1)fillcolor(rgbLED2->h,rgbLED2->s,index2, rgbLED2);
        index2 = index2+0.01;
        if (index2 == MAXLEDINTENSE)count = 0;
    }
    
}

CY_ISR(isr_BlinkLED)
{
    switch (count3)
    {
        case 0: //Tænder LED-strip
        {
            if(rgbLED1->blink == 1) fillcolor(rgbLED1->h, rgbLED1->s,1, rgbLED1);
            if(rgbLED2->blink == 1) fillcolor(rgbLED2->h, rgbLED2->s,1, rgbLED2);
            count3++;
        }
        break;
        case 1: //Slukker LED-strip
        {
            if(rgbLED1->blink == 1)fillcolor(rgbLED1->h, rgbLED1->s,0, rgbLED1);
            if(rgbLED2->blink == 1)fillcolor(rgbLED2->h, rgbLED2->s,0, rgbLED2);
            count3 = 0;
        }
        break;
    }
  
}

CY_ISR(isr_delay)
{
    count2++;
    startSeq(rgbLED1, rgbLED2);
}

void setrefreshrate(int Hz)
{
    Hz = 1/(float)Hz*1000*10; //Omregner HZ til en bestemt periode for timeren
    Timer1_WritePeriod(Hz);
}

void addLEDstrip(int LEDlength_, LEDctrl *rgbLED_, int strip)
{
    if (strip == 1) //Sammen kobler den givende objekt med enten rgbLED1 eller 2
    {
        rgbLED1 = rgbLED_;
    }else{
        rgbLED2 = rgbLED_;
    }
    
    rgbLED_->LEDlength = LEDlength_; //Sammen kobler varibel LEDlength
    rgbLED_->pin = strip; //Sammen kobler varibel strip
    LEDOff(rgbLED_); //Slukker for alle sekvenser for objektet
    
    for(int i = 0; i < rgbLED_->LEDlength; i++)
    {
        setcolorLED(0,0,0,i, rgbLED_); //Slukker for alle LED'er
    }
}

void initLED(int Hz)
{    
    //Sætter alle interrupts op
    isr_LED_refreshrate_StartEx(isr_refreshrate);
    isr_LED_ring_StartEx(isr_LED_ring);
    isr_LED_pulse_StartEx(isr_LED_pulse);
    isr_BlinkLED_StartEx(isr_BlinkLED);
    isr_delay_StartEx(isr_delay);
    
    //Slukker for alle sekvenser
    LEDOff(rgbLED1);
    LEDOff(rgbLED2);
    
    //Sætter defeault værdier for globale variabler
    pulselength_ = 0;
    index_ = 0;
    index2 = MAXLEDINTENSE;
    count = 0;
    count2 = 0;
    count3 = 0;
    
    //Starter timerer og SPI-modul
    SPIM_1_Start();
    Timer1_Start();
    Timer2_Start();
    Timer3_Start();
    Timer4_Start();
    
    //Sætter LED-strips refreshrate 
    setrefreshrate(Hz);
    
}


void fillcolor(double h, double s, double v, LEDctrl *rgbLED)
{
    //Sætter farven på hele LED-strip'en
    for(int i = 0; i < rgbLED->LEDlength; i++)
    {
        setcolorLED(h, s, v, i, rgbLED);
    }
}

void setspeed(int ms_ring, int ms_pulse, int ms_blink)
{
    //Ændre hvor hurtigt timerne interrupt, og derved hastigheden på sekvenserne
    Timer2_WritePeriod(ms_pulse*10);
    Timer3_WritePeriod(ms_ring*10);
    Timer4_WritePeriod(ms_blink*10);
}


void pulseLED(double h1, double s1, double v1, LEDctrl *rgbLED)
{
    LEDOff(rgbLED);     //Slukker alle sekvenser for det givende objekt
    rgbLED->pulse = 1;  //Tænder for pulse sekvens for det givende objekt
    
    //Gemmer farven der er givet med
    rgbLED->h = h1;     
    rgbLED->s = s1;
    rgbLED->v = v1;
    
    //Sætter farven på hele LED-strip'en for det givende objekt
    fillcolor(h1,s1,v1, rgbLED);
}

void ringLED(int pulselength, double h1, double s1, double v1, LEDctrl *rgbLED)
{
    
    pulselength_ = pulselength;
    LEDOff(rgbLED);
    rgbLED->ring = 1;
    
    for(int i = 0; i<rgbLED->LEDlength; i++)
    {
        (rgbLED + i)->h = h1;
        (rgbLED + i)->s = s1;
        (rgbLED + i)->v = v1;
    }
}

void BlinkLED(double h1, double s1, double v1, LEDctrl *rgbLED)
{
    LEDOff(rgbLED);
    rgbLED->blink = 1;
    
    for(int i = 0; i<rgbLED->LEDlength; i++)
    {
        (rgbLED + i)->h = h1;
        (rgbLED + i)->s = s1;
        (rgbLED + i)->v = v1;
    }
}


void hsv2rgb(double h, double s, double v, int LED, LEDctrl *rgbLED)
{
    double  C, hh, X, m, r, g, b;
    int i;
    
    if(v > MAXLEDINTENSE) v = MAXLEDINTENSE;

    if(s <= 0.0) {       // < is bogus, just shuts up warnings
        (rgbLED + LED)->green = v;
        (rgbLED + LED)->red = v;
        (rgbLED + LED)->blue = v;
        return;
    }
    
    //HSV til RGB beregning
    C = v * s;
    hh = h / 60.0;
    X = C * (1- fabs(fmod(hh, 2) -1));
    m = v - C;
    
    i = hh;

    switch(i) {
    case 0:
        r = C;
        g = X;
        b = 0.0;
        break;
    case 1:
        r = X;
        g = C;
        b = 0.0;
        break;
    case 2:
        r = 0.0;
        g = C;
        b = X;
        break;

    case 3:
        r = 0.0;
        g = X;
        b = C;
        break;
    case 4:
        r = X;
        g = 0.0;
        b = C;
        break;
    case 5:
    default:
        r = C;
        g = 0.0;
        b = X;
        break;
    }
    
    //Sætter RGB værdier til at være fra 0-255 og ikke 0-1
    r = round((r + m)*255.0);
    g = round((g + m)*255.0);
    b = round((b + m)*255.0);
    
    //Sikre ingen negative værdier
    r = r < 0 ? 0 : r;
    g = g < 0 ? 0 : g;
    b = b < 0 ? 0 : b;
    
    //Giver det givende objekt nye RGB værdier
    (rgbLED + LED)->green = g;
    (rgbLED + LED)->red = r;
    (rgbLED + LED)->blue = b;
    return;
    
}

void UpdateLED(LEDctrl *rgbLED)
{
    if(rgbLED->pin == 1){ //Hvis LED strip til pin 1 skiftes SPIM til at output til LEDdata2
        SPIMOutCtrl_Write(1);
    }else if (rgbLED->pin == 2){ //Hvis LEd stip til pin 2 skiftes SPIM til at output til LEDdata
        SPIMOutCtrl_Write(0);
    }else{
        return;
    }
    for(int i = 0; i < rgbLED->LEDlength; i++) //Sender data til LED strip
    {
        //8bit grøn farve
        SPIM_1_WriteTxData((rgbLED + i)->green1);
        SPIM_1_WriteTxData((rgbLED + i)->green2);
        
        //8bit rød farve
        SPIM_1_WriteTxData((rgbLED + i)->red1);
        SPIM_1_WriteTxData((rgbLED + i)->red2);
        
        //8bit blå farve
        SPIM_1_WriteTxData((rgbLED + i)->blue1);
        SPIM_1_WriteTxData((rgbLED + i)->blue2);
    }
}

void setcolorLED(double h, double s, double v, int LED, LEDctrl *rgbLED)
{
    int Red, Green, Blue;
    
    hsv2rgb(h,s,v,LED, rgbLED); //hsv konverteres til RGB og gemmes i rgbLED's red, green blue
    
    Red = (rgbLED + LED)->red;
    Green = (rgbLED + LED)->green;
    Blue = (rgbLED + LED)->blue;
 
    int x = Green;
    int buf[12];
    
    for (int i = 0; i<8; i++) //Hver farve er 8bit lang derfor konvertes hver bit til det delay som svarer til 1 eller 0
    {
        if(x & 128)     //Tjekker om det bittet på bit plads 7 er 1
        {
            buf[i] = 0b110; //Konverterer 1 til det tilsvarende delay
        }else{
            buf[i] = 0b100; //Konverterer 0 til det tilsvarende delay
        }
        x = x<<1;   //Flytter alle bit i x til venstre, så næste bit gang tjekkes
    }
    //Da SPI komponenten maks kan sende 16bit af gange og der skal sendes 24bit for hver farve deles farven op i 2
    (rgbLED + LED)->green1 = (buf[0]<<9) + (buf[1]<<6) + (buf[2]<<3) + buf[3];
    (rgbLED + LED)->green2 = (buf[4]<<9) + (buf[5]<<6) + (buf[6]<<3) + buf[7];
    
    x = Red;
    for (int i = 0; i<8; i++)
    {
        if(x & 128)
        {
            buf[i] = 0b110;
        }else{
            buf[i] = 0b100;
        }
        x = x<<1;
    }
    (rgbLED + LED)->red1 = (buf[0]<<9) + (buf[1]<<6) + (buf[2]<<3) + buf[3];
    (rgbLED + LED)->red2 = (buf[4]<<9) + (buf[5]<<6) + (buf[6]<<3) + buf[7];
    
    x = Blue;
    for (int i = 0; i<8; i++)
    {
        if(x & 128)
        {
            buf[i] = 0b110;
        }else{
            buf[i] = 0b100;
        }
        x = x<<1;
    }
    (rgbLED + LED)->blue1 = (buf[0]<<9) + (buf[1]<<6) + (buf[2]<<3) + buf[3];
    (rgbLED + LED)->blue2 = (buf[4]<<9) + (buf[5]<<6) + (buf[6]<<3) + buf[7];

}

void LEDOff(LEDctrl *rgbLED)
{
    //Slukker Timer5 og andre sekvenser
    Timer5_Stop();
    rgbLED->ring = 0;
    rgbLED->pulse = 0;
    rgbLED->blink = 0;
}



//Forskellige sekvenser til LED OBS ordforklaringer er i system arkitketur
void LEDinitSeq(LEDctrl *rgbLED)    //Initieringssekvens
{
    ringLED(3, 191, 1.0, 0.5, rgbLED);
}

void idleSeq(LEDctrl *rgbLED)      //Idle-sekvens
{
    pulseLED(307, 1.0, 0.85, rgbLED);
}

void loserSeq(LEDctrl *rgbLED)     //Tabersekvens
{
    LEDOff(rgbLED);
    fillcolor(3, 1.0, 0.83, rgbLED);
    
}

void zeroCalibrateSeq(LEDctrl *rgbLED) //Kalibreringssekvens
{
    pulseLED(65, 1, 1, rgbLED);
}

void checkSeq(LEDctrl *rgbLED) //Tjek vægt sekvens
{
    ringLED(3, 65, 1, 1, rgbLED);
}

void weightapprovedSeq(LEDctrl *rgbLED) //Vægt godkendt sekvens
{
    LEDOff(rgbLED);
    fillcolor(116, 1, 1.0, rgbLED);
}

int startSeq(LEDctrl *rgbLED_1, LEDctrl *rgbLED_2) //Start sekvens
{
    switch (count2)
    {
        case 0:
        {
            //Slukker alle sekvenser
            LEDOff(rgbLED_1);
            LEDOff(rgbLED_2);
            
            //Tænder 1sek delay timer
            Timer5_Start();
            isr_delay_Enable();
        }
        case 1:
        {            
            //Sætter rød farve på begge LED-strip
            fillcolor(3, 1.0, 0.83, rgbLED_1);
            fillcolor(3, 1.0, 0.83, rgbLED_2);
        }
        break;
        
        case 2:
        {
            //Sætter gul farve på begge LED-strip
            fillcolor(65, 1, 1, rgbLED_1);
            fillcolor(65, 1, 1, rgbLED_2);
        }
        break;
        
        case 3:
        {
            //Sætter gul farve på begge LED-strip
            fillcolor(65, 1, 1, rgbLED_1);
            fillcolor(65, 1, 1, rgbLED_2);
        }
        break;
        case 4:
        {
            //Sætter grøn farve på begge LED-strip
            fillcolor(116, 1, 1.0, rgbLED_1);
            fillcolor(116, 1, 1.0, rgbLED_2);
            
            //Slukker for 1sek delay timer
            Timer5_Stop();
            isr_delay_Disable();
            
            count2++;
        }
        break;
        case 5:
        {  
            //returner 1 for at indikere at start sekvens er færdig
            count2 = 0;
            return 1;
        }
        break;
    }
    return 0;
}

void errorSeq(LEDctrl *rgbLED) //Fejl sekvens
{
    BlinkLED(3, 1.0, 0.83, rgbLED);
}

void winnerSeq(LEDctrl *rgbLED)   //Vindersekvens
{
    LEDOff(rgbLED);
    fillcolor(116, 1, 1.0, rgbLED);
}


