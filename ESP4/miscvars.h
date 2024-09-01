#ifndef MISC_VARS_H
#define MISC_VARS_H

#include <WiFi.h>
//wifi stuff
const char* ssid = "iPhone";
const char* password = "beepboop";    //this is definitely a strong password
WiFiServer server(80);
//IPAddress local_IP(***, ***, *, ***);  //hiding my IP from you internet weirdos
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

//data throughput stuff
float receiveFloats[20];
byte sendBytes[8];

#endif