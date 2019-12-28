/*  Copyright (c) 2016 Macchina
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included
 *  in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 *  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 *  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 *  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *  LIN STACK for TJA1021 
 *  v2.0
 *
 *  Short description: 
 *  Comunication stack for LIN and TJA1021 LIN transceiver. 
 *  Can be modified for any Arduino board with UART available and any LIN slave.
 *  
 *  Author: Blaž Pongrac B.S., RoboSap, Institute of Technology, Ptuj (www.robosap-institut.eu)
 *  
 *  Arduino IDE 1.6.9
 *  RoboSap, Institute of Technology, September 2016
 */ 

#include "lin_stack.h"

/* LIN PACKET:
   It consist of:
    ___________ __________ _______ ____________ _________ 
   |           |          |       |            |         |
   |Synch Break|Synch Byte|ID byte| Data Bytes |Checksum |
   |___________|__________|_______|____________|_________|
   
   Every byte have start bit and stop bit and it is send LSB first.
   Synch Break - 13 bits of dominant state ("0"), followed by 1 bit recesive state ("1")
   Synch Byte - Byte for baud rate syncronization, always 0x55
   ID Byte - consist of parity, length and address; parity is determined by LIN standard and depends from address and message length
   Data Bytes - user defined; depend on devices on LIN bus
   Checksum - inverted 256 checksum; data bytes are sumed up and then inverted
*/

// CONSTRUCTORS
lin_stack::lin_stack(byte Ch){
	sleep_config(Ch); // Configurating Sleep pin for transceiver
	ch = Ch;
}

lin_stack::lin_stack(byte Ch, byte ident){
	sleep_config(Ch); // Configuration of Sleep pin for transceiver
	identByte = ident; // saving idet to private variable
	sleep(1); // Transceiver is always in Normal Mode
}

// PUBLIC METHODS
// WRITE methods
// Creates a LIN packet and then send it via USART(Serial) interface.
int lin_stack::write(byte ident, byte data[], byte data_size){
	// Calculate classic checksum
	byte checksum = validateClassicChecksum(data, data_size);
	sleep(1); // Go to Normal mode
	// Synch Break
	serial_pause(13);
	// Send data via Serial interface
	if(ch==1){ // For LIN1 or Serial1
		Serial1.begin(baudRate); // config Serial
		Serial1.write(0x55); // write Synch Byte to serial
		Serial1.write(ident); // write Identification Byte to serial
		for(int i=0;i<data_size;i++) Serial1.write(data[i]); // write data to serial
		Serial1.write(checksum); // write Checksum Byte to serial
		Serial1.end(); // clear Serial config
	}else if(ch==2){ // For LIN2 or Serial2
		Serial2.begin(baudRate); // config Serial
		Serial2.write(0x55); // write Synch Byte to serial
		Serial2.write(ident); // write Identification Byte to serialv
		for(int i=0;i<data_size;i++) Serial2.write(data[i]); // write data to serial
		Serial2.write(checksum);// write Checksum Byte to serial
		Serial2.end(); // clear Serial config
	}
	sleep(0); // Go to Sleep mode
	return 1;
}

int lin_stack::writeRequest(byte ident){
	// Create Header
	byte identByte = (ident&0x3f) | calcIdentParity(ident);
	byte header[2]= {0x55, identByte};
	// Start interface
	sleep(1); // Go to Normal mode
	// Synch Break
	serial_pause(13);
	// Send data via Serial interface
	if(ch==1){ // For LIN1 or Serial1
		Serial1.begin(baudRate); // config Serial
		Serial1.write(header,2); // write data to serial
		Serial1.end(); // clear Serial config
	}else if(ch==2){ // For LIN2 or Serial2
		Serial2.begin(baudRate); // config Serial
		Serial2.write(header,2); // write data to serial
		Serial2.end(); // clear Serial config
	}
	sleep(0); // Go to Sleep mode
	return 1;
}

