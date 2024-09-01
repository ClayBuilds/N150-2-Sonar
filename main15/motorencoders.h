#ifndef MOTOR_ENCODERS_H
#define MOTOR_ENCODERS_H

void readlims()
{
  sLval = analogRead(steerL);
  tLval = analogRead(turrL);
}

void checkturrPosition()
{
  turrenc->tick();
  int newPos = turrenc->getPosition();
  if (turrencpos != newPos)
  {
    turrencpos = newPos;
    //turn the integer value into more useful degrees of rotation in the turret
    turrposdeg = -turrencpos*turrconvert;
    while(turrposdeg>360)
      {turrposdeg -= 360;}
    while(turrposdeg<0)
      {turrposdeg += 360;}
    sendFloats[0] = turrposdeg;   //put the data into the array that will be sent over i2c
  }
}

void checksteerPosition()
{
  steerenc->tick();
  int newPos = steerenc->getPosition();
  if (steerencpos != newPos)
  {
    steerencpos = newPos;
    //turn the integer value into more useful degrees of rotation in the turret
    steerposdeg = -steerencpos*steerconvert;
    while(steerposdeg>360)
      {steerposdeg -= 360;}
    while(steerposdeg<0)
      {steerposdeg += 360;}
    sendFloats[1] = steerposdeg;  //put the data into the array that will be sent over i2c
  }
}

void checkdrivePosition()
{
  driveenc->tick();
  int newPos = driveenc->getPosition();
  if (driveencpos != newPos)
  {
    driveencpos = newPos;
  }
}

void deadreckon()
{
  int d = driveencpos - lastdriveencpos;
  lastdriveencpos = driveencpos;
  float thrad = (steerposdeg-90)*PI/180.0; //plus 90 because I'm defining the positive y axis as 0 degrees for my steering rotation. so an angle of 0 degrees should give 1d for the y axis. 
  float dx = d*cos(thrad);
  float dy = -d*sin(thrad);   //minus sign here because I'm defining clockwise rotation as positive degrees. For example, a 10 degree value of steerposdeg is a slight right turn from its starting direction.
  xraw+=dx;
  yraw+=dy;
  xft = xraw*driveconvert;
  yft = yraw*driveconvert;
  sendFloats[2] = xft;
  sendFloats[3] = yft;
}

#endif