// pass data from the MDB to the intermediary
// pass data from the intermediary to the MDB


//----------------------------------------------------------------
// CONSTANTS
//----------------------------------------------------------------

#define BAUD 9600
#define RPI_BUFFER_SIZE  (64)
#define MDB_BUFFER_SIZE (36+1)  // section 2.2, +1 for safety


//State trackers taken in reference to page 94 of 3.0 spec pdf
#define sINACTIVE 0
#define sDISABLED 1
#define sENABLED 2
#define sSESSION_IDLE 3
#define sVEND 4
#define sREVALUE 5
#define sNEGATIVE_VEND 6

// retransmit states
#define rRETRANSMIT 0
#define rCONTINUE 1
#define rUNKNOWN 2

// generic ACK stuff from page 33 of the 4.2 spec pdf
#define sACK 0x100
#define rACK 0x00
#define RET 0xAA
#define sNAK 0x1FF
#define rNAK 0xFF

// Commands from VMC
// the following are taken from page 100 of the 3.0 spec pdf
// i think might arrive with 9bit set
#define RESET 0x10
#define SETUP 0x11
#define POLL 0x12
#define VEND 0x13
#define READER 0x14
#define REVALUE 0x15
#define EXPANSION 0x16

// Sub Commands
// setup
#define CONFIG_DATA 0x00
#define MINMAX_PRICES 0x01
// vend
#define VEND_REQUEST 0x00
#define VEND_CANCEL 0x01
#define VEND_SUCCESS 0x02
#define VEND_FAILURE 0x03
#define SESSION_COMPLETE 0x04
#define CASH_SALE 0x05
#define NEGATIVE_VEND_REQUEST 0x06
//reader
#define READER_DISABLE 0x00
#define READER_ENABLE 0x01
#define READER_CANCEL 0x02
#define DATE_ENTRY_RESPONSE 0x03
// revaule
#define REVALUE_REQUEST 0x00
#define REVALUE_LIMIT_REQUEST 0x01
// expansion
#define RESQUEST_ID 0x00
#define READ_USER_FILE 0x01
#define WRITE_USER_FILE 0x02
#define WRITE_TIME_DATE 0x03
#define OPTIONAL_FEATURE_ENABLE 0x04
#define FTL_REQTORCV 0xFA
#define FTL_RETRYDENY 0xFB
#define FTL_SENDBLOCK 0xFC
#define FTL_OKTOSEND 0xFD
#define FTL_REQTOSEND 0xFE
#define DIAGNOSTICS 0xFF

// responses
#define JUST_RESET 0x00
#define JUST_RESET_CHK 0x100 // pre calculated CHK
#define READER_CONFIG_DATA 0x01
#define DISPLAY_REQUEST 0x02
#define BEGIN_SESSION 0x03
#define SESSION_CANCEL_REQUEST 0x04
#define VEND_APPROVED 0x05
#define VEND_DENIED 0x06
#define VEND_DENIED_CHK 0x106
#define END_SESSION 0x07
#define CANCELLED 0x08
#define PERIPHERAL_ID 0x09
#define MALFUNCTION_ERROR 0x0A
#define CMD_OUT_OF_SEQUENCE 0x0B
#define CMD_OUT_OF_SEQUENCE_CHK 0x10B
#define REVALUE_APPROVED 0x0D
#define REVALUE_DENIED 0x0E
#define REVALUE_LIMIT_AMOUNT 0x0F
#define USER_DATA_FILE 0x10
#define TIMEDATE_REQUEST 0x11
#define DATA_ENTRY_REQUEST 0x12
#define DATA_ENTRY_CANCEL 0x13
#define FTL_REQTORCV 0x1B
#define FTL_RETRYDENY 0x1C
#define FTL_SENDBLOCK 0x1D
#define FTL_OKTOSEND 0x1E
#define FTL_REQTOSEND 0x1F
#define DIAGNOSTICS_RESPONSE 0xFF

// error codes
#define PAYMENT_MEDIA_ERROR 0x00
#define INVALID_PAYMENT_MEDIA 0x10
#define TAMPER_ERROR 0x20
#define MANUFACTURER_DEFINED_ERROR1 0x30
#define COMMUNICATIONS_ERROR 0x40
#define READER_REQUIRES_SERVICE 0x50
#define MANUFACTURER_DEFINED_ERROR2 0x70
#define READER_FAILURE 0x80
#define COMMUNICATIONS_ERROR3 0x90
#define PAYMENT_MEDIA_JAMMED 0xA0
#define MANUFACTURER_DEFINED_ERROR3 0xB0
#define REFUND_ERROR 0xC0


//----------------------------------------------------------------
// INCLUDES
//----------------------------------------------------------------

#include <SoftwareSerial.h>
#include <Wire.h> 
#include <util/setbaud.h>

//----------------------------------------------------------------
// STRUCTURES
//----------------------------------------------------------------


// MDB stuff
struct MDB_Byte {
  byte data;
  byte mode;
};


//----------------------------------------------------------------
// GLOBALS
//----------------------------------------------------------------


// Raspberry Pi stuff
SoftwareSerial RPI(10,11);
char RPI_buffer[RPI_BUFFER_SIZE];
int RPI_buffer_count;


