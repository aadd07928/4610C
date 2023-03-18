/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Student                                          */
/*    Created:      Sat Mar 18 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// l1                   motor         1               
// l2                   motor         4               
// l3                   motor         13              
// r1                   motor         8               
// r2                   motor         10              
// r3                   motor         18              
// fly                  motor         16              
// Inert                inertial      5               
// rot1                 rotation      2               
// rot2                 rotation      9               
// intake               motor         20              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

void sl(int speed){
  int s = speed*12/100;
  l3.spin(forward, s, volt);
  l2.spin(forward, s, volt);
  l1.spin(forward, s, volt);
}
void sr(int speed){
  int s = speed*12/100;
  r3.spin(forward, s, volt);
  r2.spin(forward, s, volt);
  r1.spin(forward, s, volt);
}

void spinIntake() {
  intake.spin(forward,12.5,volt);
}

void spinFly(int speed) {
  fly.spin(forward,speed*12/100,volt);
}

float Kps = .7;
float Kds = .3;
float Kpt = .9;
float Kdt = .2;
void pid(int dist,int head) {
  int error =dist - (rot1.position(degrees)+rot2.position(degrees))/2;
  int terror = head-Inert.rotation(degrees);
  while(true) {
  int pe = error;
  int tpe = terror;
  error = dist - (rot1.position(degrees)+rot2.position(degrees))/2;
  terror = head-Inert.rotation(degrees);


  int td = tpe-terror;
  int d = pe-error;

  sl(error*Kps+d*Kds+terror*Kpt+td*Kdt);
  sr(error*Kps+d*Kds-terror*Kpt-td*Kdt);
  }
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  pid(200,0);
}
