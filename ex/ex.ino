#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

int gpio2_pin = 2;

MDNSResponder mdns;

const char* ssid = "Deathstart";
const char* pass = "4f2day1Kn0";

const char *mqtt_server = "m24.cloudmqtt.com";
const int mqtt_port = 17587;
const char *mqtt_user = "fnetydgq";
const char *mqtt_pass = "SEbDu7GOHR35";

#define BUFFER_SIZE 100

IPAddress ip(192,168,1,16);  //статический IP
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

String webPage = "";
String webPage1 = "";
String webPage2 = "";
String webPage3 = "";

void callback(const MQTT::Publish& pub)     // Функция получения данных от сервера
{
    Serial.print(pub.topic());                // выводим в сериал порт название топика
    Serial.print(" => ");
    Serial.println(pub.payload_string());     // выводим в сериал порт значение полученных данных
    
    String payload = pub.payload_string();
    
    if(String(pub.topic()) == "test/sc2")    //  проверяем из нужного ли нам топика пришли данные 
    {
        int num = payload.toInt(); 
        if (num==0){
          digitalWrite(gpio2_pin,1);
          delay(10);
        }
        if (num==1){
          digitalWrite(gpio2_pin,0);
          delay(10);
        }
    
   
}
}


WiFiClient wclient;      
PubSubClient client(wclient, mqtt_server, mqtt_port);

void setup() {
    
 
    Serial.begin(115200);
    delay(10);
    
   
    
    Serial.println();
    Serial.println();
  
    pinMode(gpio2_pin, OUTPUT);
    if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
               //  "Запущен MDNSresponder"
  }
 
 

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
        
        if (WiFi.waitForConnectResult() != WL_CONNECTED)
            return;
        Serial.println("WiFi connected");
    }
    
    // подключаемся к MQTT серверу
    if (WiFi.status() == WL_CONNECTED) {
        if (!client.connected()) {
            Serial.println("Connecting to MQTT server");
            if (client.connect(MQTT::Connect("arduinoClient2")
                                 .set_auth(mqtt_user, mqtt_pass))) {
                Serial.println("Connected to MQTT server");
                client.set_callback(callback);
                client.subscribe("test/sc2");                  // подписывааемся по топик с данными для светодиода
                              // подписывааемся по топик с данными для Сервопривода
            } else {
                Serial.println("Could not connect to MQTT server");   
            }
        }
        
        if (client.connected()){
            client.loop();
                     
        }
    }
} 

