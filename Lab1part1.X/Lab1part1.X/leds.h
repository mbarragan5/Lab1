/*
* File:   leds.h
* Author:
*
* Created on December 27, 2014, 1:31 PM
*/

#ifndef LEDS_H
#define	LEDS_H

#define LED1 LATBbits.LATB2
#define LED2 LATBbits.LATB3

#define OFF 1;
#define ON 0;

#define PRESSED 0
#define RELEASED 1

void initLEDs();
void initSW2();

#endif	/* LEDS_H */

