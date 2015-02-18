/*
 * File:   lcd.c
 * Authors:
 *
 * Created on December 31, 2014, 1:39 PM
 */

#include "p24fj64ga002.h"
#include "lcd.h"
#include "timer.h"
#define OUT 0
#define IN 1
#define LCD_DATA   LATB
#define LCD_RS  LATBbits.LATB7
#define LCD_E   LATBbits.LATB6

#define TRIS_D7  TRISBbits.TRISB15
#define TRIS_D6  TRISBbits.TRISB14
#define TRIS_D5  TRISBbits.TRISB13
#define TRIS_D4  TRISBbits.TRISB12
#define TRIS_RS  TRISBbits.TRISB7
#define TRIS_E   TRISBbits.TRISB6

#define LCD_WRITE_DATA    1
#define LCD_WRITE_CONTROL 0

#define LOWER 1
#define UPPER 0

/* This function should take in a two-byte word and writes either the lower or upper
 * byte to the last four bits of LATB. Additionally, according to the LCD data sheet
 * It should set LCD_RS and LCD_E with the appropriate values and delays.
 * After these commands are issued, there should be a delay.
 * The command type is a simplification. From the data sheet, the RS is '1'
 * when you are simply writing a character. Otherwise, RS is '0'.
 */
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower)
{
    if(lower){
        LCD_DATA=(0x0FFF & LCD_DATA) | ((word & 0x0F)<<12);
    }
   else{
         LCD_DATA=(0x0FFF & LCD_DATA) | ((word & 0xF0)<<8);
   }
    LCD_RS = commandType; delayUs(1);
    LCD_E = 1;  delayUs(1); //minimum 230 ns
    LCD_E = 0;  delayUs(1);
    delayUs(delayAfter);
}

/* Using writeFourBits, this function should write the two bytes of a character
 * to the LCD.
 */
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter)
{
    //TODO:
    writeFourBits(word, commandType, delayAfter, UPPER);
    writeFourBits(word, commandType, delayAfter, LOWER);
}

/* Given a character, write it to the LCD. RS should be set to the appropriate value.
 */
void printCharLCD(char c)
{
    //TODO:
    writeLCD(c, LCD_WRITE_DATA, 46);
}
/*Initialize the LCD
 */
void initLCD(void)
{
    int i = 0;
    // Setup D, RS, and E to be outputs (0).
    TRIS_D7 = OUT;
    TRIS_D6 = OUT;
    TRIS_D5 = OUT;
    TRIS_D4 = OUT;
    TRIS_RS = OUT;
    TRIS_E = OUT;

    LCD_DATA = (LCD_DATA & 0x0FFF) | 0x0000;
    LCD_RS = 0;
    LCD_E = 0;

    for(i = 0; i < 15; i++)//initial delay for 15ms
    {
        delayUs(1000);
    }

    writeFourBits(0x03,0,4100,LOWER);

    writeFourBits(0x03,0,100,LOWER);

    writeLCD(0x32,0,100);

    writeLCD(0x28,0,40);
    writeLCD(0x08,0,40);

    writeLCD(0x01,0,1500);

    writeLCD(0x06,0,40);
    writeLCD(0x0C,0,40);
    delayUs(100);

    //Finished first Part


    // Initilization sequence utilizes specific LCD commands before the general configuration
    // commands can be utilized. The first few initilition commands cannot be done using the
    // WriteLCD function. Additionally, the specific sequence and timing is very important.


    // Enable 4-bit interface

    // Function Set (specifies data width, lines, and font.

    // 4-bit mode initialization is complete. We can now configure the various LCD
    // options to control how the LCD will function.
    // TODO: Display On/Off Control
        // Turn Display (D) Off

    // TODO: Clear Display (The delay is not specified in the data sheet at this point. You really need to have the clear display delay here.

    // TODO: Entry Mode Set
        // Set Increment Display, No Shift (i.e. cursor move)
    // TODO: Display On/Off Control
        // Turn Display (D) On, Cursor (C) Off, and Blink(B) Off
}

/*
 * You can use printCharLCD here. Note that every time you write a character
 * the cursor increments its position automatically.
 * Since a string is just a character array, try to be clever with your use of pointers.
 */
void printStringLCD(const char* s)
{
    //TODO:
    while(*s != 0)
    {
        printCharLCD(*s);
        *s++;

    }
}

/*
 * Clear the display.
 */
void clearLCD()
{
    writeLCD(0x01,0,1500);
}

/*
 Use the command for changing the DD RAM address to put the cursor somewhere.
 */
void moveCursorLCD(unsigned char x, unsigned char y)
{
    unsigned char row;
    unsigned char value = 0x80;
    row = 0x40*x;
    value = value|row;
    value = value|y;

    writeLCD(value,0,40);

}

char getChar(int value)
{
    char out;

    if(value == 0)
    {
        out = '0';
    }
    else if(value == 1)
    {
        out = '1';
    }
    else if(value == 2)
    {
        out = '2';
    }
    else if(value == 3)
    {
        out = '3';
    }
    else if(value == 4)
    {
        out = '4';
    }
    else if(value == 5)
    {
        out = '5';
    }
    else if(value == 6)
    {
        out = '6';
    }
    else if(value == 7)
    {
        out = '7';
    }
    else if(value == 8)
    {
        out = '8';
    }
    else if(value == 9)
    {
        out = '9';
    }

    return out;
}

void getTimeString(int time)
{
    int mill;
    int sec;
    int min;

    char M1;
    char M2;
    char S1;
    char S2;
    char F1;
    char F2;

    mill = time%60;
    time = time/60;
    sec = time%60;
    min = time/60;

    M1 = getChar(min/10);
    moveCursorLCD(1, 0);
    printCharLCD(M1);

    M2 = getChar(min%10);
    moveCursorLCD(1, 1);
    printCharLCD(M2);

    moveCursorLCD(1, 2);
    printCharLCD(':');

    S1 = getChar(sec/10);
    moveCursorLCD(1, 3);
    printCharLCD(S1);

    S2 = getChar(sec%10);
    moveCursorLCD(1, 4);
    printCharLCD(S2);

    moveCursorLCD(1, 5);
    printCharLCD(':');

    F1 = getChar(mill/10);
    moveCursorLCD(1, 6);
    printCharLCD(F1);

    F2 = getChar(mill%10);
    moveCursorLCD(1, 7);
    printCharLCD(F2);

}



/*
 * This function is called in lab1p2.c for testing purposes.
 * If everything is working properly, you should get this to look like the video on D2L
 * However, it is suggested that you test more than just this one function.
 */
void testLCD()
{
    int i;
    initLCD();
    printCharLCD('c');

    for(i = 0; i < 1000; i++) delayUs(1000);
    clearLCD();
    moveCursorLCD(0, 0);
    printStringLCD("Hello!");
    moveCursorLCD(1, 2);
    for(i = 0; i < 1000; i++) delayUs(1000);
    printStringLCD("Hello!");
    for(i = 0; i < 1000; i++) delayUs(1000);
}

