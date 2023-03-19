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
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

void sl(int speed){
  int s = speed*12/95;
  l3.spin(forward, s, volt);
  l2.spin(forward, s, volt);
  l1.spin(forward, s, volt);
}
void sr(int speed){
  int s = speed*12/95;
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

float Kps = .2;
float Kds = 0.2;
float Kpt = 0.4;
float Kdt = 0.15;
void pid(int dist,int head) {
  rot1.resetPosition();
  rot2.resetPosition();
  Kpt = (head^2/1000000)+.415;
  int error =dist - (rot1.position(degrees)+rot2.position(degrees))/2;
  int terror = head-Inert.rotation(degrees);
  int slew = dist/10;
  while(true) {
    //slew+=10;
  int pe = error;
  int tpe = terror;
  error = dist - (rot1.position(degrees)+rot2.position(degrees))/2;
  terror = head-Inert.rotation(degrees);
  int td = tpe-terror;
  int d = error-pe;
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print(error);
  Controller1.Screen.setCursor(2,1);
  Controller1.Screen.print(d);
  Controller1.Screen.setCursor(3,1);
  Controller1.Screen.print(terror);
  int pow;
  if (error*Kps+d*Kds>slew) pow = slew;
  else {pow = error*Kps+d*Kds;}
  int tpow;
  if (terror*Kpt+td*Kdt>40) tpow=40;
  else {tpow=terror*Kpt+td*Kdt;}

  sl(pow+tpow);
  sr(pow-tpow);
  wait(10,msec);
  }
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Inert.calibrate();
  wait(3, seconds);
  pid(0,90);
}
