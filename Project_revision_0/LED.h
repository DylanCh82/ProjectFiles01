/*
 * LED.h
 *
 *  Created on: Feb 8, 2020
 *      Author: Dylan
 */

#ifndef LED_H_
#define LED_H_

#include <stdint.h>
#include <inc/tm4c123gh6pm.h>

//initialize the push buttons
void LED_init();


///Non-blocking call
///Returns highest value button being pressed, 0 if no button pressed
void LED_setLED(int ledSwitch);






#endif /* LED_H_ */
