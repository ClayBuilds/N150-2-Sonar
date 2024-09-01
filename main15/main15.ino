//program for drive control on N150 robot
//there are several onboard microcontrollers, this program runs on the one connected to the 3 motors, encoders, limit switches, and PS2 controller.
// 8-30-2024
//version 15

//changes from v14:
/*
-implement dead reckoning for cartesian position
*/

//test results:
/*
-works nicely
*/

#include "pinout.h"
#include "miscvars.h"
#include "motorcontrol.h"
#include "ps2.h"
#include "miscfuncs.h"
#include "motorencoders.h"
#include "I2Cstuff.h"
#include "turretandsteermatch.h"
#include <RotaryEncoder.h>
#include <Wire.h>
#include <QuickPID.h>

void setup() 
{
  //initialize I2C as a slave
  Wire1.begin(0x08);
  Wire1.onReceive(receiveEvent);
  Wire1.onRequest(requestEvent);
  
  //set all pins for drive control to output
  pinMode(m1dirpin, OUTPUT);
  pinMode(m1pwmpin, OUTPUT);
  pinMode(m1clpin, OUTPUT);
  pinMode(m2dirpin, OUTPUT);
  pinMode(m2pwmpin, OUTPUT);
  pinMode(m2clpin, OUTPUT);
  pinMode(m3dirpin, OUTPUT);
  pinMode(m3pwmpin, OUTPUT);
  pinMode(m3clpin, OUTPUT);
  
  //initialize the enable pins
  digitalWrite(m1clpin, HIGH);
  digitalWrite(m2clpin, HIGH);
  digitalWrite(m3clpin, HIGH);
  
  //set limit switch pins and encoder pins to input
  pinMode(turrL, INPUT);
  pinMode(steerL, INPUT);
  pinMode(m1e1, INPUT);
  pinMode(m1e2, INPUT);
  pinMode(m2e1, INPUT);
  pinMode(m2e2, INPUT);
  pinMode(m3e1, INPUT);
  pinMode(m3e2, INPUT);
  
  //homing
  homesteer();
  
  //encoder stuff
  attachInterrupt(digitalPinToInterrupt(m3e1), checkturrPosition, CHANGE);
  attachInterrupt(digitalPinToInterrupt(m3e2), checkturrPosition, CHANGE);
  turrenc = new RotaryEncoder(m3e1, m3e2, RotaryEncoder::LatchMode::TWO03);
  
  attachInterrupt(digitalPinToInterrupt(m2e1), checksteerPosition, CHANGE);
  attachInterrupt(digitalPinToInterrupt(m2e2), checksteerPosition, CHANGE);
  steerenc = new RotaryEncoder(m2e1, m2e2, RotaryEncoder::LatchMode::TWO03);
  
  attachInterrupt(digitalPinToInterrupt(m1e1), checkdrivePosition, CHANGE);
  attachInterrupt(digitalPinToInterrupt(m1e2), checkdrivePosition, CHANGE);
  driveenc = new RotaryEncoder(m1e1, m1e2, RotaryEncoder::LatchMode::TWO03);
  
  //ps2 controller stuff
  fastPinMode (PIN_BUTTONPRESS, OUTPUT);
	fastPinMode (PIN_HAVECONTROLLER, OUTPUT);
	Serial.begin (115200);
	Serial.println (F("Ready!"));
  
  //setup PID Control loop
  Setpoint = 0;
  turrPID.SetTunings(Kp, Ki, Kd);
  turrPID.SetOutputLimits(-50,50);
  turrPID.SetMode(0); //start in manual mode
  
}

void loop() 
{
  checkcontroller();
  controller();
  mapTargets();
  readlims();
  steermatch();
  deadreckon();
  adjustmotor1(m1throtT);
  adjustmotor2(m2throtT);
  adjustmotor3(m3throtT);
  
  //printcontroller();      //rapidly prints analog stick values from controller
  //printbuts();            //rapidly prints integer values 1-16 corresponding to which digital buttons on ps2 controller are pressed
  //printmotvals();         //rapidly prints throttle values to each motor and actual pwm duty cycle being fed to each
  //printlims();            //rapidly prints limit switch values
  //printencs();            //rapidly prints encoder values
  //printreceived();        //rapidly prints data received from ESP up the chain
  //printPIDstuff();
}
