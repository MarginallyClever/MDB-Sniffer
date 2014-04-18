//------------------------------------------------------------------------------
// MDB Parser - Make MDB communications human readable
// 2014-04-15 dan@marginallyclever.com
// Copyright at end of file.
//------------------------------------------------------------------------------
#ifndef CONFIG_H
#define CONFIG_H


//------------------------------------------------------------------------------
// CONSTANTS
//------------------------------------------------------------------------------

#define MAX_MSG_LEN (36)  // section 2.2

#define ADDRESS_MASK      (0xF8)  // section 2.3 - top five bits of address are actually address
#define COMMAND_MASK      (0x07)  // section 2.3 - bottom three bits are command


// Address of each device (section 2.2)
#define ADDRESS_VMC       (0x00)
#define ADDRESS_CHANGER   (0x08)
#define ADDRESS_CD1       (0x10)  // Cashless Device 1
#define ADDRESS_GATEWAY   (0x18)  // Communication Gateway
#define ADDRESS_DISPLAY   (0x20)
#define ADDRESS_EMS       (0x28)  // Energy Management System
#define ADDRESS_VALIDATOR (0x30)  // Bill Validator

#define ADDRESS_USD1      (0x40)  // Universal satellite device 1
#define ADDRESS_USD2      (0x48)  // Universal satellite device 2
#define ADDRESS_USD3      (0x50)  // Universal satellite device 3
#define ADDRESS_COIN1     (0x58)  // Coin Hopper 1
#define ADDRESS_CD2       (0x60)  // Cashless Device 2
#define ADDRESS_AVD       (0x68)  // Age Verification Device
#define ADDRESS_COIN2     (0x70)  // Coin Hopper 2
// higher addresses are for future expansion


// section 2.2
#define MSG_ACK  (0x00)  // ack
#define MSG_RET  (0xAA)  // please retransmit last byte
#define MSG_NAK  (0xFF)  // negative ack



#endif  // CONFIG_H



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
