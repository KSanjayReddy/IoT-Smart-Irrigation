#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

#define USERNAME "aditya"
#define DEVICE_ID "nodemcu"
#define DEVICE_CREDENTIAL "esp8266"

#define SSID "Zairza Net"
#define SSID_PASSWORD "notyourwifi"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {  
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(D0,INPUT);
  thing.add_wifi(SSID, SSID_PASSWORD);
  thing["led"] << digitalPin(BUILTIN_LED);
}

void loop() {
  int tmp;
  tmp = digitalRead(D0);
  if(tmp){
    thing["security"] >> [](pson& out){
      out = "Alert";
};
  }
  else{
    thing["moisture1"] >> [](pson& out){
      out = analogRead(A0);
};
  }
  thing["security"] >> [](pson& out){
      out = "Safe";
};

  thing.handle();
}
