#include "tft_van.h"


void tft_van::initInfoScreen()
{

  this->fillScreen(ST7735_BLACK);
  this->setTextColor(ST7735_BLUE, ST7735_BLACK);
  this->setCursor(1, 33);
  this->print("MEMO ");

  this->setCursor(1, 50);
  this->print("M");
  this->setTextColor(ST7735_WHITE, ST7735_BLACK);
  this->print("ultivan ");
  this->setTextColor(ST7735_BLUE, ST7735_BLACK);
  this->print("E");
  this->setTextColor(ST7735_WHITE, ST7735_BLACK);
  this->print("nergy ");
  this->setTextColor(ST7735_BLUE, ST7735_BLACK);
  this->print("Mo");
  this->setTextColor(ST7735_WHITE, ST7735_BLACK);
  this->print("nitor");  


  this->setTextColor(ST7735_WHITE, ST7735_BLACK);
  this->setCursor(1, 75);
  this->print("Build-Date:\n");
  this->print(compile_date);

   this->setCursor(1, 95);
  this->print("by duronflo@web.de");
}

void tft_van::initSetupScreen()
{

// Absolute Koordinaten
/*
 * X0 0
 * X1 135
 * 
 * Y0 27
 * Y1 107
 */

 byte isStarterBatt = 1;

  byte x0 = 0;
  byte y0 = 27;
  byte w = 135;
  byte h = 85;

  this->setTextColor(ST7735_WHITE, ST7735_BLACK);
  this->setCursor(x0, y0+5);
  if (isStarterBatt)
    this->print("STARTER");
  else
    this->print("WOHNEN");



  this->fillRect(x0+2, y0+18, 30, 60, ST7735_WHITE);
  // Kappe
  this->fillRect(x0+7, y0+15, 20, 60, ST7735_WHITE);
  
  // SoC Text
  this->setTextColor(ST7735_BLUE, ST7735_WHITE);
  this->setCursor(x0+7, y0+69);
  this->print("99%");

  // SoC Bars
  this->fillRect(x0 + 4, y0+19 , 26, 5, ST7735_GREEN);
  this->fillRect(x0 + 4, y0+26, 26, 5, ST7735_GREEN);
  this->fillRect(x0 + 4, y0+33, 26, 5, ST7735_GREEN);
  this->fillRect(x0 + 4, y0+40, 26, 5, ST7735_GREEN);
  this->fillRect(x0 + 4, y0+47, 26, 5, ST7735_GREEN);  
  this->fillRect(x0 + 4, y0+54, 26, 5, ST7735_GREEN);  
  this->fillRect(x0 + 4, y0+61, 26, 5, ST7735_GREEN);  


 // Boxes for Text #### MIDDLE
  byte x1 = x0 + (w/2) - 20 ;
  byte y1 = y0 + 4;
  this->fillRect(x1, y1, 44, 24, ST7735_WHITE);
  this->fillRect(x1, y1 + 28, 44, 24, ST7735_WHITE);
  this->fillRect(x1, y1 + 56, 44, 24, ST7735_WHITE);
  this->setTextColor(ST7735_BLACK, ST7735_WHITE);
  this->setCursor(x1 + 9, y1 + 2);
  this->print("UBat");
  this->setCursor(x1 + 9, y1 + 13);
  this->print("12.5V");
  this->setCursor(x1 + 12, y1 + 30);
  this->print("SoH");
  this->setCursor(x1 + 12, y1 + 41);
  this->print("100%");
  this->setCursor(x1 + 12, y1 + 58);
  this->print("Temp");
  this->setCursor(x1 + 8, y1 + 69);
  this->print("28 C");


//  // Boxes for Text #### LAST ROW
//  x1 = x0 + (3*w/4) - 7 ;
//  y1 = y0 + 4;
//  this->fillRect(x1, y1, 44, 24, ST7735_WHITE);
//  this->setTextColor(ST7735_BLACK, ST7735_WHITE);
//  this->setCursor(x1 + 9, y1 + 2);
//  this->print("Ibat");
//  this->setTextColor(ST7735_RED, ST7735_WHITE);
//  this->setCursor(x1 + 9, y1 + 13);
//  this->print("-5.4A");


//  // Boxes for Text #### FIRST ROW
//  byte x1 = x0 ;
//  byte y1 = y0 + 4;
//  this->fillRect(x1, y1 + 56, 44, 24, ST7735_WHITE);
//  this->setTextColor(ST7735_BLACK, ST7735_WHITE);
//  this->setCursor(x1 + 12, y1 + 58);
//  this->print("SoC");
//
//  this->setCursor(x1 + 12, y1 + 69);
//  this->print("50%");


  this->fillRect(x0+130, y0 + 5, 5, 60, ST7735_WHITE);
  //fat lines
  this->drawLine(x0+130 - 9, y0 + 5, x0+130, y0 + 5, ST7735_WHITE);
  this->drawLine(x0+130 - 12, y0 + 5 + 30, x0+130, y0 + 5 + 30, ST7735_WHITE);
  this->drawLine(x0+130 - 9, y0 + 5 + 59, x0+130, y0 + 5 + 59, ST7735_WHITE);
  // thin lines
  this->drawLine(x0+130 - 5, y0 + 5 + 15, x0+130, y0 + 5 + 15, ST7735_WHITE);
  this->drawLine(x0+130 - 5, y0 + 5 + 45, x0+130, y0 + 5 + 45, ST7735_WHITE);

  //middle
  this->setTextColor(ST7735_WHITE, ST7735_BLACK);
  this->setCursor(x0+130 - 25, y0 + 5 + 27);
  this->print("0A");

  //top
  this->setTextColor(ST7735_WHITE, ST7735_BLACK);
  this->setCursor(x0+130 - 31, y0 + 5);
  this->print("+5A");

  //bottom
  this->setTextColor(ST7735_WHITE, ST7735_BLACK);
  this->setCursor(x0+130 - 31, y0 + 5 + 53);
  this->print("-5A");

  // Boxes for Text #### LAST ROW
  this->setTextColor(ST7735_GREEN, ST7735_BLACK);
  this->setCursor(x0 + 105, y0 + 71);
  this->print("+3.0A");

  // Boxes for Text #### LAST ROW
  this->fillRect(x0+126, y0 + 5 + 56, 9, 4, ST7735_GREEN);


}