int lin_stack::writeResponse(byte data[], byte data_size){
  // Calculate classic checksum
  byte checksum = validateClassicChecksum(data, data_size);
	// Start interface
	sleep(1); // Go to Normal mode
	// Send data via Serial interface
	if(ch==1){ // For LIN1 or Serial1
		Serial1.begin(baudRate); // config Serial
		Serial1.write(data, data_size); // write data to serial
		Serial1.write(checksum); // write data to serial
		Serial1.end(); // clear Serial config
	}else if(ch==2){ // For LIN2 or Serial2
		Serial2.begin(baudRate); // config Serial
		Serial2.write(data, data_size); // write data to serial
		Serial2.write(checksum); // write data to serial
		Serial2.end(); // clear Serial config
	}
	sleep(0); // Go to Sleep mode
	return 1;
}

int lin_stack::writeStream(byte data[], byte data_size){
	// Start interface
	sleep(1); // Go to Normal mode
	// Synch Break
	serial_pause(13);
	// Send data via Serial interface
	if(ch==1){ // For LIN1 or Serial1
		Serial1.begin(baudRate); // config Serial
		for(int i=0;i<data_size;i++) Serial1.write(data[i]);
		Serial1.end(); // clear Serial config
	}else if(ch==2){ // For LIN2 or Serial2
		Serial2.begin(baudRate); // config Serial
		for(int i=0;i<data_size;i++) Serial2.write(data[i]);
		Serial2.end(); // clear Serial config
	}
	sleep(0); // Go to Sleep mode
	return 1;
}

// READ methods


int lin_stack::read(byte data[], byte data_size){
	byte rec[data_size+3];
  int retVal = 0;
  
	if(ch==1)
	{ // For LIN1 or Serial1
    sleep(1);
    Serial1.begin(baudRate); // Configure Serial1
		if(Serial1.read() != -1)
		{ // Check if there is an event on LIN bus
			Serial1.readBytes(rec,data_size+3);
#if (DEBUG_LIN_PRINT_RAW_PURE_RX_MSGS >= 1)
      printLinRxDataBuffer(ch, rec,data_size+3); 
#endif      
			if((validateParity(rec[1]))&(validateClassicChecksum(rec,data_size+3))) {
				for(int j=0;j<data_size;j++) 
				  data[j] = rec[j+2];
				retVal = 1;
			}
		}
#if (DEBUG_LIN_PRINT_RAW_DATA_RX_MSGS >= 1)
      printLinRxDataBuffer(ch, data,data_size); 
#endif 
      sleep(0);
      Serial1.end();
      return retVal;
	}
	else if(ch==2)
	{ // For LIN2 or Serial2
    sleep(1);
    Serial2.begin(baudRate); // Configure Serial1
    if(Serial2.read() != -1)
    { // Check if there is an event on LIN bus
      Serial2.readBytes(rec,data_size+3);
#if (DEBUG_LIN_PRINT_RAW_PURE_RX_MSGS >= 1)
      printLinRxDataBuffer(ch, rec,data_size+3); 
#endif            
      if((validateParity(rec[1]))&(validateClassicChecksum(rec,data_size+3))) {
        for(int j=0;j<data_size;j++) 
          data[j] = rec[j+2];
        retVal = 1;
      }
    }
#if (DEBUG_LIN_PRINT_RAW_DATA_RX_MSGS >= 1)
      printLinRxDataBuffer(ch, data,data_size); 
#endif 
      sleep(0);
      Serial2.end();
      return retVal;
 	}
}

int lin_stack::readStream(byte data[],byte data_size){
	byte rec[data_size];
	if(ch==1){ // For LIN1 or Serial1
    Serial1.begin(baudRate); // Configure Serial1
    sleep(1);
		if(Serial1.read() != -1){ // Check if there is an event on LIN bus
			Serial1.readBytes(rec,data_size);
    sleep(0);
    Serial1.end();    
		return 1;
		}
	}else if(ch==2){ // For LIN2 or Serial2
    Serial1.begin(baudRate); // Configure Serial1
    sleep(1);
		if(Serial2.read() != -1){ // Check if there is an event on LIN bus
			Serial2.readBytes(data,data_size);
    sleep(0);
    Serial2.end();      
		return 1;
		}
	}
	return 0;
}


