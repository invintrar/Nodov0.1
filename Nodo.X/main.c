/*
 * File:   main.c
 * Author: Darwin
 *
 * Created on June 26, 2019, 12:15 AM
 */

/*----------------------------------------------------------------------------
 HEADER FILES
 -----------------------------------------------------------------------------*/
#include "main.h"


/*----------------------------------------------------------------------------
 VARIABLE GLOBALES
 -----------------------------------------------------------------------------*/
struct sdflags sdflags;
unsigned char ccs;
unsigned char adxlBuffer[243];
unsigned char bufferE[512];
unsigned char bufferR[512];
unsigned char banderInt;
unsigned int banderCont;

/*----------------------------------------------------------------------------
 FUNCTION PROTOTYPES
 -----------------------------------------------------------------------------*/

/*============================================================================
 FUNCTION MAIN
 =============================================================================*/
int main(void) {
    /* Variables Locales*/
    char valorX = 0;
    banderInt = 0;
    banderCont = 0;

    SYSTEM_Initialize();

    /*Encendemos el ADXL255*/
    ADXL355_Write_Byte(POWER_CTL, MEASURING);
    __delay_ms(250);

    while (1) {
        LATAbits.LATA0 ^= 1;

        if (banderInt) {

            valorX = dataCBuffer[0];  
            valorX = dataCBuffer[1];                                    
            valorX = dataCBuffer[2];                      

            banderInt = 0;
        }       
        
        __delay_ms(250);
    }

    return 0;
}