void tft_van::updateStartupScreen()
{
}

void tft_van::updateBatteryInfo(batteryInfo* battInfo)
{
  if (battInfo->isBatteryInfoValid)
  {
    drawAkku(battInfo->SoC);
    drawAmp(battInfo->I_Current);
    drawTxt(0, battInfo->U_Voltage, battInfo->SoH, battInfo->availCap, battInfo->batteryTemp);    
  }
  else 
  {
    drawAkku(0);
    drawAmp(0);
    drawTxt(1,0,0,0,0);    
  }

}

void tft_van::initBatteryInfoScreen(byte isStarterBatt) {

  this->fillScreen(ST7735_BLACK);



/// TEXT Starter or Wohnen which indictes the sensor
  this->setTextColor(ST7735_WHITE, ST7735_BLACK);
  this->setCursor(x0, y0+5);
  if (isStarterBatt)
    this->print("STARTER");
  else
    this->print("WOHNEN");


  // Draw Battery
  this->fillRect(x0+2, y0+18, 30, 60, ST7735_WHITE);
  // Batterycape
  this->fillRect(x0+7, y0+15, 20, 60, ST7735_WHITE);
  


 // Text Boxes in the middle of the screen
  byte x1 = x0 + (w/2) - 20 ;
  byte y1 = y0 + 4;
  this->fillRect(x1, y1, 44, 24, ST7735_WHITE);
  this->fillRect(x1, y1 + 28, 44, 24, ST7735_WHITE);
  this->fillRect(x1, y1 + 56, 44, 24, ST7735_WHITE);


/// Draw Ampere meter ...

  this->fillRect(x0+130, y0 + 5, 5, 60, ST7735_WHITE);
  //fat lines
  this->drawLine(x0+130 - 9, y0 + 5, x0+130, y0 + 5, ST7735_WHITE);
  this->drawLine(x0+130 - 12, y0 + 5 + 30, x0+130, y0 + 5 + 30, ST7735_WHITE);
  this->drawLine(x0+130 - 9, y0 + 5 + 59, x0+130, y0 + 5 + 59, ST7735_WHITE);
  // thin lines
  this->drawLine(x0+130 - 5, y0 + 5 + 15, x0+130, y0 + 5 + 15, ST7735_WHITE);
  this->drawLine(x0+130 - 5, y0 + 5 + 45, x0+130, y0 + 5 + 45, ST7735_WHITE);

}


