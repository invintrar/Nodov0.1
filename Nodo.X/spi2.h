#ifndef SPI2_H

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
#define	SPI2_H

/*Elegir velocidad en la transmisión*/
#define FAST 1//Frecuencia reloj 5Mhz
#define SLOW 0//Frecuencia reloj 312.5kHz

/*----------------------------------------------------------------------------
 FUCTION PROTOTYPES
 -----------------------------------------------------------------------------*/


/**
 * @param Velocidad: FAST = 2Mhz or SLOW = 312.5kHz 
 */
void SPI2_Init(unsigned char);

/**
 * @param  Dato a enviar
 * @return Dato recibido
 */
uint8_t SPI2_Exchange_Byte(uint8_t data);

/**
 * 
 * @param Dato a enviar
 * @return Dato recibido
 */
uint8_t SPI2_Write(uint8_t data);


#endif
/*END*/
