#include "lin_ibs.h"

byte lin_ibs::readBatteryValues(batteryInfo* battInfo)
{
  // Check messages for valid data
  
  if ( !readFrame1(battInfo) || !readFrame2(battInfo) || !readFrame3(battInfo)) 
  {    
    battInfo->cntRecvInvalidMsgs++;
    Serial.print("\n -- INVALID -- \n");
    if ( battInfo->cntRecvInvalidMsgs > MAX_ERROR_MSG_COUNT)
      battInfo->cntRecvInvalidMsgs = MAX_ERROR_MSG_COUNT;
    // possibly bus is sleeping, try to wake up ...
    busWakeUp();
  }
  else
  {
    battInfo->cntRecvInvalidMsgs--;
    if ( battInfo->cntRecvInvalidMsgs < 0)
      battInfo->cntRecvInvalidMsgs = 0;   
  }

  // Decide wether data is valid or not
  if (battInfo->cntRecvInvalidMsgs < MAX_ERROR_MSG_COUNT && battInfo->cntRecvInvalidMsgs >= 0)
  {
    battInfo->isBatteryInfoValid = 1;
    return 1;
  }
    
  else 
  {
    battInfo->isBatteryInfoValid = 0;
    return 0;
  }
  
}

// Read Frame IBS_FRM - Current Values
bool lin_ibs::readFrame1(batteryInfo* battInfo)
{
  // grab dataframe from bus
  int ret;
  byte recv_buffer[8];
  ret = readResponseByID(0x28, recv_buffer, 7);
  if (ret < 0)
    return 0;
  else
  {
    battInfo->U_Voltage = (float(   (recv_buffer[4] << 8) + recv_buffer[3])) / 1000;
    battInfo->I_Current = (float((long(recv_buffer[2]) << 16) + (long(recv_buffer[1]) << 8) + long(recv_buffer[0]) - 2000000L)) / 1000;
    battInfo->batteryTemp = long(recv_buffer[5]) / 2 - 40;   
#if (DEBUG_LIN_PRINT_MSG_1 >= 1)
  Serial.write("#### DEBUG_LIN_PRINT_MSG_1 ####\n");
  Serial.print("\nU_batt "); 
  Serial.print(battInfo->U_Voltage, DEC);
  Serial.print("\n");
  Serial.print("\nI_batt "); 
  Serial.print(battInfo->I_Current, DEC);
  Serial.print("\n");
  Serial.print("\nT_batt "); 
  Serial.print(battInfo->batteryTemp, DEC);
  Serial.print("\n");
#endif
    return 1; 
  }
}

// Read Frame IBS_FRM - SoC, SoH
bool lin_ibs::readFrame2(batteryInfo* battInfo)
{
  // grab dataframe from bus
  int ret;
  byte recv_buffer[8] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  ret = readResponseByID(0x2B, recv_buffer, 6);
  if (ret < 0)
    return 0;
  else
  {
    battInfo->SoC = int(recv_buffer[0]) / 2;
    battInfo->SoH = int(recv_buffer[1]) / 2; 

#if (DEBUG_LIN_PRINT_MSG_2 >= 1)
  Serial.write("#### DEBUG_LIN_PRINT_MSG_2 ####\n");
  Serial.print("\nSoC "); 
  Serial.print(battInfo->SoC, DEC);
  Serial.print("\n");
  Serial.print("\nSoH "); 
  Serial.print(battInfo->SoH, DEC);
  Serial.print("\n");
#endif
   return 1; 
  }
}

bool lin_ibs::readFrame3(batteryInfo* battInfo)
{
  // grab dataframe from bus
  int ret;
  byte recv_buffer[8] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  ret = readResponseByID(0x2C, recv_buffer, 6);
  if (ret < 0)
    return 0;
  else
  {
     
    int Calib = bitRead(recv_buffer[5], 0);
    battInfo->availCap = (float((recv_buffer[3] << 8) + recv_buffer[2])) / 10; 
#if (DEBUG_LIN_PRINT_MSG_3 >= 1)
  Serial.write("#### DEBUG_LIN_PRINT_MSG_3 ####\n");
  Serial.print("\Available Capacity:"); 
  Serial.print(battInfo->availCap, DEC);
  Serial.print("\n");
  Serial.print("\nKalibration aktiv: "); 
  Serial.print(Calib, DEC);
  Serial.print("\n");
#endif
    return 1; 
  }
}

byte lin_ibs::sendConfiguration(byte batteryType, byte nomCapacity)
{
  // setting nominal capacity
  byte send_buffer[8] = {0x2, 0x3, 0xb5, 0x39, 0x0, 0xff, 0xff, 0xff}; 
  send_buffer[4] = nomCapacity;
  write(0x3C, send_buffer, 8);

  delay(100);
  //settinb battery type
  send_buffer[3] = 0x3a;
  send_buffer[4] = 0x0a;
  send_buffer[5] = batteryType;
  write(0x3C, send_buffer, 8);

}
