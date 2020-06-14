/* Comments:
    Code to measure temperature using a termistor. It seems to be accurate to about 2 degrees

*/


/*  TODO:
      The other todos.
*/

#include "webpage.h"

// Load Wi-Fi library
#include <WiFi.h>
#include "thermometer.h"


struct thermometer temperature = {
  .pin = 35,
  .read_res = 11,
  .P = 0,
  .motion_noise = 0.00000000000000001,
  .meas_noise = 10,
  .a = 0.001049960637, 
  .b = 0.0002509871139,
  .c = -0.00000001794237955,
  .u_in = 3.3, 
  .R_in = 6800,
  .T = 0,
  .motion_model = 1,
  .meas_model = 1,
  .x = 1.1
};

const int n = 2; 
struct thermometer thermometers[n] = {temperature, temperature}; 
char names[n][50] = {{"Test name 1"},{"Test name 2"}};
int pins[n] = {32, 35};

int counter = 0;
void setup() {
  Serial.begin(115200);
  
  // Add the names to the thermomemters
  for (int i = 0; i < n; i++) {
    if (strlen(names[i]) < name_max_len)
      strcpy(thermometers[i].name, names[i]);
    else{
      printf("Name too long, naming thermometer to unnamed\n");
      strcpy(thermometers[i].name, "unnamed");
    }
  }

  // Configure the pins
  for (int i = 0; i < n; i++)
    thermometers[i].pin = pins[i];

  webpage_init();
  analogReadResolution(11);

}

void loop(){
  update_all_thermometers(thermometers, n);  
  webpage_update(thermometers);
  delay(100);
}



