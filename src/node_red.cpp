/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <WiFi.h>
#include <PubSubClient.h>
#include "confidential.h"
#include "thermometer.h"
#include <stdio.h>



WiFiClient espClient;
PubSubClient mqtt_client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;


void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
}

void node_red_publish(const char* topic, const char* data){
    mqtt_client.publish(topic, data);
}

void node_red_publish_temperatures(thermometer* thermometers, int n_thermometers){
  char number_c[50];
  for(int i = 0; i < n_thermometers; i++){
    sprintf(number_c, "%f", thermometers[i].T);
    node_red_publish(thermometers[0].name, number_c);

  }
}

void node_red_start(){
  printf("node red start\n");

  char* ssid = "Noa";
  const char* password = "hejhejhej";
  //WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.begin(ssid, password);


  printf("gonna connect\n");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  printf("Connected\n");

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mqtt_client.setServer(MQTT_BROKER, 1883);
  mqtt_client.setCallback(callback);
}
