/*
 * EEPROM Read
 *
 * Reads the value of each byte of the EEPROM and prints it 
 * to the computer.
 * This example code is in the public domain.
 *
 * Example part of E2PROM, Extended EEPROM library.
 * 
 */

#include <E2PROM.h>

// start reading from the first byte (address 0) of the EEPROM
int address = 0;
byte value;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // read a byte from the current address of the EEPROM
  value = EEPROM.read(address);
  
  Serial.print(address);
  Serial.print("\t");
  Serial.print(value, DEC);
  Serial.println();
  
  // advance to the next address of the EEPROM
  address = address + 1;
  
  // there are only E2END + 1 bytes of EEPROM, from 0 to E2END, so if we're
  // on address E2END + 1, wrap around to address 0
  if (address == E2END + 1)
    address = 0;
    
  delay(500);
}
