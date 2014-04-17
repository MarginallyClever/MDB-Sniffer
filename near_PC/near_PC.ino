//------------------------------------------------------------------------------
// MDB Parser - Make MDB communications human readable
// 2014-04-15 dan@marginallyclever.com
// Copyright at end of file.
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------

#include <SoftwareSerial.h>
#include "config.h"



//------------------------------------------------------------------------------
// GLOBALS
//------------------------------------------------------------------------------

SoftwareSerial MDB(10,11);
byte msg_address;
byte msg_data[MAX_MSG_LEN];
int msg_count=0;




//------------------------------------------------------------------------------
// METHODS
//------------------------------------------------------------------------------

void setup() {
  Serial.begin(57600);
  Serial.print("Hello from near PC\n");
  MDB.begin(57600);
  digitalWrite(10,HIGH);  // pull up resistor
}


void loop() {
  if(MDB.available()) {
    char data,mode;
    mode = MDB.read();
    data = MDB.read();

    if(mode!=0) {
      // address byte is start of a new message block
      msg_count=0;
      msg_address = data;
    } else {
      // data or checksum
      if(msg_count<MAX_MSG_LEN) {
        msg_data[msg_count++]=data;
      }
      
      if(calculate_checksum()) {
        // TODO could the checksum be received prematurely by accident?
        
        parse_message();
        Serial.print("\n");
      }
    }
  }
  
  //if(Serial.available()) {
  //  MDB.write(Serial.read());
  //}
}


byte calculate_checksum() {
  byte value = msg_address;
  for(int i=0;i<msg_count;++i) {
    value+=msg_data[i];
  }
  return value;
}


void parse_message() {
  switch(msg_address & ADDRESS_MASK) {
  case ADDRESS_VMC      :  VMC_parse();  break;
  case ADDRESS_CHANGER  :  CHANGER_parse();  break;
  case ADDRESS_GATEWAY  :  GATEWAY_parse();  break;
  case ADDRESS_DISPLAY  :  DISPLAY_parse();  break;
  case ADDRESS_EMS      :  EMS_parse();  break;
  case ADDRESS_VALIDATOR:  VALIDATOR_parse();  break;
  case ADDRESS_AVD      :  AVD_parse();  break;
  case ADDRESS_CD1      :  CD_parse(1);  break;
  case ADDRESS_CD2      :  CD_parse(2);  break;
  case ADDRESS_USD1     :  USD_parse(1);  break;
  case ADDRESS_USD2     :  USD_parse(2);  break;
  case ADDRESS_USD3     :  USD_parse(3);  break;
  case ADDRESS_COIN1    :  COIN_parse(1);  break;
  case ADDRESS_COIN2    :  COIN_parse(2);  break;
  
  default:
    Serial.print(F("ADR #"));
    Serial.print((int)(msg_address & ADDRESS_MASK));
    Serial.print(F(" CMD #"));
    Serial.print((int)(msg_address & COMMAND_MASK));
    break;
  }
}


    switch(msg_data[0]) {
    case 0x00:  Serial.print(F(""));  break;
    case 0x00:  Serial.print(F(""));  break;
    case 0x00:  Serial.print(F(""));  break;
    case 0x00:  Serial.print(F(""));  break;
    }


/**
 * Displays byte in binary.  Useful for debugging comms at the start.
 */
void echo_data(char data) {
  char a;
  for(int i=0x80;i;i>>=1) {
    a = data & i;
    Serial.print(a?'1':'0');
  }
  //Serial.print(data);
}


/**
 * This file is part of MDB Parser.
 *
 * MDB Parser is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * MDB Parser is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with MDB Parser.  If not, see <http://www.gnu.org/licenses/>.
 */
