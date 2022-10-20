#include <WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>

void callback(char* topic,byte* message,unsigned int length);

#define pinServo 26
#define mqtt_server "broker.hivemq.com"//your MQTT IP Address

Servo servo;

const char *ssid = "Kharisma Agri Inovasi";
const char *password = "PTKAI2020";
const char *base_url = "iterahero";
const char *pubtopik = "respon";
const char *subtopik = "actuator";

const int switchPin1 = 2;
const int switchPin2 = 4;
const int switchPin3 = 16;
const int switchPin4 = 17;
const int switchPin5 = 18;

char const* switchTopic1 = "iterahero/actuator/1";
char const* switchTopic2 = "iterahero/actuator/2";
char const* switchTopic3 = "iterahero/actuator/3";
char const* switchTopic4 = "iterahero/actuator/4";
char const* switchTopic5 = "iterahero/actuator/5";



WiFiClient wifiClient;
PubSubClient client(mqtt_server,1883,callback,wifiClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup(){
  pinMode(switchPin1,OUTPUT);// Relay switch 1
  digitalWrite(switchPin1,LOW);
  
  pinMode(switchPin2, OUTPUT); // Relay Switch 2
  digitalWrite(switchPin2, LOW);

  pinMode(switchPin3, OUTPUT); // Relay Switch 3
  digitalWrite(switchPin3, LOW);

  pinMode(switchPin4, OUTPUT); // Relay Switch 4
  digitalWrite(switchPin4, LOW);
  Serial.begin(115200);
  delay(100);
  WiFi.begin(ssid,password);
  reconnect();
    delay(1000);
}
void loop(){
  if (!client.connected() && WiFi.status() == 3) {reconnect();}
  client.loop();
  //client.subscribe(switchTopic1);
  //client.subscribe(switchTopic2);
  //client.subscribe(switchTopic3);
  //client.subscribe(switchTopic4);
  //client.subscribe(switchTopic5);
  delay(10);
}

void callback(char* topic, byte* message, unsigned int length) {
  String topicStr = topic;
  Serial.print("Message Arrived on topic:");
  Serial.print("Topic:");
  Serial.print("Message:");
  String messageTemp;

  for (int i = 0; i < length; i++){
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  if(String(topic) == "iterahero/actuator/1"){
    Serial.print("iterahero/actuator/1");
    if(messageTemp == "1"){
      Serial.println("HIGH");
      digitalWrite(switchPin1,HIGH);
      client.publish("iterahero/respon/actuator/1","1");
    }
    else if(messageTemp == "0"){
      Serial.println("LOW");
      digitalWrite(switchPin1,LOW);
      client.publish("iterahero/respon/actuator/1","0");
    }
  }
  else if(String(topic) == "iterahero/actuator/2"){
    Serial.print("iterahero/actuator/2");
    if(messageTemp == "1"){
      Serial.println("HIGH");
      digitalWrite(switchPin2,HIGH);
      client.publish("iterahero/respon/actuator/2","1");
    }
    else if(messageTemp == "0"){
      Serial.println("LOW");
      digitalWrite(switchPin2,LOW);
      client.publish("iterahero/respon/actuator/2","0");
    }
  }
  else if(String(topic) == "iterahero/actuator/3"){
    Serial.print("iterahero/actuator/3");
    if(messageTemp == "1"){
      Serial.println("HIGH");
      digitalWrite(switchPin3,HIGH);
      client.publish("iterahero/respon/actuator/3","1");
    }
    else if(messageTemp == "0"){
      Serial.println("LOW");
      digitalWrite(switchPin3,LOW);
      client.publish("iterahero/respon/actuator/3","0");
    }
  }
  else if(String(topic) == "iterahero/actuator/4"){
    Serial.print("iterahero/actuator/4");
    if(messageTemp == "1"){
      Serial.println("HIGH");
      digitalWrite(switchPin4,HIGH);
      client.publish("iterahero/respon/actuator/4","1");
    }
    else if(messageTemp == "0"){
      Serial.println("LOW");
      digitalWrite(switchPin4,LOW);
      client.publish("iterahero/respon/actuator/4","0");
    }
  }
  else if(String(topic) == "iterahero/actuator/5"){
    Serial.print("iterahero/actuator/5");
    if(messageTemp == "1"){
      Serial.println("HIGH");
      digitalWrite(switchPin5,HIGH);
      client.publish("iterahero/respon/actuator/5","1");
    }
    else if(messageTemp == "0"){
      Serial.println("LOW");
      digitalWrite(switchPin5,LOW);
      client.publish("iterahero/respon/actuator/5","0");
    }
  }
}
  
void reconnect(){
  if(WiFi.status()!= WL_CONNECTED){
    Serial.print("Connecting to...");
    Serial.println(ssid);
    
  while (WiFi.status()!= WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address:");
    Serial.println(WiFi.localIP());
  }

    if (WiFi.status()== WL_CONNECTED){
      while(!client.connected()){
        Serial.print("Attempting MQTT connection...");

        String clientName;
        clientName += "esp32-";
        uint8_t mac[6];
        WiFi.macAddress(mac);
        clientName += macToStr(mac);

        if(client.connect((char*) clientName.c_str())){
          Serial.print("\tMQTT Connected");
          client.subscribe(switchTopic1);
          client.subscribe(switchTopic2);
          client.subscribe(switchTopic3);
          client.subscribe(switchTopic4);
          client.subscribe(switchTopic5);
        }
        else{Serial.println("\tFailed.");abort();}
    } 
}
}
String macToStr(const uint8_t* mac){

  String result;

  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);

    if (i < 5){
      result += ':';
    }
  }

  return result;
}
