
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/pin_manager.h"
#include  <xc.h>
#include <libpic30.h>
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
#define Reverse_Polarity_Detected      1 //0
#define Reverse_Polarity_Not_Detected   0  //1
#define Maximum_Input_Voltage  270
#define Minimum_Input_Voltage  202
#define CHRG_ON_LED   _LATD8
#define Medium_Range_Bat_Current  33
#define Restricted_EBC_Current  22
#define Positive_Earth_Leakage   1
#define Positive_Earth_No_Detected 0
#define Negative_Earth_Leakage    1
#define Negative_Earth_No_Detected 0

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
int flag_over_detected_voltage=1;
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
float res;
unsigned char v[10];
unsigned long output[10];
unsigned long current[10];
unsigned long DC[10];
unsigned long current2[10];
unsigned long Power_Var[10];
unsigned long output1[10];
unsigned long v1[10];

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
        CT_3 = ADC1BUF5; // spare pin
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
        I_Total = (CT_2 - 2104) / (5.200);
        I_B = ((CT_1 - 2125) / (5.114)) + 2; // Battery current
        R_Y = voltage + voltage1;
        Y_B = voltage1 + voltage2;
        B_R = voltage2 + voltage;

    }


}

int main(void) 
{

    SYSTEM_Initialize();
    LCD_Init();
    LCD_String_xy(1, 0, "INTRA INDUSTRIES ");
    LCD_String_xy(2, 0, "PVT LTD PUNE");

    TMR1_SetInterruptHandler(My_Timer_ISR);
    TMR1_Start();
    __delay_ms(500);
    LCD_Command(0x01);

    int p, j, l, n, m, a, x, y;
    float k_RBC = 34;
    float k_EBC=25;
    float power_RBC;
    float power_EBC;
    int flag_RBC = 1, flag_EBC = 1, flag_reached_RBC = 0, flag_reached_EBC = 0, s = 8;
    int flag = 0;
    int flag_shut_down=0;
     int flag_shut_down_EBC=0;
     TRISDbits.TRISD13=1;            // DC_Coil
     TRISFbits.TRISF12=1;            // IGBT_TRIP
     TRISFbits.TRISF13=1;            // Rectifier_TRIP
    
     TRISDbits.TRISD8=0;             // CHRG_ON_LED
     TRISGbits.TRISG9=0;             // BUZZER
     
    while (1) 
    {
        IO_RD8_SetHigh();
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
        
        else if(n==0 && p==1 && flag==5)        // UP button is pressed
        {
           Battery_Current_SP++;
        }
        
        else if(n==1 && p==0 && flag==5)        // Down button is pressed
        {
            Battery_Current_SP--;
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
        
        /*Enter button is pressed*/
        
        if (j == 0 && flag==2) 
        {
            RBC_Enter_SP = RBC_SP;
        }
        
        else if(j==0 && flag==5)
        {
            Battery_Current_SP_Enter=Battery_Current_SP;
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
            
        }
       
/*********************************************************************************/        
        
       
        /**** Detection of single phase***/
        
        if((voltage >=Maximum_Input_Voltage && voltage2>=Maximum_Input_Voltage ) || (voltage>=Maximum_Input_Voltage && voltage1>=Maximum_Input_Voltage) || (voltage1>=Maximum_Input_Voltage && voltage2>=Maximum_Input_Voltage))
        {
            IO_RA15_SetLow();
            //PWM_EBC_Shut_Down();
        }
        else   if((voltage <=Minimum_Input_Voltage && voltage2<=Minimum_Input_Voltage ) || (voltage<=Minimum_Input_Voltage && voltage1<=Minimum_Input_Voltage) || (voltage1<=Minimum_Input_Voltage && voltage2<=Minimum_Input_Voltage))
        {
            IO_RA15_SetHigh();
            //PWM_EBC_Shut_Down();
        }
    /****** Detection of over-voltage*******/    
       
        else if((voltage >=Maximum_Input_Voltage && voltage2>=Maximum_Input_Voltage ) || (voltage>=Maximum_Input_Voltage && voltage1>=Maximum_Input_Voltage) || (voltage1>=Maximum_Input_Voltage && voltage2>=Maximum_Input_Voltage))
        {
            IO_RA15_SetLow();
            //PWM_EBC_Shut_Down();
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
        
        if((voltage<=Minimum_Input_Voltage)||(voltage1<=Minimum_Input_Voltage )||(voltage2<=Minimum_Input_Voltage)&&(flag_over_detected_voltage==0))
        {
           // LCD_Command(0x01);
            __delay_ms(10);
            LCD_String_xy(1,0,"Under Voltage");
            __delay_ms(100);
            flag_over_detected_voltage=1;
        }
        else if((voltage>=Maximum_Input_Voltage)||(voltage1>=Maximum_Input_Voltage)||(voltage2>=Maximum_Input_Voltage))
        {
            LCD_Command(0x01);
             __delay_ms(10);
            LCD_String_xy(1,0,"Over Voltage");
            __delay_ms(100);
        }
        
/*******************************************************************************/        
       
        /* SCR and IGBT trip*/
       
        if(flag_scr_trip==1)
        {
            LATGbits.LATG9=1;              // Buzzer
             LCD_Command(0x01);
             __delay_ms(10);
            LCD_String_xy(1,0,"SCR TRIP");
            __delay_ms(100);
            flag_scr_trip=0;
            //flag_scr_trip=0;
        }
        
        if(flag_igbt_trip==1)

        {
            LATGbits.LATG9=1;              // Buzzer
            LCD_Command(0x01);
             __delay_ms(10);
            LCD_String_xy(1,0,"IGBT TRIP");
            __delay_ms(100);
            flag_igbt_trip=0;
            //flag_igbt_trip=0;
        }

/******************************************************************************/        
        
       if(OP_Voltage>= Minimum_OP_Voltage) 
       {
           IO_RA3_SetLow();
       }
       else
       {
           IO_RA3_SetHigh();           // Battery_Not_Healthy_Led
       }
       
/******************************************************************************/        
       
        /*Y-phase is absent*/
        
        if((voltage1==0)||(voltage1>=Maximum_Input_Voltage))
       {
           PWM_RBC_Shut_Down();
           PWM_EBC_Shut_Down();
           LCD_Command(0x01);
            __delay_ms(10);
           LCD_String_xy(1,0,"Y-Phase Absent");
           __delay_ms(100);  
           
       }
       
/*********************************************************************************/        
       
        if( flag_over_detected==1)
        {
            LCD_Command(0x01);
            __delay_ms(10);
           LCD_String_xy(1,0,"Over_Voltage in Phase ");
           __delay_ms(100);
        }
        
        if(flag_under_detected==1)
        {
            LCD_Command(0x01);
            __delay_ms(10);
           LCD_String_xy(1,0,"Under_Voltage in Phase");
           __delay_ms(100);
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
                __delay_ms(10);
                PWM_RBC_Shut_Down();
                LCD_String_xy(1,0,"Bat_Rev_Polarity");
                LATGbits.LATG9=1;
                while(1);
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
                   if(I_Total>=Short_Ckt_Current)
                    {
                        PWM_RBC_Shut_Down();
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
                   if(I_Total>=Short_Ckt_Current)
                    {
                       PWM_RBC_Shut_Down();
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

           
            
              if((R_Y >=540) || (Y_B>=540) || (B_R>=540) &&(flag_over_detected==0))
            {
                
                   
                  PWM_RBC_Shut_Down();
                  flag_over_detected=1;
            }
              else if((R_Y <=404) || (Y_B<=404) || (B_R<=404) && (flag_under_detected==0))
            {
                
                PWM_RBC_Shut_Down();
                flag_under_detected=1;
                
            }
           
           
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
            else if((I_B>=Minimum_Settable_Bat_Current) && (I_B<=15) && (flag==5))
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
            
            
            else if(OP_Voltage>=Maximum_OP_Voltage)
            {
                __delay_ms(2000);
                 LATGbits.LATG9=1;
                PWM_RBC_Shut_Down();
                while(1);
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
                while(1);
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
            if (flag >= 7) 
            {
                flag = 0;
            }
        }
        if (flag == 1) 
        {
            LCD_Command(0x01);
            __delay_ms(10);
            //LCD_String_xy(1,0,"Input_voltage:");

            // LCD_String_xy(1,0,"CT2:");
            sprintf(current, "%.1f", I_B);
            LCD_String_xy(1, 0, current);


            sprintf(Power_Var, "%.1f",power_RBC);
            LCD_String_xy(1,5,Power_Var);

            //LCD_String_xy(1,11,"DC:");
            sprintf(DC, "%.1f", k_RBC);
            LCD_String_xy(1, 11, DC);

            //LCD_String_xy(2,0,"CT2:");
            sprintf(current2, "%.1f",I_Total);
            LCD_String_xy(2, 0, current2);

            sprintf(output, "%d", OP_Voltage);
            LCD_String_xy(2, 10, output);

            sprintf(v, "%d", RBC_SP);
            LCD_String_xy(2, 4, v);

            __delay_ms(100);
        }
        if (flag == 2) 
        {

            LCD_Command(0x01);
            __delay_ms(10);
            LCD_String_xy(1, 1, "RBC_SP:");
            sprintf(v, "%d", RBC_SP);
            LCD_String_xy(1, 10, v);


            LCD_String_xy(2, 1, "OP_VOLTAGE:");
            sprintf(output, "%d", OP_Voltage);
            LCD_String_xy(2, 12, output);

            __delay_ms(100);

        }

        if (flag == 6)
        {
            LCD_Command(0x01);
            __delay_ms(10);


            LCD_String_xy(1, 0, "PH_B=");
            sprintf(data, "%d", voltage); // Displaying phase B
            LCD_String_xy(1, 5, data);


            LCD_String_xy(1, 9, "P_Y=");
            sprintf(data1, "%d", voltage1); // Displaying phase Y
            LCD_String_xy(1, 13, data1);


            LCD_String_xy(2, 0, "PH_R=");
            sprintf(data2, "%d", voltage2); // Displaying phase R
            LCD_String_xy(2, 5, data2);
            __delay_ms(100);
        }

        if (flag == 4) {
            LCD_Command(0x01);
            __delay_ms(10);
            LCD_String_xy(1, 1, "EBC_SP:");
            sprintf(v, "%d", EBC_SP);
            LCD_String_xy(1, 10, v);


            LCD_String_xy(2, 1, "OP_VOLTAGE:");
            sprintf(output, "%d", OP_Voltage);
            LCD_String_xy(2, 12, output);

            __delay_ms(100);
        }
        
        
        if(flag==5)
        {
            LCD_Command(0x01);
            __delay_ms(10);
            LCD_String_xy(1,1,"I_Bat_SP:");
            sprintf(v1,"%d",Battery_Current_SP);
            LCD_String_xy(1,12,v1);
            
            LCD_String_xy(2, 1, "I_Bat:");
            sprintf(output1, "%.1f",I_B);
            LCD_String_xy(2, 12, output1);
            
            __delay_ms(100);

    }
        
        if(flag==0)
        {
           sprintf(current, "%.1f", I_B);
            LCD_String_xy(1, 0, current);


            sprintf(Power_Var, "%.1f",power_EBC);
            LCD_String_xy(1,5,Power_Var);

            //LCD_String_xy(1,11,"DC:");
            sprintf(DC, "%.1f", k_EBC);
            LCD_String_xy(1, 11, DC);

            //LCD_String_xy(2,0,"CT2:");
            sprintf(current2, "%.1f", I_Total);
            LCD_String_xy(2, 0, current2);

            sprintf(output, "%d", OP_Voltage);
            LCD_String_xy(2, 10, output);

            sprintf(v, "%d", EBC_SP);
            LCD_String_xy(2, 4, v);

            __delay_ms(100);
            
           
        }

        
       

}
}
