#include <Arduino.h>
#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
}

void loop() {
  Serial.println("Hello world");
  
  digitalWrite(2, HIGH);
  delay(500);

  digitalWrite(2, LOW);
  delay(500);

}