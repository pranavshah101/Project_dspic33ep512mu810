
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/pin_manager.h"
#include  <xc.h>
#include <libpic30.h>
#include "lcd.h"
#include "function.h"
#define RBC_NO_Fault   1
#define RBC_Fault      0
#define EBC_NO_Fault   0      
#define EBC_Fault      1

int phase_B[110],phase_Y[110],phase_R[110];
int i;
int voltage,voltage1,voltage2;
int RBC_DCV,EBC_DCV,BAT_OP_DCV;
int CT_1=0,CT_2,CT_3;
float I_B,I_Total;
float Total_Current,Battery_Current;
int input_voltage=115;
float res;
unsigned char v[10];
unsigned long output[10];
unsigned long current[10];
unsigned long DC[10];
unsigned long current2[10];
void My_Timer_ISR()
{
    init_ADC();                   
      
    for(i=0;i<110;i++)
    {
      while(!IFS0bits.AD1IF);
      IFS0bits.AD1IF=0;
      phase_B[i]=ADC1BUF0;         //  B-AN0
      phase_Y[i]=ADC1BUF1;         //  Y-AN1
      phase_R[i]=ADC1BUF2;         //  R-AN2
      RBC_DCV=ADC1BUF3;            // RBC Capacitor voltage
      EBC_DCV=ADC1BUF4;            // EBC Capacitor voltage
      BAT_OP_DCV=ADC1BUF5;         // Output voltage
      CT_3=ADC1BUF6;               // spare pin
      CT_2=ADC1BUF7;               // Battery current
      CT_1=ADC1BUF8;              // Total current
                           
       if(phase_B[i]>=phase_B[0])
       {
           phase_B[0]=phase_B[i];
       }
       
      
      if(phase_Y[i]>=phase_Y[0])
       {
           phase_Y[0]=phase_Y[i];
       }
      
      if(phase_R[i]>=phase_R[0])
       {
           phase_R[0]=phase_R[i];
       }
         
      voltage  = (phase_B[0]-2001)/(float)(4.547);
      voltage1 = (phase_Y[0]-2008)/(float)(4.487);
      voltage2 = (phase_R[0]-2004)/(float)(4.57);
      BAT_OP_DCV = (BAT_OP_DCV)*(0.041);
      I_Total = (CT_2-2104)/(5.0571);
       I_B = (CT_1-2125)/(5.114);            // Battery current
      
                
    }
   
   
}
    
         
int main(void)
{
    
   SYSTEM_Initialize();
   LCD_Init(); 
   LCD_String_xy(1,0,"INTRA INDUSTRIES ");
   LCD_String_xy(2,0,"PVT LTD PUNE");
   
   TMR1_SetInterruptHandler(My_Timer_ISR);   
   TMR1_Start();
   __delay_ms(500);
   LCD_Command(0x01);
    
   int p,j,k=8,l,n,m,a;
   int flag_RBC=1,flag_EBC=1;
   int flag=0;
   while(1)
   { 
    
    j=IO_RF5_GetValue();     // ENTER
    l=IO_RG13_GetValue();    // BACK
    n=IO_RA6_GetValue();     // UP
    p=IO_RA7_GetValue();     // DOWN
    m=M_RBC_FLT_GetValue();  // RD6-RBC IGBT FAULT
    a=M_EBC_FLT_GetValue();  // RD7-EBC IGBT FAULT
    
    __delay_ms(100);
  
         /*RBC MODE*/
    if((voltage>170)&&(voltage1>170)&&(voltage2>170))
    {
        IO_RA15_SetLow();
        PWM_EBC_Shut_Down();
        
        /*Power sequence for RBC*/
        if(flag_RBC==1)
        {
            ALL_RELAY_OFF(); 
            __delay_us(10);
            RBC_POWER_SEQ();
            flag_RBC=0;
            
           
        }
         
            
      PWM_RBC_MODE();
      
      if(m==RBC_NO_Fault)                    // No fault detected
      {
          PWM_Duty_Cycle_RBC(k);
      }
              
      
     
    
   
      
      else if(m==RBC_Fault)                 // Fault detected
      {
          PWM_RBC_Shut_Down();
      }
             
      flag_EBC=1;
    }
    
      /*EBC MODE*/

   else 
   {
       IO_RA15_SetHigh();                   // SP_LED
       PWM_RBC_Shut_Down();
       
       /*Power sequence for EBC*/
       if(flag_EBC==1)
       {
           ALL_RELAY_OFF();
           __delay_us(10);
           EBC_POWER_SEQ();
           flag_EBC=0;
           
       }
       
       PWM_EBC_MODE();
       
       if(a==EBC_NO_Fault)                   // No fault detected
      {
             PWM_Duty_Cycle_EBC(k);
       }
               
     
    
    
   
      
      else if(a==EBC_Fault)                    // Fault detected
      {
          PWM_EBC_Shut_Down();
      }
         
       flag_RBC=1;
      
}
    if(l==0)         // BACK button is pressed
    {
        flag=flag+1;
        if(flag>=2)
        {
            flag=0;
        }
    }
    if(flag==1)
    {
        LCD_Command(0x01);
        __delay_ms(50);
        LCD_String_xy(1,0,"CT1:");
        sprintf(current,"%.1f",I_B);
        LCD_String_xy(1,5,current);
        
        LCD_String_xy(1,11,"DC:");
        sprintf(DC,"%d",k);
        LCD_String_xy(1,14,DC);
        
        LCD_String_xy(2,0,"CT2:");
        sprintf(current2,"%.1f",I_Total);
        LCD_String_xy(2,4,current2);
        
         __delay_ms(100);
    }
    if(flag==0)
    {
        
     LCD_Command(0x01);
     __delay_ms(10);    
    LCD_String_xy(1,1,"Enter SP:");
    sprintf(v,"%d",input_voltage);
    LCD_String_xy(1,10,v);  
    if(n==0 && p==1) //UP button is pressed
    {
        input_voltage++;
    }
    else if(n==1 && p==0) //dOWN BUTTON IS pressed
    {
        input_voltage--;
    }
    
    if(input_voltage>135)
    {
        input_voltage=135;
    }
    else if(input_voltage<110)
    {
        input_voltage=110;
    }
    res=(input_voltage/I_Total);
    
    if(j==0)                       // ENTER button is pressed
    {
        k=-0.57455*res+0.84689*(input_voltage)-63.84955;
    } 
        if(k>40)
        {
            k=40;
        }
        else if(k<8)
        {
            k=8;
        }
    
    LCD_String_xy(2,1,"BAT_OP:");
    sprintf(output,"%d",BAT_OP_DCV);
    LCD_String_xy(2,9,output);
    __delay_ms(100);
     
    }
            
}    
       
}
