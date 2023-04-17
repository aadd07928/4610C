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
// l1                   motor         11              
// l2                   motor         13              
// l3                   motor         14              
// r1                   motor         20              
// r2                   motor         18              
// r3                   motor         19              
// Inert                inertial      21              
// Controller1          controller                    
// fly                  motor         17              
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

void turn(int head) {
  int terror = head-Inert.rotation(degrees);
  int ti =head-Inert.rotation(degrees);
  float kp = .825;
  if (terror <30) kp=1.1;
  if (terror>90) kp=.3;
  float d=0;
  while (abs(terror)>10||fabs(d)>1) {
    int p = terror;
    terror = head-Inert.rotation(degrees);
    d= p-terror;
    float kp2 = 0;
    if (abs(terror)<35&&ti>30) kp2=.5;
    sl(terror*(kp+kp2));
    sr(terror*kp*-1);
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print(terror);
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print(d);
  }
  Controller1.Screen.clearScreen();
}

float Kps = .139;
float Kds = 0.259;
float Kpt = 0.1;
float Kdt = 0;
void pid(int dist,int head) {
  l1.resetPosition();
  l2.resetPosition();
  l3.resetPosition();
  r1.resetPosition();
  r3.resetPosition();
  r2.resetPosition();
  Kpt = (head^2/1000000)+.415;
  int error =dist - (l1.position(degrees)+r1.position(degrees)+l2.position(degrees)+r2.position(degrees)+l3.position(degrees)+r3.position(degrees))/6;
  int terror = head-Inert.rotation(degrees);
  int slew = 80;
  double kp2 = 0;
  float d=0;
  while(abs(error)>15|| fabs(d)>0) {
    slew+=10;
  int pe = error;
  int tpe = terror;
  
  error =  dist - (l1.position(degrees)+r1.position(degrees)+l2.position(degrees)+r2.position(degrees)+l3.position(degrees)+r3.position(degrees))/6;
  terror = head-Inert.rotation(degrees);
  int td = tpe-terror;
   d = error-pe;

  if (error>250) kp2=0.05;
  else if (abs(error)>20&&fabs(d)<.1&&abs(error)<250) kp2 = .24;
  else if(abs(error)>5&&fabs(d)<.1&&abs(error)<20) kp2=0.11;
  else kp2=0;


  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print(error);
  Controller1.Screen.setCursor(2,1);
  Controller1.Screen.print(d);
  Controller1.Screen.setCursor(3,1);
  Controller1.Screen.print(kp2);
  int pow;
  if (error*Kps+d*Kds>slew) pow = slew;
  else {pow = error*(Kps+kp2)+d*Kds;}
  int tpow;
  if (terror*Kpt+td*Kdt>40) tpow=40;
  else {tpow=terror*Kpt+td*Kdt;}

  sl(pow+tpow);
  sr(pow-tpow);
  wait(10,msec);
  }
  Controller1.Screen.clearScreen();
  l1.stop();
  l2.stop();
  l3.stop();
  r1.stop();
  r2.stop();
  r3.stop();
}


int driver2() {

  while (true) {
    int error = 70-fly.velocity(rpm);

    fly.spin(forward,(70+error*.2)/8.5,volt);

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print(fly.velocity(rpm));
  }

}

void driver() {
  while (true) {
    int adder=0;
    l1.resetPosition();l2.resetPosition();l3.resetPosition();r1.resetPosition();r2.resetPosition();r3.resetPosition();
    if (Controller1.Axis3.position()) {
      if (abs(Controller1.Axis1.position())<10) {
        adder = (l1.position(degrees)+l2.position(degrees)+l3.position(degrees))/3-(r1.position(degrees)+r2.position(degrees)+r3.position(degrees))/3;
      }
    }

    sl(Controller1.Axis3.position()+Controller1.Axis1.position());
    sr(Controller1.Axis3.position()-Controller1.Axis1.position());
  }
}
competition comp;
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  comp.drivercontrol(driver);

}
