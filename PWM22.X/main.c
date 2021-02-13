
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
int RBC_DCV,EBC_DCV,OP_Voltage;
int CT_1=0,CT_2,CT_3;
float I_B,I_Total;
float Total_Current,Battery_Current;
int RBC_SP=122,EBC_SP=110;
int RBC_Enter_SP=122;
int R_Y,Y_B,B_R;

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
      phase_B[i]=ADC1BUF0;         // B-AN0
      phase_Y[i]=ADC1BUF1;         // Y-AN1
      phase_R[i]=ADC1BUF2;         // R-AN2
      RBC_DCV=ADC1BUF3;            // RBC Capacitor voltage
      EBC_DCV=ADC1BUF4;            // EBC Capacitor voltage
      OP_Voltage=ADC1BUF5;         // Output voltage
      CT_3=ADC1BUF6;               // spare pin
      CT_2=ADC1BUF7;               // Battery current
      CT_1=ADC1BUF8;               // Total current
                           
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
         
      voltage  = (phase_B[0]-2002)/(float)(5.6641);
      voltage1 = (phase_Y[0]-2009)/(float)(5.4358);
      voltage2 = (phase_R[0]-2005)/(float)(5.4297);
      OP_Voltage = (OP_Voltage)*(0.041);
      I_Total = (CT_2-2104)/(5.0571);
       I_B = (CT_1-2125)/(5.114);            // Battery current
       R_Y=voltage+voltage1;
       Y_B=voltage1+voltage2;
       B_R=voltage2+voltage;
      
                
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
   int flag_RBC=1,flag_EBC=1,flag_reached_RBC=0,flag_reached_EBC=0,s=8;
   int flag=0;
   while(1)
   { 
   
    /*IO_RA4_SetHigh();   //Both earth leakage
    IO_RA5_SetHigh();  //Negative earth leakage
    IO_RA2_SetHigh();    //Emergency led
   
    IO_RA14_SetHigh();   //positive earth leakage*/
   // IO_RA15_SetHigh();    //SP Led
    
    j=IO_RF5_GetValue();     // ENTER
    l=IO_RG13_GetValue();    // BACK
    n=IO_RA6_GetValue();     // UP
    p=IO_RA7_GetValue();     // DOWN
    m=M_RBC_FLT_GetValue();  // RD6-RBC IGBT FAULT
    a=M_EBC_FLT_GetValue();  // RD7-EBC IGBT FAULT
    
    __delay_ms(100);
    
    if(n==0 && p==1)                // UP button is pressed
    {
        RBC_SP++;
    }
    else if(n==1 && p==0)           // DOWN BUTTON IS pressed
    {
        RBC_SP--;
    }
    
    /*Output voltage limit*/
    if(RBC_SP>135)
    {
        RBC_SP=135;
    }
    else if(RBC_SP<110)
    {
        RBC_SP=110;
    }
    
    /*Enter button is pressed*/
    if(j==0)                    
    {
        RBC_Enter_SP=RBC_SP;
    }
    if((voltage>170)&&(voltage1>170)&&(voltage2>170))
    {
        IO_RA15_SetLow();    //SP LED LOW
          //Charging led 
        //IO_RA3_SetHigh();   //Battery not healthy
        
        PWM_EBC_Shut_Down();
        
        /*Power sequence for RBC*/
        if(flag_RBC==1)
        {
            ALL_RELAY_OFF(); 
            __delay_us(10);
            RBC_POWER_SEQ();
            flag_RBC=0;
            
           
        }
        
        
         
       IO_RD8_SetHigh();     
      PWM_RBC_MODE();
      
      if(m==RBC_NO_Fault)                    // No fault detected
      {
          if((R_Y>=480)||(Y_B>=480)||(B_R>=480))                  // Fault detected
      {
           
          PWM_RBC_Shut_Down();
      }
          else if((R_Y<=300)||(Y_B<=300)||(B_R<=300))
          {
              PWM_RBC_Shut_Down();
          }
      
          else if(RBC_Enter_SP>OP_Voltage)
          {
              k=k+1;
                                     
              if(k>40)
              {
                  k=40;
              }
              else if(k<8)
              {
                  k=8;
              }
              
              PWM_Duty_Cycle_RBC(k);
              
          }
          
                  
          else if(RBC_Enter_SP<OP_Voltage)
          {
              k=k-1;
              if(k>40)
              {
                  k=40;
              }
              else if(k<8)
              {
                  k=8;
              }
              PWM_Duty_Cycle_RBC(k);
          }
          
          else if(RBC_Enter_SP==OP_Voltage)
          {
               if(k>40)
              {
                  k=40;
              }
              else if(k<8)
              {
                  k=8;
              }
              PWM_Duty_Cycle_RBC(k);
          }
     
    
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
       
                       
       
       PWM_RBC_Shut_Down();
       
       /*Power sequence for EBC*/
       if(flag_EBC==1)
       {
           ALL_RELAY_OFF();
           __delay_us(10);
           EBC_POWER_SEQ();
           flag_EBC=0;
           
       }
       IO_RA15_SetHigh();    // SP_LED
       IO_RD8_SetLow();     
       PWM_EBC_MODE();
       
       
       
       if(a==EBC_NO_Fault)                   // No fault detected
      {
           
            if((R_Y>=480)||(Y_B>=480)||(B_R>=480))                  // Fault detected
             {
              PWM_EBC_Shut_Down();
             }
            
          /* else if((R_Y<=300)||(Y_B<=300)||(B_R<=300))
            {
              PWM_EBC_Shut_Down();
            }*/
            
           else if(EBC_SP>OP_Voltage)
           {
           k=k+1;
           flag_reached_EBC=1;
           s=k;
              if(k>40)
              {
                  k=40;
              }
              else if(k<8)
              {
                  k=8;
              }
              if(flag_reached_EBC==1)
              {
                  PWM_Duty_Cycle_EBC(k);
              }
          }
           
       else if(EBC_SP<OP_Voltage)
          {
              k=k-1;
              if(k>40)
              {
                  k=40;
              }
              else if(k<8)
              {
                  k=8;
              }
              PWM_Duty_Cycle_EBC(k);
          }
          
          else if(EBC_SP==OP_Voltage)
          {
               if(k>40)
              {
                  k=40;
              }
              else if(k<8)
              {
                  k=8;
              }
              PWM_Duty_Cycle_EBC(k);
          }
       
       }
               
                        
      
      else if(a==EBC_Fault)                    // Fault detected
      {
          PWM_EBC_Shut_Down();
      }
         
       flag_RBC=1;
      
}
    
    
   
  
         /*RBC MODE*/
  
    if(l==0)             // BACK button is pressed
    {
        flag=flag+1;
        if(flag>=5)
        {
            flag=0;
        }
    }
    if(flag==2)
    {
        LCD_Command(0x01);
        __delay_ms(10);
        //LCD_String_xy(1,0,"Input_voltage:");
        
         LCD_String_xy(1,0,"CT2:");
        sprintf(current,"%.1f",I_B);
        LCD_String_xy(1,4,current);
                    
        LCD_String_xy(1,11,"DC:");
        sprintf(DC,"%d",k);
        LCD_String_xy(1,14,DC);
        
        LCD_String_xy(2,0,"CT2:");
        sprintf(current2,"%.1f",I_Total);
        LCD_String_xy(2,4,current2);
        
         __delay_ms(100);
    }
    if(flag==1)
    {
        
     LCD_Command(0x01);
     __delay_ms(10);    
    LCD_String_xy(1,1,"RBC_SP:");
    sprintf(v,"%d",RBC_SP);
    LCD_String_xy(1,10,v);  
    
    
    LCD_String_xy(2,1,"OP_VOLTAGE:");
    sprintf(output,"%d",OP_Voltage);
    LCD_String_xy(2,12,output);
    
    __delay_ms(100);
     
    }
    
    if(flag==0)
    {
        LCD_Command(0x01);
       __delay_ms(10);
       
       
      LCD_String_xy(1,0,"PH_B=");
      sprintf(data,"%d",voltage);          // Displaying phase B
      LCD_String_xy(1,5,data);
      
      
      LCD_String_xy(1,9,"P_Y=");
      sprintf(data1,"%d",voltage1);        // Displaying phase Y
      LCD_String_xy(1,13,data1);
     
      
      LCD_String_xy(2,0,"PH_R=");
      sprintf(data2,"%d",voltage2);        // Displaying phase R
      LCD_String_xy(2,5,data2);
      __delay_ms(100);  
    }
    
    if(flag==4)
    {
        LCD_Command(0x01);
     __delay_ms(10);    
    LCD_String_xy(1,1,"EBC_SP:");
    sprintf(v,"%d",EBC_SP);
    LCD_String_xy(1,10,v);  
    
    
    LCD_String_xy(2,1,"OP_VOLTAGE:");
    sprintf(output,"%d",OP_Voltage);
    LCD_String_xy(2,12,output);
    
    __delay_ms(100);
    }
            
}    
       
}
