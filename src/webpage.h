#ifndef WEBPAGE
#define WEBPAGE


#include <WiFi.h>

void webpage_init();
void webpage_update();
double read_temp(int pin);
void disp_temps(WiFiClient client);

#endif