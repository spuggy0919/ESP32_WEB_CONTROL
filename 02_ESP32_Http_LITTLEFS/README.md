# [中文](./讀我.md)
# Homepage save into LittleF
The Web Server read html file in LittleFS for HTTP_GET and other respones.
Here we can study javascritp at client side, and HTML control, but server does not implement.
# Platform.IO IDE
 Both ESP32 and ESP8266 are supported
 Web Server use me-no-dev/ESPAsyncWebServer
 *Platform.io* will check dependecy and download dependency libraries automatically.
 Tool bar at bottom , click Switch  env icon to select Project and env
#### For ESP32
```
*env:esp32dev (02_esp32_Http_LITTLEFS) folder*
```
#### For ESP8266
```
*env:nodemcuv3 (02_esp32_Http_LITTLEFS) folder*
```
# Edit *platform.ini*.
 Select esp32dev and nodemcu environment 
#### For ESP32
```
[platformio]
default_envs = esp32dev
; default_envs = nodemcuv3
```
#### For ESP8266
```
[platformio]
; default_envs = esp32dev
default_envs = nodemcuv3
```
 We also define *lib_extra_dirs* in *platform.ini* , then *platform.io* will search this path.
 It is located in *00_esp32_littlefs/lib* folder

```
lib_extra_dirs = ../00_esp32_littlefs/lib
```
# In main.cpp, include below.
All self defined functions include.
```
  #include "ESP32_8266.h"
```

 config WIFI MODE in winit.cpp
 if STA modified SSID PASS in *WiFiInit*, the Server dispatchs some *HTTP_GET* and respones.
```
// 1. *** modified your SSID, PASSWORD pair 
  if (!WiFiInit(WIFI_STA_AUTO_MODE,"****", "********")) {
      Serial.println("Error:Wifi fail");
      return ;
  } 
// 2, mount and initalize littlefs for reading page locates in file system

  if(!initLittleFS()){
      Serial.println("Error:LittleFS init fail...");
      return ;
  }
// 3, start up Web Server
  WebServerPage();
```
# Build and Upload, need to push EN button.
 Click the pio tool bar upload icon, for clean build, you can delete *.pio* sub folder in explorer Window at first.

# upload file system, and need to push EN button.
 It will upload data folder to partition SPIFFS, it is OK.
 Click the pio tool bar terminal icon, then cli terminal will display, make sure path with your data then run command in terminal.
```
02_ESP32_Http_LITTLEFS % pio run -t uploadfs [enter]
```

# Running, serial Monitor will display below Messages
```
PWM init...done!
WiFiSTA() AutoMode 
WiFiSTAStatic(ssid *****,pwd ********,ip, gw ) 
if ip and gateway is null then Auto Sta mode
Config as auto IP
Connecting to WiFi...
..192.168.1.149
Server Starting...
```
# browser visits http://192.168.1.149 or http://192.168.1.149/any

```
http://192.168.1.149
http://192.168.1.149/button.html 
http://192.168.1.149/slider.html   
http://192.168.1.149/chart.html   
http://192.168.1.149/switch.html   
http://192.168.1.149/textare.html 
```

# Good Luck!

# [Back to Top](../README.md)