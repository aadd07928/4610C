#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor l1 = motor(PORT8, ratio18_1, true);
motor l2 = motor(PORT4, ratio18_1, true);
motor l3 = motor(PORT9, ratio18_1, false);
motor r1 = motor(PORT7, ratio18_1, false);
motor r2 = motor(PORT6, ratio18_1, true);
motor r3 = motor(PORT5, ratio18_1, false);
inertial Inert = inertial(PORT14);
controller Controller1 = controller(primary);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}