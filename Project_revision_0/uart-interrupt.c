/*
 *
 *   uart-interrupt.c
 *
 *
 *
 *   @Dylan Christensen
 *   @Feb 2020
 */

// The "???" placeholders should be the same as in your uart.c file.
// The "?????" placeholders are new in this file and must be replaced.
#include "uart-interrupt.h"
#include <stdint.h>
#include "Timer.h"
#include "lcd.h"
#include "cyBot_Scan.h"  // For scan sensors
//#include "uart.h"
// These variables are declared as examples for your use in the interrupt handler.
volatile char command_byte = -1; // byte value for special character used as a command
volatile int command_flag = 0; // flag to tell the main program a special command was received
volatile char receive_buffer[]; // buffer for characters received from PuTTY
volatile int receive_index = 0; // index to keep track of characters in buffer
//volatile char port = 'b';

//**************************************************************************************************
//**************************************************************************************************
//***********************************DON'T MODIFY BLOCK BEGIN***************************************
//**************************************************************************************************
//**************************************************************************************************

/**
 *	This	method	will	be	used	to	initialize UART1 (Port B) or UART0 (Port A).
 *	Created from modified CprE288 Lab 5 supplied code.
 *	@author	Dylan Christensen/Savva Zeglin
 *	@param	port	The port to be initialized
 *	@date	Spring 2020
 */

void uart_interrupt_init(char port) {
	//If we are using port B for UART1
	if (port == 'b') {
		//enable clock to GPIO port B
		SYSCTL_RCGCGPIO_R |= 0x02;

		//enable clock to UART1
		SYSCTL_RCGCUART_R |= 0x02;

		//wait for GPIOB and UART1 peripherals to be ready
		while ((SYSCTL_PRGPIO_R & 0x02) == 0) {
		};
		while ((SYSCTL_PRUART_R & 0x02) == 0) {
		};

		//enable alternate functions on port B pins
		GPIO_PORTB_AFSEL_R |= 0x03;

		//enable digital functionality on port B pins
		GPIO_PORTB_DEN_R |= 0x03;

		//enable UART1 Rx and Tx on port B pins
		GPIO_PORTB_PCTL_R |= 0x11;

		//calculate baud rate
		uint16_t iBRD = 0x8; //115200 baud
		uint16_t fBRD = 0x2C;

		//turn off UART1 while setting it up
		UART1_CTL_R &= 0xFFFFFFFE;

		//set baud rate
		//note: to take effect, there must be a write to LCRH after these assignments
		UART1_IBRD_R = iBRD;
		UART1_FBRD_R = fBRD;

		//set frame, 8 data bits, 1 stop bit, no parity, no FIFO
		//note: this write to LCRH must be after the BRD assignments
		UART1_LCRH_R |= 0x00000060;

		//use system clock as source
		//note from the datasheet UARTCCC register description:
		//field is 0 (system clock) by default on reset
		//Good to be explicit in your code
		UART1_CC_R = 0x0;

		//first clear RX interrupt flag (clear by writing 1 to ICR)
		UART1_ICR_R |= 0b00010000;

		//enable RX raw interrupts in interrupt mask register
		UART1_IM_R |= 0x10;

		//NVIC setup: set priority of UART1 interrupt to 1 in bits 21-23
		NVIC_PRI1_R = (NVIC_PRI1_R & 0xFF0FFFFF) | 0x00200000;

		//NVIC setup: enable interrupt for UART1, IRQ #6, set bit 6
		NVIC_EN0_R |= 0X40;

		//tell CPU to use ISR handler for UART1 (see interrupt.h file)
		//from system header file: #define INT_UART1 22
		IntRegister(INT_UART1, UART1_Handler);

		//globally allow CPU to service interrupts (see interrupt.h file)
		IntMasterEnable();

		//re-enable UART1 and also enable RX, TX (three bits)
		//note from the datasheet UARTCTL register description:
		//RX and TX are enabled by default on reset
		//Good to be explicit in your code
		UART1_CTL_R |= 0x00000301;
		//If we are using Port A for UART0. Needed for use with virtual COM port
	} else if (port == 'a') {	//add in code for the port A to test
		//enable clock to GPIO port A
		SYSCTL_RCGCGPIO_R |= 0x01;

		//enable clock to UART1
		SYSCTL_RCGCUART_R |= 0x01;

		//wait for GPIOA and UART0 peripherals to be ready
		while ((SYSCTL_PRGPIO_R & 0x01) == 0) {
		};
		while ((SYSCTL_PRUART_R & 0x01) == 0) {
		};

		//enable alternate functions on port A pins
		GPIO_PORTA_AFSEL_R |= 0x03;

		//enable digital functionality on port A pins
		GPIO_PORTA_DEN_R |= 0x03;

		//enable UART0 Rx and Tx on port A pins
		GPIO_PORTA_PCTL_R |= 0x11;

		uint16_t iBRD = 0x8; //115200 baud
		uint16_t fBRD = 0x2C;

		//turn off UART0 while setting it up
		UART0_CTL_R &= 0xFFFFFFFE;

		//set baud rate
		//note: to take effect, there must be a write to LCRH after these assignments
		UART0_IBRD_R = iBRD;
		UART0_FBRD_R = fBRD;

		//set frame, 8 data bits, 1 stop bit, no parity, no FIFO
		//note: this write to LCRH must be after the BRD assignments

		UART0_LCRH_R |= 0x00000060;

		//use system clock as source
		//note from the datasheet UARTCCC register description:
		//field is 0 (system clock) by default on reset
		//Good to be explicit in your code
		UART0_CC_R = 0x0;

		//first clear RX interrupt flag (clear by writing 1 to ICR)
		UART0_ICR_R |= 0b00010000;

		//enable RX raw interrupts in interrupt mask register
		UART0_IM_R |= 0x10;

		//check this next line
		//NVIC setup: set priority of UART0 interrupt to 1 in bits 13-15
		//                                62840
		NVIC_PRI1_R = (NVIC_PRI1_R & 0xFFFF0FFF) | 0x00002000;

		//check this nexty line
		//NVIC setup: enable interrupt for UART1, IRQ #6, set bit 6
		//assuming for UART0, IRQ#5, set bit 5
		NVIC_EN0_R |= 0X20;

		//tell CPU to use ISR handler for UART1 (see interrupt.h file)
		//from system header file: #define INT_UART0 22
		IntRegister(INT_UART0, UART0_Handler);

		//globally allow CPU to service interrupts (see interrupt.h file)
		IntMasterEnable();

		//re-enable UART1 and also enable RX, TX (three bits)
		//note from the datasheet UARTCTL register description:
		//RX and TX are enabled by default on reset
		//Good to be explicit in your code
		UART0_CTL_R |= 0x00000301;
	}
}

