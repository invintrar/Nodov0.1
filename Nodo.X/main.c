/*
 * File:   main.c
 * Author: Darwin
 *
 * Created on June 26, 2019, 12:15 AM
 */

/*----------------------------------------------------------------------------
 HEADER FILES
 -----------------------------------------------------------------------------*/
#include "main.h"

/*----------------------------------------------------------------------------
 VARIABLE GLOBALES
 -----------------------------------------------------------------------------*/
unsigned char bufferE[512];
unsigned char bufferR[512];
unsigned char banderInt1;
unsigned char banderaSPI1;
unsigned int banderCont;
unsigned long sector;
int ADCValue;
float voltajeSensor;

unsigned char mutex;

typedef struct _data_to_send {
    uint32_t resp;
} data_to_sent;
data_to_sent to_send;

typedef struct _data_to_received {
    uint32_t recv0;
    uint32_t recv1;
} data_received;
data_received received;

/*----------------------------------------------------------------------------
 FUNCTION PROTOTYPES
 -----------------------------------------------------------------------------*/

/*============================================================================
 FUNCTION MAIN
 =============================================================================*/
int main(void) {
    /* Direction RX*/
    //unsigned char rx_addr[5] = {0x78, 0x78, 0x78, 0x78, 0x78};
    //unsigned char tx_addr[5] = {0x78, 0x78, 0x78, 0x78, 0x78};

    banderInt1 = 1;
    banderCont = 0;
    banderaSPI1 = 0;
    sdF.detected = 0;
    sdF.init_ok = 0;
    sdF.saving = 0;
    int i;
    //int continuar = 0;
    sector = 2051;
    mutex = 0;

    SYSTEM_Initialize();

    /* Incializamos la variable de la memoria a 0*/
    for (i = 0; i < 512; i++) {
        bufferE[i] = 0xAA;
    }

    //Configuramos  RF24L01
    //RF24L01_setup(tx_addr, rx_addr, 12);

    /*Encendemos el ADXL255*/
    //ADXL355_Write_Byte(POWER_CTL, MEASURING);
    //__delay_ms(250);

    while (1) {
        mutex = 0;

        LED_rojo_toggle();

        AD1CON1bits.SAMP = 1; // Start sampling
        __delay_us(10); // Wait for sampling time (10 us)
        AD1CON1bits.SAMP = 0; // Start the conversion
        while (!AD1CON1bits.DONE); // Wait for the conversion to complete
        ADCValue = ADC1BUF0; // Read the ADC conversion result
        voltajeSensor = ADCValue * (3.3/1023);
        /*
        while(continuar < 511){
            bufferE[continuar] = (ADCValue & 0x00FF);
            bufferE[continuar+1] = (ADCValue >> 8);
            continuar += 2;
        }
         */
        
        /*Comprobamos que la microSD siga conectada*/
        SD_Check();
        if (sdF.detected) {
            /* Compromabos si esta inicializamos*/
            if (!sdF.init_ok) {
                /* Inicializamos microSD*/
                if (SD_Init() == SUCCESSFUL_INIT) {
                    sdF.init_ok = 1;
                    SD_Led_On();
                }
            }
            SD_Write_Block(bufferE, sector);
            sector++;
        } else {
            SD_Led_Off();
        }

        __delay_ms(250);

        /*Set Mode RX*/
        //RF24L01_set_mode_RX();

        /*Wait interrupt*/
        //while (!mutex);
        //if (mutex == 1) {
        //  unsigned char recv_data[32];
        //RF24L01_read_payload(recv_data, sizeof (recv_data));
        //received = *((data_received *) & recv_data);

        //asm("nop"); //Place a breakpoint here to see memmory

        //} else {
        //Something happened
        //  to_send.resp = 0;
        //}
        //unsigned short delay = 0xFFF;
        //while (delay--);

        /*
         * PREPARE THE RESPONSE
         */

        //Prepare the buffer to send from the data_to_send struct
        //unsigned char buffer_to_send[32];
        //for (i = 0; i < 32; i++) {
        //  buffer_to_send[i] = 0xAA;
        //}


        //*((data_to_sent *) & buffer_to_send) = to_send;

        //mutex = 0;

        /*Set Mode TX*/
        //RF24L01_set_mode_TX();

        /*Write Payload*/
        //RF24L01_write_payload(buffer_to_send, sizeof (buffer_to_send));

        //while (!mutex);
        //if (mutex != 1) {
        //The transmission failed
        //  LED_verde_setLow();
        //} else {
        //  LED_rojo_toggle();
        //}
        //__delay_ms(10);
        /*
                if (banderInt1 == 0) {
                    for (j = 0; j < 63; j++) {
                        bufferE[i] = dataCBuffer[j];
                        if (i < 512) {
                            i++;
                        } else {
                            if (sector > 975871)
                                break;
                            SD_Write_Block(bufferE, sector);
                            i = 0;
                            sector++;
                        }
                    }
                    banderInt1 = 1;
                }*/

    }

    return 0;
}
