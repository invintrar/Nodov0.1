/*
 * File:   main.c
 * Author: Darwin y Joshe
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

unsigned char mutex;

typedef struct _data_to_send {
    uint32_t add;
    uint32_t sub;
    uint32_t mult;
    uint32_t div;
} data_to_sent;
data_to_sent to_send;

typedef struct _data_to_received {
    uint32_t op1;
    uint32_t op2;
} data_received;
data_received received;

/*----------------------------------------------------------------------------
 FUNCTION PROTOTYPES
 -----------------------------------------------------------------------------*/

/*============================================================================
 FUNCTION MAIN
 =============================================================================*/
int main(void) {
    /* Variables Locales*/
    unsigned char rx_addr[5] = {0x78, 0x78, 0x78, 0x78, 0x78};
    unsigned char tx_addr[5] = {0x78, 0x78, 0x78, 0x78, 0x78};

    unsigned int  j;

    banderInt1 = 1;
    banderCont = 0;
    banderaSPI1 = 0;
    sdF.detected = 0;
    sdF.init_ok = 0;
    sdF.saving = 0;
    sector = 2051;
    mutex = 0;

    SYSTEM_Initialize();

    /* Incializamos la variable de la memoria a 0*/
    for (j = 0; j < 512; j++) {
        bufferE[j] = 0;
    }

    //Configuramos  RF24L01
    RF24L01_setup(tx_addr, rx_addr, 12);

    /*Encendemos el ADXL255*/
    //ADXL355_Write_Byte(POWER_CTL, MEASURING);
    //__delay_ms(250);
    
    for (j = 0; j < 10; j++) {
        LED_rojo_toggle();
        __delay_ms(250);
    }

    LED_verde_setHigh();

    while (1) {

        mutex = 0;

        /*Set Mode RX*/
        RF24L01_set_mode_RX();
        
        /*Wait interrupt*/
        while (!mutex);
        if (mutex == 1) {
            unsigned char recv_data[32];
            RF24L01_read_payload(recv_data, sizeof(recv_data));
            received = *((data_received *) & recv_data);

            asm("nop"); //Place a breakpoint here to see memmory

        } else {
            //Something happened
            to_send.add = 0;
            to_send.div = 0;
            to_send.mult = 0;
            to_send.sub = 0;
        }
        unsigned short delay = 0xFFF;
        while (delay--);

        //Prepare the response
        to_send.add = received.op1 + received.op2;
        to_send.sub = received.op1 - received.op2;
        to_send.mult = received.op1 * received.op2;

        if (received.op2 != 0) {
            to_send.div = received.op1 / received.op2;
        } else {
            to_send.div = 1;
        }

        //Prepare the buffer to send from the data_to_send struct
        unsigned char buffer_to_send[32];


        *((data_to_sent *) & buffer_to_send) = to_send;
        
        mutex = 0;

        /*Set Mode TX*/
        RF24L01_set_mode_TX();

        /*Write Payload*/
        RF24L01_write_payload(buffer_to_send, sizeof(buffer_to_send));

        while (!mutex);
        if (mutex != 1) {
            //The transmission failed
            LED_verde_setLow();
        }else{
            LED_rojo_toggle();
        }
        __delay_ms(10);
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



