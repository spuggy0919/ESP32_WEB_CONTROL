#include "ESP32inc.h"
#include <Time.h>

// Create AsyncWebServer object on port 80
AsyncWebServer  server(80);
// Create an Server Sent Event (SSE) Source on /events
AsyncEventSource events("/events");


// SSE variables 
String currentTime;
int triggerCnt = 10;

void webEventTask(){
    // Handle Web Server Events
  events.onConnect([](AsyncEventSourceClient *client){
    Serial.println("events.onConnect ...");
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    // client->send("hello!", NULL, millis(), 10000);
    client->send(String(timerCurrent()).c_str(),"currenttime",millis(), 8000);
    // client->send(pwmledState.c_str(),"gpiostate",millis());

  });
  server.addHandler(&events);  // Handle Web Server Events
}
void eventPrint(String msg){
  msg += "\n\n"; // SSE protocol ending with two "\n\n"
  events.send(msg.c_str(),"textarea",millis());
  Serial.println("event: "+msg); 
}
void eventPrintln(String msg){
  eventPrint(msg);
  Serial.println("event: "+msg); 
}

// 1. Replaces placeholder %STATE% with LED state value
// 2. using SSE to change it. (now)
String processor(const String& var) {
  // if(var == "STATE") {
  //   events.send(pwmledState.c_str(),"gpiostate",millis());
  //   return pwmledState;
  // }
  // if(var == "CHARTDATA") {
  //   return pwmlogData(); // placeholder %CHARTDATA% in index.htm
  // }
  // if(var == "CURRENTTIME") {
  //   events.send(timerCurrent().c_str(),"currenttime",millis());
  //   return timerCurrent();
  // }
  // if (var == "SLIDERVALUE"){
  //   return String(pwmledr());
  // } 
  return String();
}

// Web HTTP Server
void notFoundPage(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "404 Not Found");
}
#define OK200() request->send(200, "text/plain", "200 OK")

String dumpParams(AsyncWebServerRequest *request){
  String plist = "/param?";
  for(int i=0;i< request->params();i++){
      AsyncWebParameter *p = request->getParam(i);
      Serial.print("Param name: "); 
      Serial.println(p->name()); plist += p->name() +"=" ;
      Serial.print("Param value: ");
      Serial.println(p->value()); plist += p->value();
      if (i !=  request->params()-1) plist +=  "&";
  }
  return plist;
}
String indexPath = "/index.html";
void WebServerPage()
{

  server.serveStatic("/", LittleFS, "/");  // for style.css load
  // Route to set GPIO state to LOW
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    eventPrintln("HTTP_GET / ");
    request->send(LittleFS, indexPath, "text/html", false, processor);
  });
  server.on("/on", HTTP_POST, [](AsyncWebServerRequest *request) {
    pwmled(255);
    events.send(pwmledState.c_str(),"gpiostate",millis());
    eventPrintln("HTTP_POST /on "+pwmledState);
    OK200();
    // request->send(LittleFS, indexPath, "text/html", false, processor);
  });
  server.on("/off", HTTP_POST, [](AsyncWebServerRequest *request) {
    pwmled(0);
    events.send(pwmledState.c_str(),"gpiostate",millis());
    eventPrintln("HTTP_POST /off "+ pwmledState);
    OK200();
    // request->send(LittleFS, indexPath, "text/html", false, processor);
  });
  server.on("/trigger", HTTP_POST, [](AsyncWebServerRequest *request) {
    pwmtriggerstart();
    eventPrintln("HTTP_POST /trigger ");
    OK200(); // no content for stay same page
    // request->send(LittleFS, indexPath, "text/html", false, processor);
  });
  // Send a GET request to <ESP_IP>/param?value=<inputMessage>
  // ex. <ESP_IP>/param?field1=value1&field2=value2&field3=value3...
  server.on("/param", HTTP_POST, [] (AsyncWebServerRequest *request) {
    String value = "";
    // text loger can input enter key to send txt line
    if (request->hasParam("cmd")) {
      value = request->getParam("cmd")->value();
      Serial.println("recv String:"+value);
      value = "cmd=" + value;
    }
    if (request->hasParam("slider")) {
      value = request->getParam("slider")->value();
      pwmled(value.toInt()); // fpr ESP32 pwm led 
      Serial.println("pwm value for LED:"+value);
      value = "slider=" + value;
    }
    if (request->hasParam("timer")) {
      value = request->getParam("timer")->value();
      if (value != ""){
        // Serial.println("clientTime="+clientTime);
        // set RTC epoch 
        String timeinsec=value.substring(0,value.length()-3);
        unsigned long t = atol(timeinsec.c_str());
        // Serial.println(t);
        timerSetEpoch(t);
        value = "timer=" + value;
      }
    }
    if (value == "") {
       value = dumpParams(request);
    }
    eventPrintln("HTTP_POST/param?"+value);
    OK200();
  });
  // 4. Set up Server Sent Event
  webEventTask();

  server.begin();
  Serial.println("WebServerGPIOControl Starting..."); 

}

void setup(){
  Serial.begin(115200);
  Serial.println("Web Control");
  pwminit();
  // 1. *** modified your SSID, PASSWORD pair 
  if (!WiFiInit(WIFI_STA_AUTO_MODE,"Kuo", "22320397")) {
      Serial.println("Error:Wifi fail");
      return ;
  } 
  // 2, mount and initalize littlefs for reading page locates in file system

  if(!initLittleFS()){
      Serial.println("Error:LittleFS init fail...");
      return ;
  }  

  // check LittleFS , it is not necessary 
  // listDir(LittleFS,"/",2);
  // String indexfile = readFile(LittleFS,"/index.html");

  // 3, start up Web Server
  WebServerPage();
}

static int curmillis = millis();
void loop(){

  // similar as log data
  pwmtrigger(500, triggerCnt, (bool)(triggerCnt%2)); // true:pwm, false: no pwm

  // input key counter
  int button = debounceKeyRead(BUTTON_PIN); // read new state  
  if(button == LOW) {
    triggerCnt++; 
    if (triggerCnt>30) triggerCnt = 1;
    // eventPrint("E: triggerCnt"+String(triggerCnt));
    events.send(String(triggerCnt).c_str(),"switchcnt",millis());
    // Serial.printf("The button is pressed(%2d)\r",triggerCnt);
    // toggle state of LED
    pwmled(255);
    events.send("ON","gpiostate",millis());

  }
  if (KeygetChange()){
     events.send((button == LOW)? "1" : "0","onoff",millis());
     pwmled((button == LOW)? 255 : 0);
     events.send((button == LOW)? "ON": "OFF" ,"gpiostate",millis());
  }
  // SSE push event Update
  if (pwmledChange) {
     Serial.println("pwmledChange"+pwmledState);
     events.send(pwmledState.c_str(),"gpiostate",millis());
    //  eventPrint("E:LED "+pwmledState+ " " +String(pwmtriggernum())+ "pwm:" +String(pwmledr()));
  if (!pwmtriggerStopOrNot()){ // trigging
      eventPrint(pwmlogData()+" \r");
  }     pwmledChange =false;
  }

  if ((millis() - curmillis) > 5000  ) {
      curmillis = millis();
      events.send(timerCurrent().c_str(),"currenttime",millis());
      // eventPrintln("E:"+timerCurrent());
  } 

}