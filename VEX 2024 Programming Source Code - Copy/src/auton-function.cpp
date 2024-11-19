#include "auton-function.h"
#include "basic-functions.h"
#include "PID.h"
#include "math-tools.h"
#include "parameters.h"
#include "sensors.h"
using namespace vex;

void softStartTimerForward(float _power_init, float _power_final, int _duration) {
    auto timer = MyTimer();
    float step = (_power_final - _power_init) / _duration;
    while (timer.getTime() < _duration) {
        moveForward(_power_init + timer.getTime() * step);
        this_thread::sleep_for(5);
    }
    unlockBase();
}

void timerForward(float _power, int _duration) {
    moveForward(_power);
    this_thread::sleep_for(_duration);
    unlockBase();
}

void posForwardRel(float _power, float _target) {
    float start = getForwardPos();
    float error = 0, feedback = 0;
    float direction = getHeading();
    float power = sign(_target) * fabs(_power);
    while (fabs(getForwardPos() - start) < fabs(_target)) {
        error = getHeading() - direction;
        feedback = error * 2.0;
        feedback = fabs(feedback)>15? 15*sign(feedback): feedback;
        moveRight(power + feedback);
        moveLeft(power - feedback);
        this_thread::sleep_for(5);
    }
    unlockBase();
}

void posForwardAbs(float _power, float _target) {
    float target_rel = _target - getForwardPos();
    posForwardRel(_power, target_rel);
}

void pidForwardRel(float _target) {
    pidForwardAbs(getForwardPos() + _target);
}
void pidForwardAbs(float _target) {
    auto pid = PID();
    pid.setCoefficient(BASE_FORWARD_PID[0], BASE_FORWARD_PID[1], BASE_FORWARD_PID[2]);
    pid.setTarget(_target);
    pid.setIMax(20);
    pid.setIRange(5);
    pid.setErrorTolerance(3); // 设定误差小于多少的时候可以跳出循环
    pid.setDTolerance(5); // 设定速度小于多少的时候车可以跳出循环
    pid.setJumpTime(20);
    while (!pid.targetArrived()) {
        pid.update(getForwardPos());
        moveForward(pid.getOutput());
        this_thread::sleep_for(5);
    }
    unlockBase();
}

void softStartTimerRotate(float _power_init, float _power_final, int _duration) {
    auto timer = MyTimer();
    float step = (_power_final - _power_init) / _duration;
    while (timer.getTime() < _duration) {
        moveClockwise(_power_init + timer.getTime() * step);
        this_thread::sleep_for(5);
    }
    unlockBase();
}

void timerRotate(float _power, int _duration) {
    moveClockwise(_power);
    this_thread::sleep_for(_duration);
    unlockBase();
}

void angleRotateRel(float _power, float _target) {
    angleRotateAbs(_power, getHeading() + _target);
}

void angleRotateAbs(float _power, float _target) {
    while(fabs(_target-getHeading()) > 180) {
        if(_target-getHeading() > 0) _target -= 360;
        else _target += 360;
    }
    float start = getHeading();
    float power = sign(_target-getHeading()) * fabs(_power);
    float target = fabs(_target-getHeading());
    moveClockwise(power);
    while(fabs(getHeading() - start) < target) {
        this_thread::sleep_for(5);
    }
    unlockBase();
}

void pidRotateRel(float _target) {
    pidRotateAbs(getHeading() + _target);
}

void pidRotateAbs(float _target) {
    auto pid = PID();
    // data transfer to prevend from huge angle rotation
    while(fabs(_target-getHeading()) > 180) {
        if(_target-getHeading() > 0) _target -= 360;
        else _target += 360;
    }
    pid.setTarget(_target);
    pid.setIMax(20);
    pid.setIRange(20); //use if sentance to define the I coeff
    pid.setErrorTolerance(1);
    pid.setDTolerance(2);
    pid.setJumpTime(20);
    while (!pid.targetArrived()) {
        pid.setCoefficient(BASE_ROTATE_PID[0], BASE_ROTATE_PID[1], BASE_ROTATE_PID[2]);
        pid.update(getHeading());
        moveClockwise(pid.getOutput());
        this_thread::sleep_for(5);
    }
    resetForwardPos();
    unlockBase();
}
