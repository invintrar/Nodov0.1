/*----------------------------------------------------------------------------
 HEADER FILES
 -----------------------------------------------------------------------------*/
#include <xc.h>
#include <stdio.h>
#include "pines_conf.h"

/*----------------------------------------------------------------------------
 PROGRAM CONSTANTS
 -----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 FUNCTIONS
 -----------------------------------------------------------------------------*/

void pines_Conf_Init() {
    /**************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     **************************************************************************/
    ANSELA = 0x0001;
    ANSELB = 0x0000;

    /**************************************************************************
     * Setting the Output Latch SFR(s)
     **************************************************************************/
    LATA = 0x0000;
    LATB = 0x0042;

    /**************************************************************************
     * Setting the GPIO Direction SFR(s)
     **************************************************************************/
    TRISA = 0x001D;
    TRISB = 0x1218;

    /**************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     **************************************************************************/
    CNPDA = 0x0000;
    CNPDB = 0x0000;
    CNPUA = 0x0000;
    CNPUB = 0x0000;

    /**************************************************************************
     * Setting the Open Drain SFR(s)
     **************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0000;



    /****************************************************************************
     * Set the PPS
     ***************************************************************************/
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS

    /* Pines de Interrupción externa*/
    RPINR0bits.INT1R = 0x0024; //RB4->EXT_INT:INT1
    RPINR1bits.INT2R = 0x0014; //RA4->EXT_INT:INT2

    /* Pines SPI2 */
    RPOR4bits.RP42R = 0x0009; //RB10->SPI2:SCK2
    RPOR4bits.RP43R = 0x0008; //RB11->SPI2:SDO2

    RPINR22bits.SDI2R = 0x002C; //RB12->SPI2:SDI2


    __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS




}



