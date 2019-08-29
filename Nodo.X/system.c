#include "system.h"

void SYSTEM_Initialize(void)
{
    oscConfig();
    pines_Conf_Init();
    INTERRUPT_Initialize();
    EXT_INT_Initialize();
    
    SD_Check();
    if(sdF.detected==1){
        if(SD_Init()== SUCCESSFUL_INIT){
            SD_Led_Off();
        }        
    }
    
    INTERRUPT_GlobalEnable();
    //ADXL355_Init();
    RF24L01_init();
}

/**
 End of File
*/