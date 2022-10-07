# [中文](./讀我.md)
# Mobile Phone Browser Control ESP32 And ESP Log Respones
[spuggy0919/ESP32_WEB_CONTROL](https://github.com/spuggy0919/ESP32_WEB_CONTROL)

Base on me-no-dev/ESPAsyncWebServer, lorol/Littlefs libraries.

Using Server Sent Event, and javascript，exchange messages from server to client

Let phone or computer be Keyboard, touch panel, display ...of your ESP32 device.

  

Functions:
  
## client to Server(HTTP Control)

1. Sync client epoch time to ESP32.
2. Send control command to ESP32, client can click UI button, or slider UI Control. Turn on Led, pwm setting.
3. In SSE textarea, user can send string text to ESP32 as command interpreter.
4. Javascript modfy page UI, add new UI control with interpreter.（*idea*）

## Server to Client (iot Log and run task)

1.  server report LED status, switch press or not.
2.  Server send simple txt for Label in page.
3.  Server send event log, it act as Serial Monitor.
4.  Server can log data for updating Chart。(*TODO*)
5.  ESP32 cmd interpreter。（*idea*）

### *Notice* ESP8266 has no builtin RTC Time.

# Platform.IO IDE
  ESP32 is supported.
 Web Server use me-no-dev/ESPAsyncWebServer
 *Platform.io* will check dependecy and download dependency libraries automatically.
 Tool bar at bottom , click Switch  env icon to select Project and env
#### For ESP32
```
*env:esp32dev (03_esp32_Http_GPIO) folder*
```

# Edit *platform.ini*.
 Select esp32dev 
#### For ESP32
```
[platformio]
default_envs = esp32dev
; default_envs = nodemcuv3
```

 We also define *lib_extra_dirs* in *platform.ini* , then *platform.io* will search this path.
 It is located in *00_esp32_littlefs/lib* folder

```
lib_extra_dirs = ../00_esp32_littlefs/lib
```
# In main.cpp, include below.
All self defined functions include.
```
#include "ESP32inc.h" // ESP32 only, because time rtc
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
// 4. Set up Server Sent Event
  webEventTask();
```

# Build and Upload, need to push EN button.
 Click the pio tool bar upload icon, for clean build, you can delete *.pio* sub folder in explorer Window at first.

# upload file system, and need to push EN button.
 It will upload data folder to partition SPIFFS, it is OK.
 Click the pio tool bar terminal icon, then cli terminal will display, make sure path with your data then run command in terminal.
```
03_ESP32_Http_GPIO % pio run -t uploadfs [enter]
```

# Running, serial Monitor will display below Messages
```
Web HTTP Control
WiFiSTA() 
WiFiSTAStatic(ssid SSID,pwd PASSWORD,ip, gw ) 
Config as auto IP
Connecting to WiFi...
..192.168.1.149
WebServerGPIOControl Starting...
pwmledChangeON
```
# browser visits http://192.168.1.149 or http://192.168.1.149/any

### You will see control page

# Good Luck!