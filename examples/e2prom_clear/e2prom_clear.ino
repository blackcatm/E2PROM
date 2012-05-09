/*
 * EEPROM Clear
 *
 * Sets all of the bytes of the EEPROM to 0.
 * This example code is in the public domain.
 *
 * Example part of E2PROM, Extended EEPROM library.
 * 
 */

#include <E2PROM.h>

//Light the LED on digital 13
#define FINISHLED 13

void setup()
{
  pinMode(FINISHLED, OUTPUT);
  
  // write a 0 to all bytes of the EEPROM
  EEPROM.set(0, E2END + 1);
    
  // turn the LED on when we're done
  digitalWrite(FINISHLED, HIGH);
  
}

void loop()
{
}