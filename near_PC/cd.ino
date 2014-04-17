//------------------------------------------------------------------------------
// MDB Parser - Make MDB communications human readable
// 2014-04-15 dan@marginallyclever.com
// Copyright at end of file.
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// CONSTANTS
//------------------------------------------------------------------------------

// cashless device
#define CMD_CD_RESET           (0x10 & COMMAND_MASK)  // Self-reset
#define CMD_CD_SETUP           (0x11 & COMMAND_MASK)  // Setup
#define CMD_CD_POLL            (0x12 & COMMAND_MASK)  // Poll
#define CMD_CD_VEND            (0x13 & COMMAND_MASK)  // Vend
#define CMD_CD_READER          (0x14 & COMMAND_MASK)  // Reader
#define CMD_CD_REVALUE         (0x15 & COMMAND_MASK)  // Revalue
#define CMD_CD_EXTRA           (0x17 & COMMAND_MASK)  // Extra

// states for the cashless devices
#define CD_STATE_INACTIVE   (0)
#define CD_STATE_DIABLED    (1)
#define CD_STATE_ENABLED    (2)
#define CD_STATE_IDLE       (3)
#define CD_STATE_VEND       (4)
#define CD_STATE_REVALUE    (5)
#define CD_STATE_NEGVEND    (6)

//------------------------------------------------------------------------------
// METHODS
//------------------------------------------------------------------------------


void CD_parse(int id) {
  Serial.print(F("Cashless Device "));
  Serial.print(id);
  Serial.print(' ');

  switch(msg_address & COMMAND_MASK) {
  case CMD_CD_RESET  :  Serial.print(F("Self-reset"));
    break;
  case CMD_CD_SETUP  :  Serial.print(F("Setup"));
    break;
  case CMD_CD_POLL   :  Serial.print(F("Poll"));
    break;
  case CMD_CD_VEND   :  Serial.print(F("Vend"));
    switch(msg_data[0]) {
    case 0x00:  Serial.print(F(" request"));  break;
    case 0x01:  Serial.print(F(" cancel"));  break;
    case 0x02:  Serial.print(F(" success"));  break;
    case 0x03:  Serial.print(F(" failure"));  break;
    case 0x04:  Serial.print(F(" session complete"));  break;
    case 0x05:  Serial.print(F(" cash sale"));  break;
    case 0x06:  Serial.print(F(" neg request"));  break;
    }
    break;
  case CMD_CD_READER :  Serial.print(F("Reader"));
    switch(msg_data[0]) {
    case 0x00:  Serial.print(F(" disable"));  break;
    case 0x01:  Serial.print(F(" enable"));  break;
    case 0x02:  Serial.print(F(" cancel"));  break;
    case 0x03:  Serial.print(F(" data entry response"));  break;
    }
    break;
  case CMD_CD_REVALUE:  Serial.print(F("Revalue"));
    switch(msg_data[0]) {
    case 0x00:  Serial.print(F(" request"));  break;
    case 0x01:  Serial.print(F(" limit request"));  break;
    }
    break;
  case CMD_CD_EXTRA  :  Serial.print(F("Extra"));
    switch(msg_data[0]) {
    case 0x00:  Serial.print(F(" request ID"));  break;
    case 0x01:  Serial.print(F(" read user file"));  break;
    case 0x02:  Serial.print(F(" write user file"));  break;
    case 0x03:  Serial.print(F(" write time/date"));  break;
    case 0x04:  Serial.print(F(" optional feature enabled"));  break;
    case 0xFA:  Serial.print(F(" FTL REQ2RCV"));  break;
    case 0xFB:  Serial.print(F(" FTL RETRY/DENY"));  break;
    case 0xFC:  Serial.print(F(" FTL SEND BLOCK"));  break;
    case 0xFD:  Serial.print(F(" FTL OK"));  break;
    case 0xFE:  Serial.print(F(" DTL REQ2SND"));  break;
    case 0xFF:  Serial.print(F(" diagnnostics"));  break;
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
