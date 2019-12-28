#ifndef LIN_IBS_H
#define LIN_IBS_H

#define DEBUG_LIN_PRINT_MSG_1 0
#define DEBUG_LIN_PRINT_MSG_2 0
#define DEBUG_LIN_PRINT_MSG_3 0

#define MAX_ERROR_MSG_COUNT 3


#include "lin_stack.h"
#include "battery_info.h"

enum { LinCh1=1, LinCh2=2 };


class lin_ibs : public lin_stack
{
  public:
    // Constructors
    lin_ibs(byte Ch) : lin_stack(Ch) {} // Constructor for Master Node

    
    // Methods
    
    // Writing data to bus
    byte readBatteryValues(batteryInfo*); // Write header only

  /*
   * batteryType
   *   Starter -- 1 
   *   GEL -- 2
   *   AGM -- 3
   *  
   * nomCapacity
   *  1...255
   */
    byte sendConfiguration(byte batteryType, byte nomCapacity);
       
  // Private methods and variables
  private:
  // read battery voltage, current and temperature
  bool readFrame1(batteryInfo* battInfo);
  // read SoC and SoH
  bool readFrame2(batteryInfo* battInfo);
  // read calibration flag and available capacity
  bool readFrame3(batteryInfo* battInfo);
  
  

  

    
};

#endif
