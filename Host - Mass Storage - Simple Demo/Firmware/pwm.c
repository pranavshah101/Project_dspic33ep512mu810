

/**
PTPER=533 for 15 KHz as pWM frequency
 * PTPER=421 FOR 19 khZ AS PWM FREQUENCY PWM Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    pwm.c

  @Summary
    This is the generated driver implementation file for the PWM driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for PWM.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.169.0
        Device            :  dsPIC33EP512MU810      
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.50
        MPLAB 	          :  MPLAB X v5.40
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include "pwm.h"
#include "spieeprom.h"
#include "rtc.h"
#define High_Freq  421       /* for 19KHz PWM frequency*/      // 16MHz in both cases
#define Low_Freq   471       /* for 17KHz PWM frequency*/
/**
  Section: Driver Interface
*/

/**
  PWM Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    pwm.c

  @Summary
    This is the generated driver implementation file for the PWM driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for PWM.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.169.0
        Device            :  dsPIC33EP512MU810      
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.50
        MPLAB 	          :  MPLAB X v5.40
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include "pwm.h"

/**
  Section: Driver Interface
*/

void PWM_RBC_MODE (void)
{
    // PCLKDIV 1; 
    PTCON2 = 0x00;
    // SYNCOEN disabled; SEIEN disabled; SESTAT disabled; SEVTPS 1; SYNCSRC SYNCI1; SYNCEN disabled; EIPU disabled; SYNCPOL disabled; 
    STCON = 0x00;
    // PCLKDIV 1; 
    STCON2 = 0x00;
    // STPER 65528; 
    STPER = 0xFFF8;
    // SSEVTCMP 0; 
    SSEVTCMP = 0x00;
    // PTPER 842;      // By using PLL, Fosc=16MHz,  PTPER = (Fosc)/((Fpwm)*(pwm input clock prescalar))= 16000000/(19000)*1 = 842
    PTPER = 1500;       // PUSH-PULL Mode
    // SEVTCMP 0; 
    SEVTCMP = 0x00;
    // MDC 421; 
   // MDC = 0x1A5;
    // CHOPCLK 0; CHPCLKEN disabled; 
    CHOP = 0x00;
    // MDCS Primary; FLTIEN disabled; CAM Edge Aligned; DTC Positive dead time for all Output modes; TRGIEN disabled; XPRES disabled; ITB Master; IUE disabled; CLIEN disabled; MTBS disabled; DTCP disabled; 
    PWMCON1 = 0x00;
    // MDCS Primary; FLTIEN disabled; CAM Edge Aligned; DTC Positive dead time for all Output modes; TRGIEN disabled; XPRES disabled; ITB Master; IUE disabled; CLIEN disabled; MTBS disabled; DTCP disabled; 
    PWMCON2 = 0x00;
    // MDCS Primary; FLTIEN disabled; CAM Edge Aligned; DTC Positive dead time for all Output modes; TRGIEN disabled; XPRES disabled; ITB Master; IUE disabled; CLIEN disabled; MTBS disabled; DTCP disabled; 
    PWMCON3 = 0x00;
    // MDCS Master; FLTIEN disabled; CAM Edge Aligned; DTC Positive dead time for all Output modes; TRGIEN disabled; XPRES disabled; ITB Master; IUE disabled; CLIEN disabled; MTBS disabled; DTCP disabled; 
    PWMCON4 = 0x100;
    // MDCS Master; FLTIEN disabled; CAM Edge Aligned; DTC Positive dead time for all Output modes; TRGIEN disabled; XPRES disabled; ITB Master; IUE disabled; CLIEN disabled; MTBS disabled; DTCP disabled; 
    PWMCON5 = 0x100;
    // MDCS Master; FLTIEN disabled; CAM Edge Aligned; DTC Positive dead time for all Output modes; TRGIEN disabled; XPRES disabled; ITB Master; IUE disabled; CLIEN disabled; MTBS disabled; DTCP disabled; 
    PWMCON6 = 0x100;
    //FLTDAT PWM1L Low, PWM1H Low; SWAP disabled; OVRENH disabled; PENL enabled; PUSH-PULL Output Mode; OVRENL disabled; OSYNC disabled; POLL disabled; PENH enabled; CLDAT PWM1L Low, PWM1H Low; OVRDAT PWM1L Low, PWM1H Low; POLH disabled; 
    IOCON1 = 0xC800;
    //FLTDAT PWM2L Low, PWM2H Low; SWAP disabled; OVRENH disabled; PENL enabled; PUSH-PULL Output Mode; OVRENL disabled; OSYNC disabled; POLL disabled; PENH enabled; CLDAT PWM2L Low, PWM2H Low; OVRDAT PWM2L Low, PWM2H Low; POLH disabled; 
    IOCON2 = 0xC800;
    //FLTDAT PWM3L Low, PWM3H Low; SWAP disabled; OVRENH disabled; PENL enabled; PUSH-PULL Output Mode; OVRENL disabled; OSYNC disabled; POLL disabled; PENH enabled; CLDAT PWM3L Low, PWM3H Low; OVRDAT PWM3L Low, PWM3H Low; POLH disabled; 
    IOCON3 = 0xC800;
    //FLTDAT PWM4L Low, PWM4H Low; SWAP disabled; OVRENH disabled; PENL enabled; PUSH-PULL Output Mode; OVRENL disabled; OSYNC disabled; POLL disabled; PENH enabled; CLDAT PWM4L Low, PWM4H Low; OVRDAT PWM4L Low, PWM4H Low; POLH disabled; 
    IOCON4 = 0xC800;
    //FLTDAT PWM5L Low, PWM5H Low; SWAP disabled; OVRENH disabled; PENL enabled; PUSH-PULL Output Mode; OVRENL disabled; OSYNC disabled; POLL disabled; PENH enabled; CLDAT PWM5L Low, PWM5H Low; OVRDAT PWM5L Low, PWM5H Low; POLH disabled; 
    IOCON5 = 0xC800;
    //FLTDAT PWM6L Low, PWM6H Low; SWAP disabled; OVRENH disabled; PENL enabled; PUSH-PULL Output Mode; OVRENL disabled; OSYNC disabled; POLL disabled; PENH enabled; CLDAT PWM6L Low, PWM6H Low; OVRDAT PWM6L Low, PWM6H Low; POLH disabled; 
    IOCON6 = 0xC800;
    //FLTPOL disabled; CLPOL disabled; CLSRC FLT1; CLMOD disabled; FLTMOD PWM1H, PWM1L pins to FLTDAT values- Latched; IFLTMOD disabled; FLTSRC FLT1; 
    FCLCON1 = 0x00;
    //FLTPOL disabled; CLPOL disabled; CLSRC FLT1; CLMOD disabled; FLTMOD PWM2H, PWM2L pins to FLTDAT values- Latched; IFLTMOD disabled; FLTSRC FLT1; 
    FCLCON2 = 0x00;
    //FLTPOL disabled; CLPOL disabled; CLSRC FLT1; CLMOD disabled; FLTMOD PWM3H, PWM3L pins to FLTDAT values- Latched; IFLTMOD disabled; FLTSRC FLT1; 
    FCLCON3 = 0x00;
    //FLTPOL disabled; CLPOL disabled; CLSRC FLT1; CLMOD disabled; FLTMOD PWM4H, PWM4L pins to FLTDAT values- Latched; IFLTMOD disabled; FLTSRC FLT1; 
    FCLCON4 = 0x00;
    //FLTPOL disabled; CLPOL disabled; CLSRC FLT1; CLMOD disabled; FLTMOD PWM5H, PWM5L pins to FLTDAT values- Latched; IFLTMOD disabled; FLTSRC FLT1; 
    FCLCON5 = 0x00;
    //FLTPOL disabled; CLPOL disabled; CLSRC FLT1; CLMOD disabled; FLTMOD PWM6H, PWM6L pins to FLTDAT values- Latched; IFLTMOD disabled; FLTSRC FLT1; 
    FCLCON6 = 0x00;
    // PDC1 0; 
    PDC1 = 0x00;
    // PDC2 0; 
    PDC2 = 0x00;
    // PDC3 0; 
    PDC3 = 0x00;
    // PDC4 0; 
    PDC4 = 0x00;
    // PDC5 0; 
    PDC5 = 0x00;
    // PDC6 0; 
    PDC6 = 0x00;
    // PHASE1 0; 
    PHASE1 = 0x00;
    // PHASE2 0; 
    PHASE2 = 0x00;
    // PHASE3 0; 
    PHASE3 = 0x00;
    // PHASE4 0; 
    PHASE4 = 0x00;
    // PHASE5 0; 
    PHASE5 = 0x00;
    // PHASE6 0; 
    PHASE6 = 0x00;
    // DTR1 0; 
    DTR1 = 0;       
    // DTR2 0; 
    DTR2 = 0;
    // DTR3 0; 
    DTR3 = 0;
    // DTR4 0; 
    DTR4 = 0;
    // DTR5 0; 
    DTR5 = 0;
    // DTR6 0; 
    DTR6 = 0;
    // ALTDTR1 0; 
    ALTDTR1 = 0;
    // ALTDTR2 0; 
    ALTDTR2 = 0;
    // ALTDTR3 0; 
    ALTDTR3 = 0;
    // ALTDTR4 0; 
    ALTDTR4 = 0;
    // ALTDTR5 0; 
    ALTDTR5 = 0;
    // ALTDTR6 0; 
    ALTDTR6 = 0;
    // SDC1 0; 
    SDC1 = 0x00;
    // SDC2 0; 
    SDC2 = 0x00;
    // SDC3 0; 
    SDC3 = 0x00;
    // SDC4 0; 
    SDC4 = 0x00;
    // SDC5 0; 
    SDC5 = 0x00;
    // SDC6 0; 
    SDC6 = 0x00;
    // SPHASE1 0; 
    SPHASE1 = 0x00;
    // SPHASE2 0; 
    SPHASE2 = 0x00;
    // SPHASE3 0; 
    SPHASE3 = 0x00;
    // SPHASE4 0; 
    SPHASE4 = 0x00;
    // SPHASE5 0; 
    SPHASE5 = 0x00;
    // SPHASE6 0; 
    SPHASE6 = 0x00;
    // TRGCMP 0; 
    TRIG1 = 0x00;
    // TRGCMP 0; 
    TRIG2 = 0x00;
    // TRGCMP 0; 
    TRIG3 = 0x00;
    // TRGCMP 0; 
    TRIG4 = 0x00;
    // TRGCMP 0; 
    TRIG5 = 0x00;
    // TRGCMP 0; 
    TRIG6 = 0x00;
    // TRGDIV 1; TRGSTRT 0; 
    TRGCON1 = 0x00;
    // TRGDIV 1; TRGSTRT 0; 
    TRGCON2 = 0x00;
    // TRGDIV 1; TRGSTRT 0; 
    TRGCON3 = 0x00;
    // TRGDIV 1; TRGSTRT 0; 
    TRGCON4 = 0x00;
    // TRGDIV 1; TRGSTRT 0; 
    TRGCON5 = 0x00;
    // TRGDIV 1; TRGSTRT 0; 
    TRGCON6 = 0x00;
    // BPLL disabled; BPHH disabled; BPLH disabled; BCH disabled; FLTLEBEN disabled; PLR disabled; CLLEBEN disabled; BCL disabled; PLF disabled; PHR disabled; BPHL disabled; PHF disabled; 
    LEBCON1 = 0x00;
    // BPLL disabled; BPHH disabled; BPLH disabled; BCH disabled; FLTLEBEN disabled; PLR disabled; CLLEBEN disabled; BCL disabled; PLF disabled; PHR disabled; BPHL disabled; PHF disabled; 
    LEBCON2 = 0x00;
    // BPLL disabled; BPHH disabled; BPLH disabled; BCH disabled; FLTLEBEN disabled; PLR disabled; CLLEBEN disabled; BCL disabled; PLF disabled; PHR disabled; BPHL disabled; PHF disabled; 
    LEBCON3 = 0x00;
    // BPLL disabled; BPHH disabled; BPLH disabled; BCH disabled; FLTLEBEN disabled; PLR disabled; CLLEBEN disabled; BCL disabled; PLF disabled; PHR disabled; BPHL disabled; PHF disabled; 
    LEBCON4 = 0x00;
    // BPLL disabled; BPHH disabled; BPLH disabled; BCH disabled; FLTLEBEN disabled; PLR disabled; CLLEBEN disabled; BCL disabled; PLF disabled; PHR disabled; BPHL disabled; PHF disabled; 
    LEBCON5 = 0x00;
    // BPLL disabled; BPHH disabled; BPLH disabled; BCH disabled; FLTLEBEN disabled; PLR disabled; CLLEBEN disabled; BCL disabled; PLF disabled; PHR disabled; BPHL disabled; PHF disabled; 
    LEBCON6 = 0x00;
    // LEB 0; 
    LEBDLY1 = 0x00;
    // LEB 0; 
    LEBDLY2 = 0x00;
    // LEB 0; 
    LEBDLY3 = 0x00;
    // LEB 0; 
    LEBDLY4 = 0x00;
    // LEB 0; 
    LEBDLY5 = 0x00;
    // LEB 0; 
    LEBDLY6 = 0x00;
    // CHOPLEN disabled; CHOPHEN disabled; BLANKSEL No state blanking; CHOPSEL No state blanking; 
    AUXCON1 = 0x00;
    // CHOPLEN disabled; CHOPHEN disabled; BLANKSEL No state blanking; CHOPSEL No state blanking; 
    AUXCON2 = 0x00;
    // CHOPLEN disabled; CHOPHEN disabled; BLANKSEL No state blanking; CHOPSEL No state blanking; 
    AUXCON3 = 0x00;
    // CHOPLEN disabled; CHOPHEN disabled; BLANKSEL No state blanking; CHOPSEL No state blanking; 
    AUXCON4 = 0x00;
    // CHOPLEN disabled; CHOPHEN disabled; BLANKSEL No state blanking; CHOPSEL No state blanking; 
    AUXCON5 = 0x00;
    // CHOPLEN disabled; CHOPHEN disabled; BLANKSEL No state blanking; CHOPSEL No state blanking; 
    AUXCON6 = 0x00;

    // SYNCOEN disabled; SEIEN disabled; SESTAT disabled; SEVTPS 1; SYNCSRC SYNCI1; SYNCEN disabled; PTSIDL disabled; PTEN enabled; EIPU disabled; SYNCPOL disabled; 
    PTCON = 0x0000;
}



