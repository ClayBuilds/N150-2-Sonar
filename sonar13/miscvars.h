#ifndef MISC_VARS_H
#define MISC_VARS_H

#include <Adafruit_MCP23X17.h>

Adafruit_MCP23X17 mcp;



//Sonar stuff
byte echo = 0;
byte fail = 0;
double sos = 1116.0; //speed of sound, ft/s
//double d0 = 0;   //offset due to delay from rise time/initiating sonar pulse (feet)
//timing for complete sonar circumference loop
unsigned long tsonlast = 0;
unsigned long dtson = 2000; //millis between each loop of the sonar ring. fires all 16.

//I2C comms stuff
//motor boardcommunication
byte sendMotorBytes[8];// = {1,2,3,4,5,6,7,8}; //values to be sent to slave motor driver
float receivedMotorFloats[4];  //values received from slave. 0 is turret position and 1 is steering position in degrees. 2 and 3 currently unused. 
//ESP communication
byte receiveESPBytes[8];
float sendESPFloats[20];  //complete set of data to be sent to the ESP32 0 is turret angle, 1 is steering angle, 2 and 3 reserved for motor x/y, 4 is ultrasonic 0, 5 is ultrasonic 1, 6 is ultrasonic 2, etc. 

//I don't know what all these are for
//tog and a for blinktest, old test code currently not required
int a = 0;
int amax = 0;
int tog = 1;
unsigned long tlast = 0;
unsigned long t1 = 0;
unsigned long t = 1;

//truth table for multiplexed sonar. Each row encodes a different module to use. 16 total.
//this is the order according to the datasheet for outputs Y0, Y1, Y2, etc. but as wired around circumference of robot it does not go in order. 
byte tt[16][4] = {
  {0,0,0,0},
  {0,0,0,1},
  {0,0,1,0},
  {0,0,1,1},
  {0,1,0,0},
  {0,1,0,1},
  {0,1,1,0},
  {0,1,1,1},
  {1,0,0,0},
  {1,0,0,1},
  {1,0,1,0},
  {1,0,1,1},
  {1,1,0,0},
  {1,1,0,1},
  {1,1,1,0},
  {1,1,1,1},
};

//rearrange the truth table so it matches the tranducer wiring, going 0-15 clockwise when looking from top.
byte ttordered[16][4] = {
  {tt[1][0],tt[1][1],tt[1][2],tt[1][3]},       //0
  {tt[14][0],tt[14][1],tt[14][2],tt[14][3]},   //1
  {tt[6][0],tt[6][1],tt[6][2],tt[6][3]},       //2
  {tt[10][0],tt[10][1],tt[10][2],tt[10][3]},   //3
  {tt[2][0],tt[2][1],tt[2][2],tt[2][3]},       //4
  {tt[12][0],tt[12][1],tt[12][2],tt[12][3]},   //5
  {tt[4][0],tt[4][1],tt[4][2],tt[4][3]},       //6
  {tt[8][0],tt[8][1],tt[8][2],tt[8][3]},       //7
  {tt[0][0],tt[0][1],tt[0][2],tt[0][3]},       //8
  {tt[15][0],tt[15][1],tt[15][2],tt[15][3]},   //9
  {tt[7][0],tt[7][1],tt[7][2],tt[7][3]},       //10
  {tt[11][0],tt[11][1],tt[11][2],tt[11][3]},   //11
  {tt[3][0],tt[3][1],tt[3][2],tt[3][3]},       //12
  {tt[13][0],tt[13][1],tt[13][2],tt[13][3]},   //13
  {tt[5][0],tt[5][1],tt[5][2],tt[5][3]},       //14
  {tt[9][0],tt[9][1],tt[9][2],tt[9][3]},       //15
};

#endif