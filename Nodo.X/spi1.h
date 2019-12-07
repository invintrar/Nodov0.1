#ifndef SPI1_H

/*----------------------------------------------------------------------------
 HEADER FILES
 -----------------------------------------------------------------------------*/
#include <xc.h>
#include <stdint.h>//Integer Types
#include <stdbool.h>//Boolean type and values

/*----------------------------------------------------------------------------
 PROGRAM CONSTANTS
 ----------------------------------------------------------------------------*/
#define	SPI1_H
/*Elegir velocidad en la transmisión*/
#define FAST 1//Frecuencia reloj 5Mhz
#define SLOW 0//Frecuencia reloj 312.5kHz
/*----------------------------------------------------------------------------
 FUCTION PROTOTYPES
 -----------------------------------------------------------------------------*/

void SPI1_Init(void);


/**
 * @param Velocidad: FAST= 5Mhz or SLOW=312.5kHz 
 */
void SD_SPI1_Init(unsigned char);

/**
 * @param  Dato a enviar
 * @return Dato recibido
 */
uint8_t SPI1_Exchange_Byte(uint8_t data);

#endif
/*END*/
