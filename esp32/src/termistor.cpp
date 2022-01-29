#include "termistor.h"
#include "Arduino.h"

#include "max6675.h"

int thermoDO = 19;
int thermoCS = 23;
int thermoCLK = 5;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void termistor_main(){
   printf("C = %f\n", thermocouple.readCelsius()); 
   // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
   delay(1000);
}




