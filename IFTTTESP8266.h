#ifndef _IFTTTESP8266_H_
#define _IFTTTESP8266_H_

#include <ESP8266WiFi.h>

#define SERVER "maker.ifttt.com"
#define PORT 80

typedef struct Value {
  // char *id;
  String value_id;
} Value;

class IFTTT {
   public:
      IFTTT(char* key);
      bool sendAll(char *eventname);
      void add(String value);
      bool wifiConnection(char *ssid, char *pass);
   
   private:
      char* _key;
      uint8_t maxValues;
      uint8_t currentValue;
      Value * val;
      float parseValue(String body);
      WiFiClient _client; 
};

#endif