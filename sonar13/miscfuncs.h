#ifndef MISCFUNCS_H
#define MISCFUNCS_H

//like blink but actually calculates data and runs true distance measurements. run in main loop
double sonar(int i)
{
  //select which sonar module to use
  if(ttordered[i][0])
    {digitalWrite(A0p, HIGH);}
    else
    {digitalWrite(A0p, LOW);}
  if(ttordered[i][1])
    {digitalWrite(A1p, HIGH);}
    else
    {digitalWrite(A1p, LOW);}
  if(ttordered[i][2])
    {digitalWrite(A2p, HIGH);}
    else
    {digitalWrite(A2p, LOW);}
  if(ttordered[i][3])
    {digitalWrite(A3p, HIGH);}
    else
    {digitalWrite(A3p, LOW);}
      
  delay(25); //allow time for relays to respond
      
  double d;
  fail = 0;
  echo = 0;
  t1 = micros();
  mcp.digitalWrite(initp1, HIGH);
  
  while(!echo)
  {
    echo = digitalRead(echop);
    if((micros()-t1)>80000)
      {
        echo = 1;
        fail = 1;
      }
  }
  t = micros()-t1;
  
  d = ((t/1000000.0)*sos)/2;
  if(fail)
    {
      //t = 999;
      d = 0;
    }
    
  //d = ((t/1000000.0)*sos)/2;
  mcp.digitalWrite(initp1, LOW);

  return d;
}

//this function tests sonar by clicking it and blinking lights every few seconds. run in main loop.
void blinktest()
{
  
  a = analogRead(echop);
  if (a>amax)
  {amax = a;}
  Serial.println(amax);
  
  
  
  if((millis()-tlast) > 3000)
    {
      tlast = millis();
      tog = tog*(-1);
    }
  
  if(tog<0)
  {
    mcp.digitalWrite(initp1, HIGH);
    Serial.println("HIGH");
  }
  else
  {
    mcp.digitalWrite(initp1, LOW);
    Serial.println("LOW");
  }
  
}

void printmotorreceived()
{
  Serial.print("Received:     ");
  Serial.print("Turret: ");
  Serial.print(receivedMotorFloats[0],5);
  Serial.print(" Steer: ");
  Serial.println(receivedMotorFloats[1],5);
}

void printespreceived()
{
  Serial.print("Bytes: ");
  Serial.print(receiveESPBytes[0]);
  Serial.print(" ");
  Serial.print(receiveESPBytes[1]);
  Serial.print(" ");
  Serial.print(receiveESPBytes[2]);
  Serial.print(" ");
  Serial.print(receiveESPBytes[3]);
  Serial.print(" ");
  Serial.print(receiveESPBytes[4]);
  Serial.print(" ");
  Serial.print(receiveESPBytes[5]);
  Serial.print(" ");
  Serial.print(receiveESPBytes[6]);
  Serial.print(" ");
  Serial.print(receiveESPBytes[7]);
  Serial.println(" ");
}
#endif