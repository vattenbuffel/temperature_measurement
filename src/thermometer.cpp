#include "thermometer.h"
#include <math.h>
#include "Arduino.h"

/*
TODO:
*/

double ReadVoltage(byte pin){
  double reading = analogRead(pin); // Reference voltage is 3v3 so maximum reading is 3v3 = 4095 in range 0 to 4095
  if(reading < 1 || reading > 4095) return 0;
  // return -0.000000000009824 * pow(reading,3) + 0.000000016557283 * pow(reading,2) + 0.000854596860691 * reading + 0.065440348345433;
  return (-0.000000000000016 * pow(reading,4) + 0.000000000118171 * pow(reading,3)- 0.000000301211691 * pow(reading,2)+ 0.001109019271794 * reading + 0.034143524634089)*1.03;
} // Added an improved polynomial, use either, comment out as required


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
  double y = ReadVoltage(Thermometer->pin);

  double S = c*P*c + R;
  double K = P*c/S;
  double v = y - c*x;
  
  Thermometer->x = x + K*v;
  Thermometer->P = P - K*S*K; 
}

void calc_temp(thermometer* Thermometer){
  double x = Thermometer->x;
  double R = Thermometer->R_in*Thermometer->u_in /x - Thermometer->R_in;
  Thermometer->T =  1/(Thermometer->a + Thermometer->b*log(R) + Thermometer->c*pow(log(R), 3)) - 273.15; // -273.15 to convert from Kelvin to Celsius
}