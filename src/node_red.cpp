/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <WiFi.h>
#include <PubSubClient.h>
#include "confidential.h"
#include "thermometer.h"
#include <stdio.h>

void reconnect();


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
  if(!mqtt_client.publish(topic, data)){
    printf("failed to send %s to %s\n", data, topic);
  }
  else{
    printf("successfully sent %s to %s\n", data, topic);
  }
  
}

void node_red_publish_temperatures(thermometer* thermometers, int n_thermometers){
  // If disconnected from the broker attempt to reconnect
  if(!mqtt_client.connected()){
    reconnect();
  }

  char number_c[50];
  for(int i = 0; i < n_thermometers; i++){
    sprintf(number_c, "%f", thermometers[i].T);
    node_red_publish(thermometers[i].name, number_c);
    //printf("Published to topic: %s\n", thermometers[i].name);
  }
  
}

void node_red_start(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);


  printf("gonna connect to wifi %s with password %s\n", WIFI_SSID, WIFI_PASSWORD);
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
  printf("Node red started\n");
}

void reconnect() {
  // Loop until we're reconnected
  while (!mqtt_client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqtt_client.connect("arduinoClient")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      mqtt_client.publish("test","Reconnected!");
      // ... and resubscribe
      mqtt_client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