// PRIVATE METHODS
int lin_stack::serial_pause(int no_bits){
	// Calculate delay needed for 13 bits, depends on baud rate
	unsigned int del = period*no_bits; // delay for number of bits (no-bits) in microseconds, depends on period
	if(ch==2){
    pinMode(LIN_CH2_TX_PIN, OUTPUT);           // set pin to input
    digitalWrite(LIN_CH2_TX_PIN, LOW);       // turn on pullup resistors
		delayMicroseconds(del); // delay
    digitalWrite(LIN_CH2_TX_PIN, HIGH);   

	}else if(ch==1){
    pinMode(LIN_CH1_TX_PIN, OUTPUT);           // set pin to input
    digitalWrite(LIN_CH1_TX_PIN, LOW);       // turn on pullup resistors
    delayMicroseconds(del); // delay
    digitalWrite(LIN_CH1_TX_PIN, HIGH);   

	}
	return 1;
}

int lin_stack::sleep(byte sleep_state){
	if(sleep_state==1){ // Go to Normal mode
		if(ch==1) digitalWrite(LIN_CH1_SLP_PIN, HIGH);    //  high state, normal mode
		if(ch==2) digitalWrite(LIN_CH2_SLP_PIN, HIGH);    //  high state, normal mode
	}else if(sleep_state==0){ // Go to Sleep mode
		if(ch==1) digitalWrite(LIN_CH1_SLP_PIN, LOW);    // low state, sleep mode
		if(ch==2) digitalWrite(LIN_CH2_SLP_PIN, LOW);    // low state, sleep mode
	}
	delayMicroseconds(20); // According to TJA1021 datasheet this is needed for proper working
	return 1;
}

int lin_stack::sleep_config(byte serial_No){
	if(serial_No==1){ // When using LIN1 channel - usign Serial1 and pin PB4 for Sleep
    pinMode(LIN_CH1_SLP_PIN, OUTPUT);           // set pin to input
    digitalWrite(LIN_CH1_SLP_PIN, LOW);       
		ch=1; // saved as private variable, used for determening Serial port
	}else if(serial_No==2)
	{ // When using LIN2 channel - usign Serial2 and pin PB7 for Sleep
    pinMode(LIN_CH2_SLP_PIN, OUTPUT);           // set pin to input
    digitalWrite(LIN_CH2_SLP_PIN, LOW);       
		ch=2; // saved as private variable, used for determening Serial port
	}
	return 1;
}

boolean lin_stack::validateParity(byte ident) {
	if(ident == identByte)
		return true;
	else
		return false;
}

boolean lin_stack::validateClassicChecksum(unsigned char data[], byte data_size){
	byte checksum = data[data_size-1];
	byte suma = 0;
	for(int i=2;i<data_size-1;i++) 
		suma = suma + data[i];
	byte v_checksum = 255 - suma - 1;

	if(checksum==v_checksum)
		return true;
	else
		return false;
} 

boolean lin_stack::validateEnhancedChecksum(unsigned char data[], byte data_size){
  byte receivedChecksum = data[data_size-1]; // read checksum from receive buffer
  long calc = data[1]; // read pID with Parity information from receive buffer

  for(int i=2;i<data_size-1;i++)
  {
    calc += data[i];
    if ( calc >= 256)
      calc -=255  ;
  }
  byte calculatedChecksum = 255 - calc;

  if(calculatedChecksum==receivedChecksum)
    return true;
  else
    return false;
} 

int lin_stack::busWakeUp()
{
  unsigned int del = period*10; // random delay for dominant signal, has to be in the timeframe from 250us ... 5ms
  if(ch==2)
  {
    Serial2.end();
    pinMode(LIN_CH2_TX_PIN, OUTPUT);           // set pin to input
    digitalWrite(LIN_CH2_TX_PIN, LOW);       // turn on pullup resistors
    delayMicroseconds(del); // delay
    digitalWrite(LIN_CH2_TX_PIN, HIGH);   
  }
  else if(ch==1)
  {
    Serial1.end();
    pinMode(LIN_CH1_TX_PIN, OUTPUT);           // set pin to input
    digitalWrite(LIN_CH1_TX_PIN, LOW);       // turn on pullup resistors
    delayMicroseconds(del); // delay
    digitalWrite(LIN_CH1_TX_PIN, HIGH);   
    
  }
  return 1;
}

