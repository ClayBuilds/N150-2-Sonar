#ifndef I2Cstuff_H
#define I2Cstuff_H

#include <Wire.h>
#include "miscvars.h"

void receiveEvent(int howMany) //will receive an array of 2 floats from the master
{
  float receive2Floats[2];
  int byteIndex = 0;
  while (Wire.available() && byteIndex < 2 * 4) //2 floats, 4 bytes per float
  {
    ((byte*)receive2Floats)[byteIndex++] = Wire.read(); // Read each byte directly into the float array
  }
  int arrayindex = round(receive2Floats[0]);
  receiveFloats[arrayindex] = receive2Floats[1];
}

void requestEvent() //will send an array of 8 bytes to the master.
{
  for (int i = 0; i < 8; i++) //8 bytes in the array
  {
    Wire.write(sendBytes[i]); // Send each byte in the array
  }
}

#endif