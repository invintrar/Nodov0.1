#ifndef SPI1_H

/*----------------------------------------------------------------------------
 HEADER FILES
 -----------------------------------------------------------------------------*/
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*----------------------------------------------------------------------------
 PROGRAM CONSTANTS
 ----------------------------------------------------------------------------*/
#define	SPI1_H
#define SS1_SetDigitalOutput()  _TRISB0 = 0
#define SD_SS1_Toggle()         _LATB0 ^= 1 
#define SD_SS1_SetLow()         _LATB0 = 0
#define SD_SS1_SetHigh()        _LATB0 = 1
#define ADXL355_CS_Toggle()     _LATB1 ^= 1 
#define ADXL355_CS_SetLow()     _LATB1 = 0
#define ADXL355_CS_SetHigh()    _LATB1 = 1

/*Elegir velocidad en la transmisión*/
#define FAST 1//Frecuencia reloj 5Mhz
#define SLOW 0//Frecuencia reloj 312.5kHz


/*----------------------------------------------------------------------------
 FUCTION PROTOTYPES
 -----------------------------------------------------------------------------*/

void ADXL355_SPI1_Init(void);

/**
 * @param Velocidad: FAST= 5Mhz or SLOW=312.5kHz 
 */
void SD_SPI1_Init(unsigned char);

/**
 * @param  Dato a enviar
 * @return Dato recibido
 */
uint8_t SPI1_Exchange_Byte(uint8_t data);

/**
 * 
 * @param Dato a enviar
 * @return Dato recibido
 */
uint8_t SPI1_Write(uint8_t data);


#endif
/*END*/
