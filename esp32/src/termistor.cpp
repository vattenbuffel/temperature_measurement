#include "termistor.h"
#include "Arduino.h"

#include "max6675.h"

int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;

static MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void termistor_main(){
   printf("C = %f\n", thermocouple.readCelsius()); 
   // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
   delay(1000);
}




