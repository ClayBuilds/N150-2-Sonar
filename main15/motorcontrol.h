//code for sending pwm values to the motors


#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include "motorencoders.h"

void writemotor1(int p)  //takes a throttle value in percent (from -100 to +100) then writes the motor pwm and direction accordingly 
{
  int d = 0;
  if(p>=0)    //determine direction
  {d = 1;}
  
  p = abs(p);
  int pwm = map(p, 0, 100, 0, 255); //determine magnitude
  
  if(d)                               //set direction
    {digitalWrite(m1dirpin, HIGH);}
  else
    {digitalWrite(m1dirpin, LOW);}
  
  pwm = constrain(pwm, 0, 255); //safety in case fuckup upstream
  
  analogWrite(m1pwmpin, pwm);   //set magnitude
  m1pwmA = pwm;   //track pwm
}

void writemotor2(int p)  //takes a throttle value in percent (from -100 to +100) then writes the motor pwm and direction accordingly 
{
  int d = 0;
  if(p>=0)    //determine direction
  {d = 1;}
  
  p = abs(p);
  int pwm = map(p, 0, 100, 0, 255); //determine magnitude
  
  if(d)                               //set direction
    {digitalWrite(m2dirpin, HIGH);}
  else
    {digitalWrite(m2dirpin, LOW);}
  
  pwm = constrain(pwm, 0, 255); //safety in case fuckup upstream
  
  analogWrite(m2pwmpin, pwm);   //set magnitude
  m2pwmA = pwm;   //track pwm
}

void writemotor3(int p)  //takes a throttle value in percent (from -100 to +100) then writes the motor pwm and direction accordingly 
{
  int d = 0;
  if(p>=0)    //determine direction
  {d = 1;}
  
  p = abs(p);
  int pwm = map(p, 0, 100, 0, 255); //determine magnitude
  
  if(d)                               //set direction
    {digitalWrite(m3dirpin, HIGH);}
  else
    {digitalWrite(m3dirpin, LOW);}
  
  pwm = constrain(pwm, 0, 255); //safety in case fuckup upstream
  
  analogWrite(m3pwmpin, pwm);   //set magnitude
  m3pwmA = pwm;   //track pwm
}


void adjustmotor1(int targ)   //gradually ramp motor speed up or down towards target
{
  targ = constrain(targ, -100, 100);
  
  if((millis()-m1tlast)<m1adjtime) //see if enough time has passed since last adjustment
  {return;}
  else
  {m1tlast= millis();}

  if(m1throtA>targ)         //ramp down
  {
    writemotor1(m1throtA-m1adjval);       
    m1throtA = m1throtA-m1adjval;
  }
  else if(m1throtA<targ)    //ramp up
  {
    writemotor1(m1throtA+m1adjval);
    m1throtA = m1throtA+m1adjval;
  }
  else
  {writemotor1(m1throtA);}   //stay the same
  
  if(abs(m1throtA-targ)<=m1adjval)   //if its within the adjutment threshhold, write it directly to the target speed
  {
    writemotor1(targ);
    m1throtA = targ;
  }
}

void adjustmotor2(int targ)   //gradually ramp motor speed up or down towards target
{
  targ = constrain(targ, -100, 100);
  
  if((millis()-m2tlast)<m2adjtime) //see if enough time has passed since last adjustment
  {return;}
  else
  {m2tlast= millis();}

  if(m2throtA>targ)         //ramp down
  {
    writemotor2(m2throtA-m2adjval);       
    m2throtA = m2throtA-m2adjval;
  }
  else if(m2throtA<targ)    //ramp up
  {
    writemotor2(m2throtA+m2adjval);
    m2throtA = m2throtA+m2adjval;
  }
  else
  {writemotor2(m2throtA);}   //stay the same
  
  if(abs(m2throtA-targ)<=m2adjval)   //if its within the adjutment threshhold, write it directly to the target speed
  {
    writemotor2(targ);
    m2throtA = targ;
  }
}

void adjustmotor3(int targ)   //gradually ramp motor speed up or down towards target
{
  targ = constrain(targ, -100, 100);
  
  if((millis()-m3tlast)<m3adjtime) //see if enough time has passed since last adjustment
  {return;}
  else
  {m3tlast= millis();}

  if(m3throtA>targ)         //ramp down
  {
    writemotor3(m3throtA-m3adjval);       
    m3throtA = m3throtA-m3adjval;
  }
  else if(m3throtA<targ)    //ramp up
  {
    writemotor3(m3throtA+m3adjval);
    m3throtA = m3throtA+m3adjval;
  }
  else
  {writemotor3(m3throtA);}   //stay the same
  
  if(abs(m3throtA-targ)<=m3adjval)   //if its within the adjutment threshhold, write it directly to the target speed
  {
    writemotor3(targ);
    m3throtA = targ;
  }
}


void mapTargets() //set target throttles for each motor depending on input received from ps2 controller or i2c coms
{
  if(!haveController) //if no controller is plugged in, use i2c data. otherwise use ps2 controller input. 
  {
    /*m1throtT = 0;
    m2throtT = 0;
    m3throtT = 0;*/
    if(receivedBytes[0] == 1) //forward
    {
      m1throtT = 100;
    }
    else if(receivedBytes[0] == 2) //backward
    {
      m1throtT = -100;
    }
    else
    {
      m1throtT = 0;
    }
    
    if(receivedBytes[1] == 1) //left
    {
      m2throtT = 100;
    }
    else if(receivedBytes[1] == 2) //right
    {
      m2throtT = -100;
    }
    else
    {
      m2throtT = 0;
    }
  }
  else
  {
    if((abs(LX-128))<7) //set sticks to their midpoint if they're close to it. This fixes "drift" from the crappy controller sticks not springing all the way back to zero.
    {LX = 128;}
    if((abs(LY-128))<5)
    {LY = 128;}
    if((abs(RX-128))<7)
    {RX = 128;}
    
    int val1 = map(LY, 0, 255, 100, -100);  //negative and positive 100 swapped because the left right was backwards on the controller input.
    int val2 = map(LX, 0, 255, 100, -100);
    int val3 = map(RX, 0, 255, -100, 100);
    
    
    val1 = constrain(val1, -100, 100);
    val2 = constrain(val2, -100, 100);
    val3 = constrain(val3, -100, 100);
    
    m1throtT = val1;
    m2throtT = val2;
    m3throtT = val3;
  }
}

//takes the steering motor to the home position, intended to run once during setup
void homesteer()
{
  readlims();
  unsigned long th0 = millis();
  while((millis()-th0)<2000)
  {
    adjustmotor2(-20);
  }
  while(sLval>10)
  {
    readlims();
    adjustmotor2(20);
  }
  writemotor2(0);
  steerencpos = 0;
  steerposdeg = 0;
  m2pwmA = 0;             
  m2pwmT = 0;
  m2throtA = 0;           
  m2throtT = 0;
}
#endif