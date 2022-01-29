#include "thermocouple.h"
#include "Arduino.h"

#include "max6675.h"

#define DO  19
#define CS  23
#define CLK  5
// For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
#define WAIT_TIME_MS 500

static MAX6675 thermocouple(CLK, CS, DO);

float thermocouple_measure(){
   static unsigned long last_measured = 0;
   static float temperature = 0;

   // Wait a bit inbetween measurements
   if(millis() - last_measured <  WAIT_TIME_MS){
      return temperature;
   }

   temperature = thermocouple.readCelsius();
   return temperature;
}




