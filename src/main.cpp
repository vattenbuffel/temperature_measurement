/* Comments:
    Code to measure temperature using a termistor. It seems to be accurate to about 2 degrees

*/


/*  TODO:
      Implement Kalman to improve measurements!
*/

#include "webpage.h"

// Load Wi-Fi library
#include <WiFi.h>


void setup() {
  Serial.begin(115200);
  webpage_init();
  //int pins[6] = {36, 39, 34, 35, 32, 33};
  analogReadResolution(11);

  //printf("100 = %f\n", read_temp_main(5));
  
}

void loop(){
  webpage_update();
  /*for (int i = 32; i < 36; i++){
    double temp = read_temp_main(i);
    Serial.printf("temp on pin %d : %0.4f \n", i, (double)temp);
  }
  Serial.println("");
  delay(2500);
*/}



