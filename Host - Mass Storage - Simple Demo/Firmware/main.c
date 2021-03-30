/********************************************************************
 FileName:     main.c
 Dependencies: See INCLUDES section
 Processor:		PIC18, PIC24, and PIC32 USB Microcontrollers
 Hardware:		This demo is natively intended to be used on Microchip USB demo
 				boards supported by the MCHPFSUSB stack.  See release notes for
 				support matrix.  This demo can be modified for use on other hardware
 				platforms.
 Complier:  	Microchip C18 (for PIC18), C30 (for PIC24), C32 (for PIC32)
 Company:		Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the ?Company?) for its PIC® Microcontroller is intended and
 supplied to you, the Company?s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN ?AS IS? CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Description
  1.0   Initial release
  2.1   Updated for simplicity and to use common
                     coding style
********************************************************************/
#define FCY  48000000UL
#include "USB/usb.h"
#include "USB/usb_host_msd.h"
#include "USB/usb_host_msd_scsi.h"
#include "MDD File System/FSIO.h"
#include <libpic30.h>
#include <xc.h>
#include "system.h"
#include "lcd.h"
#include "function.h"


#define RBC_NO_Fault   0
#define RBC_Fault      1
#define EBC_NO_Fault   0      
#define EBC_Fault      1
#define Short_Ckt_Current 42
#define RBC_Maximum_Power 4400
#define Maximum_RBC_Current 36
#define Maximum_Bat_Current 14
#define Minimum_Settable_Bat_Current 10
#define Maximum_OP_Voltage  136
#define Minimum_OP_Voltage  105
#define Maximum_EBC_Voltage 270
#define Minimum_EBC_Voltage 205
#define Maxmium_EBC_OP_Voltage 116
#define EBC_Short_Ckt_Current  24
#define Reverse_Polarity_Detected      1//1
#define Reverse_Polarity_Not_Detected   0//0
#define Maximum_Input_Voltage  270
#define Minimum_Input_Voltage  202
#define Medium_Range_Bat_Current  33
#define Restricted_EBC_Current  22
#define Positive_Earth_Leakage   1//1
#define Positive_Earth_No_Detected 0//0
#define Negative_Earth_Leakage    1//1
#define Negative_Earth_No_Detected 0//0
#define  DS13070  0xD0
#define  DS13071  0xD1
#define pre_fixed_time  13
#define Maximum_Input_Voltage_Phase  540
#define Minimum_Input_Voltage_Phase  300

#include "i2c.h"
#include "spi.h"
#include "spieeprom.h"


int phase_B[110], phase_Y[110], phase_R[110];
int i;
int voltage, voltage1, voltage2;
int RBC_DCV, EBC_DCV, OP_Voltage;
int CT_1 = 0, CT_2, CT_3;
int flag_EBC_Voltage_Crossing=0;
int flag_fault=0;
int flag_scr_trip=0;
int flag_igbt_trip=0;
int counter_fault=1,counter_fault_EBC=1;
float I_B, I_Total;
int counter=1;

int flag_under_detected;
int flag_over_detected;
float Total_Current, Battery_Current;
int RBC_SP = 122, EBC_SP = 110;
int Battery_Current_SP=10;
int Battery_Current_SP_Enter=10;
int RBC_Enter_SP = 122;
int R_Y, Y_B, B_R;
int e,f;
int counter_ShortCkt=1;
unsigned char res[200];
int hours=12;
int hours_enter=13;
int minutes_enter=15;
int minutes=59;
unsigned char v[10];
unsigned long output[10];
unsigned long current[10];
unsigned long DC[10];
unsigned long current2[10];
unsigned long Power_Var[10];
unsigned long output1[10];
unsigned long v1[10];
unsigned char temp=0x26;
unsigned char time[100],time1[100],time2[100],time3[100],time5[100],time4[100],time6[100],date7[100],date8[100];
unsigned char date[100],date1[100],date2[100],date3[100],date5[100],date4[100],date6[100],time7[100],time8[100];
RTCTime result;
unsigned char year;
unsigned char month;
unsigned char day;
unsigned char weekday;
unsigned char hour;
unsigned char minute;
unsigned char seconds;
unsigned int txData[10];
unsigned int rxData[10];
int flag_over_voltage=0;
 
 int u=0;
int  s=0,g=0,h=0,d=0,w=0,r=0,o=0,z=0;


 
 
void My_Timer_ISR()
{
    init_ADC();

    for (i = 0; i < 110; i++) 
    {
        while (!IFS0bits.AD1IF);
        IFS0bits.AD1IF = 0;
        phase_B[i] = ADC1BUF0; // B-AN0
        phase_Y[i] = ADC1BUF1; // Y-AN1
        phase_R[i] = ADC1BUF2; // R-AN2
        RBC_DCV = ADC1BUF3; // RBC Capacitor voltage
        EBC_DCV = ADC1BUF4; // EBC Capacitor voltage
        //OP_Voltage = ADC1BUF5; // Output voltage
        CT_3 = ADC1BUF5; // spas pin
        CT_2 = ADC1BUF6; 
        CT_1 = ADC1BUF7; 
        OP_Voltage=ADC1BUF8;

        if (phase_B[i] >= phase_B[0])
        {
            phase_B[0] = phase_B[i];
        }


        if (phase_Y[i] >= phase_Y[0]) 
        {
            phase_Y[0] = phase_Y[i];
        }

        if (phase_R[i] >= phase_R[0])
        {
            phase_R[0] = phase_R[i];
        }

        voltage = (phase_B[0] - 2002) / (float) (5.091);
        voltage1 = (phase_Y[0] - 2009) / (float) (5.3008);
        voltage2 = (phase_R[0] - 2005) / (float) (5.3008);
        OP_Voltage = (OP_Voltage)*(0.041);
        I_Total = (CT_2 - 2104) / (4.90);
        I_B = ((CT_1 - 2125) / (5.114)) + 2.8; // Battery current
        R_Y = voltage + voltage1;
        Y_B = voltage1 + voltage2;
        B_R = voltage2 + voltage;

    }


}





// *****************************************************************************
// *****************************************************************************
// Configuration Bits
// *****************************************************************************
// *****************************************************************************

