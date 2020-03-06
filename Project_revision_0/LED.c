/*
 * LED.c
 *
 *  Created on: Feb 8, 2020
 *      Author: Dylan
 *      Function used in LAB 3 to set the LED status
 */

#include "button.h"
#include "REF_tm4c123gh6pm.h"
#include <stdio.h>


void LED_init() {

    //****************************************************************************************
    //****************************************************************************************
    //****************************************************************************************
    //DID NOT CHANGE ANYTHING IN THIS BLOCK (UNTIL NEXT **** LINES!!!)************************
    static uint8_t initialized = 0;

    //Check if already initialized
    if(initialized){
        return;
    }


    // delete warning after implementing

    // Reading: To initialize and configure GPIO PORTE, visit pg. 656 in the
    // Tiva datasheet.

    // Follow steps in 10.3 for initialization and configuration. Some steps
    // have been outlined below.

    // Ignore all other steps in initialization and configuration that are not
    // listed below. You will learn more about additional steps in a later lab.

    // 1) Turn on PORTE system clock, do not modify other clock enables


    //SYSCTL_RCGCGPIO_R |= THE HEX DIGIT CORRESPONDING TO PROT E TURN ON BIT 4 SHOULD BE HEX 8
    SYSCTL_RCGCGPIO_R |= 0x00000010;
    // You may need to add a delay here of several clock cycles for the clock to start, e.g., execute a simple dummy assignment statement, such as "long delay = SYSCTL_RCGCGPIO_R".
    long delay = SYSCTL_RCGCGPIO_R;
  // Instead, use the PRGPIO register and busy-wait on the peripheral ready bit for PORTE.
   //((SYSCTL_PRGPIO_R & 0x??) == 0) {};
    //****************************************************************************************
    //****************************************************************************************
    //****************************************************************************************

    // 2) Set the buttons as inputs, do not modify other PORTE wires

     GPIO_PORTE_DIR_R |= 0x00000001;    //SET BIT 1 AS OUTPUT

    // 3) Enable digital functionality for button inputs,
    //    do not modify other PORTE enables
     GPIO_PORTE_DEN_R |= 0x00000001;    //DIGITAL ENABLE BIT 1
     GPIO_PORTE_DATA_R |= 0x00000001;   //INITIALIZE LED TO OFF
    initialized = 1;
}

void LED_setLED(ledSwitch) {
        if (ledSwitch == 0) {   //If we get a 0 input to the function we set BIT 1 to a zero, turning on the LED
            printf("ON\n");//human-readable to console
            fflush (stdout);//human-readable to console
            GPIO_PORTE_DATA_R &= (0x11111110);
        } else {
            GPIO_PORTE_DATA_R |= (0x00000001);  //If we dont get the turn on LED signal we turn LED off by setting bit 1 to a 1
            printf("OFF\n");//human-readable to console
            fflush (stdout);//human-readable to console
        }
}
