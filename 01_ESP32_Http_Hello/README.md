# [中文](./讀我.md)
# Hello World! Web Server
# Platform.IO IDE
 Both ESP32 and ESP8266 are supported
 Web Server use me-no-dev/ESPAsyncWebServer
 *Platform.io* will check dependecy and download dependency libraries automatically.
 Tool bar at bottom , click Switch  env icon to select Project and env
#### For ESP32
```
*env:esp32dev (01_esp32_Hello) folder*
```
#### For ESP8266
```
*env:nodemcuv3 (01_esp32_Hello) folder*
```
# Edit *platform.ini*.
 Select esp32 and nodemcu environment 
 You also can compiler both, platform.io will select right code and Serial to download, it takes longer.
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
# In main.cpp, include these files which will be used.
```
  #include <Arduino.h> 
  #include "debuglog.h" // log print
  #include "ledpwm.h"   // esp32 pin 2 can use pwm mode, ESP8266 cannot.
  #include "WebServer.h" // i.e. ESPAsyncWebServer include...
```

 config WIFI MODE in winit.cpp
 if STA modified SSID PASS in *WiFiInit*, the Server dispatchs some *HTTP_GET* and respones.
```
// 1. *** modified your SSID, PASSWORD pair 
  if (!WiFiInit(WIFI_STA_AUTO_MODE,"****", "********")) {
      Serial.println("Error:Wifi fail");
      return ;
  } 
// 2, start up Web Server
  WebServerHello();
```
# Build and Upload, need to push EN button.
 Click the pio tool bar upload icon, for clean build, you can delete *.pio* sub folder in explorer Window at first.

# upload file system, and need to push EN button.
 It will upload data folder to partition SPIFFS, it is OK.
 Click the pio tool bar terminal icon, then cli terminal will display, make sure path with your data then run command in terminal.
```
01_ESP32_Http_Hello % pio run -t uploadfs [enter]
```
# Running, serial Monitor will display below Messages
```
Web Hello World
WiFiSTA() 
WiFiSTAStatic(ssid SSID,pwd PASSWORD,ip, gw ) 
Config as auto IP
Connecting to WiFi...
..192.168.1.149
Server Starting...
```
# browser visits http://192.168.1.149 or http://192.168.1.149/any

### You will see "Hello World!" or "404 not Found"

# Good Luck!

# [Back to Top](../README.md)