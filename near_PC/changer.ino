//------------------------------------------------------------------------------
// MDB Parser - Make MDB communications human readable
// 2014-04-15 dan@marginallyclever.com
// Copyright at end of file.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// CONSTANTS
//------------------------------------------------------------------------------

// changer commands
#define CMD_CHANGER_RESET       (0x08)  // Self-reset
#define CMD_CHANGER_SETUP       (0x09)  // Setup
#define CMD_CHANGER_TUBE_STATUS (0x0A)  // Request tube status
#define CMD_CHANGER_POLL        (0x0B)  // Request activity status
#define CMD_CHANGER_COIN_TYPE   (0x0C)  // Coin type config
#define CMD_CHANGER_DISPENSE    (0x0D)  // Dispense a coin
#define CMD_CHANGER_FUTURE      (0x0F)  // Future expansion


//------------------------------------------------------------------------------
// METHODS
//------------------------------------------------------------------------------

void CHANGER_parse() {
  Serial.print(F("Changer "));

  switch(msg_address) {
  case CMD_CHANGER_RESET      :  Serial.print(F("Self-reset"));  break;
  case CMD_CHANGER_SETUP      :  Serial.print(F("Request setup information"));  break;
  case CMD_CHANGER_TUBE_STATUS:  Serial.print(F("Request tube status"));  break;
  case CMD_CHANGER_POLL       :  Serial.print(F("Request activity status"));  break;
  case CMD_CHANGER_COIN_TYPE  :  Serial.print(F("Coin type config"));  break;
  case CMD_CHANGER_DISPENSE   :  Serial.print(F("Dispense a coin"));  break;
  case CMD_CHANGER_FUTURE     :  Serial.print(F("Future expansion"));  break;
  default:
    Serial.print(F(" CMD #"));
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
