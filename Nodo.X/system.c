#include "system.h"

void SYSTEM_Initialize(void)
{
    oscConfig();
    
    pines_Conf_Init();
    
    SPI1_Init();
    
    INTERRUPT_Initialize();
    
    EXT_INT_Initialize();
    
    /*Comprobamos que este conecto una microSD*/
    SD_Check();
    if(sdF.detected==1){
        /* Inicializamos y si es exitoso encedemos el Led,
         * actualizamos la bandera*/
        if(SD_Init()== SUCCESSFUL_INIT){
            sdF.init_ok = 1;
            SD_Led_On();
        }       
    }
    
    INTERRUPT_GlobalEnable();
    
    //ADXL355_Init();
    
    RF24L01_init();
}

/**
 End of File
*/