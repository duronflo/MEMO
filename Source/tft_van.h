#ifndef TFT_VAN_H
#define TFT_VAN_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include "battery_info.h"
#include "settings.h"


class tft_van : public  Adafruit_ST7735
{
  public:
    // Constructors
    tft_van() : Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST) {}// Constructor for Master Node
    
    // Methods
    void initBatteryInfoScreen(byte isStarterBatt);
    void updateBatteryInfo(batteryInfo*);
    void initStartupScreen();
    void updateStartupScreen();
    void displayCarInfo() {}   
  
  // Private methods and variables
  private:
    void drawTxt(bool isInit, float u, int soh, float cap, float temp);
    void drawAmp(float amp);
    void drawAkku(int cap, int ti, int calib);

    
};

#endif