void tft_van::drawTxt(bool isInit, float u, int soh, float soc, float temp) {

  byte x1 = x0 + (w/2) - 20 ;
  byte y1 = y0 + 4;

  
  if (isInit)
  {
    this->setTextColor(ST7735_BLACK, ST7735_WHITE);
    this->setCursor(x1 + 9, y1 + 2);
    this->print("UBat");
    this->setCursor(x1 + 9, y1 + 13);
    this->print("---");
    this->setCursor(x1 + 12, y1 + 30);
    this->print("SoH");
    this->setCursor(x1 + 12, y1 + 41);
    this->print("---");
    this->setCursor(x1 + 12, y1 + 58);
    this->print("Temp");
    this->setCursor(x1 + 8, y1 + 69);
    this->print("---");   
  }
  else 
  {
    this->setTextColor(ST7735_BLACK, ST7735_WHITE);
    this->setCursor(x1 + 9, y1 + 2);
    this->print("UBat");
    this->setCursor(x1 + 6, y1 + 13);
    this->print(u);
    this->print("V");
    this->setCursor(x1 + 12, y1 + 30);
    this->print("SoH");
    this->setCursor(x1 + 12, y1 + 41);
    this->print(round(soh));
    this->print("%");
    this->setCursor(x1 + 12, y1 + 58);
    this->print("Temp");
    this->setCursor(x1 + 10, y1 + 69);
    this->print(round(temp));
    this->print(" C");
  }


}


