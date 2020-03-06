/*
 * data.c
 *

 */




#include "data.h"


void cyBot_sendData(char string[]){
    int i = 0;

    if (1){      //Do this if connected to cybot
        while (string[i] != '\0') {
            cyBot_sendByte(string[i]);
            i++;
        }
        cyBot_sendByte('\0');
        cyBot_sendByte('\n');
        cyBot_sendByte('\r');
    } else{
        printf("%s", string);
    }
}


int cyBot_followCommand(char command){

    if (1) { //globalCybotOnline doesn't seem to be set to 1 at this point     //Do this if connected to cybot
        if (command=='m'){

            //cyBOT_init_Scan();

            cyBOT_Scan_t scanData;

           char buffer[500];
            int i = 0;

            while (i <= 180){

                cyBOT_Scan(i, &scanData);
                timer_waitMillis(100);

                sprintf(buffer, "%d\t%f\t%d\t\0", i, scanData.sound_dist, scanData.IR_raw_val);

                cyBot_sendData(buffer);
                i+=5;
            }
        }
    } else{
        if (command=='m'){
            int i=0;
            float dataIR = -3.0;
            float dataSONAR = 0.0;
            for(i=0; i<=180;i+=5){
                //do some stuff
                char buffer [50];
                sprintf(buffer, "%d\t%f\t%f\t\n",i, dataSONAR, dataIR );
                cyBot_sendData(buffer);
                //timer_waitMillis(500);
                dataIR +=0.168;
                dataSONAR +=.1;
            }
        }
    }
    return 0;
}
double readDist_cm(double calibVal) { //return type is double, could be set to int and then just round the double in the function before returning.

    unsigned long genOutAvg;
    double est;


    genOutAvg = 0;

    int i;
    for (i = 0; i < 8; i++) {
        genOutAvg += adc_read();

        timer_waitMillis(100);
    }
    genOutAvg /= 8;

    est = calibVal / pow(genOutAvg, 1.8); //to change the formula, basically change this value(1.783) in both functions //1.825
    est += pow(est - 29.5, 2) / 240; //actual spaghetti code. basically my function gets values off by -2cm at the extremes(9cm and 50cm), so this function """""fixes""""" that

    return est; //this function reads once, although in main I make it read multiple times.
}
