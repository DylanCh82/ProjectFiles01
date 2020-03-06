///*
//*
//*   uart.h
//*
//*   Used to set up the RS232 connector and WIFI module
//*   Functions for communicating between CyBot and PC via UART1
//*   Serial parameters: Baud = 115200, 8 data bits, 1 stop bit,
//*   no parity, no flow control on COM1, FIFOs disabled on UART1
//*
//*   @author Dane Larson
//*   @date 07/18/2016
//*   Phillip Jones updated 9/2019, removed WiFi.h, Timer.h
//*   Diane Rover updated 2/2020, changed receive return type to char
//*/
//
//#ifndef UART_H_
//#define UART_H_
//
//#include <string.h>
////#include "uart.h"
//#include <stdint.h>
//#include "Timer.h"
//#include "lcd.h"
//#include "cyBot_Scan.h"  // For scan sensors
//#include "uart.h"
//#include <inc/tm4c123gh6pm.h>
//
//extern volatile char port; // byte value for special character used as a command
////extern volatile int command_flag; // flag to tell the main program a special command was received
//// UART1 device initialization for CyBot to PuTTY
//void uart_init(void);
//
//// Send a byte over UART1 from CyBot to PuTTY
//void uart_sendChar(char data);
//
//// CyBot waits (i.e. blocks) to receive a byte from PuTTY
//// returns byte that was received by UART1
//char uart_receive(void);
//
//// Send a string over UART1
//// Sends each char in the string one at a time
//void uart_sendStr(char *data);
//
////  Send a string to the LCD
////  Used for Part 1 of Lab 5
//void uart_sendChars_LCD(void);
//
////Echo input from Putty
////Used for Part 2 of Lab 5
///**
//*   This    method  will    be  used    to  echo input from putty back to the terminal.
//*   @author first_name last_name
//*   @param  angle_turned_cm The angle   the robot   turned  in  cm
//*   @date   Month/Day/Year
//*/
//void uart_echoInput(void);
//
////Echo input from Putty
////Used for Part 2 of Lab 5
///**
//*   This    method  will    be  used    to  send various messages to the terminal based on recieved commands.
//*   @author first_name last_name
//*   @param  command_Character
//*   @date   Month/Day/Year
//*/
//void uart_sendMessage(char command_Character);
//
//
//#endif /* UART_H_ */
