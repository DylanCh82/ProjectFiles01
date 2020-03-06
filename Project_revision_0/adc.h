/*
 * adc.h
 *
 *  Created on: Mar 1, 2016
 *      Author: nbergman
 */

#ifndef ADC_H_
#define ADC_H_

//#define IS_STEPPER_BOARD
//#define IS_STEPPER_BOARD

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include "Timer.h"

void adc_init (void);
unsigned long adc_read (void);

#endif /* ADC_H_ */
