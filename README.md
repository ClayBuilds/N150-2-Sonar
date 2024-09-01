# N150-2-Sonar
This is the second iteration of my control code for the Nomadic Technologies N150 robot. I've now implemented sonar functionality, a basic gui, and dead reckoning via motor encoders. 

There are four main code groups. "mainXX" runs on the microcontroller wired to all the motor drivers, encoders and limit switches.
"ESPX" runs on the ESP32, and just handles wifi coms. 
"sonarXX" runs on the microcontroller wired to the sonar electronics, it handles timing and rangefinding for all 16 sonar transducers.
"processingskethchX" is just the gui, it displays received data onscreen and sends arrow key commands back to the robot. 
