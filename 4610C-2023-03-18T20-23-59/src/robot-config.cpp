#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor l1 = motor(PORT1, ratio18_1, true);
motor l2 = motor(PORT4, ratio18_1, false);
motor l3 = motor(PORT13, ratio18_1, true);
motor r1 = motor(PORT8, ratio18_1, true);
motor r2 = motor(PORT10, ratio18_1, false);
motor r3 = motor(PORT18, ratio18_1, false);
motor fly = motor(PORT16, ratio6_1, true);
inertial Inert = inertial(PORT5);
rotation rot1 = rotation(PORT2, true);
rotation rot2 = rotation(PORT9, false);
motor intake = motor(PORT20, ratio6_1, true);
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