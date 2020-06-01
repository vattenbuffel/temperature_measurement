#ifndef WEBPAGE
#define WEBPAGE


#include <WiFi.h>
#include "thermometer.h"

void webpage_init();
void webpage_update(thermometer* thermometers);
double read_temp(int pin); // REMOVE?
void disp_temps(WiFiClient client, thermometer* thermometer);

#endif