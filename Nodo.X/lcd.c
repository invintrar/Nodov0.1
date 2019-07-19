/*----------------------------------------------------------------------------
 HEADER FILES
 -----------------------------------------------------------------------------*/
#include "lcd.h"

/*----------------------------------------------------------------------------
 VARIABLE DECLARATIONS
 -----------------------------------------------------------------------------*/
LCD lcd;

/*----------------------------------------------------------------------------
 FUNCTION 
 -----------------------------------------------------------------------------*/
void LCD_Init(LCD display) {

    lcd = display;

    if (lcd.PIN == &LATA) {
        TRISA &= ~(1 << lcd.D7);
        TRISA &= ~(1 << lcd.D6);
        TRISA &= ~(1 << lcd.D5);
        TRISA &= ~(1 << lcd.D4);
        TRISA &= ~(1 << lcd.EN);
        TRISA &= ~(1 << lcd.RS);
    } else if (lcd.PIN == &LATB) {
        TRISB &= ~(1 << lcd.D7);
        TRISB &= ~(1 << lcd.D6);
        TRISB &= ~(1 << lcd.D5);
        TRISB &= ~(1 << lcd.D4);
        TRISB &= ~(1 << lcd.EN);
        TRISB &= ~(1 << lcd.RS);
    }
    // Give some time to the LCD to start function properly
    __delay_ms(20);

    // Send reset signal to the LCD
    LCD_Write(0x03);
    __delay_ms(5);
    LCD_Write(0x03);
    __delay_ms(16);
    LCD_Write(0x03);

    // Specify the data lenght to 4 bits
    LCD_Write(0x02);

    // Set interface data length to 8 bits, number of display lines to 2 and font to 5x8 dots
    LCD_Cmd(0x28);

    // Set cursor to move from left to right
    LCD_Cmd(0x06);

    LCD_Display(True, False, False); // Turn on display and set cursor off

    LCD_Clear();
}

void LCD_Out(char c) {
    if (c & 1) {
        *(lcd.PIN) |= 1 << lcd.D4;
    } else {
        *(lcd.PIN) &= ~(1 << lcd.D4);
    }

    if (c & 2) {
        *(lcd.PIN) |= 1 << lcd.D5;
    } else {
        *(lcd.PIN) &= ~(1 << lcd.D5);
    }

    if (c & 4) {
        *(lcd.PIN) |= 1 << lcd.D6;
    } else {
        *(lcd.PIN) &= ~(1 << lcd.D6);
    }

    if (c & 8) {
        *(lcd.PIN) |= 1 << lcd.D7;
    } else {
        *(lcd.PIN) &= ~(1 << lcd.D7);
    }
}

void LCD_Write(unsigned char c) {

    *(lcd.PIN) &= ~(1 << lcd.RS); // => RS = 0
    LCD_Out(c);

    *(lcd.PIN) |= 1 << lcd.EN; // => E = 1
    __delay_ms(4);
    *(lcd.PIN) &= ~(1 << lcd.EN); // => E = 0

}

void LCD_putc(char c) {
    *(lcd.PIN) |= 1 << lcd.RS; // => RS = 1
    LCD_Out((c & 0xF0) >> 4); //Data transfer

    *(lcd.PIN) |= 1 << lcd.EN;
    __delay_us(40);
    *(lcd.PIN) &= ~(1 << lcd.EN);

    LCD_Out(c & 0x0F);

    *(lcd.PIN) |= 1 << lcd.EN;
    __delay_us(40);
    *(lcd.PIN) &= ~(1 << lcd.EN);

}

void LCD_puts(char *a) {
    int i;
    for (i = 0; a[i] != '\0'; ++i) {
        LCD_putc(a[i]);
    }

}

void LCD_putrs(const char *a) {
    int i;

    for (i = 0; a[i] != '\0'; ++i) {
        LCD_putc(a[i]);
    }

}

void LCD_SetCursor(char x, char y) {
    if (x == 1) {
        LCD_Cmd(0x80 + (y - 1));
    } else if (x == 2) {
        LCD_Cmd(0xC0 + (y - 1));
    } else if (x == 3) {
        LCD_Cmd(0x94 + (y - 1));
    } else if (x == 4) {
        LCD_Cmd(0xD4 + (y - 1));
    }

}

void LCD_Display(char on, char cursor, char blink) {
    unsigned char cmd = 0x08;
    if (on == 1) {
        cmd |= 1 << 2;
    }

    if (cursor == 1) {
        cmd |= 1 << 1;
    }

    if (blink == 1) {
        cmd |= 1;
    }

    LCD_Cmd(cmd);
}

void LCD_Cmd(char c) {
    LCD_Write((c & 0xF0) >> 4);
    LCD_Write(c & 0x0F);
}
/*----------------------------------------------------------------------------
 END FILE
 -----------------------------------------------------------------------------*/