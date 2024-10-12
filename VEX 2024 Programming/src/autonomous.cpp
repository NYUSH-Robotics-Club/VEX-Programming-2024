#include "autonomous.h"
#include "iostream"

static auto auton_timer = MyTimer();

void auton_init(void) {
  // init
  auton_timer.reset();
}

void auton_pre_usercontrol(void) {
  Brain.Screen.setCursor(8, 1);
  Brain.Screen.print("AutonTimer: %2.2fsec", auton_timer.getTime()/1000.0);
}