int lin_stack::readResponseByID(byte messageID, byte* recvBuffer, byte bufferLength)
{
  // ####### WRITE FRAMEREQEST
  // #####################################
  // Create Header
  byte identByte = (messageID&0x3f) | calcIdentParity(messageID);
  byte header[2]= {0x55, identByte};
  // Start interface
  sleep(1); // Go to Normal mode
  // Synch Break
  serial_pause(13);
  // Send data via Serial interface
  if(ch==1)
  { // For LIN1 or Serial1
    Serial1.begin(baudRate); // config Serial
    Serial1.write(header,2); // write data to serial

  }
  else if(ch==2)
  { // For LIN2 or Serial2
    Serial2.begin(baudRate); // config Serial
    Serial2.write(header,2); // write data to serial
  }

  // ####### READ VALUES FROM SLAVE(S)
  // #####################################
  
  byte rec[bufferLength+3];
  int retVal = 0;

  // wait a little until slaves have sent its data
  delay(10);
  
  
  if(ch==1)
  { // For LIN1 or Serial1

    if(Serial1.available() == bufferLength+3 )
    { // Check if there is an event on LIN bus
     
      Serial1.readBytes(rec,bufferLength+3);
#if (DEBUG_LIN_PRINT_RAW_PURE_RX_MSGS >= 1)
      printLinRxDataBuffer(ch, rec,bufferLength+3); 
#endif 
      if((validateEnhancedChecksum(rec,bufferLength+3))) 
      {
        for(int j=0;j<bufferLength;j++) 
          recvBuffer[j] = rec[j+2];
        retVal = 1; // success
      }
      else
        retVal = -2; // transmittion error, checksum not valid
    }
    else
      retVal = -1; // no data available on LIN bus

#if (DEBUG_LIN_PRINT_RAW_DATA_RX_MSGS >= 1)
      printLinRxDataBuffer(ch, recvBuffer,bufferLength); 
#endif 

   sleep(0);
   Serial1.end();
   return retVal;
  }


  else if(ch==2)
  { // For LIN1 or Serial1

    if(Serial2.available() > 0 )
    { // Check if there is an event on LIN bus
     
      Serial2.readBytes(rec,bufferLength+3);
#if (DEBUG_LIN_PRINT_RAW_PURE_RX_MSGS >= 1)
      printLinRxDataBuffer(ch, rec,bufferLength+3); 
#endif 
      if((validateEnhancedChecksum(rec,bufferLength+3))) 
      {
        for(int j=0;j<bufferLength;j++) 
          recvBuffer[j] = rec[j+2];
        retVal = 1; // success
      }
      else
        retVal = -2; // transmittion error, checksum not valid
    }
    else
      retVal = -1; // no data available on LIN bus

#if (DEBUG_LIN_PRINT_RAW_DATA_RX_MSGS >= 1)
      printLinRxDataBuffer(ch, recvBuffer,bufferLength); 
#endif 

   sleep(0);
   Serial2.end();
   return retVal;
  }

  
}

void lin_stack::printLinRxDataBuffer(byte channel, byte * data, byte dataLength)
{
  int i = 0;
  Serial.print("\n### Channel:");
  Serial.print(channel, DEC); 
  Serial.print(" ### ID  "); 
  for (i=0; i<dataLength; i++ )
  {
    Serial.print(" ## 0x"); 
    Serial.print(data[i], HEX);
  }
}

/* Create the Lin ID parity */
#define BIT(data,shift) ((ident&(1<<shift))>>shift)
byte lin_stack::calcIdentParity(byte ident)
{
  byte p0 = BIT(ident,0) ^ BIT(ident,1) ^ BIT(ident,2) ^ BIT(ident,4);
  byte p1 = ~(BIT(ident,1) ^ BIT(ident,3) ^ BIT(ident,4) ^ BIT(ident,5));
  return (p0 | (p1<<1))<<6;
}
