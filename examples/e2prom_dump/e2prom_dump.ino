/*
 * EEPROM Dump
 *
 * Prints the output of all bytes of EEPROM memory
 *
 * Example part of E2PROM, Extended EEPROM library.
 * Written by J.P. McGlinn for Black Cat Microelectronics.  
 *
 * EEPROM Dump is meant as a debugging tool. This is an expensive
 * function to include, taking about 2.5k of flash above just
 * whatever including the Serial interface.
 *
 * E2PROM.print can print to different Streams, so it should
 * work with software serial ports and I even used it with
 * the EthernetClient. Just pass the Stream as a parameter
 * as seen in the example. If no Stream is passed, Serial is assumed.
 * 
 */


#include <E2PROM.h>

void setup(){
  // Should open the stream you will be using, in this case the first
  // hardware serial port. I like fast, so 57,600 baud!
  Serial.begin(57600);
  
  // If you don't like the default line endings, change them. If you
  // need a really long line ending you might have to adjust the max
  // defined size in E2EPROM.h. Factory setting allows 7 characters.
  //EEPROM.setLineEnding(" BOB\n");
  
  // now just tell the EEPROM to print, optionally include a stream
  // to send the printed output to. In this example we specify Serial,
  // even though it is the default.
  EEPROM.print(Serial);
}

void loop(){
}
