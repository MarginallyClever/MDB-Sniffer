//------------------------------------------------------------------------------
// MDB Parser - Make MDB communications human readable
// 2014-04-15 dan@marginallyclever.com
// Copyright at end of file.
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// CONSTANTS
//------------------------------------------------------------------------------

// coin hopper
#define CMD_COIN_RESET         (0x58 & COMMAND_MASK)  // Self-reset
#define CMD_COIN_SETUP         (0x59 & COMMAND_MASK)  // Setup
#define CMD_COIN_STATUS        (0x5A & COMMAND_MASK)  // Tube status & coin count
#define CMD_COIN_POLL          (0x5B & COMMAND_MASK)  // Request activity status
#define CMD_COIN_MANUAL        (0x5C & COMMAND_MASK)  // Coin type config
#define CMD_COIN_DISPENSE      (0x5D & COMMAND_MASK)  // Dispense coins
#define CMD_COIN_PAYOUT        (0x5E & COMMAND_MASK)  // Payout confirm
#define CMD_COIN_FUTURE        (0x5F & COMMAND_MASK)  // Future expansion


//------------------------------------------------------------------------------
// METHODS
//------------------------------------------------------------------------------

void COIN_parse(int id) {
  Serial.print(F("Coin Hopper "));
  Serial.print(id);
  Serial.print(' ');

  switch(msg_address & COMMAND_MASK) {
  case CMD_COIN_RESET   : Serial.print(F("Self-reset"));  break;
  case CMD_COIN_SETUP   : Serial.print(F("Request setup information"));  break;
  case CMD_COIN_STATUS  : Serial.print(F("Tube status & coin count"));  break;
  case CMD_COIN_POLL    : Serial.print(F("Request activity status"));  break;
  case CMD_COIN_MANUAL  : Serial.print(F("Coin type config"));  break;
  case CMD_COIN_DISPENSE: Serial.print(F("Dispense coins"));  break;
  case CMD_COIN_PAYOUT  : Serial.print(F("Payout confirm"));  break;
  case CMD_COIN_FUTURE  : Serial.print(F("Future expansion"));  break;
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
