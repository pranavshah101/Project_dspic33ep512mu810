#include "mcc_generated_files/pin_manager.h"


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
int var,var1,var2,var3=0,var4=0,var5=0,var8=0,var9=0,var10=0;
float voltage;

    unsigned long data[110];
    unsigned long data1[110];
    unsigned long data2[110];
    unsigned long data3[110];
    unsigned long data4[10];
    unsigned long data5[10];
    unsigned long data8[10];
    unsigned long data9[10];
    unsigned long data10[110];
    unsigned long data_1[10];
    
 void LED_OFF()
 {
     IO_RA2_SetLow();
     IO_RA3_SetLow();
     IO_RA4_SetLow();
     IO_RA5_SetLow();
     
 }
 
 void LED_EBC_SEQ()
 {
     IO_RA5_SetHigh();   //8
     __delay_ms(10000);
     IO_RA2_SetHigh(); //5
     __delay_ms(1000);
     IO_RA5_SetLow();//8
     
     
 }
 
 void LED_RBC_SEQ()
 {
     IO_RA4_SetHigh();//6
     __delay_ms(10000);
     IO_RA3_SetHigh();//5
      __delay_ms(1000);
     IO_RA4_SetLow();//6
     
    // IO_RD7_SetHigh();   
 }

void RBC_POWER_SEQ()
{

RS_RL4_ON();     // RS_RL4- RBC RELAY START
__delay_ms(10000);     // delay of exact 10 seconds
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
ES_RL2_ON();     // RS_RL4- RBC RELAY START
__delay_ms(10000);     // delay of exact 10 seconds
EM_RL1_ON();     // RS_RL3_RBC COIL CONTRACTOR RELAY
ES_RL2_OFF();    // RS_RL4_RBC_RELAY_START
}

void init_ADC()
{
   
   ANSELB=ANSELA=ANSELC=ANSELD=ANSELG=ANSELE=0x0000;
   ANSELB=0x0107;     // 4 channel
  // ANSELB=0x0007;      // 3 channel
    
    AD1CON1 = 0x04E4;    // Enable 12-bit mode, auto-sample and auto-conversion  
    AD1CON2 = 0x240C;   //  Sample 4 channels alternately using channel scanning
   // AD1CON2 = 0x2408;     // Sample 3 channels alternately using channel scanning
//    AD1CON2.VCFG=1;
    AD1CON3 = 0x0F0F;   //  Sample for 15*TAD before converting
    //AD1CON3 = 0x117F;     // 500 us sampling time
    AD1CON4 = 0x0000;
    AD1CSSH = 0x0000;
    AD1CSSL = 0x0107; // Select AN2, AN3, AN5 and AN8 for scanning
    
    //AD1CSSL = 0x0007;   // 3 channel
    
AD1CHS0bits.CH0SA = 0; 
AD1CHS0bits.CH0NA = 0; 
AD1CON1bits.ADON = 1;

//__delay_us(100);
    
  
   
}
void init_adc()
{
    int i;
    AD1CON1bits.FORM = 0;                       // Data Output Format: Signed Fraction (Q15 format)
    AD1CON1bits.SSRC = 2;                       // Sample Clock Source: GP Timer3 starts conversion
    AD1CON1bits.SSRCG = 0;                      // Sample Clock Source: GP Timer3 starts conversion
    AD1CON1bits.ASAM = 1;                       // ADC Sample Control: Sampling begins immediately after conversion
    AD1CON1bits.AD12B = 1;                      // 12-bit ADC operation
    AD1CON2bits.CSCNA = 1;                      // Scan Input Selections for CH0+ during Sample A bit
    AD1CON2bits.VCFG = 1;                       // External Vref+ selected(i.e 2.5V)
    AD1CON2bits.CHPS = 0;                       // Converts CH0
    AD1CON3bits.ADRC = 0;                       // ADC Clock is derived from Systems Clock
    
   AD1CON3bits.ADCS = 15;     
   
                     // ADC Conversion Clock Tad=Tcy*(ADCS+1)= (1/40M)*64 = 1.6us (625Khz)

    // ADC Conversion Time for 10-bit Tc=12*Tab = 19.2us
    AD1CON2bits.SMPI = 8;    // 4 ADC Channel is scanned
    AD1CON4bits.ADDMAEN = 1;                    // Conversion results stored in ADCxBUF0 register

    //AD1CSSH/AD1CSSL: A/D Input Scan Selection Register
    AD1CSSH = 0x0000;
    AD1CSSLbits.CSS0= 1;                      
    AD1CSSLbits.CSS1 = 1;
    AD1CSSLbits.CSS2 = 1;
    AD1CSSLbits.CSS3 = 1;
    AD1CSSLbits.CSS4 = 1;                      
    AD1CSSLbits.CSS5 = 1;      
    AD1CSSLbits.CSS8 = 1; 
    AD1CSSLbits.CSS9 = 1; 
    AD1CSSLbits.CSS10 = 1; 
    ANSELB = 0x073f;
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB4 = 1;
    TRISBbits.TRISB5 = 1;
    TRISBbits.TRISB8 = 1;
    TRISBbits.TRISB9 = 1;
    TRISBbits.TRISB10 = 1;

    IFS0bits.AD1IF = 0;     // Clear the A/D interrupt flag bit
    IEC0bits.AD1IE = 1;     // Enable A/D interrupt
    AD1CON1bits.ADON = 1;   // Turn on the A/D converter
    __delay_us(10);
}

