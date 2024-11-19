#ifndef AUTON_FUNCTION_H_
#define AUTON_FUNCTION_H_

void softStartTimerForward(float _power_init, float _power_final, int _duration);
void timerForward(float _power, int _duration);
void posForwardRel(float _power, float _target);
void posForwardAbs(float _power, float _target);
void pidForwardRel(float _target);
void pidForwardAbs(float _target);

void softStartTimerRotate(float _power_init, float _power_final, int _duration);
void timerRotate(float _power, int _duration);
void angleRotateRel(float _power, float _target);
void angleRotateAbs(float _power, float _target);
void pidRotateRel(float _target);
void pidRotateAbs(float _target);

#endif