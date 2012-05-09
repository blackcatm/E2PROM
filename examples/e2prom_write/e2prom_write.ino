/*
 * EEPROM Write
 *
 * Stores values read from analog input 0 into the EEPROM.
 * These values will stay in the EEPROM when the board is
 * turned off and may be retrieved later by another sketch.
 */

#include <E2PROM.h>

//Light the LED on digital 13
#define FINISHLED 13

// the current address in the EEPROM (i.e. which byte
// we're going to write to next)
int addr = 0;

void setup()
{
  pinMode(FINISHLED, OUTPUT);
}

void loop()
{
  // need to divide by 4 because analog inputs range from
  // 0 to 1023 and each byte of the EEPROM can only hold a
  // value from 0 to 255.
  int val = analogRead(0) / 4;
  
  // write the value to the appropriate byte of the EEPROM.
  // these values will remain there when the board is
  // turned off.
  EEPROM.write(addr, val);
 
  // advance to the next address.
  
  addr = addr + 1;
  
  // there are E2END + 1 bytes in the EEPROM, so stop when
  // we get to E2END + 1. No need to wear out the EEPROM
  if (addr == E2END + 1){
    digitalWrite(FINISHLED, HIGH);  //indicate that we made it
    while(1){}
    digitalWrite(FINISHLED, LOW); //prove that it's really not getting here 
  }
  
  delay(100);
  
  //blink the LED while we're working
  digitalWrite(FINISHLED, addr % 2);
}
