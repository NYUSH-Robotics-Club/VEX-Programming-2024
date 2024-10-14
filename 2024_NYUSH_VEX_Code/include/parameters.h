#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include "vex.h"

const float MOVEMENT_LOWER_LIMIT = 5;
const float JOYSTICK_DEADZONE = 5;
const float ADS = 0.4;

const float CHASSIS_GEAR_RATIO = 0.75;
const float WHEEL_DIAMETER = 2.75;
const float BASE_WIDTH_2 = 143;

const float ODOMETER_WHEEL_DIAMETER = 2;

const float BASE_FORWARD_PID[3] = {0.26, 0.1, 1.8};
const float BASE_ROTATE_PID[3] = {1.6, 0.1, 5.8};
const float A1_ROTATE_PID[3] = {5.5, 0.0, 1};
const float A2_ROTATE_PID[3] = {1.0, 0.0, 0};

#endif