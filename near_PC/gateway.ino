//------------------------------------------------------------------------------
// MDB Parser - Make MDB communications human readable
// 2014-04-15 dan@marginallyclever.com
// Copyright at end of file.
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// METHODS
//------------------------------------------------------------------------------

// Defined in section 8.2 of MDB std 4.2
void GATEWAY_parse() {
  Serial.print(F("Communication Gateway "));

  switch(msg_address) {
  case 0x18:  Serial.print(F("Self-reset"));  break;
  case 0x19:  Serial.print(F("Setup"));  break;
  case 0x1A:  Serial.print(F("Poll"));  break;
  case 0x1B:  Serial.print(F("Report"));  break;
  case 0x1C:  Serial.print(F("Control"));  
    switch(msg_data[0]) {
    case 0x00:  Serial.print(F(" Disable"));  break;
    case 0x01:  Serial.print(F(" Enable"));  break;
    case 0x02:  Serial.print(F(" Transmit"));  break;
    }
    break;
  case 0x1A:  Serial.print(F("Extra")); 
    switch(msg_data[0]) {
    case 0x00:  Serial.print(F(" Ident"));  break;
    case 0x01:  Serial.print(F(" Feature enable(d)"));  break;
    case 0x02:  Serial.print(F(" Time/Date Req"));  break;
    case 0xFA:  Serial.print(F(" REQ2RCV"));  break;
    case 0xFB:  Serial.print(F(" RETRY/DENY"));  break;
    case 0xFC:  Serial.print(F(" SEND BLOCK"));  break;
    case 0xFD:  Serial.print(F(" OK TO SEND"));  break;
    case 0xFE:  Serial.print(F(" REQ2SEND"));  break;
    case 0xFF:  Serial.print(F(" Diagnostics"));  break;
    }
    break;

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
