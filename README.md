# ESP32 WEB CONTROL TUTORIAL
# [English](03_ESP32_Http_GPIO/README.md)
# [中文](03_ESP32_Http_GPIO/讀我.md)

base on LilttleFS, ESPWebAsyncServer to create a Control Page, 
it can use IO, log, sent msg, chart,...

# *NOTICES* If you are not familier with ESP32, or Platform.IO. 
Study from Littlefs and Wifi, then  WebAsyncServer Step by Step, 00 to 02 can be use in ESP8266, too.

## *00_ESP32_littlefs study*     lorol/LittleFS library and others 

## *01_ESP32_Http_Hello study*   ESP WEB ASYNC SERVER library

## *02_ESP32_Http_LITTLEFS*      combine aboves, index.html store in Littlefs.


*NOTICES* If you are experts, Good, Use below.

## *03_ESP32_Http_GPIO*          All of libraries and Use Javascript, HTML skills


# remember to modified SSID and PASSWORD in main.cpp
```
// 1. *** modified your SSID, PASSWORD pair 
  if (!WiFiInit(WIFI_STA_AUTO_MODE,"SSID", "PASSWORD")) {
      Serial.println("Error:Wifi fail");
      return ;
  } 
```
