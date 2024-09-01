#ifndef TURRETANDSTEERMATCH_H
#define TURRETANDSTEERMATCH_H

#include <QuickPID.h>

void steermatch()
{
  if(haveController)  //stop the PID loop if there's a controller connected
  {
    turrPID.SetMode(0);
    return;
  }
  else
  {
    turrPID.SetMode(1);
  }
  
  turrPID.Compute();
  //steer angle is in azimuth where 0 = straight ahead, 180 = reverse, 90 = right , 270 = left (like a compass looking down from above)
  //turret is the same
  
  float adjustedval = turrposdeg + steerturroffset; //account for the fact that I want the position 140 degrees clockwise of turret zero to be what is actually matched to steering direction. They don't have same zero.
  if(adjustedval>360)
  {adjustedval-=360;}
  
  adiff = adjustedval - steerposdeg;     //adiff is the "error" for the PID. It's how far off the goal is from the actual heading. Keep it at zero.
  
  //the following two statements handle any weirdness if goal and current are on opposite sides of 0, i.e. if it's 358 degrees minus 2 degrees, that shouldn't be a 356 degree turn.
  if(adiff>180)   //so that it won't try ant turn around the "long" way left
  {adiff-=360;}
  
  if(adiff<(-180))  //so that it won't try and turn around the "long" way right
  {adiff+=360;}
  
  //if(abs(adiff)<3)  //stop constantly running a tiny pwm duty cycle when adiff is extremely close, a few degrees is good enough for now. 
  //{adiff = 0;}
  
  //set pid input based on angle error. note: adiff>0 left turn, adiff<0 right turn
  PIDInput = adiff;
  //at this point the PIDInput, is in the range of +/- 180 degrees
  
  m3throtT = PIDOutput; //set the throttle target on the turret motor equal to the PID output
  

  //safeguards to prevent out of bounds throttle
  if(m3throtT>100)
  {m3throtT = 100;}
  if(m3throtT<-100)
  {m3throtT = -100;}

}


#endif