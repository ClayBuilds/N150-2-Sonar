#ifndef I2Cstuff_H
#define I2Cstuff_H

#include <Wire.h>

void requestFloatsFromMotorSlave() 
{
  Wire.requestFrom(0x08, 4 * 4); // Request 16 bytes (4 floats * 4 bytes per float) from slave at address 0x08  
  int byteIndex = 0;
  while (Wire.available() && byteIndex < 4 * 4) 
  {
    ((byte*)receivedMotorFloats)[byteIndex++] = Wire.read(); // Read each byte directly into the float array
  }
}

void sendBytesToMotorSlave() 
{
  for(int a = 0; a<8; a++)
  {
      sendMotorBytes[a] = receiveESPBytes[a];
  }

  Wire.beginTransmission(0x08); // Start communication with slave at address 0x08
  for (int i = 0; i < 8; i++) //8 bytes in the array
  {
    Wire.write(sendMotorBytes[i]); // Send each byte in the array
  }
  Wire.endTransmission(); // End communication
}

void requestBytesFromESP()
{
  Wire.requestFrom(0x09, 8); // Request 8 bytes  from ESP slave at address 0x09
  
  int byteIndex = 0;
  while (Wire.available() && byteIndex < 8) //receive 8 bytes
  {
    ((byte*)receiveESPBytes)[byteIndex++] = Wire.read(); // Read each byte directly into the float array
  }
}

void sendFloatsToESP()
{
  //make sure the values received from the motor board are in the array being sent to the esp
  for(int a = 0; a<4; a++)
  {sendESPFloats[a] = receivedMotorFloats[a];}
    
  for(int i = 0; i<20; i++) //twenty floats total
  {
    Wire.beginTransmission(0x09);
    /*
    for (int j = 0; j < 2; j++) //two floats at a time, first one is just an index
    {
      float sendFloats[2] = {i, sendESPFloats[i]};
      // Send each float as 4 bytes
      byte* floatAsBytes = (byte*)(void*)&sendFloats[j];
      for (int k = 0; k < 4; k++) 
      {
        Wire.write(floatAsBytes[k]);
      }
    }
    */
    
        // Send index as the first float (converted to float for compatibility)
    float index = (float)i;
    byte* indexAsBytes = (byte*)(void*)&index;
    for (int k = 0; k < 4; k++) {
      Wire.write(indexAsBytes[k]);
    }

    // Send the actual float value
    byte* floatAsBytes = (byte*)(void*)&sendESPFloats[i];
    for (int k = 0; k < 4; k++) {
      Wire.write(floatAsBytes[k]);
    }
    
    
    Wire.endTransmission();
  }
}

#endif