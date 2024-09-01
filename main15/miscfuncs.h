//miscellaneous functions that don't fit elsewhere, mostly for testing purposes


#ifndef MISCFUNCS_H
#define MISCFUNCS_H

//This function prints the positions as determined by encoders
void printencs()
{
  Serial.print("Steering Raw: ");
  Serial.print(steerencpos);
  Serial.print(" Steering Deg: ");
  Serial.print(steerposdeg);
  Serial.print("     Turret Raw: ");
  Serial.print(turrencpos);
  Serial.print(" Turret Deg: ");
  Serial.print(turrposdeg);
  Serial.print("     Drive Raw: ");
  Serial.print(driveencpos);
  Serial.print(" Xft: ");
  Serial.print(xft);
  Serial.print(" Yft: ");
  Serial.println(yft);
}

//This function prints the values read by the limit switches.
void printlims()
{
  Serial.print("Steering: ");
  Serial.print(sLval);
  Serial.print("     Turret: ");
  Serial.println(tLval);
}


//This function prints the analog stick readings from the controller for debugging
void printcontroller()
{
  Serial.print("LX: ");
  Serial.print(LX);
  Serial.print("  LY: ");
  Serial.print(LY);
  Serial.print("  RX: ");
  Serial.print(RX);
  Serial.print("  RY: ");
  Serial.print(RY);
  Serial.print("  CONTROLLER: ");
  Serial.println(haveController);
}

//this function prints an array of 16 values, with each number corresponding to the button press of that index
void printbuts()
{
  for(byte i = 0; i<16; ++i)
  {
    Serial.print("  ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(BUTTNUMS[i]);
  }
  Serial.println(" ");
}

//prints actual motor pwm signal value and target throttle (%)
void printmotvals()
{
  Serial.print("DRIVE MOTOR: Throttle: ");
  Serial.print(m1throtT);
  Serial.print(" PWM actual: ");
  Serial.print(m1pwmA);
  
  Serial.print("     STEER MOTOR: Throttle: ");
  Serial.print(m2throtT);
  Serial.print(" PWM actual: ");
  Serial.print(m2pwmA);
  
  Serial.print("     TURRET MOTOR: Throttle: ");
  Serial.print(m3throtT);
  Serial.print(" PWM actual: ");
  Serial.print(m3pwmA);
  
  Serial.println(" ");
}

//prints values received over i2c from the master. an array of bytes. 
void printreceived()
{
  Serial.print("Received: ");
  Serial.print(receivedBytes[0]);
  Serial.print(" ");
  Serial.print(receivedBytes[1]);
  Serial.print(" ");
  Serial.print(receivedBytes[2]);
  Serial.print(" ");
  Serial.print(receivedBytes[3]);
  Serial.print(" ");
  Serial.print(receivedBytes[4]);
  Serial.print(" ");
  Serial.print(receivedBytes[5]);
  Serial.print(" ");
  Serial.print(receivedBytes[6]);
  Serial.print(" ");
  Serial.println(receivedBytes[7]);
}

void printPIDstuff()
{
  Serial.print("Adiff: ");
  Serial.print(adiff);
  Serial.print("   PIDOUT: ");
  Serial.println(PIDOutput);
}

#endif