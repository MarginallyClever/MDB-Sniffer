// output data from the MDB arduino to the PC
// send data from the PC to the MDB arduino
#include <SoftwareSerial.h>




#define MAX_MSG_LEN (36)  // section 2.2 of MDB format

#define ADDRESS_MASK      (0xF8)  // top five bits of address are actually address
#define COMMAND_MASK      (0x07)  // bottom three bits are command


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


// changer commands
#define CMD_CHANGER_RESET       (0x08)  // Self-reset
#define CMD_CHANGER_SETUP       (0x09)  // Request setup information
#define CMD_CHANGER_TUBE_STATUS (0x0A)  // Request tube status
#define CMD_CHANGER_POLL        (0x0B)  // Request activity status
#define CMD_CHANGER_COIN_TYPE   (0x0C)  // Coin type config
#define CMD_CHANGER_DISPENSE    (0x0D)  // Dispense a coin
#define CMD_CHANGER_FUTURE      (0x0F)  // Future expansion

// Bill validator commands
#define CMD_VALIDATOR_RESET     (0x30)  // Self-reset
#define CMD_VALIDATOR_SETUP     (0x31)  // Request setup information
#define CMD_VALIDATOR_SECURITY  (0x32)  // Set Security Mode
#define CMD_VALIDATOR_POLL      (0x33)  // Request activity status
#define CMD_VALIDATOR_BILL_TYPE (0x34)  // Bill type config
#define CMD_VALIDATOR_ESCROW    (0x35)  // Action for bill in escrow
#define CMD_VALIDATOR_STACKER   (0x36)  // Stacker is full!
#define CMD_VALIDATOR_FUTURE    (0x37)  // Future expansion

#define CMD_COIN1_RESET         (0x58)  // Self-reset
#define CMD_COIN1_SETUP         (0x59)  // Request setup information
#define CMD_COIN1_STATUS        (0x5A)  // Tube status & coin count
#define CMD_COIN1_POLL          (0x5B)  // Request activity status
#define CMD_COIN1_MANUAL        (0x5C)  // Coin type config
#define CMD_COIN1_DISPENSE      (0x5D)  // Dispense coins
#define CMD_COIN1_PAYOUT        (0x5E)  // Payout confirm
#define CMD_COIN1_FUTURE        (0x5F)  // Future expansion

#define CMD_COIN2_RESET         (0x70)  // Self-reset
#define CMD_COIN2_SETUP         (0x71)  // Request setup information
#define CMD_COIN2_STATUS        (0x72)  // Tube status & coin count
#define CMD_COIN2_POLL          (0x73)  // Request activity status
#define CMD_COIN2_MANUAL        (0x74)  // Coin type config
#define CMD_COIN2_DISPENSE      (0x75)  // Dispense coins
#define CMD_COIN2_PAYOUT        (0x76)  // Payout confirm
#define CMD_COIN2_FUTURE        (0x77)  // Future expansion

// states for the cashless devices
#define CD_STATE_INACTIVE   (0)
#define CD_STATE_DIABLED    (1)
#define CD_STATE_ENABLED    (2)
#define CD_STATE_IDLE       (3)
#define CD_STATE_VEND       (4)
#define CD_STATE_REVALUE    (5)
#define CD_STATE_NEGVEND    (6)




