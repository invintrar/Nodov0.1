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
#define SS2_SetDigitalOutput()  _TRISB6 = 0
#define SS2_SetDigitalInput()   _TRISB6 = 1
#define SD_SS_Toggle()          _LATB6 ^= 1 
#define SD_SS_SetLow()          _LATB6 = 0
#define SD_SS_SetHigh()         _LATB6 = 1

#define CD_SetDigitalOutput()   _TRISB13 = 0
#define CD_SetDigitalInput()    _TRISB6 = 0
#define SD_CD_Toggle()          _LATB13 ^= 1 
#define SD_CD_SetLow()          _LATB13 = 0
#define SD_CD_SetHigh()         _LATB13 = 1


/*Elegir velocidad en la transmisión*/
#define FAST 1//Frecuencia reloj 5Mhz
#define SLOW 0//Frecuencia reloj 312.5kHz


/*----------------------------------------------------------------------------
 FUCTION PROTOTYPES
 -----------------------------------------------------------------------------*/

/**
 * @param Velocidad: FAST= 5Mhz or SLOW=312.5kHz 
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
