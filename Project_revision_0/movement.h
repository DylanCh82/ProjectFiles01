/*
 * movement.h
 *
 *  Created on: Jan 30, 2020
 *      Author: dylan1
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_
#include "open_interface.h"

double move_forward(oi_t*sensor_data, double distance_mm);
double move_backward(oi_t*sensor_data, double distance_mm);
turn_right(oi_t*sensor_data, double degrees);
turn_left(oi_t*sensor_data, double degrees);





#endif /* MOVEMENT_H_ */
