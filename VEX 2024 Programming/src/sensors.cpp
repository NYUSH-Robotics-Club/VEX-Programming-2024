#include "sensors.h"

void Sensors::updateSensors() {
  base_left_pos = deg2rad(Motor_BaseLF.position(deg)+Motor_BaseLB.position(deg)) / 2 * CHASSIS_GEAR_RATIO * (WHEEL_DIAMETER * 25.4) / 2.0;
  base_right_pos = deg2rad(Motor_BaseRF.position(deg)+Motor_BaseRB.position(deg)) / 2 * CHASSIS_GEAR_RATIO * (WHEEL_DIAMETER * 25.4) / 2.0;
  base_left_vel = (Motor_BaseLF.velocity(pct) + Motor_BaseLB.velocity(pct)) / 2;
  base_right_vel = (Motor_BaseRF.velocity(pct) + Motor_BaseRB.velocity(pct)) / 2;
  base_heading = 360-IMU.heading();
  base_rotation = IMU.rotation();
}

float Sensors::getBaseLeftPos() {
  return base_left_pos;
}

float Sensors::getBaseRightPos() {
  return base_right_pos;
}

float Sensors::getBaseForwardPos() {
  return (base_left_pos + base_right_pos) / 2;
}

void Sensors::resetBaseLeftPos() {
  Motor_BaseLF.resetPosition();
  Motor_BaseLB.resetPosition();
}

void Sensors::resetBaseRightPos() {
  Motor_BaseRF.resetPosition();
  Motor_BaseRB.resetPosition();
}

void Sensors::resetBasePos() {
  resetBaseLeftPos();
  resetBaseRightPos();
}

float Sensors::getBaseLeftVel() {
  return base_left_vel;
}

float Sensors::getBaseRightVel() {
  return base_right_vel;
}

/**
 * return base forward velocity from -100 to 100
*/
float Sensors::getBaseForwardVel() {
  return (base_left_vel + base_right_vel) / 2;
}

float Sensors::getBaseHeading() {
  return base_heading;
}

void Sensors::setBaseHeading(float _heading) {
  IMU.setHeading(_heading, degrees);
}

void Sensors::resetBaseHeading() {
  IMU.resetHeading();
}

float Sensors::getBaseRotation(void) {
  return base_rotation;
}

void Sensors::setBaseRotation(float _rotation) {
  IMU.setRotation(_rotation, degrees);
}

void Sensors::resetBaseRotation(void) {
  IMU.resetRotation();
}

void autonSensors() {
  while(1) {
    Sensors::getInstance()->updateSensors();
    this_thread::sleep_for(5);
  }
}