void tft_van::drawAmp(float amp) 
{

  float absCurrent;
  bool isCharging = false;
  absCurrent = abs(amp);
  if (amp > 0)
  {
    isCharging = true;
  }
  if (absCurrent <= 5)
  {
    //middle
    this->setTextColor(ST7735_WHITE, ST7735_BLACK);
    this->setCursor(x0+130 - 25, y0 + 5 + 27);
    this->print("0A");
  
    //top
    this->setTextColor(ST7735_WHITE, ST7735_BLACK);
    this->setCursor(x0+130 - 31, y0 + 5);
    this->print("-5A");
  
    //bottom
    this->setTextColor(ST7735_WHITE, ST7735_BLACK);
    this->setCursor(x0+130 - 31, y0 + 5 + 53);
    this->print("+5A");
  
    // Boxes for Text #### LAST ROW

    this->fillRect(x0+130, y0 + 5, 5, 60, ST7735_WHITE);  
    // Indicator on amp meter which is GREEN for charging and RED for discharging
    if (isCharging)
    {
      byte y1 = 30 + 6*absCurrent;
      this->fillRect(x0+130, y0 + 5 + y1, 5, 3, ST7735_GREEN);  
      
      // clean rect for proper and plain overprinting 
      this->setCursor(x0 + 98, y0 + 71);
      this->setTextColor(ST7735_BLACK);
      this->setTextColor(ST7735_GREEN, ST7735_BLACK);
      this->print(amp,2);
      this->print("A");
    }
      
    else
    {
      byte y1 = 30 - 6*absCurrent;
      this->fillRect(x0+130, y0 + 5 + y1, 5, 3, ST7735_RED);
      
      // clean rect for proper and plain overprinting 
      this->setCursor(x0 + 98, y0 + 71);
      this->setTextColor(ST7735_BLACK);
      this->setTextColor(ST7735_RED, ST7735_BLACK);
      this->print(amp,2);
      this->print("A");
    }
       
  }

  else if (absCurrent <= 10)
  {
    //middle
    this->setTextColor(ST7735_WHITE, ST7735_BLACK);
    this->setCursor(x0+130 - 25, y0 + 5 + 27);
    this->print("0A");
  
    //top
    this->setTextColor(ST7735_WHITE, ST7735_BLACK);
    this->setCursor(x0+130 - 31, y0 + 5);
    this->print("-10A");
  
    //bottom
    this->setTextColor(ST7735_WHITE, ST7735_BLACK);
    this->setCursor(x0+130 - 31, y0 + 5 + 53);
    this->print("+10A");
  
    // Boxes for Text #### LAST ROW

    this->fillRect(x0+130, y0 + 5, 5, 60, ST7735_WHITE);  
    // Indicator on amp meter which is GREEN for charging and RED for discharging
    if (isCharging)
    {
      byte y1 = 30 + 3*absCurrent;
      this->fillRect(x0+130, y0 + 5 + y1, 5, 3, ST7735_GREEN);  
      
      // clean rect for proper and plain overprinting 
      this->setCursor(x0 + 98, y0 + 71);
      this->setTextColor(ST7735_BLACK);
      this->setTextColor(ST7735_GREEN, ST7735_BLACK);
      this->print(amp,1);
      this->print("A");
    }
      
    else
    {
      byte y1 = 30 - 3*absCurrent;
      this->fillRect(x0+130, y0 + 5 + y1, 5, 3, ST7735_RED);
      
      // clean rect for proper and plain overprinting 
      this->setCursor(x0 + 98, y0 + 71);
      this->setTextColor(ST7735_BLACK);
      this->setTextColor(ST7735_RED, ST7735_BLACK);
      this->print(amp,1);
      this->print("A");
    }
       
  }
  else if (absCurrent <= 30)
  {
    //middle
    this->setTextColor(ST7735_WHITE, ST7735_BLACK);
    this->setCursor(x0+130 - 25, y0 + 5 + 27);
    this->print("0A");
  
    //top
    this->setTextColor(ST7735_WHITE, ST7735_BLACK);
    this->setCursor(x0+130 - 31, y0 + 5);
    this->print("-30A");
  
    //bottom
    this->setTextColor(ST7735_WHITE, ST7735_BLACK);
    this->setCursor(x0+130 - 31, y0 + 5 + 53);
    this->print("+30A");
  
    // Boxes for Text #### LAST ROW

    this->fillRect(x0+130, y0 + 5, 5, 60, ST7735_WHITE);  
    // Indicator on amp meter which is GREEN for charging and RED for discharging
    if (isCharging)
    {
      byte y1 = 30 + 1*absCurrent;
      this->fillRect(x0+130, y0 + 5 + y1, 5, 3, ST7735_GREEN);  
      
      // clean rect for proper and plain overprinting 
      this->setCursor(x0 + 98, y0 + 71);
      this->setTextColor(ST7735_BLACK);
      this->setTextColor(ST7735_GREEN, ST7735_BLACK);
      this->print(amp,1);
      this->print("A");
    }
      
    else
    {
      byte y1 = 30 - 1*absCurrent;
      this->fillRect(x0+130, y0 + 5 + y1, 5, 3, ST7735_RED);
      
      // clean rect for proper and plain overprinting 
      this->setCursor(x0 + 98, y0 + 71);
      this->setTextColor(ST7735_BLACK);
      this->setTextColor(ST7735_RED, ST7735_BLACK);
      this->print(amp,1);
      this->print("A");
    }
       
  }

  else if (absCurrent <= 60)
  {
    //middle
    this->setTextColor(ST7735_WHITE, ST7735_BLACK);
    this->setCursor(x0+130 - 25, y0 + 5 + 27);
    this->print("0A");
  
    //top
    this->setTextColor(ST7735_WHITE, ST7735_BLACK);
    this->setCursor(x0+130 - 31, y0 + 5);
    this->print("-60A");
  
    //bottom
    this->setTextColor(ST7735_WHITE, ST7735_BLACK);
    this->setCursor(x0+130 - 31, y0 + 5 + 53);
    this->print("+60A");
  
    // Boxes for Text #### LAST ROW

    this->fillRect(x0+130, y0 + 5, 5, 60, ST7735_WHITE);  
    // Indicator on amp meter which is GREEN for charging and RED for discharging
    if (isCharging)
    {
      byte y1 = 30 + 0.5*absCurrent;
      this->fillRect(x0+130, y0 + 5 + y1, 5, 3, ST7735_GREEN);  
      
      // clean rect for proper and plain overprinting 
      this->setCursor(x0 + 98, y0 + 71);
      this->setTextColor(ST7735_BLACK);
      this->setTextColor(ST7735_GREEN, ST7735_BLACK);
      this->print(amp,1);
      this->print("A");
    }
      
    else
    {
      byte y1 = 30 - 0.5*absCurrent;
      this->fillRect(x0+130, y0 + 5 + y1, 5, 3, ST7735_RED);
      
      // clean rect for proper and plain overprinting 
      this->setCursor(x0 + 98, y0 + 71);
      this->setTextColor(ST7735_BLACK);
      this->setTextColor(ST7735_RED, ST7735_BLACK);
      this->print(amp,1);
      this->print("A");
    }
       
  }


   else if (absCurrent <= 200)
  {
    //middle
    this->setTextColor(ST7735_WHITE, ST7735_BLACK);
    this->setCursor(x0+130 - 25, y0 + 5 + 27);
    this->print("0A");
  
    //top
    this->setTextColor(ST7735_WHITE, ST7735_BLACK);
    this->setCursor(x0+130 - 31, y0 + 5);
    this->print("-200A");
  
    //bottom
    this->setTextColor(ST7735_WHITE, ST7735_BLACK);
    this->setCursor(x0+130 - 31, y0 + 5 + 53);
    this->print("+200A");
  
    // Boxes for Text #### LAST ROW

    this->fillRect(x0+130, y0 + 5, 5, 60, ST7735_WHITE);  
    // Indicator on amp meter which is GREEN for charging and RED for discharging
    if (isCharging)
    {
      byte y1 = 30 + 6.67*absCurrent;
      this->fillRect(x0+130, y0 + 5 + y1, 5, 3, ST7735_GREEN);  
      
      // clean rect for proper and plain overprinting 
      this->setCursor(x0 + 98, y0 + 71);
      this->setTextColor(ST7735_BLACK);
      this->setTextColor(ST7735_GREEN, ST7735_BLACK);
      this->print(amp,1);
      this->print("A");
    }
      
    else
    {
      byte y1 = 30 - 6.67*absCurrent;
      this->fillRect(x0+130, y0 + 5 + y1, 5, 3, ST7735_RED);
      
      // clean rect for proper and plain overprinting 
      this->setCursor(x0 + 98, y0 + 71);
      this->setTextColor(ST7735_BLACK);
      this->setTextColor(ST7735_RED, ST7735_BLACK);
      this->print(amp,1);
      this->print("A");
    } 
  }
}


