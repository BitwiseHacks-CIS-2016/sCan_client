#include <WiFi.h>
#include <Wire.h>
#include <BMA222.h>
#include "SPI.h"

#include <aJSON.h>
#include "M2XStreamClient.h"

char ssid[] = "BitwiseHacks"; //  your network SSID (name)
char pass[] = "bwhackathon"; // your network password (use for WPA, or use as key for WEP)

int status = WL_IDLE_STATUS;

char deviceId[] = " 4031a753526af7ad07ec534e059c52da"; // Feed you want to post to
char m2xKey[] = "6be81fc77c44b5d8238ee01092c082a"; // Your M2X access key
char streamName[] = "ldr_voltage"; // Stream you want to post to

//BMA222 mySensor;

WiFiClient client;
//Initialise the port for the LDR
int port = 6;
//Setup the connection to M2X
M2XStreamClient m2xClient(&client, m2xKey);

void setup() {
//Start the serial monitor at 9600 baud.
  Serial.begin(9600);
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
  }// Confirm connection and inform the user that the launchpad is waiting to obtain the IP address.
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
  //Read the resistance in the LDR and assign the value to the integer variable sensorValue
  int sensorValue = analogRead(port);
  //Do a quick calculation to convert the resistance to voltage.
  int voltage = sensorValue * (3.0/1023.0);
  // Initialise a variable that will be used to send data to the M2X device.
  int response;
  if(voltage > 0) { // If the voltage is greater than 0 i.e. The LDR detects brightness.
     response = m2xClient.updateStreamValue(deviceId,streamName,0); //Send a 0 binary digit to M2X, meaning that the rubbish bin is not full.
  }
  else { // Otherwise if the LDR reads a value of 0, meaning it is dark...
     response = m2xClient.updateStreamValue(deviceId,streamName,1); // Send a 1 binary digit to M2X, meaning that the rubbish bin is full.
  }
  
  delay(10000); // Wait 10 seconds. The LDR is checked every 10 seconds. 
  Serial.println("sCAN is still functioning"); //Tell the user that the program is still running.
}

void printWifiStatus() { // A method that does the following:
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}
