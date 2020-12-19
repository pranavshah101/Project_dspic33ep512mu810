
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/pin_manager.h"
#include  <xc.h>
#include <libpic30.h>
#include "lcd.h"
#include "function.h"


int phase_B[110],phase_Y[110],phase_R[110];
int i;
float voltage_B,voltage_Y,voltage_R;
int CT_1,CT_2,CT_3;
int RBC_DCV,EBC_DCV,BAT_OP_DCV;



void My_Timer_ISR()
{
    init_ADC();                   
      
    for(i=0;i<110;i++)
    {
      while(!IFS0bits.AD1IF);      // Wait for all 4 conversion to complete
      IFS0bits.AD1IF=0;            // clear conversion done status bit
      phase_B[i]=ADC1BUF0;         // B-AN0
      phase_Y[i]=ADC1BUF1;         // Y-AN1
      phase_R[i]=ADC1BUF2;         // R-AN2
                           
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
         
      voltage_B  = (phase_B[0]-2361)/(float)(4.89);
      voltage_Y = (phase_Y[0]-2359)/(float)(4.53);
      voltage_R = (phase_R[0]-2355)/(float)(4.52);
        
                
    }
    
   
}

void My_Timer_ISR_1()
{
    init_ADC();
   while(!IFS0bits.AD1IF);
   IFS0bits.AD1IF=0;
   BAT_OP_DCV=ADC1BUF5;
   CT_1=ADC1BUF6;
   CT_2=ADC1BUF7;
   
   LCD_Command(0x01);
   __delay_ms(200);
   
   
   sprintf(data3,"%d",BAT_OP_DCV);
  
   LCD_String_xy(1,0,data3);
   
   sprintf(data4,"%d",CT_1);
   LCD_String_xy(1,8,data4);
   
   sprintf(data5,"%d",CT_2);
   LCD_String_xy(2,0,data5);
   
  
   
    
}
    
         
int main(void)
{
    
   SYSTEM_Initialize();
   LCD_Init();    
   LCD_String_xy(0,1,"INTRA INDUSTRIES");
   LCD_String_xy(2,1,"PVT LTD PUNE");
  
   TMR1_SetInterruptHandler(My_Timer_ISR);   // Registers a user defined function as the ISR for Timer1
   TMR1_Start();                             // Starts the operation of Timer1
   TMR3_SetInterruptHandler(My_Timer_ISR_1);
   TMR3_Start();
  
   __delay_ms(250);
   
   int p,j,k=10,l,n,m,a;
   int flag_RBC=1,flag_EBC=1;
    
   while(1)
   { 
    
         
    j=IO_RF5_GetValue();     // ENTER BUTTON
    l=IO_RG13_GetValue();    // BACK BUTTON
    n=IO_RA6_GetValue();     // UP  BUTTON
    p=IO_RA7_GetValue();     // DOWN BUTTON
    m=M_RBC_FLT_GetValue();  // RD6-RBC IGBT FAULT
    a=M_EBC_FLT_GetValue();  // EBC IGBT FAULT
    
         
    
 
            
      if((voltage_B>170)&&(voltage_Y>170)&&(voltage_R>170))
    {
        IO_RA15_SetLow();                   // SP_LED OFF
        PWM_EBC_Shut_Down();
        if(flag_RBC==1)
        {
            ALL_RELAY_OFF(); 
            __delay_us(10);
            RBC_POWER_SEQ();
            flag_RBC=0;
            
           
        }
         
            
      PWM_RBC_MODE();
      
      if(m==RBC_NO_Fault)          // No fault detected
      {
                      
      if(j==0&&l==1)               // ENTER PRESSED FOR DECREMENT
      {
        k = k+1;                   // Increment by 1% 
            if(k>=51)
            {
                k=50;
            }
            PWM_Duty_Cycle_RBC(k); 
            __delay_us(200)
    }
     
      else if(j==1&&l==0)               // BACK PRESSED FOR DECREMENT
    {
        
        k = k-1;                      // Decrement by 1%
            if(k<=10)
            {
                k=10;
            }
            PWM_Duty_Cycle_RBC(k); 
            __delay_us(200)
    }
    
    else if(j==1&l==1)                // Nothing is pressed 
    {
       
        PWM_Duty_Cycle_RBC(k);        // To hold duty cycle
        
    }
      }
      else if(m==RBC_Fault)                 // Fault detected
      {
          PWM_RBC_Shut_Down();
      }
             
      flag_EBC=1;
      
     
    }
    
      // EBC MODE
  
   else 
   {
          
       
       IO_RA15_SetHigh();                  // SP_LED ON
       PWM_RBC_Shut_Down();
       
       if(flag_EBC==1)                     // EBC power sequence
       {
           ALL_RELAY_OFF();
           EBC_POWER_SEQ();
           flag_EBC=0;
           
       }
       
       PWM_EBC_MODE();
       
       if(a==EBC_Fault)                   // No fault detected
      {
               
      if(j==0&&l==1)                        // ENTER BUTTON IS PRESSED FOR INCREMENT
    {
        k = k+1;                            // Increment by 1% 
            if(k>=51)
            {
                k=50;
            }
            PWM_Duty_Cycle_EBC(k); 
            __delay_us(5000)
    }
     
    else if(j==1&&l==0)                      // BACK PRESSED FOR DECREMENT
    {
        
        k = k-1;                             // Decrement by 1%
            if(k<=10)
            {
                k=10;
            }
            PWM_Duty_Cycle_EBC(k); 
            __delay_us(5000)
    }
    
    else if(j==1&l==1)                      // Nothing is pressed 
    {
        
        PWM_Duty_Cycle_EBC(k);             // To hold duty cycle
        
        
        
    }
      }
      else if(a==EBC_NO_Fault)                    // Fault detected
      {
          PWM_EBC_Shut_Down();
      }
      
      
      flag_RBC=1;
      
}
    
     
      
    
     
}    
       
}
