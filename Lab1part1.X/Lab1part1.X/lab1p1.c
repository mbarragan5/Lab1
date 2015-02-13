// ******************************************************************************************* //
//
// File:         lab1p1.c
// Date:
// Authors:
//
// Description: Part 1 for lab 1
// ******************************************************************************************* //

#include "p24FJ64GA002.h"
#include "leds.h"
#include "timer.h"
#include <stdio.h>


_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_ON & COE_OFF & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )

// ******************************************************************************************* //

#define DELAY 10000

typedef enum stateTypeEnum
{
    //TODO: Define states by name
    RUN,
    RUNDELAY,
    STOP,
    STOPDELAY
} stateType;

volatile stateType currentState;

int main(void)
{
    initLEDs();
    initSW2();

    currentState = RUN;

    while(1)
    {
        //TODO: Using a finite-state machine, define the behavior of the LEDs
        switch(currentState)
        {
            case RUN:
            {
                LED1 = ON;
                LED2 = OFF;
                break;
            }

            case RUNDELAY:
            {
                delayUs(DELAY);
                currentState = STOP;
                break;
            }

            case STOP:
            {
                LED1 = OFF;
                LED2 = ON;
                break;
            }

            case STOPDELAY:
            {
                delayUs(DELAY);
                currentState = RUN;
                break;
            }

        }
        //Debounce the switch
    }

    return 0;
}

void _ISR _CNInterrupt(void)
{
    //TODO: Implement the interrupt to capture the press of the button
    IFS1bits.CNIF = 0;

    if(PORTBbits.RB2 == RELEASED)
    {
        if(currentState == RUN)
        {
            currentState = RUNDELAY;
        }

        else if(currentState == STOP)
        {
            currentState = STOPDELAY;
        }
    }

}
