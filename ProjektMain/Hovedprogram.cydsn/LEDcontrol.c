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
#define MAXLEDINTENSE 0.5
#include "LEDcontrol.h"

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
    Timer1_Stop();
    if (rgbLED1 != NULL)
    {
    UpdateLED(rgbLED1);
    }
    CyDelayUs(100);
    if (rgbLED2 != NULL)
    {
    UpdateLED(rgbLED2);
    }
    CyDelayUs(100);
    Timer1_Start();
}

CY_ISR(isr_LED_ring)
{
    if((rgbLED1->ring == 0) && (rgbLED2->ring == 0)) return;
    if(rgbLED1->ring == 1) fillcolor(0,0,0,rgbLED1);
    if(rgbLED2->ring == 1) fillcolor(0,0,0,rgbLED2);
    
        for(int i2 = index_; i2 < pulselength_+index_; i2++)
        {
            if(rgbLED1->ring == 1)
            {
                int x = i2 >= rgbLED1->LEDlength ? i2 - rgbLED1->LEDlength : i2;
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
        index_ = index_ < (rgbLED1->LEDlength-1) ? index_ + 1 : 0;
        return;
    }else if (rgbLED2 != NULL){
        index_ = index_ < (rgbLED2->LEDlength-1) ? index_ + 1 : 0;
    }
}

CY_ISR(isr_LED_pulse)
{
    
    if(count == 0)
    {
        if (rgbLED1->pulse == 1)fillcolor(rgbLED1->h,rgbLED1->s,index2, rgbLED1);
        if (rgbLED2->pulse == 1)fillcolor(rgbLED2->h,rgbLED2->s,index2, rgbLED2);
        index2 = index2-0.01;
        if (index2 < 0)count = 1;
    }else if(count == 1){
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
        case 0:
        {
            if(rgbLED1->blink == 1) fillcolor(rgbLED1->h, rgbLED1->s,1, rgbLED1);
            if(rgbLED2->blink == 1) fillcolor(rgbLED2->h, rgbLED2->s,1, rgbLED2);
            count3++;
        }
        break;
        case 1:
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
    Hz = 1/(float)Hz*1000*10;
    Timer1_WritePeriod(Hz);
}

void addLEDstrip(int LEDlength_, LEDctrl *rgbLED_, int strip)
{
    if (strip == 1)
    {
        rgbLED1 = rgbLED_;
    }else{
        rgbLED2 = rgbLED_;
    }
    
    rgbLED_->LEDlength = LEDlength_;
    rgbLED_->pin = strip;
    LEDOff(rgbLED_);
    
    for(int i = 0; i < rgbLED_->LEDlength; i++)
    {
        setcolorLED(0,0,0,i, rgbLED_);
    }
}

void initLED(int Hz)
{    
    isr_LED_refreshrate_StartEx(isr_refreshrate);
    isr_LED_ring_StartEx(isr_LED_ring);
    isr_LED_pulse_StartEx(isr_LED_pulse);
    isr_BlinkLED_StartEx(isr_BlinkLED);
    isr_delay_StartEx(isr_delay);
    
    LEDOff(rgbLED1);
    LEDOff(rgbLED2);
    
    pulselength_ = 0;
    index_ = 0;
    index2 = MAXLEDINTENSE;
    count = 0;
    count2 = 0;
    count3 = 0;
    
    
    SPIM_1_Start();
    Timer1_Start();
    Timer2_Start();
    Timer3_Start();
    Timer4_Start();
    
    setrefreshrate(Hz);
    
}


void fillcolor(double h, double s, double v, LEDctrl *rgbLED)
{
    for(int i = 0; i < rgbLED->LEDlength; i++)
    {
        setcolorLED(h, s, v, i, rgbLED);
    }
}

void pulseLED(double h1, double s1, double v1, LEDctrl *rgbLED)
{
    LEDOff(rgbLED);
    rgbLED->pulse = 1;
    
    rgbLED->h = h1;
    rgbLED->s = s1;
    rgbLED->v = v1;
    fillcolor(h1,s1,v1, rgbLED);
}

void setspeed(int ms_ring, int ms_pulse, int ms_blink)
{
    Timer2_WritePeriod(ms_pulse*10);
    Timer3_WritePeriod(ms_ring*10);
    Timer4_WritePeriod(ms_blink*10);
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

void hsv2rgb(double h, double s, double v, int LED, LEDctrl *rgbLED)
{
    double      hh, p, q, t, ff, r, g, b;
    long        i;
    
    if(v > MAXLEDINTENSE) v = MAXLEDINTENSE;

    if(s <= 0.0) {       // < is bogus, just shuts up warnings
        (rgbLED + LED)->green = v;
        (rgbLED + LED)->red = v;
        (rgbLED + LED)->blue = v;
        return;
    }
    
    hh = h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = v * (1.0 - s);
    q = v * (1.0 - (s * ff));
    t = v * (1.0 - (s * (1.0 - ff)));

    switch(i) {
    case 0:
        r = v;
        g = t;
        b = p;
        break;
    case 1:
        r = q;
        g = v;
        b = p;
        break;
    case 2:
        r = p;
        g = v;
        b = t;
        break;

    case 3:
        r = p;
        g = q;
        b = v;
        break;
    case 4:
        r = t;
        g = p;
        b = v;
        break;
    case 5:
    default:
        r = v;
        g = p;
        b = q;
        break;
    }
    r = r*256.0-1;
    g = g*256.0-1;
    b = b*256.0-1;
    
    r = r < 0 ? 0 : r;
    g = g < 0 ? 0 : g;
    b = b < 0 ? 0 : b;
    
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
    Timer5_Stop();
    rgbLED->ring = 0;
    rgbLED->pulse = 0;
    rgbLED->blink = 0;
}

void BlinkLED(double h1, double s1, double v1, LEDctrl *rgbLED)
{
    LEDOff(rgbLED);
    
    for(int i = 0; i<rgbLED->LEDlength; i++)
    {
        (rgbLED + i)->h = h1;
        (rgbLED + i)->s = s1;
        (rgbLED + i)->v = v1;
    }
    
    rgbLED->blink = 1;
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
            LEDOff(rgbLED_1);
            LEDOff(rgbLED_2);
            Timer5_Start();
            isr_delay_Enable();
        }
        case 1:
        {            
            fillcolor(3, 1.0, 0.83, rgbLED_1);
            fillcolor(3, 1.0, 0.83, rgbLED_2);
        }
        break;
        
        case 2:
        {
            fillcolor(65, 1, 1, rgbLED_1);
            fillcolor(65, 1, 1, rgbLED_2);
            //return 1;
        }
        break;
        
        case 3:
        {
            fillcolor(65, 1, 1, rgbLED_1);
            fillcolor(65, 1, 1, rgbLED_2);
               
            count2++;
            //fillcolor(65, 1, 1, rgbLED_1);
            //fillcolor(65, 1, 1, rgbLED_2);
            //return 1;
            
        }
        break;
        case 4:
        {
            //1 sekund delay
        }
        break;
        case 5:
        {
            LEDOff(rgbLED_1);
            LEDOff(rgbLED_2);
            
            fillcolor(116, 1, 1.0, rgbLED_1);
            fillcolor(116, 1, 1.0, rgbLED_2);
            Timer5_Stop();
            //count2 = 0;
            isr_delay_Disable();
            count2++;
        }
        break;
        case 6:
        {  
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


