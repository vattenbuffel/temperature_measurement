/* Comments:
    Code to measure temperature using a termistor. It seems to be accurate to about 2 degrees
*/




#include "thermometer.h"
#include "Arduino.h"
#include "node_red.h"
#include <WiFi.h>


struct thermometer temperature = {
  .pin = 35,
  .read_res = 12,
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

/*double ReadVoltage(byte pin){
  double reading = analogRead(pin); // Reference voltage is 3v3 so maximum reading is 3v3 = 4095 in range 0 to 4095
  if(reading < 1 || reading > 4095) return 0;
  // return -0.000000000009824 * pow(reading,3) + 0.000000016557283 * pow(reading,2) + 0.000854596860691 * reading + 0.065440348345433;
  return (-0.000000000000016 * pow(reading,4) + 0.000000000118171 * pow(reading,3)- 0.000000301211691 * pow(reading,2)+ 0.001109019271794 * reading + 0.034143524634089)*1.03;
} // Added an improved polynomial, use either, comment out as required
*/

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
  
  node_red_start();

  // Configure the pins
  for (int i = 0; i < n; i++)
    thermometers[i].pin = pins[i];

  analogReadResolution(12);

}

void loop(){
  update_all_thermometers(thermometers, n);  
  node_red_publish_temperatures(thermometers, n);
  printf("32: %f\n", analogRead(32)*3.3/4095);
  printf("33: %f\n", analogRead(33)*3.3/4095);
  printf("34: %f\n", analogRead(34)*3.3/4095);
  printf("35: %f\n", analogRead(35)*3.3/4095);
  

  delay(1000);

}



