
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/pin_manager.h"
#include  <xc.h>
#include <libpic30.h>
#include "lcd.h"
#include "function.h"

int phase_B[110],phase_Y[110],phase_R[110];
int i;
float voltage,voltage1,voltage2;


void My_Timer_ISR()
{
    init_ADC();                   // For single channel
      
    for(i=0;i<110;i++)
    {
      while(!IFS0bits.AD1IF);
      IFS0bits.AD1IF=0;
      phase_B[i]=ADC1BUF0;         //  B-AN0
      phase_Y[i]=ADC1BUF1;         //  Y-AN1
      phase_R[i]=ADC1BUF2;         //  R-AN2
                           
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
         
      voltage  = (phase_B[0]-2361)/(float)(4.89);
      voltage1 = (phase_Y[0]-2359)/(float)(4.53);
      voltage2 = (phase_R[0]-2355)/(float)(4.52);
                
    }
   
     /* sprintf(data,"%.1f",voltage);        // Displaying phase B
      strcat(data,"V=B");
      LCD_String_xy(0,1,data);
      
      sprintf(data1,"%.1f",voltage1);        // Displaying phase Y
      strcat(data1,"V=Y");
      LCD_String_xy(0,9,data1);
     
      sprintf(data2,"%.1f",voltage2);        // Displaying phase R
      strcat(data2,"V=R");
      LCD_String_xy(2,1,data2);
      __delay_us(1);*/
}
    
         
int main(void)
{
    
   SYSTEM_Initialize();
   LCD_Init();  
   
   TMR1_SetInterruptHandler(My_Timer_ISR);   
   TMR1_Start();
   __delay_ms(500);
   int p,j,k=5,l,n,m,a;
   int flag_RBC=1,flag_EBC=1;
    
   while(1)
   { 
    
    j=IO_RF5_GetValue();     // ENTER
    l=IO_RG13_GetValue();    // BACK
    n=IO_RA6_GetValue();     // Switch for scrolling display //UP
    p=IO_RA7_GetValue();     // Another switch for scrolling display//DOWN
    m=M_RBC_FLT_GetValue();  // RD6-RBC IGBT FAULT
    a=M_EBC_FLT_GetValue();  // EBC IGBT FAULT
    
      sprintf(data,"%.1f",voltage);        // Displaying phase B
      strcat(data,"V=B");
      LCD_String_xy(0,1,data);
      
      sprintf(data1,"%.1f",voltage1);        // Displaying phase Y
      strcat(data1,"V=Y");
      LCD_String_xy(0,9,data1);
     
      sprintf(data2,"%.1f",voltage2);        // Displaying phase R
      strcat(data2,"V=R");
      LCD_String_xy(2,1,data2);
      __delay_ms(50);
    
    
    
      /*sprintf(data,"%d",phase_B[0]);         // Displaying phase B
       strcat(data,"=B");
      LCD_String_xy(0,1,data);
      
      sprintf(data1,"%d",phase_Y[0]);        // Displaying phase Y
      strcat(data1,"=Y");
      LCD_String_xy(0,9,data1);
     
      sprintf(data2,"%d",phase_R[0]);        // Displaying phase R
      strcat(data2,"=R");
      LCD_String_xy(2,1,data2);
      __delay_ms(5);*/
    
       
      /*sprintf(data,"%.1f",voltage);        // Displaying phase B
       strcat(data,"V=B");
      LCD_String_xy(0,1,data);
      
      sprintf(data1,"%.1f",voltage1);        // Displaying phase Y
      strcat(data1,"V=Y");
      LCD_String_xy(0,9,data1);
     
      sprintf(data2,"%.1f",voltage2);        // Displaying phase R
      strcat(data2,"V=R");
      LCD_String_xy(2,1,data2);
      __delay_us(1);*/
    

    //For RBC MODE
   // if((phase_Y[0]>3000) &&( phase_R[0]>3000 )&& (phase_B[0]>3000)) 
      if((voltage>170)&&(voltage1>170)&&(voltage2>170))
    {
        IO_RA15_SetLow();
        PWM_EBC_Shut_Down();
        if(flag_RBC==1)
        {
            ALL_RELAY_OFF(); 
            __delay_us(10);
            RBC_POWER_SEQ();
            flag_RBC=0;
            
           
        }
            
      PWM_RBC_MODE();
      
      if(m==0)                    // No fault detected
      {
          
      
      if(j==0&&l==1)               // ENTER PRESSED FOR DECREMENT
      {
        k = k+1;                   // Increment by 5% 
            if(k>=51)
            {
                k=50;
            }
            PWM_Duty_Cycle_RBC(k); 
            __delay_us(200)
    }
     
    else if(j==1&&l==0)               // BACK PRESSED FOR DECREMENT
    {
        
        k = k-1;                      // Decrement by 5%
            if(k<=5)
            {
                k=6;
            }
            PWM_Duty_Cycle_RBC(k); 
            __delay_us(200)
    }
    
    else if(j==1&l==1)             // Nothing is pressed 
    {
       // PWM_RBC_MODE();
        PWM_Duty_Cycle_RBC(k);
        //__delay_us(200);
    }
      }
      else if(m==1)                 // Fault detected
      {
          PWM_RBC_Shut_Down();
      }
          
      flag_RBC=0;  
      
      flag_EBC=1;
    }
    
      /*EBC MODE*/
  // else if((phase_B[0]>2350) || (phase_Y[0]>2350) || (phase_R[0]>2350 ))
    else 
   {
       IO_RA15_SetHigh();    // SP_LED
       PWM_RBC_Shut_Down();
       
       if(flag_EBC==1)
       {
           ALL_RELAY_OFF();
           //LED_OFF();
           //LED_EBC_SEQ();
           EBC_POWER_SEQ();
           flag_EBC=0;
           //LED_OFF();
       }
       
       PWM_EBC_MODE();
       
       if(a==0)                   // No fault detected
      {
               
      if(j==0&&l==1)               // ENTER PRESSED FOR INCREMENT
    {
        k = k+1;                   // Increment by 5% 
            if(k>=51)
            {
                k=50;
            }
            PWM_Duty_Cycle_EBC(k); 
            __delay_us(200)
    }
     
    else if(j==1&&l==0)              // BACK PRESSED FOR DECREMENT
    {
        
        k = k-1;                      // Decrement by 5%
            if(k<=5)
            {
                k=6;
            }
            PWM_Duty_Cycle_EBC(k); 
            __delay_us(200)
    }
    
    else if(j==1&l==1)                 // Nothing is pressed 
    {
       // PWM_RBC_MODE();
        PWM_Duty_Cycle_EBC(k);
        //__delay_us(200);
    }
      }
      else if(a==1)                    // Fault detected
      {
          PWM_EBC_Shut_Down();
      }
      
      flag_EBC=0;
      flag_RBC=1;
      
}
     
}    
       
}
