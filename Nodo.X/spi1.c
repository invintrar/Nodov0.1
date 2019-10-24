/*----------------------------------------------------------------------------
 HEADER FILES
 -----------------------------------------------------------------------------*/
#include "spi1.h"

/*----------------------------------------------------------------------------
 FUNCTION PROTOTYPES
 -----------------------------------------------------------------------------*/

void SPI1_Exchange(uint8_t *pTransmitData, uint8_t *pReceiveData);

/*----------------------------------------------------------------------------
 FUNCTIONS
 -----------------------------------------------------------------------------*/

void SPI1_Init() {
    SPI1STATbits.SPIEN = 0;
    /* 
     * FCY = 40 Mhz
     * Fosc spi = 40Mhz/(1*16) =2.5Mhz
     * MSTEN Master; DISSDO disabled; SPRE 1:1(0b111); PPRE 16:1(0b01); MODE16 disabled; 
     * SMP Middle; DISSCK disabled; CKP Idle:Low, Active:High; 
     * CKE Active to Idle;
     *  SSEN disabled.*/
    SPI1CON1 = 0x13D;
    /* SPIFSD disabled; SPIBEN disabled; FRMPOL disabled; FRMDLY disabled;
     *  FRMEN disabled.*/
    SPI1CON2 = 0x00;
    // SISEL SPI_INT_SPIRBF; SPIROV disabled; SPIEN enabled; SPISIDL disabled.
    SPI1STAT = 0x8000;
}

void SPI1_Exchange(uint8_t *pTransmitData, uint8_t *pReceiveData) {

    while (SPI1STATbits.SPITBF == true) {

    }

    SPI1BUF = *((uint8_t*) pTransmitData);

    while (SPI1STATbits.SPIRBF == false);

    *((uint8_t*) pReceiveData) = SPI1BUF;

}

uint8_t SPI1_Exchange_Byte(uint8_t data) {
    uint8_t receiveData;

    SPI1_Exchange(&data, &receiveData);

    return (receiveData);
}
/*End SPI1*/