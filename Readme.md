
# ESP8266 IFTTT Maker library


## Requiremets

* [Arduino IDE 1.6.5 or higher](https://www.arduino.cc/en/Main/Software)
* [IFTTT ESP8266 library](https://github.com/gamo256/IFTTT-esp/archive/master.zip)


## Setup

1. Go to the Arduino IDE, click on **Files -> Preferences** and enter http://arduino.esp8266.com/versions/2.2.0/package_esp8266com_index.json into Additional Board Manager URLs field. You can add multiple URLs, separating them with commas
2. Open Boards Manager from **Tools -> Board menu** and install esp8266 platform (and don't forget to select your ESP8266 board from Tools > Board menu after installation)
3. Download the IFTTT ESP8266 library [here](https://github.com/gamo256/IFTTT-esp/archive/master.zip)
4. Now, click on **Sketch -> Include Library -> Add .ZIP Library**
5. Select the .ZIP file of IFTTT-esp and then "Accept" or "Choose"
6. Close the Arduino IDE and open it again.
    
## Send one value to IFTTT Maker Channel

To send a value to dweet.io, go to **Sketch -> Examples ->  dweet-esp library** and select the "IFTTTSaveValue" example. 
Put your  Maker Event Name and key where indicated, as well as the WiFi settings.
Upload the code, open the Serial monitor to check the results. If no response is seen, try unplugging your board and then plugging it again. Make sure the baud rate of the Serial monitor is set to the same one specified in your code.

```c++
#include "IFTTTESP8266.h"
#define EVENT  "Your_Maker_Event_Name_here"  // Put here your Maker Event Name
#define KEY  "Your_Key_here"  // Put here your IFTTT key
#define WIFISSID "ssid"
#define PASSWORD "password"

IFTTT client(KEY);

void setup(){
    Serial.begin(115200);
    delay(10);
    client.wifiConnection(WIFISSID, PASSWORD);
}
void loop(){
    String value = String(analogRead(A0));
    client.add(value1); // specifies the args of type "String
    //Send value can specify up to three
    client.add(value2); // optional
    client.add(value3); // optional
    client.sendAll(EVENT);
}
```
