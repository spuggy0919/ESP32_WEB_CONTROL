#ifndef __WEBSERVER__H__
#define __WEBSERVER__H__


#include <Arduino.h>
#include "wifiinit.h"



#ifdef ESP32
  #include <AsyncTCP.h>
// #define _PROCESSOR_ESP_ "ESP32"
#else
  #include <ESPAsyncTCP.h>
  #include <Hash.h>
#endif
#include <ESPAsyncWebServer.h>

#define SETUP_STATE 0
#define LOOP_STATE  1

// #include "WebHello.h"

// bool WebwifiManage();
// bool WebNTPPage();
// void WebInputServer();


// // NTP
// bool WebNTPManage();
// void WebNPTloop();
#endif