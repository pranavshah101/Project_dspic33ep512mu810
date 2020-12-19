#include "mcc_generated_files/pin_manager.h"
#define SAMP_BUFF_SIZE  8
#define RBC_NO_Fault   1
#define RBC_Fault      0
#define EBC_NO_Fault   1
#define EBC_Fault      0

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
int var,var1,var2,var3=0,var4=0,var5=0,var8=0,var9=0,var10=0;

    unsigned long data[110];
    unsigned long data1[110];
    unsigned long data2[110];
    unsigned long data3[10];
    unsigned long data4[10];
    unsigned long data5[10];
    unsigned long data8[10];
    unsigned long data9[10];
    unsigned long data10[110];
   
void RBC_POWER_SEQ()
{

RS_RL4_ON();          // RS_RL4- RBC RELAY START
__delay_ms(2300);     // delay of exact 10 seconds
RM_RL3_ON();          // RS_RL3_RBC COIL CONTRACTOR RELAY
RS_RL4_OFF();         // RS_RL4_RBC_RELAY_START
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
__delay_ms(190);       // Delay of exact 10 seconds
EM_RL1_ON();            // RS_RL3_RBC COIL CONTRACTOR RELAY
ES_RL2_OFF();           // RS_RL4_RBC_RELAY_START
}

void init_ADC()
{
   
    ANSELB=ANSELA=ANSELC=ANSELD=ANSELG=ANSELE = 0x0000; // Set port configuration,default: Digital I/O
    ANSELB  = 0x073F;         // Selected 9 channel (AN0,AN1,AN2,AN3,AN4,AN5,AN8,AN9,AN10)as analog input
    AD1CON1 = 0x04E4;         // Enable 12-bit mode, auto-sample and auto-conversion  
    AD1CON2 = 0x2420;         // Sample 9 channels alternately using channel scanning
    AD1CON3 = 0x0F0F;         // Sample for 15*TAD before converting       
    AD1CON4 = 0x0000;
    AD1CSSH = 0x0000;
    AD1CSSL = 0x073F;         // Select AN0,AN1,AN2,AN3,AN4,AN5,AN8,AN9,AN10 for scanning   
    AD1CHS0bits.CH0SA = 0;    // CH0SA bits ignored for CH0 +ve input selection
    AD1CHS0bits.CH0NA = 0;    // Select VREF- for CH0 -ve input
    AD1CON1bits.ADON  = 1;    // Enable ADC module
   
}


