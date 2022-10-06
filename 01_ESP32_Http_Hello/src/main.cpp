#include <Arduino.h> 
#include "debuglog.h" // log print
#include "ledpwm.h"   // esp32 pin 2 can use pwm mode, ESP8266 cannot.
// #include "littlefsfun.h" // ittlefs
#include "WebServer.h" // i.e. ESPAsyncWebServer include...

AsyncWebServer server(80);

void notFoundhello(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "404 Not found");
}
void WebServerHello()
{
 
  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", "Hello World!");
  });
  server.onNotFound(notFoundhello);
  
  server.begin();
  Serial.println("Server Starting...");
}

void setup(){
  Serial.begin(115200);
  Serial.println("Web Hello World");
  pwminit();
  // 1. *** modified your SSID, PASSWORD pair 
  if (!WiFiInit(WIFI_STA_AUTO_MODE,"SSID", "PASSWORD")) {
      Serial.println("Error:Wifi fail");
      return ;
  } 
  // 2, start up Web Server
  WebServerHello();
}

void loop(){

}
