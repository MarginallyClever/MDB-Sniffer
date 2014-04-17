//------------------------------------------------------------------------------
// MDB Parser - Make MDB communications human readable
// 2014-04-15 dan@marginallyclever.com
// Copyright at end of file.
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// CONSTANTS
//------------------------------------------------------------------------------

// Universal satellite device commands
#define USD_CMD_RESET   (0x40 & COMMAND_MASK)
#define USD_CMD_SETUP   (0x41 & COMMAND_MASK)
#define USD_CMD_POLL    (0x42 & COMMAND_MASK)
#define USD_CMD_VEND    (0x43 & COMMAND_MASK)
#define USD_CMD_FUNDS   (0x44 & COMMAND_MASK)
#define USD_CMD_CONTROL (0x45 & COMMAND_MASK)
#define USD_CMD_EXTRA   (0x47 & COMMAND_MASK)


//------------------------------------------------------------------------------
// METHODS
//------------------------------------------------------------------------------

void USD_parse(int id) {
  Serial.print(F("Universal Satellite Device "));
  Serial.print(id);
  Serial.print(' ');

  switch(msg_address & COMMAND_MASK) {
    
  case USD_CMD_RESET:  Serial.print(F("Self-reset"));  break;
  case USD_CMD_SETUP:  Serial.print(F("Setup"));  break;
  case USD_CMD_POLL:  Serial.print(F("Poll"));  break;
  case USD_CMD_VEND:  Serial.print(F("Vend"));
    switch(msg_data[0]) {
    case 0x00:  Serial.print(F(" Approved"));  break;
    case 0x01:  Serial.print(F(" Denied"));  break;
    case 0x02:  Serial.print(F(" vend item"));  break;
    case 0x03:  Serial.print(F(" home item"));  break;
    case 0x04:  Serial.print(F(" status of item"));  break;
    }
  break;
  case USD_CMD_FUNDS:  Serial.print(F("Funds"));
    switch(msg_data[0]) {
    case 0x00:  Serial.print(F(" Credit level change"));  break;
    case 0x01:  Serial.print(F(" Price request"));  break;
    }
  break;
  case USD_CMD_CONTROL:  Serial.print(F("Control"));
    switch(msg_data[0]) {
    case 0x00:  Serial.print(F(" Disable"));  break;
    case 0x01:  Serial.print(F(" Enable"));  break;
    }
    break;
  case USD_CMD_EXTRA:  Serial.print(F("Extra"));
    switch(msg_data[0]) {
    case 0x00:  Serial.print(F(" Status"));  break;
    case 0x01:  Serial.print(F(" Enable feature"));  break;
    case 0x02:  Serial.print(F(" number of blocks to receive"));  break;
    case 0x03:  Serial.print(F(" data block N of M"));  break;
    case 0x04:  Serial.print(F(" please resend block"));  break;
    case 0x05:  Serial.print(F(" one data block"));  break;
    case 0xFA:  Serial.print(F(" REQ2RCV"));  break;
    case 0xFB:  Serial.print(F(" RETRY/DENY"));  break;
    case 0xFC:  Serial.print(F(" SEND BLOCK"));  break;
    case 0xFD:  Serial.print(F(" OK TO SEND"));  break;
    case 0xFE:  Serial.print(F(" REQ2SEND"));  break;
    case 0xFF:  Serial.print(F(" diagnostics"));  break;
    }
    break;
  
  default:
    Serial.print(F("CMD #"));
    Serial.print((int)(msg_address & COMMAND_MASK));
    break;
  }
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
