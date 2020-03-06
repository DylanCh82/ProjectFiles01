/*
 * button.h
 *
 *  Created on: Jul 18, 2016
 *      Author: Eric Middleton
 *
 * @edit: Phillip Jones 05/30/2019 : Removed uneeded helper functions
 */

#ifndef DATA_H_
#define DATA_H_

#include <stdio.h>
#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include "cyBot_Scan.h"
#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART1)

extern char globaltestCommand;
extern int globalCybotOnline;
void cyBot_sendData(char[]);
int cyBot_followCommand(char);
double readDist_cm(double calibVal);


///Non-blocking call
///Returns highest value button being pressed, 0 if no button pressed
uint8_t button_getButton();


#endif /* BUTTON_H_ */
