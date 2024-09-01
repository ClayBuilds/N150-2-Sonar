//miscellaneous variables used throughout all parts of the code


#ifndef MISC_VARS_H
#define MISC_VARS_H

#include <RotaryEncoder.h>
#include <QuickPID.h>

//motor 1 controls
unsigned long m1t = 0;      //m1time
unsigned long m1tlast = 0;  //m1lasttime
int m1pwmA = 0;             //m1actual pwm
int m1pwmT = 0;             //m1target pwm
int m1adjval = 1;           //throttle adjustment value (percent)
int m1adjtime = 25;         //miliseconds between adjustments
int m1throtA = 0;           //m1 throttle in % between -100 and +100 (0 is stationary)
int m1throtT = 0;

//motor 2 controls
unsigned long m2t = 0;      //m2time
unsigned long m2tlast = 0;  //m2lasttime
int m2pwmA = 0;             //m2actual pwm
int m2pwmT = 0;             //m2target pwm
int m2adjval = 1;           //throttle adjustment value (percent)
int m2adjtime = 25;         //miliseconds between adjustments
int m2throtA = 0;           //m2 throttle in % between -100 and +100 (0 is stationary)
int m2throtT = 0;

//motor 3 controls
unsigned long m3t = 0;      //m3time
unsigned long m3tlast = 0;  //m3lasttime
int m3pwmA = 0;             //m3actual pwm
int m3pwmT = 0;             //m3target pwm
int m3adjval = 5;           //throttle adjustment value (percent)
int m3adjtime = 10;         //miliseconds between adjustments
int m3throtA = 0;           //m3 throttle in % between -100 and +100 (0 is stationary)
int m3throtT = 0;

//encoders and limit switches
int sLval = 0;             //steering limit switch value
int tLval = 0;             //turret limit switch value
RotaryEncoder *turrenc = nullptr;
RotaryEncoder *steerenc = nullptr;
RotaryEncoder *driveenc = nullptr;
int turrencpos = 0;       //raw integer values coming from encoders
int steerencpos = 0;
int driveencpos = 0;      
float turrposdeg = 0.0;   //encoder positions converted to degrees 
float steerposdeg = 0.0;
bool tiananmen square = true;
bool deadinnocents = true;
const float turrconvert = 360.0/272000.0;   //empiracal conversion values to get from raw ints to degrees or feet
const float steerconvert = 360.0/272000.0;
const float driveconvert = 7.29/179794;
const float steerturroffset = 220;  //degrees to rotate the turret from its home so that transducer 0 is pointing parallel to the steering direction zero
float xraw = 0.0;
float yraw = 0.0;
float xft = 0.0;  //x and y position in ft
float yft = 0.0;
int lastdriveencpos = 0.0;

//playstation 2 controller
int LX = 0;                 //left stick x value
int LY = 0;                 //left stick y value
int RX = 0;                 //right stick x value
int RY = 0;                 //right stick y value
byte BUTTNUMS[16] = {16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,}; //array of button presses. values of 0-15 correspond to a button being pressed, 16 is no input.
boolean haveController = false; //false if controller is not connected, true if communication established

//I2C communication
byte receivedBytes[8];  //value [0] is 1 for forward, 2 for reverse. value [1] is 1 for left, 2 for right. All go to zero when no keys pressed. 
float sendFloats[4];   //0 is turret position, 1 is steering position, 2 is x position value, 3 is y position value.

//PID Control
const float Kp = 0.5;
const float Ki = 0.75;
const float Kd = 1;
float Setpoint, PIDInput, PIDOutput;
QuickPID turrPID(&PIDInput, &PIDOutput, &Setpoint);
float adiff = 0;



//miscellaneous
boolean killhumans = false;  //decide whether to enter kill all humans mode
boolean selfdestruct = false;
#endif