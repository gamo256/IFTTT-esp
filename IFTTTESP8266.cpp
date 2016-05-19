#include "IFTTTESP8266.h"

/**
 * Constructor.
 */
IFTTT::IFTTT(char* key){
    _key = key;
    maxValues = 3;
    currentValue = 0;
    val = (Value *)malloc(maxValues*sizeof(Value));
}

/**
 * Add a value of variable to save
 * @arg key variable key to save in a struct
 * @arg value variable value to save in a struct
 */
void IFTTT::add(String value){
  if(currentValue == maxValues){
    Serial.println(F("You are sending more than 3 consecutives variables, you just could send 3 variables. Then other variables will be deleted!"));
    //currentValue = maxValues;
  } else {
    //(val+currentValue)->id = key;
    (val+currentValue)->value_id = value;
    currentValue++;
  }
}
/**
 * Send all data of all variables that you saved
 * @reutrn true upon success, false upon error.
 */
bool IFTTT::sendAll(char *eventname){
    int i;
    String all;
    String str;
    all = "{";
    for(i=0; i<currentValue;){
        str = (val+i)->value_id;
        all += "\"value";
        all += String(i+1);
        all += "\":\"";
        all += str;
        all += "\"";
        i++;
        if(i<currentValue){
            all += ", "; 
        }
    }
    all += "}";
    i = all.length();
    Serial.println(all);
    
    if (_client.connect(SERVER, PORT)){
          Serial.println(F("Posting your variables"));
          _client.print(F("POST /trigger/"));
          Serial.print(F("POST /trigger/"));
          _client.print(eventname);
          Serial.print(eventname);
          _client.print(F("/with/key/"));
           Serial.print(F("/with/key/"));
          _client.print(_key);
          Serial.print(_key);
          _client.println(F(" HTTP/1.1"));
          Serial.println(F(" HTTP/1.1"));
          _client.println(F("Host: maker.ifttt.com"));
          Serial.println(F("Host: maker.ifttt.com"));
          _client.println(F("User-Agent: ESP8266-WiFi/1.0"));
          Serial.println(F("User-Agent: ESP8266-WiFi/1.0"));
          _client.println(F("Connection: close"));
          Serial.println(F("Connection: close"));
          _client.println(F("Content-Type: application/json"));
          Serial.println(F("Content-Type: application/json"));
          _client.print(F("Content-Length: "));
          Serial.print(F("Content-Length: "));
          _client.println(String(i));
          Serial.println(String(i));
          _client.println();
          Serial.println();
          _client.println(all);
          Serial.println(all);
          _client.println();
          Serial.println();
    }
    while(!_client.available());
    while (_client.available()){
        char c = _client.read();
        Serial.write(c);
    }
    currentValue = 0;
    _client.stop();
    return true;    
}
bool IFTTT::wifiConnection(char* ssid, char* pass){
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}