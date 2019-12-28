#ifndef BATTERY_INFO_H
#define BATTERY_INFO_H

struct batteryInfo
{
  byte isBatteryInfoValid = 0;
  int cntRecvInvalidMsgs = 0;
  byte SoC;
  byte SoH;
  byte batteryTemp;
  byte availCap;
  float U_Voltage;
  float I_Current;
};

#endif
