/*----------------------------------------------------------------------------
 CONFIGURATION BITS
 -----------------------------------------------------------------------------*/
// FICD
/* ICD Communication Channel Select bits->Communicate on PGEC1 and PGED1*/
#pragma config ICS = PGD1
/* JTAG Enable bit->JTAG is disabled*/
#pragma config JTAGEN = OFF    //

// FPOR
/* Alternate I2C1 pins (I2C1 mapped to SDA1/SCL1 pins)*/
#pragma config ALTI2C1 = OFF
/* Alternate I2C2 pins (I2C2 mapped to SDA2/SCL2 pins) */
#pragma config ALTI2C2 = OFF
/* Watchdog Window Select bits->WDT Window is 25% of WDT period*/
#pragma config WDTWIN = WIN25 

// FWDT
/* Watchdog Timer Postscaler bits->1:32768 */
#pragma config WDTPOST = PS32768
/* Watchdog Timer Prescaler bit->1:128 */
#pragma config WDTPRE = PR128
/* PLL Lock Enable bit->Clock switch to PLL source will wait until 
 * the PLL lock signal is valid.*/
#pragma config PLLKEN = ON
/* Watchdog Timer Window Enable bit->Watchdog Timer in Non-Window mode */
#pragma config WINDIS = OFF
/* Watchdog Timer Enable bit->Watchdog timer enabled/disabled 
 * by user software */
#pragma config FWDTEN = OFF    

// FOSC
/* //Primary Oscillator Mode Select bits->Primary Oscillator disabled */
#pragma config POSCMD = NONE 
/* OSC2 Pin Function bit->OSC2 is general purpose digital I/O pin */
#pragma config OSCIOFNC = OFF
/* Peripheral pin select configuration (Allow multiple reconfigurations)*/
#pragma config IOL1WAY = OFF
/* Clock Switching Mode bits->Clock switching is enabled,Fail-safe 
 * Clock Monitor is disabled */
#pragma config FCKSM = CSECMD 

// FOSCSEL
/* Oscillator Source Selection->Internal Fast RC (FRC) */
#pragma config FNOSC = FRC
/* PWM Lock Enable bit (PWM registers may be written without key sequence) */
#pragma config PWMLOCK = OFF 
/* //Two-speed Oscillator Start-up Enable bit->Start 
 * Start up with user-selected oscillator source */
#pragma config IESO = OFF    

// FGS
/* General Segment Write-Protect bit->General Segment may be written */
#pragma config GWRP = OFF
/* General Segment Code-Protect bit->General Segment Code protect is Disabled */
#pragma config GCP = OFF

/*----------------------------------------------------------------------------
 HEADER FILES
 -----------------------------------------------------------------------------*/
#include "osc.h"

/*----------------------------------------------------------------------------
 FUNCTIONS
 -----------------------------------------------------------------------------*/
void oscConfig(void) {
    // FRCDIV FRC/1; PLLPRE 7; DOZE 1:8; PLLPOST 1:2; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x3005;
    // TUN Center frequency; 
    OSCTUN = 0x00;
    // ROON disabled; ROSEL FOSC; RODIV 0; ROSSLP disabled; 
    REFOCON = 0x00;
    // PLLDIV 150; 
    PLLFBD = 0x96;
    // AD1MD enabled; PWMMD enabled; T3MD enabled; T4MD enabled; T1MD enabled; U2MD enabled; T2MD enabled; U1MD enabled; QEI1MD enabled; SPI2MD enabled; SPI1MD enabled; T5MD enabled; I2C1MD enabled; 
    PMD1 = 0x00;
    // IC4MD enabled; IC3MD enabled; OC1MD enabled; IC2MD enabled; OC2MD enabled; IC1MD enabled; OC3MD enabled; OC4MD enabled; 
    PMD2 = 0x00;
    // CMPMD enabled; CRCMD enabled; I2C2MD enabled; 
    PMD3 = 0x00;
    // CTMUMD enabled; REFOMD enabled; 
    PMD4 = 0x00;
    // PWM2MD enabled; PWM1MD enabled; PWM3MD enabled; 
    PMD6 = 0x00;
    // PTGMD enabled; DMA0MD enabled; 
    PMD7 = 0x00;
    // CF no clock failure; NOSC FRCPLL; CLKLOCK unlocked; OSWEN Switch is Complete; 
    __builtin_write_OSCCONH((uint8_t) (0x01));
    __builtin_write_OSCCONL((uint8_t) (0x01));
    // Wait for Clock switch to occur
    while (OSCCONbits.OSWEN != 0);
    while (OSCCONbits.LOCK != 1);

}
