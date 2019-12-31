#ifndef TFT_VAN_H
#define TFT_VAN_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include "battery_info.h"
#include "settings.h"


const char compile_date[] = __DATE__ " " __TIME__;

class tft_van : public  Adafruit_ST7735
{
  public:
    // Constructors
    tft_van() : Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST) {}// Constructor for Master Node
    
    // Methods
    void initBatteryInfoScreen(byte isStarterBatt);
    void updateBatteryInfo(batteryInfo*);
    void initInfoScreen(); // this function is for setting up position of pixels etc..
    void updateStartupScreen();
    void initSetupScreen();
    void displayCarInfo() {}   
  
  // Private methods and variables
  private:
    void drawTxt(bool isInit, float u, int soh, float cap, float temp);
    void drawAmpOld(float amp);
    void drawAmp(float amp);
    void drawAkkuOld(int cap, int ti, int calib);
    void drawAkku(int cap);



    // coordinates for screen setup
    byte x0 = 0;
    byte y0 = 27;
    byte w = 135;
    byte h = 85;

    
};

#endif
