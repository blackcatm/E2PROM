/*
  E2PROM.h - Extended EEPROM library for Arduino
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

#ifndef E2PROM_h
#define E2PROM_h

#include <Arduino.h>
#include <inttypes.h>
#include <Stream.h>

#define MAXLENLINEENDING 7

class E2PROM
{
  public:
    E2PROM();    
    
    uint8_t read(int);
    void write(int, uint8_t);

    int set(byte value, unsigned int count){ return set(value, 0, count); }
    int set(byte value, unsigned int start, unsigned int count);

    void setLineEnding(char *lineEnding);
    
    void print() { print(Serial); }
    void print(Stream &output);
  private:
    void printASCII(char *buffer, Stream &output);
    
    char _lineEnding[MAXLENLINEENDING + 1];
};

extern E2PROM EEPROM;

#endif

