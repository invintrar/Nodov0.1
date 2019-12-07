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
#include <libpic30.h>//

#define Led_verde_setHigh()     _LATA1 = 1
#define Led_verde_setLow()      _LATA1 = 0
#define Led_verde_toggle()      _LATA1 ^= 1


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