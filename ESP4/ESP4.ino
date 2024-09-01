//ESP
//There are several microcontrollers in this robot. This code runs on the ESP32 which sends and receives data over wifi.
//8-27-2024
//Version 4

/*changes from v3:
-not really anything. 

/*test results
-
*/

#include "I2Cstuff.h"
#include "miscvars.h"
#include "miscfuncs.h"
#include <WiFi.h>
#include <Wire.h>

void setup() 
{
  //I2C setup, running as a slave
  Wire.begin(0x09);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  
  Serial.begin(115200);

  // Attempt to connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.println("Server Started");
}

void loop() 
{
  //printfloats();
  //printbytes();
  //Serial.println(WiFi.localIP());
  
  WiFiClient client = server.available();

  if (client) 
  {
    //Serial.println("New Client Connected");

    // Send an array of 20 floats to the client
    float dataToSend[20];
    for (int i = 0; i < 20; i++) 
    {
      dataToSend[i] = receiveFloats[i]; //send the same floats received from the sonar board
    }

    client.write((uint8_t*)dataToSend, sizeof(dataToSend));
    //Serial.println("Sent array of 20 floats");

    // Wait to receive 8 bytes
    while (client.connected() && client.available() < 8) {
      // wait for the full data to be available
    }

    if (client.available() >= 8) 
    {
      byte receivedData[8];
      client.readBytes(receivedData, 8);
      
      for(int i = 0; i < 8; i++)
      {
        sendBytes[i] = receivedData[i]; //put the bytes you just received from wifi into the array you're going to send over i2c
      }

    }

  }
  
}
