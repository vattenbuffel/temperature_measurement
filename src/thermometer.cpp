#include "thermometer.h"
#include <math.h>
#include <WiFi.h> //To get analogread

/*
TODO:
*/

void update_all_thermometers(thermometer* thermometers, int n){
  for(int i = 0; i < n; i++){
    predict_step(&thermometers[i]);
    update_step(&thermometers[i]);
    calc_temp(&thermometers[i]);
  }
  
}

void predict_step(thermometer* Thermometer){
  Thermometer->x = Thermometer->x * Thermometer->motion_model;
  Thermometer->P = Thermometer->motion_model * Thermometer->x * Thermometer->motion_model + Thermometer->motion_noise;
}

void update_step(thermometer* Thermometer){
  double P = Thermometer->P;
  double c = Thermometer->meas_model;
  double R = Thermometer->meas_noise;
  double x = Thermometer->x;
  double y = analogRead(Thermometer->pin) * Thermometer->u_in / (pow(2, Thermometer->read_res) - 1);

  double S = c*P*c + R;
  double K = P*c/S;
  double v = y - c*x;
  

  Thermometer->x = x + K*v;
  Thermometer->P = P - K*S*K; 
}

void calc_temp(thermometer* Thermometer){
  double x = Thermometer->x;
  double R = Thermometer->R_in*Thermometer->u_in/x - Thermometer->R_in;
  Thermometer->T =  1/(Thermometer->a + Thermometer->b*log(R) + Thermometer->c*pow(log(R), 3)) - 273.15; // -273.15 to convert from Kelvin to Celsius
}