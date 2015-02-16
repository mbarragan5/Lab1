/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include "p24FJ64GA002.h"
#include "timer.h"

#define FCY 14745600
#define MICRO_SECOND 14 //1 mircosecond

//Uses timer

void delayUs(unsigned int delay)
{
    //TODO: Create a delay using timer 2 for "delay" microseconds.
    PR2 = delay * MICRO_SECOND;
    TMR2 = 0; //According to the datasheet this should be reset automatically, but it does not sometimes.
    T2CONbits.TCKPS = 0b00; //prescalar 1
    IFS0bits.T2IF = 0; // Timer 2 interrupt flag down
    T2CONbits.TON = 1; // Turn timer 2 on

    // Wait until the timer 2 interrupt flag goes up. This is done in hardware.
    while(IFS0bits.T2IF == 0);//try setting to one

    IFS0bits.T2IF = 0; // Put the flag down afterwards.
    T2CONbits.TON = 0; // Turn the timer off so it does not keep counting.
}