//**************************************************************************************************
//**************************************************************************************************
//*************************************DON'T MODIFY BLOCK END***************************************
//**************************************************************************************************
//**************************************************************************************************

/**
 *	This	method	will	be	used a single Char over UART1 (Port B) or UART0 (Port A).
 *	Created from modified CprE288 Lab 5 supplied code.
 *	@author	Dylan Christensen/Savva Zeglin
 *	@param	data	The byte to be sent over
 *	@date	Spring 2020
 */
void uart_sendChar(volatile char data) {
	switch (port) {
	case 'a': // code to be executed if we are using GPIO Port A
		while ((UART0_FR_R & 0x20) != 0) {
		}
		UART0_DR_R = data;
		break;
	case 'b': // code to be executed if we are using GPIO Port B
		while ((UART1_FR_R & 0x20) != 0) {
		}
		UART1_DR_R = data;
		break;
	default: // defaults to Port B if none specified
		while ((UART1_FR_R & 0x20) != 0) {
		}
		UART1_DR_R = data;
	}
}

//**************************************************************************************************
//**************************************************************************************************
//**************************************************************************************************
//**************************************************************************************************
/**
 *	This	method	will	be	used to send a string over the UART by calling uart_sendChar().
 *	Created from modified CprE288 Lab 5 supplied code.
 *	@author	Dylan Christensen/Savva Zeglin
 *	@param	*data	Pointer to the data (i.e. 1st element of the string)
 *	@date	Spring 2020
 */
void uart_sendStr(volatile char *data) {
	while (*data != '\0') {
		uart_sendChar(*data);
		data++;
	}
	uart_sendChar('\n');
	uart_sendChar('\r');
}

//**************************************************************************************************
//**************************************************************************************************
//**************************************************************************************************
//**************************************************************************************************
//This code needs updated for interrupts
//TODO: Update for interrupts
void uart_sendChars_LCD(void) {                   //clear screen
	lcd_printf("%s", receive_buffer);   //print string to lcd on robot
	command_flag = 0; //clear command since it ran
	return;

}

//**************************************************************************************************
//**************************************************************************************************
//**************************************************************************************************
//**************************************************************************************************
//This code needs modified for interrupts
void uart_echoInput(char key) {

	if (key == '\r') {

		uart_sendChar(key);
		uart_sendChar('\n');

	} else {

		uart_sendChar(key);

	}

}

//**************************************************************************************************
//**************************************************************************************************
//**************************************************************************************************
//**************************************************************************************************
void uart_sendMessage(char command_Character) {
	char message[30] = "";
	switch (command_Character) {
	case '2': // code to be executed if a;
		strcpy(message, "This is message a.\r\n");
		uart_sendStr(message);
		break;
	case '3': // code to be executed if b;
		strcpy(message, "This is message b.\r\n");
		uart_sendStr(message);
		break;
	case '4': // code to be executed if c;
		strcpy(message, "This is message c.\r\n");
		uart_sendStr(message);
		break;
	default: // code to be executed if n doesn't match any cases
		strcpy(message, "Command not understood.\r\n");
		uart_sendStr(message);
		return;
	}
}

