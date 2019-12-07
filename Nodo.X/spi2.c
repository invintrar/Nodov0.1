/*----------------------------------------------------------------------------
 HEADER FILES
 -----------------------------------------------------------------------------*/
#include "spi2.h"

/*----------------------------------------------------------------------------
 FUNCTION PROTOTYPES
 -----------------------------------------------------------------------------*/

void SPI2_Exchange(uint8_t *pTransmitData, uint8_t *pReceiveData);

/*----------------------------------------------------------------------------
 FUNCTIONS
 -----------------------------------------------------------------------------*/

void SPI2_Init(unsigned char speed) {
    SPI2STATbits.SPIEN = 0;
    if (speed == FAST) {
        /*40MHz /(4*4) = 2.5MHz*/
        SPI2CON1 =  0x232; //0x13A
    } else {
        /*40MHz / (2*64) =0.3125Mhz = 312.5kHz*/
        SPI2CON1 = 0x338; //0x138;
    }
    SPI2CON2 = 0x0000;
    SPI2STAT = 0x8000;
}

void SPI2_Exchange(uint8_t *pTransmitData, uint8_t *pReceiveData) {

    while (SPI2STATbits.SPITBF == true) {

    }

    SPI2BUF = *((uint8_t*) pTransmitData);

    while (SPI2STATbits.SPIRBF == false);

    *((uint8_t*) pReceiveData) = SPI2BUF;

}

uint8_t SPI2_Exchange_Byte(uint8_t data) {
    uint8_t receiveData;

    SPI2_Exchange(&data, &receiveData);

    return (receiveData);
}
