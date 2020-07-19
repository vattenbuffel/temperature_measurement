/* Comments:
    Code to measure temperature using a termistor. It seems to be accurate to about 2 degrees
*/




#include "thermometer.h"
#include "Arduino.h"
#include "node_red.h"
#include <WiFi.h>


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

const int n = 4; 
struct thermometer thermometers[n] = {temperature, temperature, temperature,temperature}; 
char names[n][50] = {{"fran tank"},{"panna ut"},{"till tank"}, {"matarvatten"}};// 32, 35, 34, 33
int pins[n] = {32, 35, 34, 33};

int counter = 0;
void setup() {
  Serial.begin(115200);
  delay(500);

  // Add the names to the thermomemters
  for (int i = 0; i < n; i++) {
    if (strlen(names[i]) < name_max_len)
      strcpy(thermometers[i].name, names[i]);
    else{
      printf("Name too long, naming thermometer to unnamed\n");
      strcpy(thermometers[i].name, "unnamed");
    }
  }
  
  printf("gonna go to node_red_start\n");
  node_red_start();
  for(;;){
    thermometers[0].x = 1;
    calc_temp(&thermometers[0]);
    printf("Voltage %f corresponds to temperature %f\n", thermometers[0].x, thermometers[0].T);
    
    thermometers[0].x = 3.3;
    calc_temp(&thermometers[0]);
    printf("Voltage %f corresponds to temperature %f\n", thermometers[0].x, thermometers[0].T);
    
    thermometers[0].x = 1.5;
    calc_temp(&thermometers[0]);
    printf("Voltage %f corresponds to temperature %f\n", thermometers[0].x, thermometers[0].T);
    
    thermometers[0].x = 2;
    calc_temp(&thermometers[0]);
    printf("Voltage %f corresponds to temperature %f\n", thermometers[0].x, thermometers[0].T);
    
    thermometers[0].x = 3;
    calc_temp(&thermometers[0]);
    printf("Voltage %f corresponds to temperature %f\n", thermometers[0].x, thermometers[0].T);
    
    printf("\n");
    delay(10000);
  }





  // Configure the pins
  for (int i = 0; i < n; i++)
    thermometers[i].pin = pins[i];

  analogReadResolution(11);

}

void loop(){
  update_all_thermometers(thermometers, n);  
}



