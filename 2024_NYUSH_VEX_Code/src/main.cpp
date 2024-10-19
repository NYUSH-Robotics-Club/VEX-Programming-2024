#include "vex.h"
#include "basic-functions.h"
#include "auton-function.h"
#include "parameters.h"
#include "autonomous.h"
#include "my-timer.h"
#include "controller.h"
#include "cstdlib"
#include "sensors.h"

using namespace vex;
competition Competition;

int auton_strategy = 0;

void pre_auton(void) {
  vexcodeInit();
}

void autonomous(void) {
  switch(auton_strategy) {
    case 0:
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    }
}

void usercontrol(void) {
  // User control code here, inside the loop
  bool mantis_state = 0;
  while (1) {
    // Controller Input
    defineController();
    // Base Movement Control
    A3 = std::abs(A3) < JOYSTICK_DEADZONE? 0: A3;
    A1 = std::abs(A1) < JOYSTICK_DEADZONE? 0: A1;
    if (std::abs(A3 + A1) > MOVEMENT_LOWER_LIMIT)
      moveLeft(A3 + A1);
    else
      unlockLeft();
    if (std::abs(A3 - A1) > MOVEMENT_LOWER_LIMIT)
      moveRight(A3 - A1);
    else
      unlockRight();
    // Intake and spinner control
    if (R1) {
      spinIntaker(100);
    }
    else if(R2) {
      spinIntaker(-100);
    }
    else {
      spinIntaker(4);
    }

    if(L2 && !last_L2) {
      mantis_state = !mantis_state;
    }
    setPiston_Mantis(mantis_state);

    if(DOWN && !last_DOWN) {
      autonomous();
    }
    this_thread::sleep_for(10);
  }
}

int main() {
  thread AutonSensors(autonSensors);
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  // Run the pre-autonomous function.
  pre_auton();
  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}