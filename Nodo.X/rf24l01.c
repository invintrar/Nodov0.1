#include "rf24l01.h"

void RF24L01_init(void) {
    //Chip Select
    RF24L01_CS_SetDigitalOutput();
    RF24L01_CS_SetHigh();

    //CHIP ENABLE PARA TRANSMISION Y RECEPCION
    RF24L01_CE_SetDigitalOutput();
    RF24L01_CE_SetLow();

    //Iniciamos SPI
    if (banderaSPI1 != 1) {
        SPI1_Init();
    }
}

void RF24L01_send_command(uint8_t command) {
    //Chip select
    RF24L01_CS_SetLow();

    //Send command
    SPI1_Exchange_Byte(command);

    //Chip select
    RF24L01_CS_SetHigh();
}

uint8_t RF24L01_read_register(uint8_t register_addr) {
    uint8_t result;
    //Chip select -> Low
    RF24L01_CS_SetLow();

    //Send address and read command
    SPI1_Exchange_Byte(RF24L01_command_R_REGISTER | register_addr);

    //Get data
    result = SPI1_Exchange_Byte(0x00);

    //Chip select -> High
    RF24L01_CS_SetHigh();

    return result;
}

void RF24L01_write_register(uint8_t register_addr, uint8_t *value, uint8_t length) {
    uint8_t i;
    
    //Chip select -> Low
    RF24L01_CS_SetLow();

    //Send address and write command
    SPI1_Exchange_Byte(RF24L01_command_W_REGISTER | register_addr);

    //Send data  
    for (i = 0; i < length; i++) {
        SPI1_Exchange_Byte(value[i]);
    }

    //Chip select -> High
    RF24L01_CS_SetHigh();
}

void RF24L01_setup(uint8_t *tx_addr, uint8_t *rx_addr, uint8_t channel) {
    //CE -> Low
    RF24L01_CE_SetLow(); 

    RF24L01_reg_SETUP_AW_content SETUP_AW;
    *((uint8_t *) & SETUP_AW) = 0;
    SETUP_AW.AW = 0x03;
    RF24L01_write_register(RF24L01_reg_SETUP_AW, ((uint8_t *) & SETUP_AW), 1);

    RF24L01_write_register(RF24L01_reg_RX_ADDR_P0, rx_addr, 5);
    RF24L01_write_register(RF24L01_reg_TX_ADDR, tx_addr, 5);

    RF24L01_reg_EN_AA_content EN_AA;
    *((uint8_t *) & EN_AA) = 0;
    RF24L01_write_register(RF24L01_reg_EN_AA, ((uint8_t *) & EN_AA), 1);

    RF24L01_reg_EN_RXADDR_content RX_ADDR;
    *((uint8_t *) & RX_ADDR) = 0;
    RX_ADDR.ERX_P0 = 1;
    RF24L01_write_register(RF24L01_reg_EN_RXADDR, ((uint8_t *) & RX_ADDR), 1);

    RF24L01_reg_RF_CH_content RF_CH;
    *((uint8_t *) & RF_CH) = 0;
    RF_CH.RF_CH = channel;
    RF24L01_write_register(RF24L01_reg_RF_CH, ((uint8_t *) & RF_CH), 1);

    RF24L01_reg_RX_PW_P0_content RX_PW_P0;
    *((uint8_t *) & RX_PW_P0) = 0;
    RX_PW_P0.RX_PW_P0 = 0x20;//Carga util a usar de 32bytes
    RF24L01_write_register(RF24L01_reg_RX_PW_P0, ((uint8_t *) & RX_PW_P0), 1);

    RF24L01_reg_RF_SETUP_content RF_SETUP;
    *((uint8_t *) & RF_SETUP) = 0;
    RF_SETUP.RF_PWR = 0x03;//Potencia de salida 0dBm
    RF_SETUP.RF_DR = 0x01;//Air Data Rate 2Mbps
    RF_SETUP.LNA_HCURR = 0x01;//LNA gain
    RF24L01_write_register(RF24L01_reg_RF_SETUP, ((uint8_t *) & RF_SETUP), 1);

    RF24L01_reg_CONFIG_content config;
    *((uint8_t *) & config) = 0;
    config.PWR_UP = 0;//Power down 
    config.PRIM_RX = 1;//PRX (RX/TX Control)
    config.EN_CRC = 1;//Enable CRC
    config.MASK_MAX_RT = 0;//Reflect MAX_RT as active low interrupt on the IRQ pin
    config.MASK_TX_DS = 0;//Reflect TX_DS as active low interrupt on the IRQ pin
    config.MASK_RX_DR = 0;//
    RF24L01_write_register(RF24L01_reg_CONFIG, ((uint8_t *) & config), 1);
}

