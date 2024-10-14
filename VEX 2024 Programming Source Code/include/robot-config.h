#ifndef ROBOT_CONFIG_H_
#define ROBOT_CONFIG_H_
#include "vex.h"
using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;

extern motor Motor_BaseLF;
extern motor Motor_BaseLB;
extern motor Motor_BaseRF;
extern motor Motor_BaseRB;
extern motor Motor_Intaker;
extern pneumatics Piston_Mantis[2];
extern inertial IMU;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
#endif