SoftwareSerial MDB(10,11);
byte msg_address;
byte msg_data[MAX_MSG_LEN];
int msg_count=0;
int cd_state = CD_STATE_INACTIVE;



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
      // address
      interpret_address(data);
      Serial.print(": ");
    } else {
      // data
      interpret_data(data);
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


void interpret_data(char data) {
  if(data == calculate_checksum()) {
    // message ends
    parse_message();
    //Serial.print("CHK\n");
    Serial.print("\n");
    msg_count=0;
  } else {
    msg_data[msg_count++]=data;
    if(msg_count==MAX_MSG_LEN) {
      Serial.print("\n** MESSAGE OVERFLOW **\n");
      msg_count=0;
    }
    //echo_data(data);
    //Serial.print(' ');
  }
}


void parse_message() {
  switch(msg_address) {
  case CMD_CHANGER_RESET      :  Serial.print(F("Self-reset"));  break;
  case CMD_CHANGER_SETUP      :  Serial.print(F("Request setup information"));  break;
  case CMD_CHANGER_TUBE_STATUS:  Serial.print(F("Request tube status"));  break;
  case CMD_CHANGER_POLL       :  Serial.print(F("Request activity status"));  break;
  case CMD_CHANGER_COIN_TYPE  :  Serial.print(F("Coin type config"));  break;
  case CMD_CHANGER_DISPENSE   :  Serial.print(F("Dispense a coin"));  break;
  case CMD_CHANGER_FUTURE     :  Serial.print(F("Future expansion"));  break;
  
  case CMD_VALIDATOR_RESET     : Serial.print(F("Self-reset"));  break;
  case CMD_VALIDATOR_SETUP     : Serial.print(F("Request setup information"));  break;
  case CMD_VALIDATOR_SECURITY  : Serial.print(F("Set Security Mode"));  break;
  case CMD_VALIDATOR_POLL      : Serial.print(F("Request activity status"));  break;
  case CMD_VALIDATOR_BILL_TYPE : Serial.print(F("Bill type config"));  break;
  case CMD_VALIDATOR_ESCROW    : Serial.print(F("Action for bill in escrow"));  break;
  case CMD_VALIDATOR_STACKER   : Serial.print(F("Stacker is full!"));  break;
  case CMD_VALIDATOR_FUTURE    : Serial.print(F("Future expansion"));  break;

  case CMD_COIN1_RESET   : Serial.print(F("Self-reset"));  break;
  case CMD_COIN1_SETUP   : Serial.print(F("Request setup information"));  break;
  case CMD_COIN1_STATUS  : Serial.print(F("Tube status & coin count"));  break;
  case CMD_COIN1_POLL    : Serial.print(F("Request activity status"));  break;
  case CMD_COIN1_MANUAL  : Serial.print(F("Coin type config"));  break;
  case CMD_COIN1_DISPENSE: Serial.print(F("Dispense coins"));  break;
  case CMD_COIN1_PAYOUT  : Serial.print(F("Payout confirm"));  break;
  case CMD_COIN1_FUTURE  : Serial.print(F("Future expansion"));  break;

  case CMD_COIN2_RESET   : Serial.print(F("Self-reset"));  break;
  case CMD_COIN2_SETUP   : Serial.print(F("Request setup information"));  break;
  case CMD_COIN2_STATUS  : Serial.print(F("Tube status & coin count"));  break;
  case CMD_COIN2_POLL    : Serial.print(F("Request activity status"));  break;
  case CMD_COIN2_MANUAL  : Serial.print(F("Coin type config"));  break;
  case CMD_COIN2_DISPENSE: Serial.print(F("Dispense coins"));  break;
  case CMD_COIN2_PAYOUT  : Serial.print(F("Payout confirm"));  break;
  case CMD_COIN2_FUTURE  : Serial.print(F("Future expansion"));  break;

  default:
    Serial.print(F("CMD #"));
    Serial.print((int)(msg_address & COMMAND_MASK));
    break;
  }
}


void interpret_address(char address) {
  msg_address = address;
  switch(address & ADDRESS_MASK) {
  case ADDRESS_VMC      :  Serial.print(F("Vending Master Controller"));  break;
  case ADDRESS_CHANGER  :  Serial.print(F("Changer"));  break;
  case ADDRESS_CD1      :  Serial.print(F("Cashless Device 1"));  break;
  case ADDRESS_GATEWAY  :  Serial.print(F("Communication Gateway"));  break;
  case ADDRESS_DISPLAY  :  Serial.print(F("Display"));  break;
  case ADDRESS_EMS      :  Serial.print(F("Energy Management System"));  break;
  case ADDRESS_VALIDATOR:  Serial.print(F("Bill Validator"));  break;
  case ADDRESS_USD1     :  Serial.print(F("Universal Satellite Device 1"));  break;
  case ADDRESS_USD2     :  Serial.print(F("Universal Satellite Device 2"));  break;
  case ADDRESS_USD3     :  Serial.print(F("Universal Satellite Device 3"));  break;
  case ADDRESS_COIN1    :  Serial.print(F("Coin Hopper 1"));  break;
  case ADDRESS_CD2      :  Serial.print(F("Cashless Device 2"));  break;
  case ADDRESS_AVD      :  Serial.print(F("Age verification device"));  break;
  case ADDRESS_COIN2    :  Serial.print(F("Coin Hopper 2"));  break;
  
  default:
    Serial.print(F("ADR #"));
    Serial.print((int)(msg_address & ADDRESS_MASK));
    break;
  }
}


void echo_data(char data) {
  char a;
  for(int i=0x80;i;i>>=1) {
    a = data & i;
    Serial.print(a?'1':'0');
  }
  //Serial.print(data);
}
