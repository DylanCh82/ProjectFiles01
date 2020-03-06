/**
 * lab4_template.c
 *
 * Template file for CprE 288 lab 4
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 *
 * @author Phillip Jones, updated 6/4/2019
 */

#include "button.h"
#include "timer.h"
#include "lcd.h"
#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART1)
#include "adc.h"
#include "movement.h"
#include "uart.h"
#include "math.h" //added 3/3
#include "calibrate.h"

#include "cyBot_Scan.h"  // For scan sensors
#include "data.h"
#define REPLACEME 0
int globalCybotOnline = 1; // Acts as a switch to decide if we are connected to Cybot
char globaltestCommand;       //Varaible used for keyboard input testing

double autoCalib(oi_t *sensor_data);
double readDist_cm(double calibVal);

int main(void) {

	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
    button_init();
	cyBot_uart_init_clean();// Clean UART initialization, before running your UART GPIO init code
    oi_t *s_data = oi_alloc(); // do this only once at start of main()
    oi_init(s_data); // do this only once at start of main()
    uart_init();

    adc_init();


    //basically every time we run this(and especially on different cybots) the code will use a different function by calculating a different "calibAvg" value, which is the constant in the function.

    //(5*10^6)x^-1.769 <-- formula from Dylan

    //(2*10^7)x^-1.867 <-- formula from cybot 0(based on 80 points)

    //based on cybot 9: (10^7) * x ^ -1.783 <<<actual formula used in autoCalib() function (based on 50 points)

    char buffer1[50]; //main basically tests the two functions I wrote

    double c;

    c = autoCalib(s_data);


    timer_waitMillis(1000);

    int i;

        for(i = 0; i < 400; i++) {

        sprintf(buffer1, "Dist(cm): %lf\nQ: %ul", readDist_cm(c), adc_read());

        timer_waitMillis(100);

        //uart_sendStr(buffer1);
        lcd_printf("%s", buffer1);

        }

        oi_free(s_data); // do this once at end of main()

        return 0;

}
