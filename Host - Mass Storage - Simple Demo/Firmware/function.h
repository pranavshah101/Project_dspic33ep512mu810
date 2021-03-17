#include "pin_manager.h"
#define SAMP_BUFF_SIZE  8
int ain0Buff[SAMP_BUFF_SIZE];
int ain1Buff[SAMP_BUFF_SIZE];
int ain2Buff[SAMP_BUFF_SIZE];
int ain3Buff[SAMP_BUFF_SIZE];
int ain4Buff[SAMP_BUFF_SIZE];
int ain5Buff[SAMP_BUFF_SIZE];
int ain8Buff[SAMP_BUFF_SIZE];
int ain9Buff[SAMP_BUFF_SIZE];
int ain10Buff[SAMP_BUFF_SIZE];
int scanCounter = 0;
int sampleCounter = 0;

unsigned long data[110];
unsigned long data1[110];
unsigned long data2[110];
unsigned long data3[110];
unsigned long data4[10];
unsigned long data5[10];
unsigned long data8[10];
unsigned long data9[10];
unsigned long data10[10];
unsigned long data_1[10];
    
 
void RBC_POWER_SEQ()
{

RS_RL4_ON();     // RS_RL4- RBC RELAY START
__delay_ms(2300);     // delay of exact 10 seconds
RM_RL3_ON();     // RS_RL3_RBC COIL CONTRACTOR RELAY
RS_RL4_OFF();    // RS_RL4_RBC_RELAY_START
}

void ALL_RELAY_OFF()
{
    RS_RL4_OFF();
    RM_RL3_OFF();
    ES_RL2_OFF();
    EM_RL1_OFF();
}

void EBC_POWER_SEQ()
{
ES_RL2_ON();            // RS_RL4- RBC RELAY START
__delay_ms(1200);       // delay of exact 10 seconds
EM_RL1_ON();           // RS_RL3_RBC COIL CONTRACTOR RELAY
ES_RL2_OFF();          // RS_RL4_RBC_RELAY_START
}

void init_ADC()
{
   
   ANSELB=ANSELA=ANSELC=ANSELD=ANSELG=ANSELE=0x0000;
   ANSELB=0x0F1F;        // Select AN0,AN1,AN2,AN3,AN4,AN5,AN8,AN9and AN10 channel as analog input
   AD1CON1 = 0x04E4;     // Enable 12-bit mode, auto-sample and auto-conversion  
   AD1CON2 = 0x2420;     // Sample 4 channels alternately using channel scanning
   AD1CON3 = 0x0F01;   
   AD1CON4 = 0x0000;
   AD1CSSH = 0x0000;
   AD1CSSL = 0x0F1F;     // Select AN0,AN1,AN2,AN3,AN4,AN5,AN8,AN9and AN10 for scanning      
   AD1CHS0bits.CH0SA = 0; 
   AD1CHS0bits.CH0NA = 0; 
   AD1CON1bits.ADON = 1;

   
}