void InitTmr3( void )
{
    TMR3 = 0x0000;
    PR3 =4999;         // Trigger ADC1 every 125usec
    IFS0bits.T3IF = 0;  // Clear Timer 3 interrupt
    IEC0bits.T3IE = 0;  // Disable Timer 3 interrupt

    //Start Timer 3
    T3CONbits.TON = 1;
}

void __attribute__ ( (interrupt, no_auto_psv) ) _AD1Interrupt( void )
{
    switch( scanCounter )
    {
        case 1:
            ain1Buff[sampleCounter] = ADC1BUF0;
            break;

       /* case 1:
            ain1Buff[sampleCounter] = ADC1BUF0;
            break;
         
        case 2:
            ain2Buff[sampleCounter]=ADC1BUF0;
            break;
         
        case 3:
            ain3Buff[sampleCounter]=ADC1BUF0;
            break;
                      
        case 4:
            ain4Buff[sampleCounter] = ADC1BUF0;
            break;

        case 5:
            ain5Buff[sampleCounter] = ADC1BUF0;
            break;
        
        case 6:
            ain8Buff[sampleCounter]=ADC1BUF0;
            break;
         
        case 7:
            ain9Buff[sampleCounter]=ADC1BUF0;
            break;
        case 8:
            ain10Buff[sampleCounter]=ADC1BUF0;
            break;    */       

        default:
            break;
    }
    scanCounter++;
    if( scanCounter == 9 )
    {
        scanCounter = 0;
        sampleCounter++;
    }

    if( sampleCounter == SAMP_BUFF_SIZE )
    {
        sampleCounter = 0;
    }

    //TglPin();           // Toggle RA6
    IFS0bits.AD1IF = 0; // Clear the ADC1 Interrupt Flag
}

void read_input_current()
{
    
   var8=ain8Buff[sampleCounter];
   var9=ain9Buff[sampleCounter];
   var10=ain10Buff[sampleCounter];
    
   LCD_Command(0x01);
   __delay_ms(10);
   sprintf(data8,"%d",var8);
   strcat(data8,"=CT3");
   LCD_String_xy(1,0,data8);   
    
   sprintf(data9,"%d",var9);
   strcat(data9,"=CT2");
   LCD_String_xy(1,9,data9);  
    
   sprintf(data10,"%d",var10);
   strcat(data10,"=CT1");
   LCD_String_xy(2,0,data10);  
    
    __delay_ms(150);
   
}

void read_input_voltage()
{
    int i;
    int variable1;
    
   
        
    
    //var=ain0Buff[sampleCounter];
    variable1=ain1Buff[sampleCounter];
    
    
   // var2=ain2Buff[sampleCounter];
    
    //LCD_Command(0x01);
    //__delay_ms(10);
    
   
    
   
    
    sprintf(data1,"%d",variable1);
    strcat(data1,"=V_Y");
    LCD_String_xy(1,8,data1);  //Y-
   
     
     
   
    __delay_ms(100);   
    //LCD_Command(0x01);
    //__delay_ms(10);
}
    


void read_dc_voltage()
{
    
    var3=ain3Buff[sampleCounter];
    var4=ain4Buff[sampleCounter];
    var5=ain5Buff[sampleCounter];
      
    LCD_Command(0x01);
    __delay_ms(10);
    sprintf(data3,"%d",var3);
    strcat(data3,"=RBCV");
    LCD_String_xy(1,0,data3);   
    
    sprintf(data4,"%d",var4);
    strcat(data4,"=EBCV");
    LCD_String_xy(1,9,data4);  
    
    sprintf(data5,"%d",var5);
    strcat(data5,"=BAT_OP_DCV");
    LCD_String_xy(2,0,data5);  
    __delay_ms(150);
    
}