void PWM_EBC_MODE (void)
{
    // PCLKDIV 1; 
    PTCON2 = 0x00;
    // SYNCOEN disabled; SEIEN disabled; SESTAT disabled; SEVTPS 1; SYNCSRC SYNCI1; SYNCEN disabled; EIPU disabled; SYNCPOL disabled; 
    STCON = 0x00;
    // PCLKDIV 1; 
    STCON2 = 0x00;
    // STPER 65528; 
    STPER = 0xFFF8;
    // SSEVTCMP 0; 
    SSEVTCMP = 0x00;
    // PTPER 842;          // PTPER = (Fosc)/((Fpwm)*(pwm input clock prescalar))= 16000000/(19000)*1 = 842
    PTPER = 1500;           // PUSH-PULL Mode
    // SEVTCMP 0; 
    SEVTCMP = 0x00;
    // MDC 421; 
    //MDC = 0x1A5;
    // CHOPCLK 0; CHPCLKEN disabled; 
    CHOP = 0x00;
    // MDCS Master; FLTIEN disabled; CAM Edge Aligned; DTC Positive dead time for all Output modes; TRGIEN disabled; XPRES disabled; ITB Master; IUE disabled; CLIEN disabled; MTBS disabled; DTCP disabled; 
    PWMCON1 = 0x100;
    // MDCS Master; FLTIEN disabled; CAM Edge Aligned; DTC Positive dead time for all Output modes; TRGIEN disabled; XPRES disabled; ITB Master; IUE disabled; CLIEN disabled; MTBS disabled; DTCP disabled; 
    PWMCON2 = 0x100;
    // MDCS Master; FLTIEN disabled; CAM Edge Aligned; DTC Positive dead time for all Output modes; TRGIEN disabled; XPRES disabled; ITB Master; IUE disabled; CLIEN disabled; MTBS disabled; DTCP disabled; 
    PWMCON3 = 0x100;
    // MDCS Primary; FLTIEN disabled; CAM Edge Aligned; DTC Positive dead time for all Output modes; TRGIEN disabled; XPRES disabled; ITB Master; IUE disabled; CLIEN disabled; MTBS disabled; DTCP disabled; 
    PWMCON4 = 0x00;
    // MDCS Primary; FLTIEN disabled; CAM Edge Aligned; DTC Positive dead time for all Output modes; TRGIEN disabled; XPRES disabled; ITB Master; IUE disabled; CLIEN disabled; MTBS disabled; DTCP disabled; 
    PWMCON5 = 0x00;
    // MDCS Primary; FLTIEN disabled; CAM Edge Aligned; DTC Positive dead time for all Output modes; TRGIEN disabled; XPRES disabled; ITB Master; IUE disabled; CLIEN disabled; MTBS disabled; DTCP disabled; 
    PWMCON6 = 0x00;
    //FLTDAT PWM1L Low, PWM1H Low; SWAP disabled; OVRENH disabled; PENL enabled; PMOD Complementary Output Mode; OVRENL disabled; OSYNC disabled; POLL disabled; PENH enabled; CLDAT PWM1L Low, PWM1H Low; OVRDAT PWM1L Low, PWM1H Low; POLH disabled; 
    IOCON1 = 0xC800;
    //FLTDAT PWM2L Low, PWM2H Low; SWAP disabled; OVRENH disabled; PENL enabled; PMOD Complementary Output Mode; OVRENL disabled; OSYNC disabled; POLL disabled; PENH enabled; CLDAT PWM2L Low, PWM2H Low; OVRDAT PWM2L Low, PWM2H Low; POLH disabled; 
    IOCON2 = 0xC800;
    //FLTDAT PWM3L Low, PWM3H Low; SWAP disabled; OVRENH disabled; PENL enabled; PMOD Complementary Output Mode; OVRENL disabled; OSYNC disabled; POLL disabled; PENH enabled; CLDAT PWM3L Low, PWM3H Low; OVRDAT PWM3L Low, PWM3H Low; POLH disabled; 
    IOCON3 = 0xC800;
    //FLTDAT PWM4L Low, PWM4H Low; SWAP disabled; OVRENH disabled; PENL enabled; PMOD Complementary Output Mode; OVRENL disabled; OSYNC disabled; POLL disabled; PENH enabled; CLDAT PWM4L Low, PWM4H Low; OVRDAT PWM4L Low, PWM4H Low; POLH disabled; 
    IOCON4 = 0xC800;
    //FLTDAT PWM5L Low, PWM5H Low; SWAP disabled; OVRENH disabled; PENL enabled; PMOD Complementary Output Mode; OVRENL disabled; OSYNC disabled; POLL disabled; PENH enabled; CLDAT PWM5L Low, PWM5H Low; OVRDAT PWM5L Low, PWM5H Low; POLH disabled; 
    IOCON5 = 0xC800;
    //FLTDAT PWM6L Low, PWM6H Low; SWAP disabled; OVRENH disabled; PENL enabled; PMOD Complementary Output Mode; OVRENL disabled; OSYNC disabled; POLL disabled; PENH enabled; CLDAT PWM6L Low, PWM6H Low; OVRDAT PWM6L Low, PWM6H Low; POLH disabled; 
    IOCON6 = 0xC800;
    //FLTPOL disabled; CLPOL disabled; CLSRC FLT1; CLMOD disabled; FLTMOD PWM1H, PWM1L pins to FLTDAT values- Latched; IFLTMOD disabled; FLTSRC FLT1; 
    FCLCON1 = 0x00;
    //FLTPOL disabled; CLPOL disabled; CLSRC FLT1; CLMOD disabled; FLTMOD PWM2H, PWM2L pins to FLTDAT values- Latched; IFLTMOD disabled; FLTSRC FLT1; 
    FCLCON2 = 0x00;
    //FLTPOL disabled; CLPOL disabled; CLSRC FLT1; CLMOD disabled; FLTMOD PWM3H, PWM3L pins to FLTDAT values- Latched; IFLTMOD disabled; FLTSRC FLT1; 
    FCLCON3 = 0x00;
    //FLTPOL disabled; CLPOL disabled; CLSRC FLT1; CLMOD disabled; FLTMOD PWM4H, PWM4L pins to FLTDAT values- Latched; IFLTMOD disabled; FLTSRC FLT1; 
    FCLCON4 = 0x00;
    //FLTPOL disabled; CLPOL disabled; CLSRC FLT1; CLMOD disabled; FLTMOD PWM5H, PWM5L pins to FLTDAT values- Latched; IFLTMOD disabled; FLTSRC FLT1; 
    FCLCON5 = 0x00;
    //FLTPOL disabled; CLPOL disabled; CLSRC FLT1; CLMOD disabled; FLTMOD PWM6H, PWM6L pins to FLTDAT values- Latched; IFLTMOD disabled; FLTSRC FLT1; 
    FCLCON6 = 0x00;
    // PDC1 0; 
    PDC1 = 0x00;
    // PDC2 0; 
    PDC2 = 0x00;
    // PDC3 0; 
    PDC3 = 0x00;
    // PDC4 0; 
    PDC4 = 0x00;
    // PDC5 0; 
    PDC5 = 0x00;
    // PDC6 0; 
    PDC6 = 0x00;
    // PHASE1 0; 
    PHASE1 = 0x00;
    // PHASE2 0; 
    PHASE2 = 0x00;
    // PHASE3 0; 
    PHASE3 = 0x00;
    // PHASE4 0; 
    PHASE4 = 0x00;
    // PHASE5 0; 
    PHASE5 = 0x00;
    // PHASE6 0; 
    PHASE6 = 0x00;
    // DTR1 0; 
    DTR1 = 0;
    // DTR2 0; 
    DTR2 = 0;
    // DTR3 0; 
    DTR3 = 0;
    // DTR4 0; 
    DTR4 = 0;
    // DTR5 0; 
    DTR5 = 0;
    // DTR6 0; 
    DTR6 = 0;
    // ALTDTR1 0; 
    ALTDTR1 = 0;
    // ALTDTR2 0; 
    ALTDTR2 = 0;
    // ALTDTR3 0; 
    ALTDTR3 = 0;
    // ALTDTR4 0; 
    ALTDTR4 = 0;
    // ALTDTR5 0; 
    ALTDTR5 = 0;
    // ALTDTR6 0; 
    ALTDTR6 = 0;
    // SDC1 0; 
    SDC1 = 0x00;
    // SDC2 0; 
    SDC2 = 0x00;
    // SDC3 0; 
    SDC3 = 0x00;
    // SDC4 0; 
    SDC4 = 0x00;
    // SDC5 0; 
    SDC5 = 0x00;
    // SDC6 0; 
    SDC6 = 0x00;
    // SPHASE1 0; 
    SPHASE1 = 0x00;
    // SPHASE2 0; 
    SPHASE2 = 0x00;
    // SPHASE3 0; 
    SPHASE3 = 0x00;
    // SPHASE4 0; 
    SPHASE4 = 0x00;
    // SPHASE5 0; 
    SPHASE5 = 0x00;
    // SPHASE6 0; 
    SPHASE6 = 0x00;
    // TRGCMP 0; 
    TRIG1 = 0x00;
    // TRGCMP 0; 
    TRIG2 = 0x00;
    // TRGCMP 0; 
    TRIG3 = 0x00;
    // TRGCMP 0; 
    TRIG4 = 0x00;
    // TRGCMP 0; 
    TRIG5 = 0x00;
    // TRGCMP 0; 
    TRIG6 = 0x00;
    // TRGDIV 1; TRGSTRT 0; 
    TRGCON1 = 0x00;
    // TRGDIV 1; TRGSTRT 0; 
    TRGCON2 = 0x00;
    // TRGDIV 1; TRGSTRT 0; 
    TRGCON3 = 0x00;
    // TRGDIV 1; TRGSTRT 0; 
    TRGCON4 = 0x00;
    // TRGDIV 1; TRGSTRT 0; 
    TRGCON5 = 0x00;
    // TRGDIV 1; TRGSTRT 0; 
    TRGCON6 = 0x00;
    // BPLL disabled; BPHH disabled; BPLH disabled; BCH disabled; FLTLEBEN disabled; PLR disabled; CLLEBEN disabled; BCL disabled; PLF disabled; PHR disabled; BPHL disabled; PHF disabled; 
    LEBCON1 = 0x00;
    // BPLL disabled; BPHH disabled; BPLH disabled; BCH disabled; FLTLEBEN disabled; PLR disabled; CLLEBEN disabled; BCL disabled; PLF disabled; PHR disabled; BPHL disabled; PHF disabled; 
    LEBCON2 = 0x00;
    // BPLL disabled; BPHH disabled; BPLH disabled; BCH disabled; FLTLEBEN disabled; PLR disabled; CLLEBEN disabled; BCL disabled; PLF disabled; PHR disabled; BPHL disabled; PHF disabled; 
    LEBCON3 = 0x00;
    // BPLL disabled; BPHH disabled; BPLH disabled; BCH disabled; FLTLEBEN disabled; PLR disabled; CLLEBEN disabled; BCL disabled; PLF disabled; PHR disabled; BPHL disabled; PHF disabled; 
    LEBCON4 = 0x00;
    // BPLL disabled; BPHH disabled; BPLH disabled; BCH disabled; FLTLEBEN disabled; PLR disabled; CLLEBEN disabled; BCL disabled; PLF disabled; PHR disabled; BPHL disabled; PHF disabled; 
    LEBCON5 = 0x00;
    // BPLL disabled; BPHH disabled; BPLH disabled; BCH disabled; FLTLEBEN disabled; PLR disabled; CLLEBEN disabled; BCL disabled; PLF disabled; PHR disabled; BPHL disabled; PHF disabled; 
    LEBCON6 = 0x00;
    // LEB 0; 
    LEBDLY1 = 0x00;
    // LEB 0; 
    LEBDLY2 = 0x00;
    // LEB 0; 
    LEBDLY3 = 0x00;
    // LEB 0; 
    LEBDLY4 = 0x00;
    // LEB 0; 
    LEBDLY5 = 0x00;
    // LEB 0; 
    LEBDLY6 = 0x00;
    // CHOPLEN disabled; CHOPHEN disabled; BLANKSEL No state blanking; CHOPSEL No state blanking; 
    AUXCON1 = 0x00;
    // CHOPLEN disabled; CHOPHEN disabled; BLANKSEL No state blanking; CHOPSEL No state blanking; 
    AUXCON2 = 0x00;
    // CHOPLEN disabled; CHOPHEN disabled; BLANKSEL No state blanking; CHOPSEL No state blanking; 
    AUXCON3 = 0x00;
    // CHOPLEN disabled; CHOPHEN disabled; BLANKSEL No state blanking; CHOPSEL No state blanking; 
    AUXCON4 = 0x00;
    // CHOPLEN disabled; CHOPHEN disabled; BLANKSEL No state blanking; CHOPSEL No state blanking; 
    AUXCON5 = 0x00;
    // CHOPLEN disabled; CHOPHEN disabled; BLANKSEL No state blanking; CHOPSEL No state blanking; 
    AUXCON6 = 0x00;

    // SYNCOEN disabled; SEIEN disabled; SESTAT disabled; SEVTPS 1; SYNCSRC SYNCI1; SYNCEN disabled; PTSIDL disabled; PTEN enabled; EIPU disabled; SYNCPOL disabled; 
    //PTCON = 0x0000;
}

