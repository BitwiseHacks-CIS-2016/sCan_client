#include <WiFi.h>
#include <Wire.h>
#include <BMA222.h>
#include "SPI.h"

#include <aJSON.h>
#include "M2XStreamClient.h"

char ssid[] = "BitwiseHacks"; //  your network SSID (name)
char pass[] = "bwhackathon"; // your network password (use for WPA, or use as key for WEP)

int status = WL_IDLE_STATUS;

char deviceId[] = "cf2da43cfec1175160be4825fc3f17ee"; // Feed you want to post to
char m2xKey[] = "8c6e7b4726806320c6671cb5f588551f"; // Your M2X access key
char streamName[] = "ldr_voltage"; // Stream you want to post to

//BMA222 mySensor;

WiFiClient client;

int port = 6;

M2XStreamClient m2xClient(&client, m2xKey);

void setup() {

  Serial.begin(9600);
//  pinMode(RED_LED, OUTPUT); 

//  mySensor.begin();
//  uint8_t chipID = mySensor.chipID();
//  Serial.print("chipID: ");
//  Serial.println(chipID);

  delay(10);

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid); 
  WiFi.begin(ssid, pass); // Use this if your wifi network requires a password
  // WiFi.begin(ssid);    // Use this if your wifi network is unprotected.
  while ( WiFi.status() != WL_CONNECTED) {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }
  Serial.println("\nConnect success!");
  Serial.println("Waiting for an ip address");

  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nIP Address obtained");

  // you're connected now, so print out the status  
  printWifiStatus();

}

void loop() {
  int sensorValue = analogRead(port);
  int voltage = sensorValue * (3.0/1023.0);
  
  int response;
  if(voltage > 0) {
     response = m2xClient.updateStreamValue(deviceId,streamName,0); 
  }
  else {
     response = m2xClient.updateStreamValue(deviceId,streamName,1);
  }
  
  delay(10000);
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

