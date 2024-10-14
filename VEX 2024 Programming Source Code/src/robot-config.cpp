#include "robot-config.h"

using namespace vex;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);

motor Motor_BaseLF = motor(PORT8, ratio6_1, false);
motor Motor_BaseLB = motor(PORT7, ratio6_1, false);
motor Motor_BaseRF = motor(PORT17, ratio6_1, true);
motor Motor_BaseRB = motor(PORT16, ratio6_1, true);
motor Motor_Intaker = motor(PORT2,ratio18_1,true);
pneumatics Piston_Mantis[2] = {pneumatics(Brain.ThreeWirePort.B), pneumatics(Brain.ThreeWirePort.A)};
inertial IMU = inertial(PORT10);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

void vexcodeInit(void) {
  IMU.startCalibration();
  while (IMU.isCalibrating()) {
    this_thread::sleep_for(5);
  }
  Controller1.Screen.setCursor(5, 1);
  Controller1.Screen.print("%19s", "CA");
}