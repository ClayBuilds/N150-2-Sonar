#ifndef I2CSTUFF_H
#define I2CSTUFF_H

#include <Wire.h>

void receiveEvent()
{
  for (int i = 0; i < 8; i++) 
  {
    receivedBytes[i] = Wire1.read(); // Read each byte directly into the array
  }
}

void requestEvent()
{
  for (int i = 0; i < 4; i++) 
  {
    // Send each float as 4 bytes
    byte* floatAsBytes = (byte*)(void*)&sendFloats[i];
    for (int j = 0; j < 4; j++) {
      Wire1.write(floatAsBytes[j]);
    }
  }
}

#endif