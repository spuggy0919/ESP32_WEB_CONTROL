#include "ESP32_8266.h"

AsyncWebServer server(80);

void notFoundPage(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "404 Not Found");
}
void WebServerPage()
{
 
   server.serveStatic("/", LittleFS, "/");  // for style.css load

  // Send web page to  client (HTTP_GET)
  server.on("/", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send(LittleFS, "/index.html", "text/html");
  });
  server.onNotFound(notFoundPage);
  
  server.begin();
  Serial.println("Server Starting...");
}

void setup(){
  Serial.begin(115200);
  Serial.println("Web With LittleFS");
  pwminit();
  // 1. *** modified your SSID, PASSWORD pair 
  if (!WiFiInit(WIFI_STA_AUTO_MODE,"SSID", "PASSWORD")) {
      Serial.println("Error:Wifi fail");
      return ;
  } 
  // 2, mount and initalize littlefs for reading page locates in file system

  if(!initLittleFS()){
      Serial.println("Error:LittleFS init fail...");
      return ;
  }  

  // check LittleFS , it is not necessary 
  listDir(LittleFS,"/",2);
  String indexfile = readFile(LittleFS,"/index.html");

  // 3, start up Web Server
  WebServerPage();
}

void loop(){

}
