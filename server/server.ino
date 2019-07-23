#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

int gpio2_pin =1;
int sc2=0;
int a=0;

MDNSResponder mdns;

const char* ssid = "XPERIA";
const char* pass = "00000000";

/*const char* ssid = "Deathstart";
const char* pass = "4f2day1Kn0";*/

const char *mqtt_server = "m24.cloudmqtt.com";
const int mqtt_port = 17587;
const char *mqtt_user = "fnetydgq";
const char *mqtt_pass = "SEbDu7GOHR35";

#define BUFFER_SIZE 100


IPAddress ip(192,168,43,2);  //статический IP
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

String webPage = "";
String webPage1 = "";
String webPage2 = "";
String webPage3 = "";

WiFiClient wclient;      
PubSubClient client(wclient, mqtt_server, mqtt_port);

void callback(const MQTT::Publish& pub)     // Функция получения данных от сервера
{
    Serial.print(pub.topic());                // выводим в сериал порт название топика
    Serial.print(" => ");
    Serial.println(pub.payload_string());     // выводим в сериал порт значение полученных данных
    
    String payload = pub.payload_string();
    
    if(String(pub.topic()) == "test/num")    //  проверяем из нужного ли нам топика пришли данные 
    {
        int num = payload.toInt();         //  преобразуем полученные данные в тип integer
        if (num==1){
          webPage=webPage1;
        }
        if (num==2){
          webPage=webPage2;
        }
    }
     if(String(pub.topic()) == "test/sc1")    //  проверяем из нужного ли нам топика пришли данные 
    {
        int num = payload.toInt();         //  преобразуем полученные данные в тип integer
        if (num==1){
          digitalWrite(gpio2_pin, LOW);
          delay(1000);
        }
        if (num==0){
          digitalWrite(gpio2_pin, HIGH);
          delay(1000);
        }
    }
   
}


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
  webPage2 +="</head>";
  webPage2 +="<body bgcolor= #c0faff>";
  webPage2 +="<center>";
  webPage2 +="&nbsp;";
  webPage2 +="<a href=\"socket1On\" class= button7>ON</a>";
  webPage2 +="<a href=\"socket1Off\" class= button7>OFF</a>";
  webPage2 +="&nbsp;";
  webPage2 +="<a href=\"socket2On\" class= button7>ON</a>";
  webPage2 +="<a href=\"socket2Off\" class= button7>OFF</a>";
  webPage2 +="</center>";
  webPage2 +="</body>";
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
digitalWrite(gpio2_pin, HIGH);
 
 webPage=webPage1;
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  server.on("/socket1On", [](){
    server.send(200, "text/html", webPage);
    a=0;
    delay(1500);
  });
  server.on("/socket1Off", [](){
    server.send(200, "text/html", webPage);
    a=1;
    delay(1500);
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
}

void loop() {
    // подключаемся к wi-fi
    
  
    if (WiFi.status() != WL_CONNECTED) {
        Serial.print("Connecting to ");
        Serial.print(ssid);
        Serial.println("...");
        WiFi.begin(ssid, pass);
    }
        if (WiFi.waitForConnectResult() != WL_CONNECTED){
            return;}
        Serial.println("WiFi connected");
        Serial.println(WiFi.localIP());
       
     WiFi.config(ip, gateway, subnet);
     
    // подключаемся к MQTT серверу
    if (WiFi.status() == WL_CONNECTED) {
        if (!client.connected()) {
            Serial.println("Connecting to MQTT server");
            if (client.connect(MQTT::Connect("arduinoClient2")
                                 .set_auth(mqtt_user, mqtt_pass))) {
                Serial.println("Connected to MQTT server");
                client.set_callback(callback);
                client.subscribe("test/num"); 
                client.subscribe("test/sc2"); 
                client.subscribe("test/sc1"); 
            } else {
                Serial.println("Could not connect to MQTT server");   
            }
        }
        
        if (client.connected()){
            
            client.loop();
            
            server.handleClient();
            if (sc2==0){
              client.publish("test/sc2", String("0"));
            }
            if (sc2==1){
              client.publish("test/sc2", String("1"));
            }
            digitalWrite(gpio2_pin, a);
            delay(1000);
            Serial.print(WiFi.localIP());
        }
    }
} 



