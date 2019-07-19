#ifndef LCD_H
/*----------------------------------------------------------------------------
 HEADER FILES
 -----------------------------------------------------------------------------*/
#include "main.h"

/*----------------------------------------------------------------------------
 PROGRAM CONSTANTS
 -----------------------------------------------------------------------------*/
#define	LCD_H
#define LCD_Clear()                 LCD_Cmd(0x01)
#define LCD_Decrement_Cursor()      LCD_Cmd(0x04)
#define LCD_Increment_Cursor()      LCD_Cmd(0x05)
#define LCD_Shift_Display_Right()   LCD_Cmd(0x06)
#define LCD_Shift_Display_Left()    LCD_Cmd(0x07)
#define LCD_Shift_Right()           LCD_Cmd(0x1C)
#define LCD_Shift_Left()            LCD_Cmd(0x18)
#define True                        1
#define False                       0

/*----------------------------------------------------------------------------
 VARIABLE DECLARATIONS
 -----------------------------------------------------------------------------*/
#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct {
        volatile uint16_t * PIN; // Pointer to the LCD port e.g &PORTC
        unsigned char RS; // The RS bit of the LCD PORT e.g. 2
        unsigned char EN; // The EN bit of the LCD PORT e.g. 3
        unsigned char D4; // The D4 bit of the LCD PORT e.g. 4
        unsigned char D5; // The D5 bit of the LCD PORT e.g. 5
        unsigned char D6; // The D6 bit of the LCD PORT e.g. 6
        unsigned char D7; // The D7 bit of the LCD PORT e.g. 7
    } LCD;

    extern LCD lcd;



/*----------------------------------------------------------------------------
 FUNCTION PROTOTYPES
 -----------------------------------------------------------------------------*/
    /*Inicializacion LCD*/
    void LCD_Init();

    // Prints a character on the LCD
    void LCD_putc(char a);

    // Prints a string on the LCD that is allocated on the RAM
    void LCD_puts(char *a);

    // Prints a string on the LCD that is allocated on the program memory
    void LCD_putrs(const char *a);

    // [Internal use only] Write a byte to the LCD
    void LCD_Write(unsigned char c);

    // [Internal use only] Outputs the data to the LCD Port
    void LCD_Out(char a);

    void LCD_SetCursor(char, char);

    void LCD_Display(char, char, char);

    void LCD_Cmd(char c);

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

