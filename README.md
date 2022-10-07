# ESP32 WEB CONTROL TUTORIAL
# [English](03_ESP32_Http_GPIO/README.md)
# [中文](03_ESP32_Http_GPIO/讀我.md)

### base on LilttleFS, ESPWebAsyncServer to create a Control Page, 
It can use IO, log, sent msg, chart,...

### *NOTICES* If you are not familier with ESP32, or Platform.IO. 
Step by Step, 00 to 02.

Both ESP32 and ESP8266 supported.

Study from Littlefs and Wifi, then  WebAsyncServer 

### [*00_ESP32_littlefs*](00_ESP32_littlefs/README.md)    
study lorol/LittleFS library and others 

### [*01_ESP32_Http_Hello*](01_ESP32_Http_Hello/README.md)  
study ESP WEB ASYNC SERVER library,for client javascript and HTML

### [*02_ESP32_Http_LITTLEFS*](02_ESP32_Http_LITTLEFS/README.md) 
combines aboves, index.html stores in Littlefs.


### *NOTICES* If you are experts, Good, start from 03. 

### *03_ESP32_Http_GPIO*
All of libraries and use Javascript, HTML skills


# Modify your SSID and PASSWORD in main.cpp
```
// 1. *** modified your SSID, PASSWORD pair 
  if (!WiFiInit(WIFI_STA_AUTO_MODE,"SSID", "PASSWORD")) {
      Serial.println("Error:Wifi fail");
      return ;
  } 
```
