/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Lewis                                                     */
/*    Created:      10/12/2024, 1:30:12 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
// A global instance of vex::controller
vex::controller  Controller;
// A global instance of vex::motor
vex::motor       Motor6(vex::PORT6, vex::gearSetting::ratio18_1, false);
// vex::motor       Motor15(vex::PORT15, vex::gearSetting::ratio18_1, false);

int main() {
    while(true) {
        int joystickValue = Controller.Axis3.position();
        // int joystickValue2 = Controller.Axis2.position();
        Motor6.spin(vex::directionType::fwd, joystickValue, vex::velocityUnits::pct);
        // Motor15.spin(vex::directionType::fwd, -joystickValue2, vex::velocityUnits::pct);
        this_thread::sleep_for(10);
    }
}