//**************************************************************************************************
//**************************************************************************************************
//**************************************************************************************************
//**************************************************************************************************
// Interrupt handler for receive interrupts
void UART1_Handler(void) {
	char byte_received;
//check if handler called due to RX event
	if (UART1_MIS_R & 0x10) {
		//byte was received in the UART data register
		//clear the RX trigger flag (clear by writing 1 to ICR)
		UART1_ICR_R |= 0b00010000;

		//read the byte received from UART1_DR_R and echo it back to PuTTY
		//ignore the error bits in UART1_DR_R
		byte_received = UART1_DR_R;
		uart_sendChar(UART1_DR_R & 0xFF);

		//TODO: Clear out this into seperate function??? maybe
		//if byte received is a carriage return
		if (byte_received == '\r') {
			//send a newline character back to PuTTY

			uart_sendChar('\n');
			uart_sendStr(receive_buffer);
			//          clearBuffer(receive_buffer);
		} else {

			switch (byte_received) { //check if the byte we received was a special command character

			case '2': //test purposes a '2' will print to LCD on robot

				//uart_sendMessage(byte_received);
				command_flag = 2;
				uart_sendChars_LCD();
				//clearBuffer(receive_buffer);

				break;

			case '3': // test purposes will echo input
				uart_sendMessage(byte_received);
				command_flag = 3;
				//              clearBuffer(*receive_buffer);
				break;

			case '4': // code to be executed if 4;
				uart_sendMessage(byte_received);
				command_flag = 4;
				//              clearBuffer(*receive_buffer);
				break;

			case '5': // code to be executed if 5;
				command_flag = 5;
				//              clearBuffer(*receive_buffer);
				break;

			default: // code to be executed if n doesn't match any cases

				if (receive_index <= 20) {
					receive_buffer[receive_index] == byte_received; // buffer for characters received from PuTTY
					receive_index++;
				} else {
					receive_buffer[receive_index] = '\0';
					uart_sendStr(receive_buffer);
					receive_index = 0;
					//                  clearBuffer(*receive_buffer);
				}
			}

			if (byte_received == command_byte) {
				command_flag = 1;
			}
		}
	}
}

//**************************************************************************************************
//**************************************************************************************************
//**************************************************************************************************
//**************************************************************************************************

void clearBuffer(volatile char *string) {
	int i = 0;
	while (string[i] != '\0') {
		string[i] = 0;
		i++;
	}
}

/*
 #include<stdio.h>
 this worked on jdoodle
 void clearBuffer(volatile char *string)	{
 int i=0;
 while (string[i]!='\0'){
 string[i]=0;
 i++;}
 }
 int main() {
 volatile char receive_buffer[9];
 int x=10;
 int y=25;
 int z=x+y;
 int i=0;
 for (i=0; i<8; i++){
 receive_buffer[i]='i';}
 printf("%s", receive_buffer);
 clearBuffer(receive_buffer);
 printf("CLeand:%s", receive_buffer);
 }
 */

//**************************************************************************************************
//**************************************************************************************************
//**************************************************************************************************
//**************************************************************************************************
void UART0_Handler(void) {
	char byte_received;
//check if handler called due to RX event on UART0
	if (UART0_MIS_R & 0x10) {
		//byte was received in the UART data register
		//clear the RX trigger flag (clear by writing 1 to ICR)
		UART0_ICR_R |= 0b00010000;

		//read the byte received from UART1_DR_R and echo it back to PuTTY
		//ignore the error bits in UART1_DR_R
		byte_received = UART0_DR_R;
		uart_sendChar(UART0_DR_R & 0xFF);

//TODO: Clear out this into seperate function??? maybe
		//if byte received is a carriage return
		if (byte_received == '\r') {
			//send a newline character back to PuTTY

			uart_sendChar('\n');
			uart_sendStr(receive_buffer);
			clearBuffer(receive_buffer);
		} else {

			switch (byte_received) {//check if the byte we received was a special command character

			case '2': //test purposes a '2' will print to LCD on robot

				//clean up these statements probably change them to call a command function
				//uart_sendMessage(byte_received);
				command_flag = 2;
				uart_sendChars_LCD();
				//clearBuffer(receive_buffer);
				break;

			case '3': // test purposes will echo input
				uart_sendMessage(byte_received);
				command_flag = 3;
				clearBuffer(receive_buffer);
				break;

			case '4': // code to be executed if 4;
				uart_sendMessage(byte_received);
				command_flag = 4;
				clearBuffer(receive_buffer);
				break;

			case '5': // code to be executed if 5;
				command_flag = 5;
				clearBuffer(receive_buffer);
				break;

			default: // code to be executed if n doesn't match any cases

				if (receive_index <= 20) {
					receive_buffer[receive_index] == byte_received; // buffer for characters received from PuTTY
					receive_index++;
				} else {
					receive_buffer[receive_index] = '\0';
					uart_sendStr(receive_buffer);
					receive_index = 0;
					clearBuffer(receive_buffer);
				}
			}

			if (byte_received == command_byte) {
				command_flag = 1;
			}
		}
	}
}