#if defined __C30__ || defined __XC16__
    #if defined(__PIC24FJ256GB110__)
        _CONFIG2(FNOSC_PRIPLL & POSCMOD_HS & PLL_96MHZ_ON & PLLDIV_DIV2 & IESO_OFF) // Primary HS OSC with PLL, USBPLL /2
        _CONFIG1(JTAGEN_OFF & FWDTEN_OFF & ICS_PGx2)   // JTAG off, watchdog timer off
    #elif defined(__PIC24FJ64GB004__)
        _CONFIG1(WDTPS_PS1 & FWPSA_PR32 & WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
        _CONFIG2(POSCMOD_HS & I2C1SEL_PRI & IOL1WAY_OFF & OSCIOFNC_ON & FCKSM_CSDCMD & FNOSC_PRIPLL & PLL96MHZ_ON & PLLDIV_DIV2 & IESO_OFF)
        _CONFIG3(WPFP_WPFP0 & SOSCSEL_SOSC & WUTSEL_LEG & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)
        _CONFIG4(DSWDTPS_DSWDTPS3 & DSWDTOSC_LPRC & RTCOSC_SOSC & DSBOREN_OFF & DSWDTEN_OFF)
    #elif defined(__PIC24FJ256GB106__)
        _CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & FWDTEN_OFF & ICS_PGx2) 
        _CONFIG2( PLL_96MHZ_ON & IESO_OFF & FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMOD_HS & FNOSC_PRIPLL & PLLDIV_DIV3 & IOL1WAY_ON)
    #elif defined(__PIC24FJ256DA210__) || defined(__PIC24FJ256GB210__)
        _CONFIG1(FWDTEN_OFF & ICS_PGx2 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
        _CONFIG2(POSCMOD_HS & IOL1WAY_ON & OSCIOFNC_ON & FCKSM_CSDCMD & FNOSC_PRIPLL & PLL96MHZ_ON & PLLDIV_DIV2 & IESO_OFF)
    #elif defined(__dsPIC33EP512MU810__)||defined(__PIC24EP512GU810__)
       // _FOSCSEL(FNOSC_FRC);
       // _FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
      //  _FWDT(FWDTEN_OFF);
    #elif defined(__PIC24FJ64GB502__)
        _CONFIG1(WDTPS_PS1 & FWPSA_PR32 & WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
	_CONFIG2(I2C1SEL_PRI & IOL1WAY_OFF & FCKSM_CSDCMD & FNOSC_PRIPLL & PLL96MHZ_ON & PLLDIV_DIV2 & IESO_OFF)
	_CONFIG3(WPFP_WPFP0 & SOSCSEL_SOSC & WUTSEL_LEG & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)
	_CONFIG4(DSWDTPS_DSWDTPS3 & DSWDTOSC_LPRC & RTCOSC_SOSC & DSBOREN_OFF & DSWDTEN_OFF)   
    #endif
#elif defined( __PIC32MX__ )
    #pragma config UPLLEN   = ON            // USB PLL Enabled
    #pragma config FPLLMUL  = MUL_15        // PLL Multiplier
    #pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider
    #pragma config FPLLIDIV = DIV_2         // PLL Input Divider
    #pragma config FPLLODIV = DIV_1         // PLL Output Divider
    #pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
    #pragma config FWDTEN   = OFF           // Watchdog Timer
    #pragma config WDTPS    = PS1           // Watchdog Timer Postscale
    //#pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
    #pragma config OSCIOFNC = OFF           // CLKO Enable
    #pragma config POSCMOD  = HS            // Primary Oscillator
    #pragma config IESO     = OFF           // Internal/External Switch-over
    #pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable (KLO was off)
    #pragma config FNOSC    = PRIPLL        // Oscillator Selection
    #pragma config CP       = OFF           // Code Protect
    #pragma config BWP      = OFF           // Boot Flash Write Protect
    #pragma config PWP      = OFF           // Program Flash Write Protect
    #pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
   
#else
    #error Cannot define configuration bits.
#endif

FSFILE *myFile;
BYTE myData[512];
size_t numBytes;
volatile BOOL deviceAttached;
unsigned char printBuffer[10];
unsigned char countchar;
char arr2[]="Date";
char arr3[]="Time(24:00:00 hr)";
char arr4[]="Brief Description";
char arr5[]="Fault Values";
char arr6[]="From";
char arr7[]="To";
char m[]=",";
char str[100];
char res1[300];
char res2[100];
char str1[100];

void main(void)
{
    SYSTEM_Initialize();
    LCD_Init();
    LCD_String_xy(1, 0, "INTRA INDUSTRIES ");
    LCD_String_xy(2, 0, "PVT LTD PUNE");

    TMR1_SetInterruptHandler(My_Timer_ISR);
    TMR1_Start();
    __delay_ms(500);
    LCD_Command(0x01);
    char buffer[10] ,buffer1[10];
    int p, j, l, n, m, a, x, y;
    float k_RBC = 34;
    float k_EBC=25;
    float power_RBC;
    float power_EBC;
    int flag_RBC = 1, flag_EBC = 1, flag_reached_RBC = 0, flag_reached_EBC = 0;
    int flag = 0;
    int flag_shut_down=0;
    int flag_shut_down_EBC=0;
    
     TRISDbits.TRISD13=1;            // DC_Coil
     TRISFbits.TRISF12=1;            // IGBT_TRIP
     TRISFbits.TRISF13=1;            // Rectifier_TRIP
    
     TRISDbits.TRISD8=0;             // CHRG_ON_LED
     TRISGbits.TRISG9=0;             // BUZZERI
     deviceAttached = FALSE;

    //Initialize the stack
    USBInitialize(0);
    
    /* Set RB5 as Digital port 
    and enable the VBUS switch*/
    ANSELBbits.ANSB5 = 0;
    TRISBbits.TRISB5 = 0;
    LATBbits.LATB5=1;
    TRISDbits.TRISD0=0;
    TRISDbits.TRISD1=0;
    int flag_detected_scr =1;
    int flag_detected_igbt=1;
    int flag_usb_scr=1;
    int k=20;
    
    I2CInit();
    DS1307_init();
        
    SPI2INTInit();
    EEPROMInit();
   //setRTCTime(21,3,28,7,10,30,00);
    __delay_ms(100);
   
   
    
    
    
    
    
    

    while(1)
    {
        result =  getRTCTime();
       
        
        
      
      
      
/*********** SWITCHES *********************************************************/      
      
        j = IO_RF5_GetValue();       // ENTER
        l = IO_RG13_GetValue();      // BACK
        n = IO_RA6_GetValue();       // UP
        p = IO_RA7_GetValue();       // DOWN
        
/*****************************************************************************/       
       
        m = M_RBC_FLT_GetValue();    // RD6-RBC IGBT FAULT
        a = M_EBC_FLT_GetValue();    // RD7-EBC IGBT FAULT
        x = IO_RD4_GetValue();       // Earth_Leakage1
        y = IO_RD5_GetValue();       // Earth_Leakage2
        
        __delay_ms(100);
        
        
        if (n == 0 && p == 1 && flag==2)        // UP button is pressed
        {
            RBC_SP++;
            
        }
        else if (n == 1 && p == 0 && flag==2)   // DOWN BUTTON IS pressed
        {
            RBC_SP--;
            
        }
        
/******************************************************************************/   
        
        
        /*Settable Battery current*/
        
        else if(n==0 && p==1 && flag==3)        // UP button is pressed
        {
           Battery_Current_SP++;
        }
        
        else if(n==1 && p==0 && flag==3)        // Down button is pressed
        {
            Battery_Current_SP--;
        }
        
        
        else if(n==0 && p==1 && flag==5)
        {
            minutes++;
            
        }
        
        else if(n==1 && p==0 && flag==5)
        {
            minutes--;
        }
        
/*******************************************************************************/
        /*RBC Output voltage limit*/
        
        if (RBC_SP > 135)                       // Over-voltage
        {
            RBC_SP = 135;
        }
        
        else if (RBC_SP < 110)                  // Under-voltage
         {
            RBC_SP = 110;
        }
        
/********************************************************************************/  
        
        /*Battery current limit*/
        
        if(Battery_Current_SP>14)              // Over-current
        {
            Battery_Current_SP=14;
        }
        else if(Battery_Current_SP<10)         // Under-current
        {
            Battery_Current_SP=10;
        }
        
/************************************************************************/               
        if(minutes>59)
        {
            minutes=0;
        }
        
        else if(minutes<0)
        {
            minutes=0;
        }
        /*Enter button is pressed*/
        
        if (j == 0 && flag==2) 
        {
            RBC_Enter_SP = RBC_SP;
        }
        
        else if(j==0 && flag==3)
        {
            Battery_Current_SP_Enter=Battery_Current_SP;
        }
        
        else if(j==0 && flag==5)
        {
            minutes_enter=minutes;
        }
        
        
/******************************************************************************/        
       
           /*Earth Leakage*/
        
        if(x==Positive_Earth_Leakage)
        {
            IO_RA14_SetHigh();          // Positive_Earth_Leakage                      
        }
        
             else
            {
                IO_RA14_SetLow();
            }
        
        
       if(y==Negative_Earth_Leakage)
        {
            IO_RA5_SetHigh();            // Negative_Earth_Leakage
        }
        
             else
            {
                IO_RA5_SetLow();
            }
        
        
       if(x==Positive_Earth_No_Detected && y==Negative_Earth_No_Detected)
        {
            IO_RA4_SetHigh();            // Both_Earth_Leakage          
        }
       else if(x==Positive_Earth_Leakage || y==Negative_Earth_Leakage)
        {
            IO_RA4_SetLow();
            
            EEPROMWriteByte(55,70+z);
            if(EEPROMReadByte(70+z)==55)
            {
                EEPROMWriteByte(result.hour,499+7*z);
                EEPROMWriteByte(result.minute,501+7*z);
                EEPROMWriteByte(result.second,502+7*z);
                EEPROMWriteByte(result.year,503+7*z);
                EEPROMWriteByte(result.month,504+7*z);
                EEPROMWriteByte(result.date,505+7*z); 
            }
            z++;
            if(z==7)
            {
                z=0;
            }
            
        }
        if(flag_over_voltage==1)
        {
            
            EEPROMWriteByte(56,54+r);
            if(EEPROMReadByte(56+r)==56)
                {
                 EEPROMWriteByte(result.hour,300+7*r);
                EEPROMWriteByte(result.minute,301+7*r);
                EEPROMWriteByte(result.second,302+7*r);
                EEPROMWriteByte(result.year,303+7*r);
                EEPROMWriteByte(result.month,304+7*r);
                EEPROMWriteByte(result.date,305+7*r);
                }
                
                r++;
                if(r==7)
                {
                    r=0;
                }
                flag_over_voltage=0;
        }
       
       
       
/*********************************************************************************/        
        
       
        /**** Detection of single phase***/
        
        if((voltage >=Maximum_Input_Voltage && voltage2>=Maximum_Input_Voltage ) || (voltage>=Maximum_Input_Voltage && voltage1>=Maximum_Input_Voltage) || (voltage1>=Maximum_Input_Voltage && voltage2>=Maximum_Input_Voltage))
        {
            IO_RA15_SetLow();
            
        }
        else   if((voltage <=Minimum_Input_Voltage && voltage2<=Minimum_Input_Voltage ) || (voltage<=Minimum_Input_Voltage && voltage1<=Minimum_Input_Voltage) || (voltage1<=Minimum_Input_Voltage && voltage2<=Minimum_Input_Voltage))
        {
            IO_RA15_SetHigh();
            EEPROMWriteByte(50,0x16+g);
            if(EEPROMReadByte(0x16+g)==50)
            {
                EEPROMWriteByte(result.hour,162+7*g);
                EEPROMWriteByte(result.minute,163+7*g);
                EEPROMWriteByte(result.second,164+7*g);
                EEPROMWriteByte(result.year,165+7*g);
                EEPROMWriteByte(result.month,166+7*g);
                EEPROMWriteByte(result.date,167+7*g); 
            }
            g++;
            if(g==7)
            {
                g=0;
            }
            
        }
    /****** Detection of over-voltage*******/    
       
        else if((voltage >=Maximum_Input_Voltage && voltage2>=Maximum_Input_Voltage ) || (voltage>=Maximum_Input_Voltage && voltage1>=Maximum_Input_Voltage) || (voltage1>=Maximum_Input_Voltage && voltage2>=Maximum_Input_Voltage))
        {
            IO_RA15_SetLow();
            
        }
        
        
        
        else
        {
            IO_RA15_SetLow();
        }
        
        
        
       
       /* else
        {
            IO_RA15_SetLow();
        }*/
        
        
        
/******************************************************************************/
        
        /*Set point increment and Decrement*/
        
       
        
/*******************************************************************************/        
       
        /* SCR and IGBT trip*/
       
        if(flag_scr_trip==1)
        {
            
            EEPROMWriteByte(49,0x08+s);
            
            if(EEPROMReadByte(0x08+s)==49)
            {
                EEPROMWriteByte(result.hour,401+7*s);
                EEPROMWriteByte(result.minute,402+7*s);
                EEPROMWriteByte(result.second,403+7*s);
                EEPROMWriteByte(result.year,404+7*s);
                EEPROMWriteByte(result.month,405+7*s);
                EEPROMWriteByte(result.date,406+7*s);
                
            }
            s++;
            if(s==7)
            {
                s=0;
            }
            flag_scr_trip=0;
        }
        
        
        
        if(flag_igbt_trip==1)

        {
            LATGbits.LATG9=1;              // Buzzer
            LCD_Command(0x01);
             __delay_ms(1);
            LCD_String_xy(1,0,"IGBT TRIP");
            __delay_ms(3);
            flag_igbt_trip=0;
            //flag_igbt_trip=0;
        }
        
        
        
        
       
       
/******************************************************************************/        
       
        /*Y-phase is absent*/
        
        if((voltage1==0)||(voltage1>=Maximum_Input_Voltage))
       {
            
           
           PWM_RBC_Shut_Down();
           PWM_EBC_Shut_Down();
           
          
       
           
           
           }
           
        
         if((voltage<=Minimum_Input_Voltage)||(voltage1<=Minimum_Input_Voltage )||(voltage2<=Minimum_Input_Voltage))
        {
           // LCD_Command(0x01);
            __delay_ms(1);
            LCD_String_xy(1,0,"Under Voltage");
            __delay_ms(3);
            
            
            EEPROMWriteByte(48,0x00+u);
            
            if(EEPROMReadByte(0x00+u)==48)
            {
                EEPROMWriteByte(result.hour,80+7*u);
                EEPROMWriteByte(result.minute,81+7*u);
                EEPROMWriteByte(result.second,82+7*u);
                EEPROMWriteByte(result.year,83+7*u);
                EEPROMWriteByte(result.month,84+7*u);
                EEPROMWriteByte(result.date,85+7*u);
                
            
              
                
                
            
            
          
                        
            }
           u++;
           
           if(u==7)
           {
               u=0;
           }
          
        }
        else if((voltage>=Maximum_Input_Voltage)||(voltage1>=Maximum_Input_Voltage)||(voltage2>=Maximum_Input_Voltage))
        {
            LCD_Command(0x01);
             __delay_ms(10);
            LCD_String_xy(1,0,"Over Voltage");
            __delay_ms(100);
            
            EEPROMWriteByte(51,30+h);
            if(EEPROMReadByte(30)==51)
            {
                EEPROMWriteByte(result.hour,450+7*h);
                EEPROMWriteByte(result.minute,451+7*h);
                EEPROMWriteByte(result.second,452+7*h);
                EEPROMWriteByte(result.year,453+7*h);
                EEPROMWriteByte(result.month,454+7*h);
                EEPROMWriteByte(result.date,455+7*h);
            }
           
            h++;
           
           if(h==7)
           {
               h=0;
           }
          
        }
       
       
/*********************************************************************************/        
       
        if( flag_over_detected==1)
        {
            LCD_Command(0x01);
            __delay_ms(1);
           LCD_String_xy(1,0,"Over_Voltage in Phase ");
           __delay_ms(3);
        }
        
        if(flag_under_detected==1)
        {
            LCD_Command(0x01);
            __delay_ms(1);
           LCD_String_xy(1,0,"Under_Voltage in Phase");
           __delay_ms(3);
           
                
        }
        
                            
        power_RBC = OP_Voltage*I_Total;
        power_EBC=OP_Voltage*I_Total;

        
        
/*******************************************************************************/        
                          
                      /*RBC MODE*/

        
if ((voltage >Minimum_Input_Voltage && voltage<Maximum_Input_Voltage)&&(voltage1 > Minimum_Input_Voltage &&  voltage1<Maximum_Input_Voltage)&&(voltage2 > Minimum_Input_Voltage && voltage2<Maximum_Input_Voltage)) 
{
            
    
            if(PORTDbits.RD13==Reverse_Polarity_Detected)
            {
                LCD_Command(0x01);
                __delay_ms(1);
                PWM_RBC_Shut_Down();
                LCD_String_xy(1,0,"Bat_Rev_Polarity");
                __delay_ms(3);
                //LATGbits.LATG9=1;
                
                EEPROMWriteByte(52,38+d);
                
                if(EEPROMReadByte(38+d)==52)
                {
                EEPROMWriteByte(result.hour,203+7*d);
                EEPROMWriteByte(result.minute,204+7*d);
                EEPROMWriteByte(result.second,205+7*d);
                EEPROMWriteByte(result.year,206+7*d);
                EEPROMWriteByte(result.month,207+7*d);
                EEPROMWriteByte(result.date,208+7*d);
                }
                d++;
                if(d==7)
                {
                    d=0;
                }
                //while(1);
            }
               
            
            PWM_EBC_Shut_Down();
            IO_RA2_SetLow();
            IO_RA15_SetLow();

/**************** Power sequence for RBC ****************************************/
            
            if (flag_RBC == 1) 
            {
               
                ALL_RELAY_OFF();
                __delay_us(10);
                RBC_POWER_SEQ();
                flag_RBC = 0;
            }
            
/******************************************************************************/           
            
            if((PORTFbits.RF12==0)&&(flag_scr_trip==0))
            {
               // LATGbits.LATG9=1;
                
                 
                PWM_RBC_Shut_Down();
                flag_scr_trip=1;
                
               
            }
            if((PORTFbits.RF13==0) &&(flag_igbt_trip==0))
            {
               /* LCD_Command(0x01);
                __delay_ms(100);*/
                 //LATGbits.LATG9=1;
               
                PWM_RBC_Shut_Down();
                 flag_igbt_trip=1;
               
            }
            
            if((m==RBC_Fault) && (counter_fault!=0))
            {
                if(counter_fault==1)
                {
                    if(m==RBC_Fault)
                    {
                        LCD_Command(0x01);
                        __delay_ms(10);
                        PWM_RBC_Shut_Down();
                         
                        LCD_String_xy(1,1,"Fault Detected");
                       // __delay_ms(10);
                        counter_fault++;
                    }
                    else
                    {
                        counter_fault=0;
                    }
                }
                else if(counter_fault==2)
                {
                    if(m==RBC_Fault)
                    {
                         LCD_Command(0x01);
                         __delay_ms(10);
                        PWM_RBC_Shut_Down();
                        
                        LCD_String_xy(1,1,"Fault Detected");
                        //__delay_ms(100);
                        counter_fault++;
                    }
                    else 
                    {
                        counter_fault==0;
                    }
                }
                else if(counter_fault==3)
                {
                    if(m==RBC_Fault)
                    {
                        LCD_Command(0x01);
                        __delay_ms(10);
                        LCD_String_xy(1,0,"Fault Detected");
                        PWM_RBC_Shut_Down();
                        LATGbits.LATG9=1;
                        while(1);
                    }
                    else
                    {
                        counter_fault=0;
                        
                    }
                }
                    }
                
            
            
            else if(m==RBC_NO_Fault)
            {
                                       
             if((PORTFbits.RF12==1)&&(PORTFbits.RF13==1))
            {
                                                                                                                         
            if((I_Total>=Short_Ckt_Current) && (counter_ShortCkt!=0) &&(flag_shut_down==0))
            {
                
                //PWM_RBC_Shut_Down();
                if( counter_ShortCkt==1)
                {
                    if(I_Total>=Short_Ckt_Current)
                    {
                        PWM_RBC_Shut_Down();
                        
                       // __delay_ms(1000);
                        counter_ShortCkt++;
                    }
                    else
                    {
                        counter_ShortCkt=0;
                    }
                }
                else if(counter_ShortCkt==2)
                {
                   if(I_Total>=Short_Ckt_Current)
                    {
                        PWM_RBC_Shut_Down();
                     //   __delay_ms(1000);
                        counter_ShortCkt++;
                    }
                    else
                    {
                        counter_ShortCkt=0;
                    } 
                }
                
                else if(counter_ShortCkt==3)
                {
                   if(I_Total>=Short_Ckt_Current)
                    {
                       PWM_RBC_Shut_Down();
                       
                       EEPROMWriteByte(53,46+w);
                    
                       EEPROMWriteByte(54,63+o);
                      
                       
                    if(EEPROMReadByte(46+w)==53)
            {
                EEPROMWriteByte(result.hour,252+7*w);
                EEPROMWriteByte(result.minute,253+7*w);
                EEPROMWriteByte(result.second,254+7*w);
                EEPROMWriteByte(result.year,255+7*w);
                EEPROMWriteByte(result.month,256+7*w);
                EEPROMWriteByte(result.date,257+7*w);
            }
                       
                        o++;
                       w++;
                       
                      if(w==7)
                    {
                        w=0;
                    }
                    if(o==7)
                    {
                        o=0;
                    }
                       flag_shut_down=1;
                       //break;
                        //__delay_ms(5000);
                       // break;
                    }
                    else
                    {
                        counter_ShortCkt=0;
                    } 
                }
            }
                
                if(flag_shut_down==1)
                {
                     LATGbits.LATG9=1;
                     LCD_Command(0x01);
                     __delay_ms(10);
                     LCD_String_xy(1,1,"Short circuit");
                    PWM_RBC_Shut_Down();
                    
                    
                   
                }
                                                                                   
        else if(I_Total<Short_Ckt_Current || (counter_ShortCkt==0))
            {
                                    
           PWM_RBC_MODE();
          /*if(I_Total>=39 && I_Total<=42)
           {
               __delay_ms(60000);
               k_RBC=k_RBC-1;
               PWM_Duty_Cycle_RBC(k_RBC);
               if(k_RBC>45)
               {
                   k_RBC=45;
                  
               }
               else if(k_RBC<8)
               {
                   k_RBC=8;
               }
                       
           }*/
           
          /* else if(I_Total>Maximum_RBC_Current)
           {
              k_RBC=k_RBC-0.5;
               PWM_Duty_Cycle_RBC(k_RBC);
               if(k_RBC>45)
               {
                   k_RBC=45;
                  
               }
               else if(k_RBC<8)
               {
                   k_RBC=8;
               }
               
           }*/

            // PWM_Duty_Cycle_RBC(10);

           
            
              if((R_Y >=Maximum_Input_Voltage_Phase) || (Y_B>=Maximum_Input_Voltage_Phase) || (B_R>=Maximum_Input_Voltage_Phase) &&(flag_over_detected==0))
            {
                
                   
                  PWM_RBC_Shut_Down();
                  
                  
                  flag_over_detected=1;
            }
              else if((R_Y <=Minimum_Input_Voltage_Phase) || (Y_B<=Minimum_Input_Voltage_Phase) || (B_R<=Minimum_Input_Voltage_Phase) && (flag_under_detected==0))
            {
                  
                PWM_RBC_Shut_Down();
               
                
                flag_under_detected=1;
                
            }
           
              
              /*else  if(result.hour==pre_fixed_time && result.minute>=(0) && result.minute<(minutes_enter))
        {
            PWM_RBC_Shut_Down();
            if(OP_Voltage<Minimum_OP_Voltage)
            {
                IO_RA3_SetHigh();
                
            }
            
            
            else
            {
                IO_RA3_SetLow();
            }
            
        }*/
              
           
           
              else if(I_B>=Maximum_Bat_Current)
              {
                 
                 
                  
                  k_RBC=k_RBC-0.5;
                   if (k_RBC > 45) 
                {
                    k_RBC = 45;
                } 
                else if (k_RBC < 8)
                {
                    k_RBC= 8;
                }

                PWM_Duty_Cycle_RBC(k_RBC);
                  
              }
           else if(I_B>=Medium_Range_Bat_Current && I_B<=Maximum_Bat_Current)
                  {
                      
                      
                      if(k_RBC>45)
                      {
                          k_RBC=45;
                      }
                      else if(k_RBC<8)
                      {
                          k_RBC=8;
                      }
                      
                      PWM_Duty_Cycle_RBC(k_RBC);
                  }
            else if (I_Total>=Maximum_RBC_Current) 
            {
                k_RBC =k_RBC - 0.5;
                if (k_RBC > 45) 
                {
                    k_RBC = 45;
                } 
                else if (k_RBC < 8)
                {
                    k_RBC= 8;
                }

                PWM_Duty_Cycle_RBC(k_RBC);


            }
            else if((I_B>=Minimum_Settable_Bat_Current) && (I_B<=15) && (flag==4))
            {
             if(Battery_Current_SP_Enter>I_B)
            {
                k_RBC=k_RBC+0.5;
                if(k_RBC>45)
                {
                    k_RBC=45;
                }
                else if(k_RBC<8)
                {
                    k_RBC=8;
                }
                PWM_Duty_Cycle_RBC(k_RBC);
            }
             
             else if(Battery_Current_SP_Enter<I_B)
             {
                 k_RBC=k_RBC-0.5;
                 if(k_RBC>45)
                {
                   k_RBC=45;
                }
                else if(k_RBC<8)
                {
                    k_RBC=8;
                }
                PWM_Duty_Cycle_RBC(k_RBC);
            }
                 
             }
            
           
            else if (RBC_Enter_SP > OP_Voltage) 
            {
                k_RBC = k_RBC + 0.5;

                if (k_RBC > 45) 
                {
                    k_RBC = 45;
                } 
                else if (k_RBC < 8) 
                {
                    k_RBC = 8;
                }

                PWM_Duty_Cycle_RBC(k_RBC);

            }
            
            
            else if((OP_Voltage>=Maximum_OP_Voltage) &&(flag_over_voltage==0))
            {
                __delay_ms(2000);
                 LATGbits.LATG9=1;
                PWM_RBC_Shut_Down();
                EEPROMWriteByte(56,54+r);
                flag_over_voltage=1;
                
                //while(1);
            }
            

            else if (RBC_Enter_SP < OP_Voltage) 
            {
                k_RBC = k_RBC - 0.5;
                if (k_RBC > 45) 
                {
                    k_RBC = 45;
                }
                else if (k_RBC < 8) 
                {
                    k_RBC = 8;
                }
                PWM_Duty_Cycle_RBC(k_RBC);
            }
            else if (RBC_Enter_SP == OP_Voltage)
            {
                if (k_RBC > 45)
                {
                    k_RBC = 45;
                } 
                else if (k_RBC < 8) 
                {
                    k_RBC = 8;
                }
                PWM_Duty_Cycle_RBC(k_RBC);
            }

        }
             }
             }

            flag_EBC = 1;
        }
        
/*********************END RBC MODE**********************************************/       
           
                     /*EBC MODE*/

else 
        {
                         
            PWM_RBC_Shut_Down();
            if(PORTDbits.RD13==Reverse_Polarity_Detected)
            {
                LCD_Command(0x01);
                PWM_EBC_Shut_Down();
                LATGbits.LATG9=1;
                LCD_String_xy(1,1,"Reverse Polarity Detected");
              //  while(1);
            }

            /*Power sequence for EBC*/
            if (flag_EBC == 1) {
                ALL_RELAY_OFF();
                __delay_us(10);
                EBC_POWER_SEQ();
                flag_EBC = 0;

            }
            IO_RA2_SetHigh(); // SP_LED
            
            if((PORTFbits.RF12==0))
            {
                PWM_EBC_Shut_Down();
            }
            if(PORTFbits.RF13==0)
            {
                PWM_EBC_Shut_Down();
            }
            
            
            
            
        
             if((a==EBC_Fault) && (counter_fault_EBC!=0))
            {
                
                if(counter_fault_EBC==1)
                {
                    if(a==EBC_Fault)
                    {
                        PWM_EBC_Shut_Down();
                       // __delay_ms(10);
                        counter_fault_EBC++;
                    }
                    else
                    {
                        counter_fault_EBC=0;
                    }
                }
                else if(counter_fault_EBC==2)
                {
                    if(a==EBC_Fault)
                    {
                        PWM_EBC_Shut_Down();
                        //__delay_ms(100);
                        counter_fault_EBC++;
                    }
                    else 
                    {
                        counter_fault_EBC==0;
                    }
                }
                else if(counter_fault_EBC==3)
                {
                    if(a==EBC_Fault)
                    {
                        PWM_EBC_Shut_Down();
                        while(1);
                    }
                    else
                    {
                        LCD_Command(0x01);
                        LCD_String_xy(1,1,"Fault Detected");
                        counter_fault_EBC=0;
                        
                    }
                }
                    }
            
             else if((a==EBC_NO_Fault))
            {
             if((PORTFbits.RF12==1)&&(PORTFbits.RF13==1))
            {
                             
             // IO_RA15_SetHigh();
                     
            PWM_EBC_MODE();
           // PWM_Duty_Cycle_EBC(10);


           if((I_Total>=EBC_Short_Ckt_Current) && (counter_ShortCkt!=0) &&(flag_shut_down_EBC==0))
            {
                
                //PWM_RBC_Shut_Down();
                if( counter_ShortCkt==1)
                {
                    if(I_Total>=EBC_Short_Ckt_Current)
                    {
                        PWM_EBC_Shut_Down();
                        
                        __delay_ms(1000);
                        counter_ShortCkt++;
                    }
                    else
                    {
                        counter_ShortCkt=0;
                    }
                }
                else if(counter_ShortCkt==2)
                {
                   if(I_Total>=EBC_Short_Ckt_Current)
                    {
                        PWM_EBC_Shut_Down();
                        __delay_ms(1000);
                        counter_ShortCkt++;
                    }
                    else
                    {
                        counter_ShortCkt=0;
                    } 
                }
                
                else if(counter_ShortCkt==3)
                {
                   if(I_Total>=EBC_Short_Ckt_Current)
                    {
                       PWM_EBC_Shut_Down();
                       flag_shut_down_EBC=1;
                       //break;
                        //__delay_ms(5000);
                       // break;
                    }
                    else
                    {
                        counter_ShortCkt=0;
                    } 
                }
            }
                
                if(flag_shut_down_EBC==1)
                {
                    PWM_EBC_Shut_Down();
                   
                }
           
            else if((I_Total<EBC_Short_Ckt_Current) || (counter_ShortCkt==0))
            {

            if(I_Total>=Restricted_EBC_Current)
            {
                k_EBC=k_EBC-0.5;
                if(k_EBC>40)
                {
                    k_EBC=40;
                }
                else if(k_EBC<7)
                {
                    k_EBC=7;
                }
                PWM_Duty_Cycle_EBC(k_EBC);
            }
            
            
            else if(voltage1>=Maximum_EBC_Voltage)
            {
                //IO_RA2_SetLow();
                IO_RA2_SetLow();
               // IO_RA15_SetLow();
                PWM_EBC_Shut_Down();
            }
            else if(voltage1<=Minimum_EBC_Voltage)
            {
                IO_RA2_SetLow();
                //IO_RA15_SetLow();
                PWM_EBC_Shut_Down();
            }
            
            
            
            else if((OP_Voltage>=Maxmium_EBC_OP_Voltage)&& (counter!=0) &&(flag_EBC_Voltage_Crossing==0))
            { 
                if(counter==1)
                {
                    if(OP_Voltage>=Maxmium_EBC_OP_Voltage)
                    {
                        PWM_EBC_Shut_Down();
                        __delay_ms(1000);
                        counter++;
                        
                    }
                    else
                    {
                        counter=0;
                    }
                }
                else if(counter==2)
                {
                   if(OP_Voltage>=Maxmium_EBC_OP_Voltage)
                    {
                        PWM_EBC_Shut_Down();
                        __delay_ms(1000);
                        counter++;
                        
                    }
                    else
                    {
                        counter=0;
                    } 
                }
                else if(counter==3)
                {
                   if(OP_Voltage>=Maxmium_EBC_OP_Voltage)
                    {
                        PWM_EBC_Shut_Down();
                        flag_EBC_Voltage_Crossing=1;
                        
                    }
                    else
                    {
                        counter=0;
                    } 
                } 
            }
                
               // PWM_EBC_Shut_Down();
            
            else if(flag_EBC_Voltage_Crossing==1)
            {
                PWM_EBC_Shut_Down();
            }
                       
            else if ((EBC_SP > OP_Voltage)||(OP_Voltage<=105)) 
            {
                    k_EBC = k_EBC + 0.5;
                    
                    if (k_EBC > 40) 
                    {
                        k_EBC = 40;
                    } 
                    else if ( k_EBC < 7) 
                    {
                         k_EBC = 7;
                    }
                    
                        PWM_Duty_Cycle_EBC( k_EBC);
                    }
                
                else if (EBC_SP < OP_Voltage) 
                {
                     k_EBC =  k_EBC - 0.5;
                    if ( k_EBC > 40) 
                    {
                         k_EBC = 40;
                    } 
                    else if ( k_EBC< 7) 
                      {
                         k_EBC = 7;
                    }
                    PWM_Duty_Cycle_EBC( k_EBC);
                }
                else if (EBC_SP == OP_Voltage)
                {
                    if (k_EBC > 40) 
                    {
                        k_EBC = 40;
                    } 
                    else if ( k_EBC < 7)
                    {
                         k_EBC = 7;
                    }
                    PWM_Duty_Cycle_EBC( k_EBC);
                }
            }
                       
             }
             }

           
            flag_RBC = 1;

        }

/**************************END EBC MODE*****************************************/
        

         if (l == 0) // BACK button is pressed
        {
            flag = flag + 1;
            if (flag >= 6) 
            {
                flag = 0;
            }
        }
        if (flag == 1) 
        {
            LCD_Command(0x01);
            __delay_ms(1);
            //LCD_String_xy(1,0,"Input_voltage:");

            // LCD_String_xy(1,0,"CT2:");
            sprintf(current, "%.1f", I_B);
            LCD_String_xy(1, 0, current);


            

            //LCD_String_xy(1,11,"DC:");
            sprintf(DC, "%.1f", k_RBC);
            LCD_String_xy(2, 11, DC);

            //LCD_String_xy(2,0,"CT2:");
            sprintf(current2, "%.1f",I_Total);
            LCD_String_xy(2, 0, current2);

            sprintf(output, "%d", OP_Voltage);
            LCD_String_xy(1, 11, output);

            

            __delay_ms(3);
        }
        
        if (flag == 2) 
        {

            LCD_Command(0x01);
            __delay_ms(1);
            LCD_String_xy(1, 1, "RBC_SP:");
            sprintf(v, "%d", RBC_SP);
            LCD_String_xy(1, 10, v);


            LCD_String_xy(2, 1, "OP_VOLTAGE:");
            sprintf(output, "%d", OP_Voltage);
            LCD_String_xy(2, 12, output);

            __delay_ms(3);

        }

        if (flag == 0)
        {
            LCD_Command(0x01);
            __delay_ms(1);


            LCD_String_xy(1, 0, "PH_B=");
            sprintf(data, "%d", voltage); // Displaying phase B
            LCD_String_xy(1, 5, data);


            LCD_String_xy(1, 9, "P_Y=");
            sprintf(data1, "%d", voltage1); // Displaying phase Y
            LCD_String_xy(1, 13, data1);


            LCD_String_xy(2, 0, "PH_R=");
            sprintf(data2, "%d", voltage2); // Displaying phase R
            LCD_String_xy(2, 5, data2);
            __delay_ms(3);
        }

        
        
        if(flag==3)
        {
            LCD_Command(0x01);
            __delay_ms(1);
            LCD_String_xy(1,1,"I_Bat_SP:");
            sprintf(v1,"%d",Battery_Current_SP);
            LCD_String_xy(1,12,v1);
            
            LCD_String_xy(2, 1, "I_Bat:");
            sprintf(output1, "%.1f",I_B);
            LCD_String_xy(2, 12, output1);
            
            __delay_ms(3);

    }
        
       
        
        
        if(flag==5)
        {
            LCD_Command(0x01);
            __delay_ms(1);
            LCD_String_xy(1,0,"RTC OFF TIME:");
            sprintf(buffer,"%d",hours);
            LCD_String_xy(1,13,buffer);
            LCD_String_xy(2,0,"RTC Mins:");
            sprintf(buffer,"%d",minutes);
            LCD_String_xy(2,11,buffer);
            __delay_ms(30);
            
        }
        
        
        if(flag==4)
        {
            
            LCD_Command(0x01);
            __delay_ms(1);
            
           sprintf(current, "%.1f", I_B);
           LCD_String_xy(1, 0, current);


           

            //LCD_String_xy(1,11,"DC:");
            sprintf(DC, "%.1f", k_EBC);
            LCD_String_xy(1, 11, DC);

            //LCD_String_xy(2,0,"CT2:");
            sprintf(current2, "%.1f", I_Total);
            LCD_String_xy(2, 0, current2);

            sprintf(output, "%d", OP_Voltage);
            LCD_String_xy(1, 11, output);

            

            __delay_ms(3);
            
           
        }
        
       

        
       



  
       
    

       
        
        
        

        //if thumbdrive is plugged in
       USBTasks();
        
        if(USBHostMSDSCSIMediaDetect())
        {
            deviceAttached = TRUE;
            
            //counter_eeprom=0;
            //counter_eeprom_1=0;
            LCD_Command(0x01);
            
             if(FSInit())
            {
                
                //Opening a file in mode "w" will create the file if it  doesn't
                //  exist.  If the file does exist it will delete the old file
                //  and create a new one that is blank.
                myFile = FSfopen("Faults3.csv","w+");
                LCD_String_xy(1,1,"USB Writing");
                
                if(EEPROMReadByte(0x00)==48)
                {
                    
                    sprintf(buffer,"%d",EEPROMReadByte(83));
                    strcat(date,buffer);
                    strcat(date,"/");
            
                    sprintf(buffer,"%d",EEPROMReadByte(84));
                    strcat(date,buffer);
                    strcat(date,"/");
            
            
                    sprintf(buffer,"%d",EEPROMReadByte(85));
                    strcat(date,buffer);
                    
                    
                    sprintf(buffer,"%d",EEPROMReadByte(80));
                    strcat(time,buffer);
                    strcat(time,":");
            
                    sprintf(buffer,"%d",EEPROMReadByte(81));
                    strcat(time,buffer);
                    strcat(time,":");
            
            
                    sprintf(buffer,"%d",EEPROMReadByte(82));
                    strcat(time,buffer);
                    
                    
                    sprintf(res1,"%s,%s,%s,%s",date,time,"Under Voltage ","Voltage is less in one of the Phase");
                    FSfwrite(res1,360,1,myFile);
                    EEPROMWriteByte(0,0x00);
                    EEPROMWriteByte(0,80);
                    EEPROMWriteByte(0,81);
                    EEPROMWriteByte(0,82);
                    EEPROMWriteByte(0,83);
                    EEPROMWriteByte(0,84);
                    EEPROMWriteByte(0,85);
                }
                
                 if(EEPROMReadByte(0x01)==48)
                {
                     
                     
                    
                    
                    sprintf(buffer,"%d",EEPROMReadByte(87));
                    strcat(time1,buffer);
                    strcat(time1,":");
            
                    sprintf(buffer,"%d",EEPROMReadByte(88));
                    strcat(time1,buffer);
                    strcat(time1,":");
            
            
                    sprintf(buffer,"%d",EEPROMReadByte(89));
                    strcat(time1,buffer);
                    
                    
                    
                    sprintf(buffer,"%d",EEPROMReadByte(90));
                    strcat(date1,buffer);
                    strcat(date1,"/");
            
                    sprintf(buffer,"%d",EEPROMReadByte(91));
                    strcat(date1,buffer);
                    strcat(date1,"/");
            
            
                    sprintf(buffer,"%d",EEPROMReadByte(92));
                    strcat(date1,buffer);
                    
                    
                     
                    
                     
                     
                    sprintf(res1,"\n %s,%s,%s,%s",date1,time1,"Under Voltage","Voltage is less in one of the Phase");
                    FSfwrite(res1,360,1,myFile);
                    EEPROMWriteByte(0,0x01);
                    EEPROMWriteByte(0,87);
                    EEPROMWriteByte(0,88);
                    EEPROMWriteByte(0,89);
                    EEPROMWriteByte(0,90);
                    EEPROMWriteByte(0,91);
                    EEPROMWriteByte(0,92);
                }
                
               
                
                
                
                 if(EEPROMReadByte(0x08)==49)
                {
                    
                     
                    sprintf(buffer,"%d",EEPROMReadByte(401));
                    strcat(time2,buffer);
                    strcat(time2,":");
            
                    sprintf(buffer,"%d",EEPROMReadByte(402));
                    strcat(time2,buffer);
                    strcat(time2,":");
            
            
                    sprintf(buffer,"%d",EEPROMReadByte(403));
                    strcat(time2,buffer);
                    
                    
                    
                    sprintf(buffer,"%d",EEPROMReadByte(404));
                    strcat(date2,buffer);
                    strcat(date2,"/");
            
                    sprintf(buffer,"%d",EEPROMReadByte(405));
                    strcat(date2,buffer);
                    strcat(date2,"/");
            
            
                    sprintf(buffer,"%d",EEPROMReadByte(406));
                    strcat(date2,buffer);
                     
                    sprintf(res1,"\n %s,%s, %s,%s",date2,time2,"Ovr Temperature","Over Temperature ");
                    FSfwrite(res1,250,1,myFile);
                    EEPROMWriteByte(0,0x08);
                    
                   
                    
                }
                
                
                if(EEPROMReadByte(0x09)==49)
                {
                    
                     sprintf(buffer,"%d",EEPROMReadByte(408));
                    strcat(time3,buffer);
                    strcat(time3,":");
            
                    sprintf(buffer,"%d",EEPROMReadByte(409));
                    strcat(time3,buffer);
                    strcat(time3,":");
            
            
                    sprintf(buffer,"%d",EEPROMReadByte(410));
                    strcat(time3,buffer);
                    
                    
                    
                    sprintf(buffer,"%d",EEPROMReadByte(411));
                    strcat(date3,buffer);
                    strcat(date3,"/");
            
                    sprintf(buffer,"%d",EEPROMReadByte(412));
                    strcat(date3,buffer);
                    strcat(date3,"/");
            
            
                    sprintf(buffer,"%d",EEPROMReadByte(413));
                    strcat(date3,buffer);
                    
                    sprintf(res1,"\n %s,%s ,%s,%s",date3,time3,"Ovr Temperature","Over Temperature ");
                    FSfwrite(res1,250,1,myFile);
                    EEPROMWriteByte(0,0x09);
                }
                
                
                 
                
                 if(EEPROMReadByte(0x16)==50)
                {
                     
                     
                     sprintf(buffer,"%d",EEPROMReadByte(162));
                    strcat(time4,buffer);
                    strcat(time4,":");
            
                    sprintf(buffer,"%d",EEPROMReadByte(163));
                    strcat(time4,buffer);
                    strcat(time4,":");
            
            
                    sprintf(buffer,"%d",EEPROMReadByte(164));
                    strcat(time4,buffer);
                    
                    
                    
                    sprintf(buffer,"%d",EEPROMReadByte(165));
                    strcat(date4,buffer);
                    strcat(date4,"/");
            
                    sprintf(buffer,"%d",EEPROMReadByte(166));
                    strcat(date4,buffer);
                    strcat(date4,"/");
            
            
                    sprintf(buffer,"%d",EEPROMReadByte(167));
                    strcat(date4,buffer);
                    
                    sprintf(res1,"\n %s, %s, %s,%s",date4,time4,"Single Phasing Present","Two Phase absent");
                    FSfwrite(res1,360,1,myFile);
                    EEPROMWriteByte(0,0x16);
                }
                
                  if(EEPROMReadByte(0x17)==50)
                {
                      
                    sprintf(buffer,"%d",EEPROMReadByte(169));
                    strcat(time5,buffer);
                    strcat(time5,":");
            
                    sprintf(buffer,"%d",EEPROMReadByte(170));
                    strcat(time5,buffer);
                    strcat(time5,":");
            
            
                    sprintf(buffer,"%d",EEPROMReadByte(171));
                    strcat(time5,buffer);
                    
                    
                    
                    sprintf(buffer,"%d",EEPROMReadByte(172));
                    strcat(date5,buffer);
                    strcat(date5,"/");
            
                    sprintf(buffer,"%d",EEPROMReadByte(173));
                    strcat(date5,buffer);
                    strcat(date5,"/");
            
            
                    sprintf(buffer,"%d",EEPROMReadByte(174));
                    strcat(date5,buffer);
                    
                    sprintf(res1,"\n %s,%s,%s,%s",date5,time5,"Single Phasing Present","Two Phase absent and only one phase present");
                    FSfwrite(res1,360,1,myFile);
                    EEPROMWriteByte(0,0x17);
                }
                
               
                
                if(EEPROMReadByte(54)==56)
                {
                    
                     sprintf(buffer,"%d",EEPROMReadByte(300));
                    strcat(time6,buffer);
                    strcat(time6,":");
            
                    sprintf(buffer,"%d",EEPROMReadByte(301));
                    strcat(time6,buffer);
                    strcat(time6,":");
            
            
                    sprintf(buffer,"%d",EEPROMReadByte(302));
                    strcat(time6,buffer);
                    
                    
                    
                    sprintf(buffer,"%d",EEPROMReadByte(303));
                    strcat(date6,buffer);
                    strcat(date6,"/");
            
                    sprintf(buffer,"%d",EEPROMReadByte(304));
                    strcat(date6,buffer);
                    strcat(date6,"/");
            
            
                    sprintf(buffer,"%d",EEPROMReadByte(305));
                    strcat(date6,buffer);
                    
                    sprintf(res1,"\n %s,%s,%s,%s",date6,time6,"Over Voltage","Maximum output voltage");
                    FSfwrite(res1,320,1,myFile);
                    EEPROMWriteByte(0,54);
                }
                
                if(EEPROMReadByte(55)==56)
                {
                    sprintf(res1,"\n %s,%s","Over Voltage","Voltage is greater than 480");
                    FSfwrite(res1,35,1,myFile);
                    EEPROMWriteByte(0,55);
                }
                
                
                
                
                if(EEPROMReadByte(38)==51)
                {
                    sprintf(res1,"\n %s,%s","Reverse Polarity","Battery not connected in proper way");
                    FSfwrite(res1,35,1,myFile);
                    EEPROMWriteByte(0,38);
                }
                if(EEPROMReadByte(39)==51)
                {
                    sprintf(res1,"\n %s,%s","Reverse Polarity","Battery not connected in proper way");
                    FSfwrite(res1,20,1,myFile);
                    EEPROMWriteByte(0,39);
                }
               
                if(EEPROMReadByte(46)==54)
                {
                    
                    sprintf(buffer,"%d",EEPROMReadByte(240));
                    strcat(time7,buffer);
                    strcat(time7,":");
            
                    sprintf(buffer,"%d",EEPROMReadByte(241));
                    strcat(time7,buffer);
                    strcat(time7,":");
            
            
                    sprintf(buffer,"%d",EEPROMReadByte(242));
                    strcat(time7,buffer);
                    
                    
                    
                    sprintf(buffer,"%d",EEPROMReadByte(243));
                    strcat(date7,buffer);
                    strcat(date7,"/");
            
                    sprintf(buffer,"%d",EEPROMReadByte(244));
                    strcat(date7,buffer);
                    strcat(date7,"/");
            
            
                    sprintf(buffer,"%d",EEPROMReadByte(245));
                    strcat(date7,buffer);
                    
                   sprintf(res1,"\n%s,%s,%s,%s",date7,time7,"Short circuit","Current is more than 42 Amp");
                    FSfwrite(res1,360,1,myFile);
                    EEPROMWriteByte(0,46);
                }
                
                if(EEPROMReadByte(48)==54)
                {
                    sprintf(res1,"\n%s,%s","Short circuit","Current is more than 42 Amp");
                    FSfwrite(res1,20,1,myFile);
                    EEPROMWriteByte(0,47);
                }
                
                
                
                if(EEPROMReadByte(63)==53)
                {
                    
                     sprintf(buffer,"%d",EEPROMReadByte(252));
                    strcat(time8,buffer);
                    strcat(time8,":");
            
                    sprintf(buffer,"%d",EEPROMReadByte(253));
                    strcat(time8,buffer);
                    strcat(time8,":");
            
            
                    sprintf(buffer,"%d",EEPROMReadByte(254));
                    strcat(time8,buffer);
                    
                    
                    
                    sprintf(buffer,"%d",EEPROMReadByte(255));
                    strcat(date8,buffer);
                    strcat(date8,"/");
            
                    sprintf(buffer,"%d",EEPROMReadByte(256));
                    strcat(date8,buffer);
                    strcat(date8,"/");
            
            
                    sprintf(buffer,"%d",EEPROMReadByte(257));
                    strcat(date8,buffer);
                    
                    sprintf(res1,"\n %s,%s,%s,%s",date8,time8,"Over Current","Current greater than 35");
                    FSfwrite(res1,20,1,myFile);
                    EEPROMWriteByte(0,63);
                }
                if(EEPROMReadByte(64)==58)
                {
                    sprintf(res1,"\n%s","Over Current");
                    FSfwrite(res1,20,1,myFile);
                    EEPROMWriteByte(0,64);
                }
                
                
              
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                LCD_String_xy(1,1,"USB Done");
                    
                
                   
                    
                    
               
                
                
                
                
                
                
                
                
               
                
               
                
                
                
              
               
               
               FSfclose(myFile);

                //Just sit here until the device is removed.
                while(deviceAttached == TRUE)
                {
                    USBTasks();
                }
                
            }
        }
      
                //Just sit here until the device is removed.
                
            
            
            
        }
}

    
    
    
 

   
  
        
        
       

        

         
         /*Set point increment and Decrement*/
        
        
  


/****************************************************************************
  Function:
    BOOL USB_ApplicationEventHandler( BYTE address, USB_EVENT event,
                void *data, DWORD size )

  Summary:
    This is the application event handler.  It is called when the stack has
    an event that needs to be handled by the application layer rather than
    by the client driver.

  Description:
    This is the application event handler.  It is called when the stack has
    an event that needs to be handled by the application layer rather than
    by the client driver.  If the application is able to handle the event, it
    returns TRUE.  Otherwise, it returns FALSE.

  Precondition:
    None

  Parameters:
    BYTE address    - Address of device where event occurred
    USB_EVENT event - Identifies the event that occured
    void *data      - Pointer to event-specific data
    DWORD size      - Size of the event-specific data

  Return Values:
    TRUE    - The event was handled
    FALSE   - The event was not handled

  Remarks:
    The application may also implement an event handling routine if it
    requires knowledge of events.  To do so, it must implement a routine that
    matches this function signature and define the USB_HOST_APP_EVENT_HANDLER
    macro as the name of that function.
  ***************************************************************************/

BOOL USB_ApplicationEventHandler( BYTE address, USB_EVENT event, void *data, DWORD size )
{
    switch( event )
    {
        case EVENT_VBUS_REQUEST_POWER:
            // The data pointer points to a byte that represents the amount of power
            // requested in mA, divided by two.  If the device wants too much power,
            // we reject it.
            return TRUE;

        case EVENT_VBUS_RELEASE_POWER:
            // Turn off Vbus power.
            // The PIC24F with the Explorer 16 cannot turn off Vbus through software.

            //This means that the device was removed
            deviceAttached = FALSE;
            return TRUE;
            break;

        case EVENT_HUB_ATTACH:
            return TRUE;
            break;

        case EVENT_UNSUPPORTED_DEVICE:
            return TRUE;
            break;

        case EVENT_CANNOT_ENUMERATE:
            //UART2PrintString( "\r\n***** USB Error - cannot enumerate device *****\r\n" );
            return TRUE;
            break;

        case EVENT_CLIENT_INIT_ERROR:
            //UART2PrintString( "\r\n***** USB Error - client driver initialization error *****\r\n" );
            return TRUE;
            break;

        case EVENT_OUT_OF_MEMORY:
            //UART2PrintString( "\r\n***** USB Error - out of heap memory *****\r\n" );
            return TRUE;
            break;

        case EVENT_UNSPECIFIED_ERROR:   // This should never be generated.
            //UART2PrintString( "\r\n***** USB Error - unspecified *****\r\n" );
            return TRUE;
            break;

        default:
            break;
    }

    return FALSE;
}
