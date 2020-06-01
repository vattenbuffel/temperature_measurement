#ifndef THERMOMETER_H
#define THERMOMETER_H

#define name_max_len 50

struct thermometer{
    int pin, read_res;
    double P, motion_noise, meas_noise, a, b, c, u_in, R_in, T, motion_model, meas_model, x;
    char name[name_max_len];
};

void predict_step(thermometer* THERMOMETER);
void update_step(thermometer* THERMOMETER);
void calc_temp(thermometer* THERMOMETER);
void update_all_thermometers(thermometer* thermometers, int n);

#endif