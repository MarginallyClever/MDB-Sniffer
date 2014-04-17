//------------------------------------------------------------------------------
// MDB Parser - Make MDB communications human readable
// 2014-04-15 dan@marginallyclever.com
// Copyright at end of file.
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// CONSTANTS
//------------------------------------------------------------------------------

// Bill validator commands
#define CMD_VALIDATOR_RESET     (0x30)  // Self-reset
#define CMD_VALIDATOR_SETUP     (0x31)  // Setup
#define CMD_VALIDATOR_SECURITY  (0x32)  // Set Security Mode
#define CMD_VALIDATOR_POLL      (0x33)  // Request activity status
#define CMD_VALIDATOR_BILL_TYPE (0x34)  // Bill type config
#define CMD_VALIDATOR_ESCROW    (0x35)  // Action for bill in escrow
#define CMD_VALIDATOR_STACKER   (0x36)  // Stacker is full!
#define CMD_VALIDATOR_FUTURE    (0x37)  // Future expansion

    

//------------------------------------------------------------------------------
// METHODS
//------------------------------------------------------------------------------

void VALIDATOR_parse() {
  Serial.print(F("Bill Validator "));

  switch(msg_address) {
  case CMD_VALIDATOR_RESET     : Serial.print(F("Self-reset"));  break;
  case CMD_VALIDATOR_SETUP     : Serial.print(F("Request setup information"));  break;
  case CMD_VALIDATOR_SECURITY  : Serial.print(F("Set Security Mode"));  break;
  case CMD_VALIDATOR_POLL      : Serial.print(F("Request activity status"));  break;
  case CMD_VALIDATOR_BILL_TYPE : Serial.print(F("Bill type config"));  break;
  case CMD_VALIDATOR_ESCROW    : Serial.print(F("Action for bill in escrow"));  break;
  case CMD_VALIDATOR_STACKER   : Serial.print(F("Stacker is full!"));  break;
  case CMD_VALIDATOR_FUTURE    : Serial.print(F("Future expansion"));  break;
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
