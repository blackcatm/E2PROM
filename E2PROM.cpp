/*
  E2PROM.cpp - Extended EEPROM library for Arduino
  Copyright (c) 2006 David A. Mellis.  All right reserved.
  Copyright (c) 2012 J.P. McGlinn. All Rights reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/******************************************************************************
 * Includes
 ******************************************************************************/

#include <avr/eeprom.h>
#include "E2PROM.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/

/******************************************************************************
 * Constructors
 ******************************************************************************/
E2PROM::E2PROM(){
    setLineEnding(0);
}

/******************************************************************************
 * Private Methods
 ******************************************************************************/

void E2PROM::printASCII(char * buffer, Stream &output){
    for(int i = 0; i < 16; i++){
        if(i == 8)
            output.print(" ");
        
        if(buffer[i] > 31 and buffer[i] < 127){
            output.print(buffer[i]);
        }else{
            output.print(".");
        }
    }
}

/******************************************************************************
 * User API
 ******************************************************************************/

void E2PROM::setLineEnding(char *lineEnding){
    if(lineEnding){
        strncpy(_lineEnding, lineEnding, MAXLENLINEENDING);
    }else{
        strncpy(_lineEnding, "\n", MAXLENLINEENDING);
    }
}

uint8_t E2PROM::read(int address)
{
	return eeprom_read_byte((unsigned char *) address);
}

void E2PROM::write(int address, uint8_t value)
{
	eeprom_write_byte((unsigned char *) address, value);
}

int E2PROM::set(byte value, unsigned int start, unsigned int count){
    if((start + count) - 1 > E2END)
        return 0;
    
    for(unsigned int i = start; i < start + count; i++)
        write(i, value);
    
    return count;
};

void E2PROM::print(Stream &output){
    char buffer[16];
    char valuePrint[4];
    byte value;
    unsigned int address;
    uint8_t trailingSpace = 2;
    
    output.print("Dumping "); output.print(E2END + 1);
    output.print(" bytes from EEPROM.");
    output.print(_lineEnding);
    output.print("baseAddr ");
    for(int x = 0; x < 2; x++){
        output.print(" ");
        for(int y = 0; y < 25; y++)
            output.print("=");
    }
    
    // E2END is a macro defined as the last EEPROM address
    // (1023 for ATMEGA328P)
    for(address = 0; address <= E2END; address++){
        // read a byte from the current address of the EEPROM
        value = EEPROM.read(address);
        
        // add space between two sets of 8 bytes
        if(address % 8 == 0)
            output.print("  ");
        
        // newline and address for every 16 bytes
        if(address % 16 == 0){
            //print the buffer
            if(address > 0 && address % 16 == 0)
                printASCII(buffer, output);
            
            sprintf(buffer, "%s 0x%05X: ",_lineEnding, address);
            output.print(buffer);
            
            //clear the buffer for the next data block
            memset (buffer, 32, 16);
        }
        
        // save the value in temporary storage
        buffer[address%16] = value;
        
        // print the formatted value
        sprintf(valuePrint, " %02X", value);
        output.print(valuePrint);
    }
    
    if(address % 16 > 0){
        if(address % 16 < 9)
            trailingSpace += 2;
        
        trailingSpace += (16 - address % 16) * 3;
    }
    
    for(int i = trailingSpace; i > 0; i--)
        output.print(" ");
    
    //last line of data and a new line
    printASCII(buffer, output);
    output.print(_lineEnding);
}




E2PROM EEPROM;
