#include "vex.h"
#include "basic-functions.h"
#include "parameters.h"
#include <queue>
#include "math-tools.h"
#include "sensors.h"

static float left_pos_last = 0, right_pos_last = 0;

/**
 * powers all motors on left side of base with duty cycle _input%
 * @param _input ranges from -100 : 100
*/
void moveLeft(float _input) {
  if (fabs(_input) > 100) _input = sign(_input) * 100;
  Motor_BaseLF.spin(directionType::fwd, (int)127 * _input, voltageUnits::mV);
  Motor_BaseLB.spin(directionType::fwd, (int)127 * _input, voltageUnits::mV);
}

void moveLeftVel(float _input) {
  // _input ranges from -100 : 100
  // powers all motors on left side of base with duty cycle _input%
  if (fabs(_input) > 100) _input = sign(_input) * 100;
  Motor_BaseLF.spin(directionType::fwd, (int)_input, velocityUnits::pct);
  Motor_BaseLB.spin(directionType::fwd, (int) _input, velocityUnits::pct);
}

/**
 * locks all motors on left side of base
*/
void lockLeft(void) {
  Motor_BaseLF.stop(vex::brakeType::hold);
  Motor_BaseLB.stop(vex::brakeType::hold);
}

/**
 * unlocks all motors on left side of base
*/
void unlockLeft(void) {
  Motor_BaseLF.stop(vex::brakeType::coast);
  Motor_BaseLB.stop(vex::brakeType::coast);
}

/**
 * powers all motors on right side of base with duty cycle _input%
 * @param _input ranges from -100 : 100
*/
void moveRight(float _input) {
  if (fabs(_input) > 100) _input = sign(_input) * 100;
  Motor_BaseRF.spin(directionType::fwd, (int)127 * _input, voltageUnits::mV);
  Motor_BaseRB.spin(directionType::fwd, (int)127 * _input, voltageUnits::mV);
}

void moveRightVel(float _input) {
  // _input ranges from -100 : 100
  // powers all motors on right side of base with duty cycle _input%
  if (fabs(_input) > 100) _input = sign(_input) * 100;
  Motor_BaseRF.spin(directionType::fwd, (int) _input, velocityUnits::pct);
  Motor_BaseRB.spin(directionType::fwd, (int) _input, velocityUnits::pct);
}

/**
 * locks all motors on right side of base
*/
void lockRight(void) {
  Motor_BaseRF.stop(vex::brakeType::hold);
  Motor_BaseRB.stop(vex::brakeType::hold);
}

/**
 * unlocks all motors on right side of base
*/
void unlockRight(void) {
  Motor_BaseRF.stop(vex::brakeType::coast);
  Motor_BaseRB.stop(vex::brakeType::coast);
}

/**
 * move forward with _input% power
 * @param _input ranges from -100 : 100
*/
void moveForward(float _input) {
  moveLeft(_input);
  moveRight(_input);
}

/**
 * rotate clockwise with _input% power
 * @param _input ranges from -100 : 100
*/
void moveClockwise(float _input) {
  moveLeft(_input);
  moveRight(-_input);
}

/**
 * lock the base
*/
void lockBase(void) {
  lockLeft();
  lockRight();
}

/**
 * unlock the base
*/
void unlockBase(void) {
  unlockLeft();
  unlockRight();
}

/**
 * powers the motor on intake with duty cycle _input%
 * @param _input ranges from -100 : 100
*/
void spinIntaker(float _input) {
  _input = fabs(_input) > 100? sign(_input) * 100: _input;
  if(!_input) {
    Motor_Intaker.stop(coast);
  }
  else {
    Motor_Intaker.spin(directionType::fwd, (int)127 * _input, voltageUnits::mV);
  }
}

/**
 * set claw
 * @param _input true or false
*/
void setPiston_Mantis(bool _input) {
  if (_input) {
    Piston_Mantis[0].open();
    Piston_Mantis[1].close();
  }
  else {
    Piston_Mantis[0].close();
    Piston_Mantis[1].open();
  }
}


/**
 * return the position of left side of base (mm from last reset position) according to encoder value
 * @return return mm
*/
float getLeftPos() {
  return Sensors::getInstance()->getBaseLeftPos() - left_pos_last;
}

/**
 * return the position of right side of base (mm from last reset position) according to encoder value
 * @return return mm
*/
float getRightPos() {
  return Sensors::getInstance()->getBaseRightPos() - right_pos_last;
}

/**
 * return the vertical position of base (mm from last reset position) according to encoder value
 * @return return mm
*/
float getForwardPos() {
  return (getLeftPos() + getRightPos()) / 2;
}

/**
 * reset encoder on the left side of the base
*/
void resetLeftPos() {
  left_pos_last = Sensors::getInstance()->getBaseLeftPos();
}

/**
 * reset encoder on the right side of the base
*/
void resetRightPos() {
  right_pos_last = Sensors::getInstance()->getBaseRightPos();
}

/**
 * reset encoders on both side of the base
*/
void resetForwardPos() {
  resetLeftPos();
  resetRightPos();
}

float getCrtVel(){
  return (Sensors::getInstance()->getBaseLeftVel() + Sensors::getInstance()->getBaseRightVel()) / 2;
}

/**
 * return the heading angle of robot in deg (+360 after a full clockwise turn, -360 after a counter-clockwise turn) 
 * @return float with 1 decimal point
 */
float getHeading() {
  return Sensors::getInstance()->getBaseRotation();
}