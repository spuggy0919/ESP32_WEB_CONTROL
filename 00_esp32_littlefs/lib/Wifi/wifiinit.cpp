#include "wifiinit.h"
#include "ledpwm.h"

/* 
  WIFI utility wifi 0.2
  Wifi initialize, mode select from arguments 
  #Function
  WiFiInit(int mode, ...)
  @Arguments
  mode : int 
      #define WIFI_AP_MODE 0
      #define WIFI_STA_AUTO_MODE 1
      #define WIFI_STA_STATIC_MODE 2


  Eaxamples:
  WiFiInit(WIFI_AP_MODE); // AP mode 
  WiFiInit(WIFI_STA_AUTO_MODE, "ssid", "password"); // auto mode 

 */

//Variables to save values from HTML form
String ssid = "SSID";   // modfied for STA mode
String pass = "PASSWORD"; // modfied for STA mode
String ip = "192.168.1.200"; // modfied for STA static ip mode
String gateway = "192.168.1.1"; // modfied for STA static ip mode

IPAddress local_IP(192,128,1,200); // modfied for STA static ip mode
// Set your Gateway IP address
IPAddress local_Gateway(192, 168, 1, 1); // modfied for STA static ip mode
//IPAddress localGateway(192, 168, 1, 1); //hardcoded
IPAddress subnet(255, 255, 255, 0);

// Timer variables
unsigned long previousMillis = 0;
const long interval = 60000;  // interval to wait for Wi-Fi connection (milliseconds)



bool WiFiInit(int mode,...)
{
  va_list arguments;
  local_IP.fromString(ip);
  local_Gateway.fromString(gateway);
    bool r=false;
    pwminit();
    va_start ( arguments, mode );
    switch(mode) {
    case WIFI_AP_MODE:
      r = WiFiAP();
      break;
    case WIFI_STA_AUTO_MODE:
        ssid = String (va_arg ( arguments, const char* ));
        pass = String (va_arg ( arguments, const char* ));
        r = WiFiSTAAutoIP();
      break;
    case WIFI_STA_STATIC_MODE:
        ssid = String (va_arg ( arguments, const char* ));
        pass = String (va_arg ( arguments, const char* ));
        ip = String (va_arg ( arguments, const char* ));
        gateway = String (va_arg ( arguments, const char* ));
        r = WiFiSTAStaticIP(ssid, pass, ip, gateway);
      break;
    default: r=false;
          break;
    }
    va_end ( arguments ); 
    if (r) {
      pwmled(255);
    }
    return r;
}
bool WiFiSTAAutoIP() 
{
     Serial.println("WiFiSTA() AutoMode ");
     return WiFiSTAStaticIP(ssid, pass, "", "");
}
bool WiFiSTAStaticIP(String ssid,String pass,String ip, String gateway) {
  Serial.println("WiFiSTAStatic(ssid "+ ssid +",pwd "+ pass +",ip"+ ip +", gw "+ gateway +") ");
  Serial.println("if ip and gateway is null then Auto Sta mode");

  if(ssid=="" ){
    Serial.println("ERROR:Undefined SSID .");
    return false;
  }

  WiFi.mode(WIFI_STA);
  if (ip!="" && gateway!="" ) {
//   for Fixed IP
    Serial.println("Config as Static IP");

    local_IP.fromString(ip.c_str());
    local_Gateway.fromString(gateway.c_str());
  
  
    if (!WiFi.config(local_IP, local_Gateway, subnet)){
      Serial.println("ERROR:STA Failed to configure");
      return false;
    }
  }else{
    Serial.println("Config as auto IP");
  }
  WiFi.begin(ssid.c_str(), pass.c_str());
  Serial.println("Connecting to WiFi...");

  unsigned long currentMillis = millis();
  previousMillis = currentMillis;

  while(WiFi.status() != WL_CONNECTED) {
    currentMillis = millis();
    Serial.print(".");
    if (currentMillis - previousMillis >= interval) {
      Serial.println("ERROR:Failed to connect.");
      ESP.restart();
      return false;
    }
    delay(500);
  }
  Serial.println(WiFi.localIP());
  return true;
}

bool WiFiAP() {
  Serial.println("Initialize Wifi as AP");
  Serial.println("Warning:This mode will lost some internet hyperlink!");

  WiFi.disconnect();
  WiFi.softAP("ESP-WIFI-WEB", NULL);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP); 
  return true;
}