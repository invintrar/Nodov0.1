#include "system.h"

void SYSTEM_Initialize(void)
{
    oscConfig();
    pines_Conf_Init();
    INTERRUPT_Initialize();
    EXT_INT_Initialize();
    INTERRUPT_GlobalEnable();
    ADXL355_Init();
}

/**
 End of File
*/