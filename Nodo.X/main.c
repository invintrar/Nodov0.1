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
    unsigned char rx_addr[5] = {0x04, 0xAD, 0x45, 0x98, 0x51};
    unsigned char tx_addr[5] = {0x44, 0x88, 0xBA, 0xBE, 0x42};
    
    SYSTEM_Initialize();

    unsigned int i = 0, j;

    banderInt1 = 1;
    banderCont = 0;
    banderaSPI1 = 0;
    sdF.detected = 0;
    sdF.init_ok = 0;
    sdF.saving = 0;
    sector = 2051;

    for (j = 0; j < 512; j++) {
        bufferE[j] = 0;
    }

    RF24L01_setup(tx_addr, rx_addr, 12);//Configuramos  RF24L01

    /*Encendemos el ADXL255*/
    ADXL355_Write_Byte(POWER_CTL, MEASURING);
    __delay_ms(250);

    while (1) {
        LED_verde_setHigh();
        mutex = 0;
        RF24L01_set_mode_RX();
        while (!mutex);
        if (mutex == 1) {
            unsigned char recv_data[32];
            RF24L01_read_payload(recv_data, 32);
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
        to_send.div = received.op1 / received.op2;

        //Prepare the buffer to send from the data_to_send struct
        unsigned char buffer_to_send[32];
        for (i = 0; i < 32; i++) {
            buffer_to_send[i] = 0;
        }

        *((data_to_sent *) & buffer_to_send) = to_send;
        mutex = 0;
        RF24L01_set_mode_TX();
        RF24L01_write_payload(buffer_to_send, 32);
        
        LED_verde_setLow();
        
        while (!mutex);
        if (mutex != 1) {
            //The transmission failed
            LED_verde_setLow();
        }

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
        }
    }

    return 0;
}



