#include "system.h"

void SYSTEM_Initialize(void)
{
    oscConfig();
    
    pines_Conf_Init();
    
    SPI1_Init();
    
    INTERRUPT_Initialize();
    
    EXT_INT_Initialize();
    
    INTERRUPT_GlobalEnable();
    
    /*Inicializamos el modulo ADC1*/
    Adc1_Init();
    
    /*Comprobamos que este conecto una microSD y si lo esta la inicilizamos*/
    SD_Check();
    if(sdF.detected==1){
        /* Inicializamos y si es exitoso encedemos el Led,
         * actualizamos la bandera*/
        if(SD_Init()== SUCCESSFUL_INIT){
            sdF.init_ok = 1;
            SD_Led_On();
        }       
    }
    
    /* Inicializamos el acelerometro*/
    //ADXL355_Init();
    
    /* Inicializamos el modulo nRF24L01*/
    //RF24L01_init();
}

/**
 End of File
*/