void tft_van::drawAkku(int cap) {


  // SoC Text
  this->setCursor(x0+7, y0+69);
  this->setTextColor(ST7735_WHITE);
  this->setTextColor(ST7735_BLUE, ST7735_WHITE);
  this->print(round(cap));
  this->print("%");


  if (cap >= 90) 
  {
    this->fillRect(x0 + 4, y0+19 , 26, 5, ST7735_GREEN);
    this->fillRect(x0 + 4, y0+26, 26, 5, ST7735_GREEN);
    this->fillRect(x0 + 4, y0+33, 26, 5, ST7735_GREEN);
    this->fillRect(x0 + 4, y0+40, 26, 5, ST7735_GREEN);
    this->fillRect(x0 + 4, y0+47, 26, 5, ST7735_GREEN);  
    this->fillRect(x0 + 4, y0+54, 26, 5, ST7735_GREEN);  
    this->fillRect(x0 + 4, y0+61, 26, 5, ST7735_GREEN);      
  }
  else if (cap >= 70) 
  {
    this->fillRect(x0 + 4, y0+19 , 26, 5, ST7735_WHITE);
    this->fillRect(x0 + 4, y0+26, 26, 5, ST7735_GREEN);
    this->fillRect(x0 + 4, y0+33, 26, 5, ST7735_GREEN);
    this->fillRect(x0 + 4, y0+40, 26, 5, ST7735_GREEN);
    this->fillRect(x0 + 4, y0+47, 26, 5, ST7735_GREEN);  
    this->fillRect(x0 + 4, y0+54, 26, 5, ST7735_GREEN);  
    this->fillRect(x0 + 4, y0+61, 26, 5, ST7735_GREEN);      
  }  
  else if (cap >= 50) 
  {
    this->fillRect(x0 + 4, y0+19 , 26, 5, ST7735_WHITE);
    this->fillRect(x0 + 4, y0+26, 26, 5, ST7735_WHITE);
    this->fillRect(x0 + 4, y0+33, 26, 5, ST7735_GREEN);
    this->fillRect(x0 + 4, y0+40, 26, 5, ST7735_GREEN);
    this->fillRect(x0 + 4, y0+47, 26, 5, ST7735_GREEN);  
    this->fillRect(x0 + 4, y0+54, 26, 5, ST7735_GREEN);  
    this->fillRect(x0 + 4, y0+61, 26, 5, ST7735_GREEN);      
  }  
  else if (cap >= 40) 
  {
    this->fillRect(x0 + 4, y0+19 , 26, 5, ST7735_WHITE);
    this->fillRect(x0 + 4, y0+26, 26, 5, ST7735_WHITE);
    this->fillRect(x0 + 4, y0+33, 26, 5, ST7735_WHITE);
    this->fillRect(x0 + 4, y0+40, 26, 5, ST7735_GREEN);
    this->fillRect(x0 + 4, y0+47, 26, 5, ST7735_GREEN);  
    this->fillRect(x0 + 4, y0+54, 26, 5, ST7735_GREEN);  
    this->fillRect(x0 + 4, y0+61, 26, 5, ST7735_GREEN);      
  }  
  else if (cap >= 30) 
  {
    this->fillRect(x0 + 4, y0+19 , 26, 5, ST7735_WHITE);
    this->fillRect(x0 + 4, y0+26, 26, 5, ST7735_WHITE);
    this->fillRect(x0 + 4, y0+33, 26, 5, ST7735_WHITE);
    this->fillRect(x0 + 4, y0+40, 26, 5, ST7735_WHITE);
    this->fillRect(x0 + 4, y0+47, 26, 5, ST7735_GREEN);  
    this->fillRect(x0 + 4, y0+54, 26, 5, ST7735_GREEN);  
    this->fillRect(x0 + 4, y0+61, 26, 5, ST7735_GREEN);      
  } 
  else if (cap >= 20) 
  {
    this->fillRect(x0 + 4, y0+19 , 26, 5, ST7735_WHITE);
    this->fillRect(x0 + 4, y0+26, 26, 5, ST7735_WHITE);
    this->fillRect(x0 + 4, y0+33, 26, 5, ST7735_WHITE);
    this->fillRect(x0 + 4, y0+40, 26, 5, ST7735_WHITE);
    this->fillRect(x0 + 4, y0+47, 26, 5, ST7735_YELLOW);  
    this->fillRect(x0 + 4, y0+54, 26, 5, ST7735_YELLOW);  
    this->fillRect(x0 + 4, y0+61, 26, 5, ST7735_YELLOW);      
  } 
  else if (cap >= 10) 
  {
    this->fillRect(x0 + 4, y0+19 , 26, 5, ST7735_WHITE);
    this->fillRect(x0 + 4, y0+26, 26, 5, ST7735_WHITE);
    this->fillRect(x0 + 4, y0+33, 26, 5, ST7735_WHITE);
    this->fillRect(x0 + 4, y0+40, 26, 5, ST7735_WHITE);
    this->fillRect(x0 + 4, y0+47, 26, 5, ST7735_WHITE);  
    this->fillRect(x0 + 4, y0+54, 26, 5, ST7735_RED);  
    this->fillRect(x0 + 4, y0+61, 26, 5, ST7735_RED);      
  } 
  else if (cap >= 0) 
  {
    this->fillRect(x0 + 4, y0+19 , 26, 5, ST7735_WHITE);
    this->fillRect(x0 + 4, y0+26, 26, 5, ST7735_WHITE);
    this->fillRect(x0 + 4, y0+33, 26, 5, ST7735_WHITE);
    this->fillRect(x0 + 4, y0+40, 26, 5, ST7735_WHITE);
    this->fillRect(x0 + 4, y0+47, 26, 5, ST7735_WHITE);  
    this->fillRect(x0 + 4, y0+54, 26, 5, ST7735_WHITE);  
    this->fillRect(x0 + 4, y0+61, 26, 5, ST7735_RED);      
  } 

 


}
