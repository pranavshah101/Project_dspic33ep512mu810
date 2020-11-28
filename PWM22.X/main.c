
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/pin_manager.h"
#include  <xc.h>
#include <libpic30.h>

#include "lcd.h"
#include "function.h"

int phase_a[110],phase_b[110],phase_c[110];
int i;
unsigned char flag_rbc=1;
unsigned char flag_ebc=1;
float voltage,voltage1,voltage2;

void My_Timer_ISR_1()
{
    init_ADC();              // For single channel
      
    for(i=0;i<100;i++)
    {
      while(!IFS0bits.AD1IF);
      IFS0bits.AD1IF=0;
      phase_a[i]=ADC1BUF0;          // B-AN0
      phase_b[i]=ADC1BUF1;         // Y-AN1
      phase_c[i]=ADC1BUF2;         // R-AN2
      
     
      
      
      if(phase_a[i]>phase_a[0] || phase_b[i]>phase_b[0] || phase_c[i]>phase_c[0] )
      {
          
       phase_a[0]=phase_a[i];
       phase_b[0]=phase_b[i];
       phase_c[0]=phase_c[i];
       
      }
         
      voltage = (phase_a[0]-2361)/(float)(4.55);
      voltage1 = (phase_b[0]-2359)/(float)(4.55);
      voltage2 = (phase_c[0]-2355)/(float)(4.55);
      
      sprintf(data,"%d",phase_a[0]);        // Displaying phase B
      //strcat(data,"=V_B");
      LCD_String_xy(0,1,data);
      
      sprintf(data1,"%d",phase_b[0]);        // Displaying phase Y
      //strcat(data1,"=V_Y");
      LCD_String_xy(0,8,data1);
     
      sprintf(data2,"%d",phase_c[0]);        // Displaying phase R
      //strcat(data2,"=V_R");
      LCD_String_xy(2,1,data2);
         
      __delay_ms(30);
            
    }
   
}
    
         
int main(void)
{
    
   SYSTEM_Initialize();
   LCD_Init();      
   TMR1_SetInterruptHandler(My_Timer_ISR_1);   
   TMR1_Start();
   
   int p,j,k=5,l,n,m,a;
   
   while(1)
   { 
    
    j=IO_RF5_GetValue();     // ENTER
    l=IO_RG13_GetValue();    // BACK
    n=IO_RA6_GetValue();     // Switch for scrolling display //UP
    p=IO_RA7_GetValue();     // Another switch for scrolling display//DOWN
    m=M_RBC_FLT_GetValue();  // RD6-RBC IGBT FAULT
    a=M_EBC_FLT_GetValue();  //RD7-EBC-IGBT FAULT 
    
    if((phase_a[0]>3340 && phase_a[0]<3400)   && (phase_b[0]>3340 && phase_b[0]<3400) && (phase_c[0]>3340 && phase_c[0]<3400))  // 3 phases are present
    {
        
       
        PWM_EBC_Shut_Down();
        
        
        if(flag_rbc==1)
        {
           
            relay_off();
            power_rbc_seq();
            
        }
        
        
      
      PWM_RBC_MODE();
      
      if(m==0)               //No fault detected
      {
          
      
      if(j==0&&l==1)   //ENTER PRESSED FOR DECREMENT
    {
        k = k+1;                   // Increment by 5% 
            if(k>=51)
            {
                k=50;
            }
            PWM_Duty_Cycle_RBC(k); 
            __delay_us(200)
    }
     
    else if(j==1&&l==0)     //BACK PRESSED FOR DECREMENT
    {
        
        k = k-1;                      // Decrement by 5%
            if(k<=5)
            {
                k=6;
            }
            PWM_Duty_Cycle_RBC(k); 
            __delay_us(200)
    }
    
    else if(j==1&l==1)  //Nothing is pressed 
    {
       // PWM_RBC_MODE();
        PWM_Duty_Cycle_RBC(k);
        //__delay_us(200);
    }
      }
      else if(m==1)                         // RBC Fault detected
      {
          PWM_RBC_Shut_Down();
      }
          
      flag_rbc=0;
      flag_ebc=1;
    }
    
   else if((phase_a[0]>2350 && phase_a[0]<2362 ) || (phase_b[0]>2350 && phase_b[0]<2362) || (phase_c[0]>2350 && phase_c[0]<2362))
   {
       PWM_RBC_Shut_Down();
       
       
       
       if(flag_ebc==1)
       {
           relay_off();
           power_ebc_seq();
       }
      PWM_EBC_MODE();
       if(a==0)               //No fault detected
      {
          
      
      if(j==0&&l==1)   //ENTER PRESSED FOR DECREMENT
    {
        k = k+1;                   // Increment by 5% 
            if(k>=51)
            {
                k=50;
            }
            PWM_Duty_Cycle_EBC(k); 
            __delay_us(200)
    }
     
    else if(j==1&&l==0)     //BACK PRESSED FOR DECREMENT
    {
        
        k = k-1;                      // Decrement by 5%
            if(k<=5)
            {
                k=6;
            }
            PWM_Duty_Cycle_EBC(k); 
            __delay_us(200)
    }
    
    else if(j==1&l==1)  //Nothing is pressed 
    {
       // PWM_RBC_MODE();
        PWM_Duty_Cycle_EBC(k);
        //__delay_us(200);
    }
      }
      else if(a==1)                         //Fault detected
      {
          PWM_EBC_Shut_Down();
      }
      
      flag_ebc=0;
      flag_rbc=1;
       
 
    
    
    
    
    
 
}

}

   
        

}