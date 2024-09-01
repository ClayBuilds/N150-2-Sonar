//defines the pinout of everything connected to the microcontroller


#ifndef PINOUT_H
#define PINOUT_H

// MOTOR 1: DRIVE
byte m1pwmpin = 0; //pin 2 on slip ring header
byte m1dirpin = 1; //pin 14 on slip ring header
byte m1clpin = 2; // pin 21 on slip ring header

// MOTOR 2: STEER
byte m2pwmpin = 3; //pin 4 on slip ring header
byte m2dirpin = 4; //pin 16 on slip ring header
byte m2clpin = 5;  //pin 10 on slip ring header

// MOTOR 3: TURRET
byte m3pwmpin = 6; //pin 6 on slip ring header
byte m3dirpin = 7; //pin 18 on slip ring header
byte m3clpin = 8;  //pin 22 on slip ring header

//M1 ENCODER: DRIVE
byte m1e1 = 23;     //2 encoder pins for drive motor encoder
byte m1e2 = 22;

//M2 ENCODER: STEER
byte m2e1 = 21;     //2 encoder pins for steering motor encoder
byte m2e2 = 20;
byte steerL = 15;   //steering limit switch pin

//M3 ENCODER : TURRET
byte m3e1 = 19;     //2 encoder pins for turret motor encoder
byte m3e2 = 18;
byte turrL = 14;    //turret limit switch pin

//other notable pins that don't need to be explicitly declared:
//arduino pin 9 to controller ribbon 12, with 1k pullup to 3v3
//arduino pin 10 (CS) to controller ribbon 6, with 1k pullup to 3v3
//arduino pin 11 (MOSI) to controller ribbon 4, with 1k pullup to 3v3
//arduino pin 12 (MISO) to controller ribbon 15, with 1k pullup to 3v3
//arduino pin 13 (SCK) to controller ribbon 11, with 1k pullup to 3v3

//pin 7 on the slip ring header is not connected to the arduino, rather switched through the estop to 12v.

#endif