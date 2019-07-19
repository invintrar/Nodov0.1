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
#include <stdio.h>
#include <stdbool.h> 
#include "lcd.h"

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
    char bufferX[512];

    SYSTEM_Initialize();

    LCD lcd = {&LATB, 15, 14, 13, 12, 11, 10}; // LAT?, RS, EN, D4, D5, D6, D7
    LCD_Init(lcd);

    /*Encendemos el ADXL255*/
    ADXL355_Write_Byte(POWER_CTL, MEASURING);
    __delay_ms(250);

    while (1) {
        LATAbits.LATA0 ^= 1;

        if (banderInt) {

            valorX = dataCBuffer[0];
            sprintf(bufferX, "Z3=%d ", valorX); //Convert to String
            LCD_SetCursor(2, 1);
            LCD_puts(bufferX);

            valorX = dataCBuffer[1];
            sprintf(bufferX, "Z2=%d ", valorX); //Convert to String
            LCD_SetCursor(1, 8);
            LCD_puts(bufferX);

            valorX = dataCBuffer[2];
            sprintf(bufferX, "Z1=%d ", valorX); //Convert to String
            LCD_SetCursor(1, 1);
            LCD_puts(bufferX);

            banderInt = 0;
        }

        sprintf(bufferX, "C=%d ", banderCont); //Convert to String
        LCD_SetCursor(2, 8);
        LCD_puts(bufferX);

        __delay_ms(250);
        LCD_Clear();
    }

    return 0;
}