void __attribute__ ((weak)) PWM_SpecialEvent_CallBack(void)
{
    // Add Application code here
}

void PWM_SpecialEvent_Tasks ( void )
{
    if(IFS3bits.PSEMIF)
    {
        // PWM SpecialEvent callback function 
        PWM_SpecialEvent_CallBack();

        // clear the PWM SpecialEvent interrupt flag
        IFS3bits.PSEMIF = 0;
    }
}

void __attribute__ ((weak)) PWM_Generator1_CallBack(void)
{
    // Add Application code here
}

void PWM_Generator1_Tasks ( void )
{
	if(IFS3bits.PSEMIF)
	{
		// PWM Generator1 callback function 
		PWM_Generator1_CallBack();
		
		// clear the PWM Generator1 interrupt flag
		IFS5bits.PWM1IF = 0;
	}
}

void __attribute__ ((weak)) PWM_Generator2_CallBack(void)
{
    // Add Application code here
}

void PWM_Generator2_Tasks ( void )
{
	if(IFS3bits.PSEMIF)
	{
		// PWM Generator2 callback function 
		PWM_Generator2_CallBack();
		
		// clear the PWM Generator2 interrupt flag
		IFS5bits.PWM2IF = 0;
	}
}

void __attribute__ ((weak)) PWM_Generator3_CallBack(void)
{
    // Add Application code here
}

