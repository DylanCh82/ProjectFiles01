#include "open_interface.h"

turn_right(oi_t*sensor_data, double degrees);
turn_left(oi_t*sensor_data, double degrees);

int baseSpeed = 50; //speed of wheels
int idiotLight = 1000; //delay for Dylan
double movementAdjust = 0.872;

move_forward(oi_t*sensor_data, double distance_mm) {
//debug comments
//  lcd_init();
//  lcd_printf("Inside move_forward");
    double sum = 0; // distance member in oi_t struct is type double
    double distance_traveled = 0;
               oi_setWheels(-baseSpeed,-baseSpeed);
               while (distance_traveled < distance_mm * movementAdjust) {
                   oi_update(sensor_data);
                   distance_traveled += sensor_data -> distance;
               }
               oi_setWheels(0,0);
               distance_traveled = 0;
    oi_setWheels(0,0); //stop
    return sensor_data -> distance;
 }

move_backward(oi_t*sensor_data, double distance_mm) {
//debug comments
//  lcd_init();
//  lcd_printf("Inside move_forward");
    double sum = 0; // distance member in oi_t struct is type double
    double distance_traveled = 0;
               oi_setWheels(-baseSpeed,-baseSpeed);
               while (distance_traveled > (-1) * distance_mm * movementAdjust) {
                   oi_update(sensor_data);
                   distance_traveled += sensor_data -> distance;
               }
               oi_setWheels(0,0);
               distance_traveled = 0;
    oi_setWheels(0,0); //stop
    return sensor_data -> distance;
 }

turn_right(oi_t*sensor_data, double degrees) {

    double sum = 0;

    oi_setWheels(-baseSpeed, baseSpeed);
    while ((-1) * sum < degrees - 14.5) {
               oi_update(sensor_data);
               sum += sensor_data -> angle; // use -> notation since pointer
//lcd_printf("I just moved %fmms!",sensor_data -> angle);
    }

    oi_setWheels(0,0);
}

turn_left(oi_t*sensor_data, double degrees) {

    double sum = 0;

    oi_setWheels(baseSpeed, -baseSpeed);
    while (sum < degrees - 14.5) {
               oi_update(sensor_data);
               sum += sensor_data -> angle; // use -> notation since pointer
// lcd_printf("I just moved %fmms!",sensor_data -> angle);
    }

    oi_setWheels(0,0);
}
