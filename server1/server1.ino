#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

int gpio2_pin = 2;
int sc2=0;

MDNSResponder mdns;

const char* ssid = "Deathstart";
const char* pass = "4f2day1Kn0";

const char *mqtt_server = "m24.cloudmqtt.com";
const int mqtt_port = 17587;
const char *mqtt_user = "fnetydgq";
const char *mqtt_pass = "SEbDu7GOHR35";

#define BUFFER_SIZE 100


IPAddress ip(192,168,1,17);  //статический IP
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

String webPage = "";
String webPage1 = "";
String webPage2 = "";
String webPage3 = "";

WiFiClient wclient;      

void setup() {
     //web page 1 head
  webPage1 +="<head>";
  webPage1 +="<title>Smart Socket</title>";
  webPage1 +="<link rel=”stylesheet” href=”style.css”  type=”text/css”/>";
  webPage1 +="<style>";
  webPage1 +="@font-face { font-family: 'SFUIDisplay-Bold';  src: local('SFUIDisplay-Bold'), url('https://nomail.com.ua/files/woff/7e427ee9b99fcefb1560e6757a2d853e.woff') format('woff'); }";
  webPage1 +="a.button7 {display:table-cell;margin: auto;width: 250px;height: -13px;font-weight: 500;font-family: SFUIDisplay-Bold;color: white;text-decoration: none;padding: .8em 1em calc(.8em + 3px);border-radius: 3px;background: rgb(24,60,75);transition: 0.2s;}";
  webPage1 +="a.button7:hover { background: rgb(69, 146, 152); }";
  webPage1 +="}";
  webPage1 +="</style>";
  webPage1 +="</head>";
  webPage1 +="<body bgcolor= #c0faff>";
  webPage1 +="<center>";
  webPage1 +="&nbsp;";
  webPage1 +="<a href=\"socket1On\" class= button7>ON</a>";
  webPage1 +="<a href=\"socket1Off\" class= button7>OFF</a>";
  webPage1 +="</center>";
  webPage1 +="</body>";
 //web page 1 tale

 //web page 2 head
  webPage2 +="<head>";
  webPage2 +="<title>Smart Socket</title>";
  webPage2 +="<link rel=”stylesheet” href=”style.css”  type=”text/css”/>";
  webPage2 +="<style>";
  webPage2 +="@font-face { font-family: 'SFUIDisplay-Bold';  src: local('SFUIDisplay-Bold'), url('https://nomail.com.ua/files/woff/7e427ee9b99fcefb1560e6757a2d853e.woff') format('woff'); }";
  webPage2 +="a.button7 {display:table-cell;margin: auto;width: 250px;height: -13px;font-weight: 500;font-family: SFUIDisplay-Bold;color: white;text-decoration: none;padding: .8em 1em calc(.8em + 3px);border-radius: 3px;background: rgb(24,60,75);transition: 0.2s;}";
  webPage2 +="a.button7:hover { background: rgb(69, 146, 152); }";
  webPage2 +="}";
  webPage2 +="</style>";
 /* webPage2 +="</head>";
  webPage2 +="<body bgcolor= #c0faff>";
  webPage2 +="<center>";
  webPage2 +="&nbsp;";
  webPage2 +="<a href=\"socket1On\" class= button7>ON</a>";
  webPage2 +="<a href=\"socket1Off\" class= button7>OFF</a>";
  webPage2 +="&nbsp;";
  webPage2 +="<a href=\"socket2On\" class= button7>ON</a>";
  webPage2 +="<a href=\"socket2Off\" class= button7>OFF</a>";
  webPage2 +="</center>";
  webPage2 +="</body>";*/
 //web page 2 tale
 
    Serial.begin(115200);
    delay(10);

   
    Serial.println();
    Serial.println();
  
    pinMode(gpio2_pin, OUTPUT);
    if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
               //  "Запущен MDNSresponder"
  }
 
 webPage=webPage1;
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  server.on("/socket1On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio2_pin, LOW);
    delay(1000);
  });
  server.on("/socket1Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio2_pin, HIGH);
    delay(1000);
  });
  server.on("/socket2On", [](){
    server.send(200, "text/html", webPage);
    sc2=1;
  });
  server.on("/socket2Off", [](){
    server.send(200, "text/html", webPage);
    sc2=0;
  });
  server.begin();
  Serial.println("HTTP server started");
  WiFi.config(ip, gateway, subnet);
}

void loop() {
    
    Serial.println(WiFi.localIP());
    server.handleClient();
    
    
    // подключаемся к MQTT серверу
    
} 


    
   

