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
unsigned char bufferE[512];
unsigned char bufferR[512];
unsigned char banderInt1;
unsigned int banderCont;
unsigned long sector;

/*----------------------------------------------------------------------------
 FUNCTION PROTOTYPES
 -----------------------------------------------------------------------------*/

/*============================================================================
 FUNCTION MAIN
 =============================================================================*/
int main(void) {
    /* Variables Locales*/
    unsigned int i, j;
    banderInt1 = 1;
    banderCont = 0;
    sector = 0x0803;

    SYSTEM_Initialize();

    /*Encendemos el ADXL255*/
    ADXL355_Write_Byte(POWER_CTL, MEASURING);
    __delay_ms(250);

    while (1) {
        LATAbits.LATA0 ^= 1;
        //SD_Check();
        /*
        if ( banderInt1) {
            for (j = 0; j < 63; j++) {
                bufferE[i] = dataCBuffer[j];
                if (i < 512) {
                    i++;
                } else {
                    SD_Write_Block(bufferE, sector);
                    i = 0;
                    sector++;
                }

            }
            banderInt1 = 1;
        }
         */
         
        __delay_ms(250);
    }

    return 0;
}