void RF24L01_set_mode_TX(void) {
    RF24L01_send_command(RF24L01_command_FLUSH_TX);

    //CE -> Low
    RF24L01_CE_SetLow();

    RF24L01_reg_CONFIG_content config;
    *((uint8_t *) & config) = 0;
    config.PWR_UP = 1;
    config.EN_CRC = 1;
    config.MASK_MAX_RT = 0;
    config.MASK_TX_DS = 0;
    config.MASK_RX_DR = 0;
    RF24L01_write_register(RF24L01_reg_CONFIG, ((uint8_t *) & config), 1);
}

void RF24L01_set_mode_RX(void) {
    RF24L01_reg_CONFIG_content config;
    *((uint8_t *) & config) = 0;
    config.PWR_UP = 1;
    config.PRIM_RX = 1;
    config.EN_CRC = 1;
    config.MASK_MAX_RT = 0;
    config.MASK_TX_DS = 0;
    config.MASK_RX_DR = 0;
    RF24L01_write_register(RF24L01_reg_CONFIG, ((uint8_t *) & config), 1);

    //Clear the status register to discard any data in the buffers
    RF24L01_reg_STATUS_content a;
    *((uint8_t *) & a) = 0;
    a.RX_DR = 1;
    a.MAX_RT = 1;
    a.TX_DS = 1;
    RF24L01_write_register(RF24L01_reg_STATUS, (uint8_t *) & a, 1);
    RF24L01_send_command(RF24L01_command_FLUSH_RX);

    //CE -> High
    RF24L01_CE_SetHigh(); 
}

RF24L01_reg_STATUS_content RF24L01_get_status(void) {
    uint8_t status;
    
    //Chip select -> Low
    RF24L01_CS_SetLow();

    //Send address and command
    SPI1_Exchange_Byte(RF24L01_command_NOP);
    status = SPI1_Exchange_Byte(0x00);

    //Chip select -> High
    RF24L01_CS_SetHigh();

    return *((RF24L01_reg_STATUS_content *) & status);
}

void RF24L01_write_payload(uint8_t *data, uint8_t length) {
    RF24L01_reg_STATUS_content a;
    uint8_t i;
    
    a = RF24L01_get_status();
    if (a.MAX_RT == 1) {
        //If MAX_RT, clears it so we can send data
        *((uint8_t *) & a) = 0;
        a.TX_DS = 1;
        RF24L01_write_register(RF24L01_reg_STATUS, (uint8_t *) & a, 1);
    }

    //Chip select -> Low 
    RF24L01_CS_SetLow();

    //Send address and command
    SPI1_Exchange_Byte(RF24L01_command_W_TX_PAYLOAD);

    //Send data
    for (i = 0; i < length; i++) {
        SPI1_Exchange_Byte(data[i]);
    }

    //Chip select -> High
    RF24L01_CS_SetHigh();

    //Generates an impulsion for CE to send the data
    RF24L01_CE_SetHigh();//CE -> High
    uint16_t delay = 0xFF;
    while (delay--);
    RF24L01_CE_SetLow();//CE -> Low
}

void RF24L01_read_payload(uint8_t *data, uint8_t length) {
    uint8_t i, status;
    //Chip select -> Low
    RF24L01_CS_SetLow();

    //Send address
    SPI1_Exchange_Byte(RF24L01_command_R_RX_PAYLOAD);
    status = SPI1_Exchange_Byte(0x00);

    //Get data
    for (i = 0; i < length; i++) {
        *(data++) = SPI1_Exchange_Byte(0x00);
    }

    //Chip select -> High
    RF24L01_CS_SetHigh();

    RF24L01_write_register(RF24L01_reg_STATUS, &status, 1);
    RF24L01_send_command(RF24L01_command_FLUSH_RX);
}

uint8_t RF24L01_was_data_sent(void) {
    RF24L01_reg_STATUS_content a;
    a = RF24L01_get_status();

    uint8_t res = 0;
    if (a.TX_DS) {
        res = 1;
    } else if (a.MAX_RT) {
        res = 2;
    }

    return res;
}

uint8_t RF24L01_is_data_available(void) {
    RF24L01_reg_STATUS_content a;
    a = RF24L01_get_status();
    return a.RX_DR;
}

void RF24L01_clear_interrupts(void) {
    RF24L01_reg_STATUS_content a;
    a = RF24L01_get_status();
    RF24L01_write_register(RF24L01_reg_STATUS, (uint8_t*) & a, 1);
}