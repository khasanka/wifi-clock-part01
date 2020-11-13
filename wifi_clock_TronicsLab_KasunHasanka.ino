#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CLK_PIN   14 //D5
#define DATA_PIN  13 //D7
#define CS_PIN    15 //D8

const char *ssid     = "TronicsLab";
const char *password = "kasun hasanka";

WiFiUDP ntpUDP;
const long offsetInSeconds = 5.5*60*60;
NTPClient timeClient(ntpUDP, offsetInSeconds);
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  P.begin();
  
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  timeClient.begin();
}

void loop() {
  timeClient.update();
  String mainTimeString = timeClient.getFormattedTime();
  String timeString = mainTimeString.substring(0,5);
  Serial.println(timeString);
  int len = timeString.length() + 1;
  char timeCharArray[len];
  timeString.toCharArray(timeCharArray, len);
 
  if (P.displayAnimate()) {
    P.displayText(timeCharArray, PA_CENTER, 0, 0, PA_NO_EFFECT);
  }
  
}
