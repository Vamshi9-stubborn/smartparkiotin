#include <NewPing.h>
#include <ESP8266WiFi.h>
#include<WiFiClient.h>
#include<PubSubClient.h>

void callback(char*topic,byte*payload,unsigned int length1);
void reconnect();
const char*ssid="Varun ";
const char*password="Varun196";
const int trigPin=2;
const int echoPin=0;
long duration;
int distance;

unsigned long lastMillis=0;
const char*mqtt_server="3.140.200.220";
int mqtt_port=1883;
WiFiClient espClient;

PubSubClient client(espClient);

void setup(){

  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);

  Serial.begin(9600);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("connecting to");
  Serial.print("ssid");
  WiFi.begin("ssid","password");
  while (WiFi.status() !=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("192,168,1,102");
  Serial.println(WiFi.localIP());
  delay(3000);

  client.setServer("3.140.200.220",1883);
  client.setCallback(callback);

  reconnect();

}


   
void callback(char* topic, byte* payload, unsigned int length)
{
  String str;
  Serial.print("Message Arrived [i]");
  Serial.print(topic);
  Serial.println(".");
  for(int i=0; i<length; i++)
  {
    str+=((char)payload[i]);
    }
    Serial.println(str);
    }
    void reconnect()
    {
      while(WiFi.status()!=WL_CONNECTED)
    {
      delay(50);
    Serial.print(".");
    }
    while(!client.connected())
    {
      if(client.connect("test"))
      {
        Serial.println("Connected...");
        client.subscribe("test");
        }
        else
        {
          Serial.print("failed, rc=");
        Serial.println(client.state());
        delay(100);
        }
        }
        }
        void loop(){
          
       
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);


duration= pulseIn(echoPin,HIGH);

distance=duration*0.034/2;

Serial.print("distance= ");
Serial.println("distance");

if(distance<=10){
  
  Serial.print("parking is not available");
  client.publish("test","!!Parking is not available");
  delay(2000);

}
else{
  Serial.println("PARKING AVAIALBLE");
  client.publish("test","PARKING AVAILABLE");
  delay(2000);
}

if(!client.connected()){
  reconnect();
}
client.loop();
client.subscribe("test");
}

  
