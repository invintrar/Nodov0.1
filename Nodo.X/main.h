#ifndef MAIN_H
/*------------------------------------------------------------------------------
 HEADER FILES
 -----------------------------------------------------------------------------*/
#include "system.h"
#include <stdint.h>
/*------------------------------------------------------------------------------
 PROGRAM CONSTANTS
 -----------------------------------------------------------------------------*/
#define MAIN_H
#define FCY 40000000
#include <libpic30.h>
#define LED_verde_setHigh()     _LATA0 = 1
#define LED_verde_setLow()      _LATA0 = 0

/*------------------------------------------------------------------------------
 VARIABLE DECLARATIONS
 -----------------------------------------------------------------------------*/
extern unsigned char banderInt1;
extern unsigned char banderaSPI1;
extern unsigned int banderCont;
extern unsigned long sector;

extern uint8_t mutex;

/*----------------------------------------------------------------------------
 FUNCTION PROTOTYPES
 -----------------------------------------------------------------------------*/

#endif
/* END FILE*/