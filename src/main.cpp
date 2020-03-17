
#include "webpage.h"

// Load Wi-Fi library
#include <WiFi.h>



void setup() {
  Serial.begin(115200);
  webpage_init();
  
}

void loop(){
  webpage_update();
  
}