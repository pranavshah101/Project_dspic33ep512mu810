#define RS          LATGbits.LATG0  /*PIN 0 of PORTG is assigned for register select Pin of LCD*/
#define EN          LATGbits.LATG1  /*PIN 1 of PORTG is assigned for enable Pin of LCD */
#define ldata       LATD         /*PORTD(PD4-PD7) is assigned for LCD Data Output*/
#define LCD_Port    TRISD     /*define macros for PORTB Direction Register*/


void LCD_Init()
{
    TRISD = 0xFFF0;       /*PORT as Output Port*/
    TRISGbits.TRISG0=0;
    TRISGbits.TRISG1=0;
    //__delay_ms(1000);       /*15ms,16x2 LCD Power on delay*/
    
    LCD_Command(0x03);
    __delay_ms(500);   //5000
    LCD_Command(0x03); 
    __delay_us(20);  //200
    LCD_Command(0x03); 
     __delay_us(20);   //200
    
    
    
    LCD_Command(0x02);  /*send for initialization of LCD
                          for nibble (4-bit) mode */
    //__delay_ms(5000);
    LCD_Command(0x28);  /*use 2 line and
                          initialize 5*8 matrix in (4-bit mode)*/
   // __delay_ms(5000);
   // LCD_Command(0x01);  /*clear display screen*/
   // __delay_ms(1000);
    LCD_Command(0x0E);  /*display on cursor off*/
  //  __delay_ms(5000);
    LCD_Command(0x06);  /*increment cursor (shift cursor to right)*/
  //  __delay_ms(5000);
    LCD_Command(0x01);  /*clear display screen*/
    __delay_ms(20);  //5000
}

void LCD_Command(unsigned char cmd )
{
LATD = (cmd>>4);  /*Send higher nibble of command first to PORT*/
RS = 0;           /*Command Register is selected i.e.RS=0*/
EN = 1;           /*High-to-low pulse on Enable pin to latch data*/
__delay_us(200);
EN = 0;
    LATD = (cmd &0x0f); /*Send lower nibble of command to PORT */
EN = 1;
__delay_us(200);
EN = 0;
}


void LCD_Char(unsigned char dat)
{
LATD = (dat >>4); /*Send higher nibble of data first to PORT*/
RS = 1;  /*Data Register is selected*/
EN = 1;  /*High-to-low pulse on Enable pin to latch data*/
__delay_us(200);
EN = 0;
   LATD = (dat & 0x0F);  /*Send lower nibble of data to PORT*/
EN = 1;  /*High-to-low pulse on Enable pin to latch data*/
__delay_us(200);
EN = 0;
}
void LCD_String(const char *msg)
{
while((*msg)!=0)
{
 LCD_Char(*msg);
 msg++;

    }
}

void LCD_String_xy(char row,char pos,const char *msg)
{
    char location=0;
    if(row<=1)
    {
        location=(0x80) | ((pos) & 0x0f);  /*Print message on 1st row and desired location*/
        LCD_Command(location);
        
    }
    else
    {
        location=(0xC0) | ((pos) & 0x0f);  /*Print message on 2nd row and desired location*/
        LCD_Command(location);    
    }  
   

    LCD_String(msg);

}
void LCD_Clear()
{
    LCD_Command(0x01);  /*clear display screen*/
    MSdelay(5);
}

void MSdelay(unsigned int val)
{
 unsigned int i,j;
 for(i=0;i<val;i++)
     for(j=0;j<165;j++);  /*This count Provide delay of 1 ms for 8MHz Frequency */
 }

