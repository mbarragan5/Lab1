/*
* File:   leds.c
* Author:
*
* Created on December 27, 2014, 1:31 PM
*/

#include "p24FJ64GA002.h"
#include "leds.h"


void initLEDs()
{

    //TODO: Initialize the appropriate pins to work with the LEDs
    //Pins 2 and 3;
    TRISAbits.TRISA0 = 0; //LED1
    TRISAbits.TRISA1 = 0; //LED2

    ODCAbits.ODA0 = 1; //Open drain collector
    ODCAbits.ODA1 = 1;

    LED1 = ON;
    LED2 = OFF;
}

void initSW2()
{
    //TODO: Initialize the appropriate pins to work with the external switch using a
    //change notification interrupt.
     //pin 6

    TRISBbits.TRISB2 = 1;
    AD1PCFGbits.PCFG4 = 1;

    IFS1bits.CNIF = 0;

    //Enable the overall change notification interrupt
    IEC1bits.CNIE = 1;

    /* Enable the change notification interrupt for the switch 1 connected to
     * the development board. This corresponds to CN27 according to the PIC24F
     * datasheet. The internal pull-up should not be used for the switch
     * on the development board because one is already there.
     */
    CNEN1bits.CN6IE = 1;
    CNPU1bits.CN6PUE = 1; //pull up resistor
}