struct MDB_Byte recvData[MDB_BUFFER_SIZE];
struct MDB_Byte sendData[MDB_BUFFER_SIZE];



//----------------------------------------------------------------
// METHODS
//----------------------------------------------------------------


void setup() {
  RPI_setup();
  MDB_setup();
}


void loop() {
  RPI_read();
  MDB_read();
}



void RPI_setup() {
  RPI.begin(57600);
  //RPI.print("Hello from near MDB!\n");
  delay(100);
  RPI.print("Hello, World!");
  RPI_buffer_count=0;
}


void RPI_read() {
  if(RPI.available()) {
    char data = RPI.read();
    // buffer the data
    RPI_buffer[RPI_buffer_count++]=data;
    // is the command finished?
    if(data==';') {
      // parse the command
      RPI_parse();
      // clear the buffer
      RPI_buffer_count=0;
    }
  }
}


void RPI_parse() {
}





void MDB_setup() {
  // Clear tx/rx buffers
  memset(recvData, 0, sizeof(recvData));
  memset(sendData, 0, sizeof(sendData));
  
  // Set baud rate
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
  // Disable USART rate doubler (arduino bootloader leaves it enabled...)
  UCSR0A &= ~(1 << U2X0);
  // Set async, no parity, 1 stop, 9bit
  UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)|(0<<UPM01)|(0<<UPM00)|(0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);
  UCSR0B |= (1<<UCSZ02); // 9bit
  // Enable rx/tx
  UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
}


void MDB_read() {
  // is data availble?
  if((UCSR0A & (1<<RXC0))) {
    // read it
    MDB_getByte(&recvData[0]);
    //RPI.print(recvData[0]);
    MDB_parse();
  }
}


void MDB_getByte(struct MDB_Byte* mdbb) {
  int b;
  char tmpstr[7];

  b = 0;
  b = USART_Receive();
  memcpy (mdbb, &b, 2);
  
  /*if (gDebug > 1) {
    if (b.mode) sprintf(tmpstr, ">%.2x*", b.data);
    else        sprintf(tmpstr, ">%.2x", b.data);
    dbg_print(tmpstr);
  }*/
}


int USART_Receive() {
  unsigned char status, resh, resl;
  char tmpstr[64];

  // Wait for data to be received
  while (!(UCSR0A & (1<<RXC0)));
  // Get status and 9th bit, then data
  // from buffer
  status = UCSR0A;
  resh = UCSR0B;
  resl = UDR0;

  // If error, return -1
  if ( (status & (1<<FE0)) | (status & (1<<DOR0)) | (status & (1<<UPE0))) {
    //sprintf(tmpstr, "<RX ERR: %.2x [%d,%d,%d], [%.2x, %.2x]", status, (status & (1<<FE0)), (status & (1<<DOR0)),(status & (1<<UPE0)), resh, resl);
    //dbg_print(tmpstr);
    return -1;
  }

  // Filter the 9th bit, then return
  resh = (resh >> 1) & 0x01;
  return ((resh << 8) | resl);
}


void MDB_parse() {
  // send it to the intermediary
  RPI.write(recvData[0].mode);
  RPI.write(recvData[0].data);
}


byte MDB_checksumValidate(struct MDB_Byte* data, byte length) {
  byte sum = 0;
  
  for (int i=0; i < (length-1); i++)
    sum += data[i].data;

  if (data[length-1].data == sum)
    return 1;
  else
    return 0;
}


byte MDB_checksumGenerate(struct MDB_Byte* data, byte length) {
  byte sum = 0;
  for (int i=0; i < (length); i++)
    sum += data[i].data;

  return sum;
}




byte MDB_transmitData(struct MDB_Byte* data, byte length) {
  int transmitState;
  struct MDB_Byte mdbb;
  int tx;
  char tmpstr[7];
  
  do
  {
    mdbb.data = MDB_checksumGenerate(data, length);
    mdbb.mode = 0x1;

    tx = 0;
    memcpy(&tx, &mdbb, 2);

    for (int i=0; i < length; i++)
      MDB_write(data[i].data);

    MDB_write(tx); //chk

    while ( !(UCSR0A & (1<<RXC0)) );
    
    MDB_getByte(&mdbb);
    
    if (mdbb.data == rNAK || mdbb.data == RET) {
      transmitState = rRETRANSMIT;
    } else if (mdbb.data == rACK) {
      transmitState = rCONTINUE;
    } else {
      transmitState = rUNKNOWN;
    }
  } while (transmitState == rRETRANSMIT);
  //if (debug) dbg_println(")");
  
  return transmitState;
}


void MDB_write(int data) {
  char tmpstr[7];
  struct MDB_Byte b;
  
  memcpy(&b, &data, 2);
  
  serial_write(b);
  
  /*if (gDebug > 1) {
    if (b.mode) sprintf(tmpstr, ">%.2x*", b.data);
    else        sprintf(tmpstr, ">%.2x", b.data);
    dbg_print(tmpstr);
  }*/
}


void serial_write(struct MDB_Byte mdbb) {
  while ( !( UCSR0A & (1<<UDRE0)));
  
  if (mdbb.mode) {
    // turn on bit 9
    UCSR0B |= (1<<TXB80);
  } else {
    // turn off bit 9
    UCSR0B &= ~(1<<TXB80);
  }
  
  UDR0 = mdbb.data;
}


