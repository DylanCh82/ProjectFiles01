///*
// *
// *   uart.c
// *
// *
// *
// *   @author
// *   @date
// */
//
////#include "uart.h"
//#include <stdint.h>
//#include "Timer.h"
//#include "lcd.h"
//#include "cyBot_Scan.h"  // For scan sensors
//#include "uart.h"
//volatile char port = 'b';
//
//void uart_init(void) {
//
//
//	if (port == 'b') {
//		//enable clock to GPIO port B
//		SYSCTL_RCGCGPIO_R |= 0x02;
//
//		//enable clock to UART1
//		SYSCTL_RCGCUART_R |= 0x02;
//
//		//wait for GPIOB and UART1 peripherals to be ready
//		while ((SYSCTL_PRGPIO_R & 0x02) == 0) {
//		};
//		while ((SYSCTL_PRUART_R & 0x02) == 0) {
//		};
//
//		//enable alternate functions on port B pins
//		GPIO_PORTB_AFSEL_R |= 0x03;
//
//		//enable digital functionality on port B pins
//		GPIO_PORTB_DEN_R |= 0x03;
//
//		//enable UART1 Rx and Tx on port B pins
//		GPIO_PORTB_PCTL_R |= 0x11;
//
//		//calculate baud rate 9600 baud
//		//uint16_t iBRD = 0x64; //104
//		//uint16_t fBRD = 0x0B; //11
//
//		uint16_t iBRD = 0x8; //115200 baud
//		uint16_t fBRD = 0x2C;
//
//		//turn off UART1 while setting it up
//		UART1_CTL_R &= 0xFFFFFFFE;
//
//		//set baud rate
//		//note: to take effect, there must be a write to LCRH after these assignments
//		UART1_IBRD_R = iBRD;
//		UART1_FBRD_R = fBRD;
//
//		//set frame, 8 data bits, 1 stop bit, no parity, no FIFO
//		//note: this write to LCRH must be after the BRD assignments
//
//		UART1_LCRH_R |= 0x00000060;
////  UART1_LCRH_R &= 0xFFFFFF60;
//
//		//use system clock as source
//		//note from the datasheet UARTCCC register description:
//		//field is 0 (system clock) by default on reset
//		//Good to be explicit in your code
//		UART1_CC_R = 0x0;
//
//		//re-enable UART1 and also enable RX, TX (three bits)
//		//note from the datasheet UARTCTL register description:
//		//RX and TX are enabled by default on reset
//		//Good to be explicit in your code
//		UART1_CTL_R |= 0x00000301;
//
//	} else if (port == 'a') {
//		//enable clock to GPIO port A
//		SYSCTL_RCGCGPIO_R |= 0x01;
//
//		//enable clock to UART1
//		SYSCTL_RCGCUART_R |= 0x01;
//
//		//wait for GPIOB and UART1 peripherals to be ready
//		while ((SYSCTL_PRGPIO_R & 0x01) == 0) {
//		};
//		while ((SYSCTL_PRUART_R & 0x01) == 0) {
//		};
//
//		//enable alternate functions on port A pins
//		GPIO_PORTA_AFSEL_R |= 0x03;
//
//		//enable digital functionality on port A pins
//		GPIO_PORTA_DEN_R |= 0x03;
//
//		//enable UART1 Rx and Tx on port A pins
//		GPIO_PORTA_PCTL_R |= 0x11;
//
//		//calculate baud rate 9600 baud
//		//uint16_t iBRD = 0x64; //104
//		//uint16_t fBRD = 0x0B; //11
//
//		uint16_t iBRD = 0x8; //115200 baud
//		uint16_t fBRD = 0x2C;
//
//		//turn off UART1 while setting it up
//		UART0_CTL_R &= 0xFFFFFFFE;
//
//		//set baud rate
//		//note: to take effect, there must be a write to LCRH after these assignments
//		UART0_IBRD_R = iBRD;
//		UART0_FBRD_R = fBRD;
//
//		//set frame, 8 data bits, 1 stop bit, no parity, no FIFO
//		//note: this write to LCRH must be after the BRD assignments
//
//		UART0_LCRH_R |= 0x00000060;
////  UART1_LCRH_R &= 0xFFFFFF60;
//
//		//use system clock as source
//		//note from the datasheet UARTCCC register description:
//		//field is 0 (system clock) by default on reset
//		//Good to be explicit in your code
//		UART0_CC_R = 0x0;
//
//		//re-enable UART1 and also enable RX, TX (three bits)
//		//note from the datasheet UARTCTL register description:
//		//RX and TX are enabled by default on reset
//		//Good to be explicit in your code
//		UART0_CTL_R |= 0x00000301;
//
//	}
//}
//
//void uart_sendChar(char data) {
//
//	//This line polls for when the flag register is ready
//	//to send data
//	switch (port) {
//	case 'a': // code to be executed if n = 1;
//		while ((UART0_FR_R & 0x20) != 0) {
//		}
//		UART0_DR_R = data;
//		break;
//	case 'b': // code to be executed if n = 2;
//		while ((UART1_FR_R & 0x20) != 0) {
//		}
//		UART1_DR_R = data;
//		break;
//	default: // code to be executed if n doesn't match any cases
//		while ((UART1_FR_R & 0x20) != 0) {
//		}
//		UART1_DR_R = data;
//	}
//	//while((UART1_FR_R & 0x20) != 0) {}
//	//UART1_DR_R = data;
//}
//
//char uart_receive(void) {
//	uint32_t get;
//	char data;
////past ie
//	switch (port) {
//	case 'a':
//		while ((UART0_FR_R & 0x10) != 0) {
//		}
//		get = UART0_DR_R;
//		if (get & 0xF00) {
//			GPIO_PORTA_DATA_R = 0xF;
//		} else {
//			data = (char) (UART0_DR_R & 0xFF);
//		}
//		return data;
//	case 'b':
//		while ((UART1_FR_R & 0x10) != 0) {
//		}
//		get = UART1_DR_R;
//		if (get & 0xF00) {
//			GPIO_PORTB_DATA_R = 0xF;
//		} else {
//			data = (char) (UART1_DR_R & 0xFF);
//		}
//		return data;
//	default: // code to be executed if n doesn't match any cases
//		while ((UART1_FR_R & 0x10) != 0) {
//		}
//		get = UART1_DR_R;
//		if (get & 0xF00) {
//			GPIO_PORTB_DATA_R = 0xF;
//		} else {
//			data = (char) (UART1_DR_R & 0xFF);
//		}
//		return data;
//	}
//	//end past
////	while((UART1_FR_R & 0x10) != 0) {}
////	get = UART1_DR_R;
////	if (get & 0xF00) {
////	    GPIO_PORTB_DATA_R = 0xF;
////	} else {
////	    data = (char)(UART1_DR_R & 0xFF);
////	}
////	return data;
//}
//
//void uart_sendStr(char *data) {
//
//	while (*data != '\0') {
//		uart_sendChar(*data);
//		data++;
//	}
//	uart_sendChar('\n');
//	uart_sendChar('\r');
//}
//
//void uart_sendChars_LCD(void) {
//	char string[21] = "                     ";     //create string of whitespace
//	int i;                                          //looping counter
//
//	//looping to get the message from Putty
//	for (i = 0; i < 20; i++) { //set up for reading 20 characters and then printing
//		char recievedChar = uart_receive();     //waiting for input from putty
//
//		if (recievedChar == '\r') {     //checking if ENTER was pressed
//			string[i] = '\0';           //add null terminator to string
//			//uart_sendStr(string);     //send to uart(Putty)
//			lcd_clear();                    //clear screen
//			lcd_printf("%s", string);   //print string to lcd on robot
//			return;                     //ENTER was recieved so exit
//		}
//
//		string[i] = recievedChar;       //add char to string
//		lcd_clear();                    //clear screen
//		lcd_printf("%d\t%c", i + 1, recievedChar); //print number of and char to screen
//	}
//
//	string[i + 1] = '\0';     //add null terminator
//	//uart_sendStr(string);     //sent to uart(Putty)
//	lcd_clear();                    //clear screen
//	lcd_printf("%s", string);   //print string to lcd on robot
//	return;
//
//}
//
//void uart_echoInput(void) {
//	char key = ' ';
//	key = uart_receive();
//	if (key == '\r') {
//
//		uart_sendChar(key);
//		uart_sendChar('\n');
//
//	} else {
//
//		uart_sendChar(key);
//
//	}
//
//}
//
//void uart_sendMessage(char command_Character) {
//	char message[30] = "";
//	switch (command_Character) {
//	case 'a': // code to be executed if n = a;
//		strcpy(message, "This is message A.");
//		uart_sendStr(message);
//		break;
//	case 'b': // code to be executed if n = b;
//		strcpy(message, "This is message B.");
//		uart_sendStr(message);
//		break;
//	case 'c': // code to be executed if n = c;
//		strcpy(message, "This is message C.");
//		uart_sendStr(message);
//		break;
//	default: // code to be executed if n doesn't match any cases
//		strcpy(message, "Command not understood.");
//		uart_sendStr(message);
//		return;
//	}
//}
