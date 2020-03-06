/*
 * calibrate.c
 *
 *  Created on: Mar 6, 2020
 *      Author: dylan1
 */
double autoCalib(oi_t *sensor_data) { //Set CyBot 9cm away from wall to calibrate

    //EQUATION: y = (calibAve) * (sensorReading) ^ -1.8

    unsigned long genOut;
    double calibInc;
    double calibAvg;

    int j;

    calibAvg = 0;

    for (j = 9; j <= 50 ; j+=2) { //starting at 9cm, goes to 50 in 1cm increments collecting data on calib

        genOut = adc_read();
        timer_waitMillis(200);
        move_backward(sensor_data, 20); //correction value 0.77358491 for our move function???
        timer_waitMillis(300);

        calibInc = j * pow(genOut, 1.8); //to change the formula, basically change this value(1.783) in both functions

        calibAvg+=calibInc;


        }
        calibAvg /= 21;

        return calibAvg; //this function returns a value who's basically only purpose is to be used as a param in the readDist_cm funciton.
}