void PWM_Generator3_Tasks ( void )
{
	if(IFS3bits.PSEMIF)
	{
		// PWM Generator3 callback function 
		PWM_Generator3_CallBack();
		
		// clear the PWM Generator3 interrupt flag
		IFS6bits.PWM3IF = 0;
	}
}

void __attribute__ ((weak)) PWM_Generator4_CallBack(void)
{
    // Add Application code here
}

void PWM_Generator4_Tasks ( void )
{
	if(IFS3bits.PSEMIF)
	{
		// PWM Generator4 callback function 
		PWM_Generator4_CallBack();
		
		// clear the PWM Generator4 interrupt flag
		IFS6bits.PWM4IF = 0;
	}
}

void __attribute__ ((weak)) PWM_Generator5_CallBack(void)
{
    // Add Application code here
}

void PWM_Generator5_Tasks ( void )
{
	if(IFS3bits.PSEMIF)
	{
		// PWM Generator5 callback function 
		PWM_Generator5_CallBack();
		
		// clear the PWM Generator5 interrupt flag
		IFS6bits.PWM5IF = 0;
	}
}

void __attribute__ ((weak)) PWM_Generator6_CallBack(void)
{
    // Add Application code here
}

void PWM_Generator6_Tasks ( void )
{
	if(IFS3bits.PSEMIF)
	{
		// PWM Generator6 callback function 
		PWM_Generator6_CallBack();
		
		// clear the PWM Generator6 interrupt flag
		IFS6bits.PWM6IF = 0;
	}
}

void PWM_Duty_Cycle_RBC(float i)
{
   PWM_RBC_MODE();
   PTCON = 0x8000;
   MDC   = 30*i;      // PUSH-PULL Mode(For getting 10% duty cycle in DSO of 17KHz freq,we have to put value of 20% of PTPER in this register)
  
    
}

void PWM_RBC_Shut_Down()
{
    PWM_RBC_MODE();
    PTCON = 0x0000;
    
}
void PWM_Duty_Cycle_EBC(float i)
{
   PWM_EBC_MODE();
   PTCON = 0x8000;
   MDC   = 30*i;    // PUSH-PULL Mode(For getting 10% duty cycle in DSO of 17KHz freq,we have to put value of 20% of PTPER in this register)
   
    
}

void PWM_EBC_Shut_Down()
{
    PWM_EBC_MODE();
    PTCON = 0x0000;
    
}
