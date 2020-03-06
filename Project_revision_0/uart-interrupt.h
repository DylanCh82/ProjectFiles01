///*
//*
//*   uart-interrupt.h
//*
//*   Used to set up the RS232 connector and WIFI module
//*   Uses RX interrupt
//*   Functions for communicating between CyBot and PC via UART1
//*   Serial parameters: Baud = 115200, 8 data bits, 1 stop bit,
//*   no parity, no flow control on COM1, FIFOs disabled on UART1
//*
//*   @author Dane Larson
//*   @date 07/18/2016
//*   Phillip Jones updated 9/2019, removed WiFi.h, Timer.h
//*   Diane Rover updated 2/2020, added interrupt code
//*/
//
//#ifndef UART_H_
//#define UART_H_
//
//#include <stdint.h>
//#include <stdio.h>
//#include <inc/tm4c123gh6pm.h>
//#include <stdbool.h>
//#include "driverlib/interrupt.h"
//#include <string.h>
////#include "uart.h"
//#include <stdint.h>
//#include "Timer.h"
//#include "lcd.h"
//#include "cyBot_Scan.h"  // For scan sensors
//#include "uart.h"
//#include <inc/tm4c123gh6pm.h>
//
//
//// Notice that interrupt.h provides library function prototypes for IntMasterEnable() and IntRegister()
//
//// The following externals are global variables defined in uart-interrupt-init.c for use with the interrupt handler.
//// Using extern here, the global variables become visible to other c files that include uart-interrupt-init.h
//// Extern does not allocate storage for a variable. It tells the compiler that the variable is defined in another file.
//extern volatile char receive_buffer[]; // buffer for characters received from PuTTY
//extern volatile int receive_index; // index to keep track of characters in buffer
//extern volatile char command_byte; // byte value for special character used as a command
//extern volatile int command_flag; // flag to tell the main program a special command was received
//extern volatile char port; // byte value for special character used as a command
//
////
////// Send a byte over UART1 from CyBot to PuTTY
//void uart_sendChar(volatile char data);
////
////// CyBot waits (i.e. blocks) to receive a byte from PuTTY
////// returns byte that was received by UART1
////char uart_receive(void);
//
////// Send a string over UART1
////// Sends each char in the string one at a time
//void uart_sendStr(volatile char *data);
////
//////  Send a string to the LCD
//////  Used for Part 1 of Lab 5
//void uart_sendChars_LCD(void);
//
//void uart_echoInput(char key);
//
//void uart_sendMessage(char command_Character);
//
//// UART1 device initialization for CyBot to PuTTY
//void uart_interrupt_init(char port);
//
//
//// CyBot waits (i.e. blocks) to receive a byte from PuTTY
//// returns byte that was received by UART1
//// Not used with interrupts; see UART1_Handler
//char uart_receive(void);
//
//// Interrupt handler for receive interrupts
//void UART0_Handler(void);
//
////
//void clearBuffer(volatile char *string);
//
//// Interrupt handler for receive interrupts
//void UART1_Handler(void);
//
//#endif /* UART_H_ */
