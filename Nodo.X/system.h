#ifndef SYSTEM_H
#define	SYSTEM_H

#include "pines_conf.h"
#include "osc.h"
#include "adxl355.h"
#include "sdcard.h"
#include "interrupt_manager.h"
#include "ext_int.h"
#include "rf24l01.h"
#include "spi1.h"
#include "spi2.h"
#include "adc1.h"

/*----------------------------------------------------------------------------
 FUNCTION PROTOTYPE
 -----------------------------------------------------------------------------*/

void SYSTEM_Initialize(void);

#endif	/* SYSTEM_H */
/**
 End of File
 */