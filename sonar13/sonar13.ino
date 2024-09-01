// program for testing sonar system on N150 robot
// There are several microcontrollers in the robot, this code runs on the one connected to the sonar units. 
// Version 13
// 8-31-2024


//changes from v11:
/*
-reduce sonar timeout from 2000 ms to 80ms
*/

//test results:
/*
-all working as expected
*/

#include "pinout.h"
#include "miscvars.h"
#include "miscfuncs.h"
#include "I2Cstuff.h"
#include <Wire.h>
#include <Adafruit_MCP23X17.h>
#include <Ultrasonic.h>


void setup() 
{
  delay(1000);
  Serial.begin(9600);
  Serial.println("HOWDY BITCH");
  
  pinMode(A0p, OUTPUT);
  pinMode(A1p, OUTPUT);
  pinMode(A2p, OUTPUT);
  pinMode(A3p, OUTPUT);
  
  digitalWrite(A0p, LOW);
  digitalWrite(A1p, LOW);
  digitalWrite(A2p, LOW);
  digitalWrite(A3p, LOW); 
  
  Wire.begin();
  
  int nomcp = 1;                //the io expander chip sometime wont initialize correctly if the microcontroller starts up too fast. Just wait around and try to reinitialize afew times. 
  if(!mcp.begin_I2C())
  {
    Serial.println("FUCK");
    while(nomcp)                //holy shit this actually worked
    {
      nomcp = !mcp.begin_I2C();
      Serial.println("FUCK");
      delay(1000);
    }
  }

  mcp.pinMode(initp1, OUTPUT);
  delay(2000);
  Serial.println("we good");
  delay(1000);
}

void loop() 
{
  if((millis()-tsonlast)>dtson) //run the sonar ring once per specified amount of time
  {
    tsonlast = millis();
    for(int i = 0; i<16; i++)
    {
      double d = sonar(i);
      sendESPFloats[i+4] = d;
      delay(10);  //delay between individual sonar transducers
      
      requestFloatsFromMotorSlave();
      sendBytesToMotorSlave();
      requestBytesFromESP();
      sendFloatsToESP();
    }
  }


  requestFloatsFromMotorSlave();
  sendBytesToMotorSlave();
  requestBytesFromESP();
  sendFloatsToESP();
  //printmotorreceived();
  //printespreceived();
}

