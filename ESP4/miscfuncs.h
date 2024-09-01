#ifndef MISCFUNCS_H
#define MISCFUNCS_H

void printfloats()
{
  Serial.println(" ");
  for(int i = 0; i <20; i++)
  {
    Serial.print(" ");
    Serial.print(receiveFloats[i],4);
  }
}

void printbytes()
{
  Serial.println(" ");
  for(int i = 0; i<8; i++)
  {
    Serial.print(" ");
    Serial.print(sendBytes[i]);
  }
}
#endif
