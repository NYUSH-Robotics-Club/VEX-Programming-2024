/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Lewis                                                     */
/*    Created:      10/14/2024, 8:48:59 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
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

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here


int main() {

    Brain.Screen.printAt( 10, 50, "Hello V5" );
    defineController();
    while(1) {
        if 
        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}
