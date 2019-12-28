#include "tft_van.h"


void tft_van::initStartupScreen()
{

  this->fillScreen(ST7735_BLACK);
  this->setTextColor(ST7735_WHITE, ST7735_BLACK);
  this->setCursor(1, 40);
  this->print("MEMO ");

  this->setCursor(1, 50);
  this->print("Multivan Energy Monitor");

    this->setCursor(1, 60);
  this->print("Build-Date: 12/19");

   this->setCursor(1, 90);
  this->print("by duronflo@web.de");
}



void tft_van::updateStartupScreen()
{
}

void tft_van::updateBatteryInfo(batteryInfo* battInfo)
{
  if (battInfo->isBatteryInfoValid)
  {
    drawAkku(battInfo->SoC, 0, 1);
    drawAmp(battInfo->I_Current);
    drawTxt(0, battInfo->U_Voltage, battInfo->SoH, battInfo->availCap, battInfo->batteryTemp);    
  }
  else 
  {
    drawAkku(0, 0, 1);
    drawAmp(0);
    drawTxt(1,0,0,0,0);    
  }

}

void tft_van::initBatteryInfoScreen(byte isStarterBatt) {

  this->fillScreen(ST7735_BLACK);

  // Akku
  int x = XAKK; // 15
  int y = YAKK; // 20

  //this->fillRect(x, y + 13, 40, 74, ST7735_WHITE);
  this->fillRect(x, y, 30, 60, ST7735_WHITE);
  
  // Batteriekappe
  //this->fillRect(x + 10, y + 6, 20, 7, ST7735_WHITE);
  //this->fillRect(x + 15, y + 1, 10, 5, ST7735_WHITE);

  
  this->setTextColor(ST7735_WHITE, ST7735_BLACK);
  this->setCursor(x, y - 10);
  if (isStarterBatt)
    this->print("Starter");
  else
    this->print("Wohnen");

  // Amperemeter
  x = XAMP;
  y = YAMP;

  this->fillRect(x, y + 3, 10, 85, ST7735_WHITE);
  this->drawLine(x + 10, y + 5, x + 20, y + 5, ST7735_WHITE);
  this->drawLine(x + 10, y + 25, x + 20, y + 25, ST7735_WHITE);
  this->drawLine(x + 10, y + 66, x + 20, y + 66, ST7735_WHITE);
  this->drawLine(x + 10, y + 86, x + 20, y + 86, ST7735_WHITE);
  this->drawLine(x + 10, y + 15, x + 15, y + 15, ST7735_WHITE);
  this->drawLine(x + 10, y + 35, x + 15, y + 35, ST7735_WHITE);
  this->drawLine(x + 10, y + 56, x + 15, y + 56, ST7735_WHITE);
  this->drawLine(x + 10, y + 76, x + 15, y + 76, ST7735_WHITE);
  this->drawLine(x + 10, y + 46, x + 25, y + 46, ST7735_WHITE);



  // Werte
  x = XTEX;
  y = YTEX;

  this->fillRect(x, y, 44, 24, ST7735_WHITE);
  this->fillRect(x, y + 28, 44, 24, ST7735_WHITE);
  this->fillRect(x, y + 56, 44, 24, ST7735_WHITE);
  this->fillRect(x, y + 84, 44, 24, ST7735_WHITE);
  this->setTextColor(ST7735_BLACK, ST7735_WHITE);
  this->setCursor(x + 9, y + 2);
  this->print("UBat:");
  this->setCursor(x + 12, y + 30);
  this->print("SOH:");
  this->setCursor(x + 4, y + 58);
  this->print("Capac.");
  this->setCursor(x + 7, y + 86);
  this->print("Temp.");
}

void tft_van::drawTxt(bool isInit, float u, int soh, float cap, float temp) {

  int x = XTEX;
  int y = YTEX;
  
  if (isInit)
  {
    this->setTextColor(ST7735_BLACK, ST7735_WHITE);
    this->setCursor(x + 3, y + 13);
    this->print("--");
    this->print("V");
  
    this->setCursor(x + 12, y + 41);
    this->print("--");
    this->print(" %");
  
    this->setCursor(x + 4, y + 69);
    this->print("--");
    this->print("Ah");
  
    this->setCursor(x + 4, y + 97);
    this->print("--");
    this->print(" C");    
  }
  else 
  {
    this->setTextColor(ST7735_BLACK, ST7735_WHITE);
    this->setCursor(x + 3, y + 13);
    this->print(u, 2);
    this->print("V");
  
    this->setCursor(x + 12, y + 41);
    this->print(soh);
    this->print(" %");
  
    this->setCursor(x + 4, y + 69);
    this->print(cap, 1);
    this->print("Ah");
  
    this->setCursor(x + 4, y + 97);
    this->print(temp, 1);
    this->print(" C");    
  }


}


void tft_van::drawAmp(float amp) {


  boolean laden = true;
  int x = XAMP;
  int y = YAMP;
  int ix;
  float strom;

  strom = amp;
  if (strom < 0) {
    strom = strom * -1;
    laden = false;
  }

  if (strom > 500) {
    return;
  }

  if (strom <= 2) {
    this->setTextColor(ST7735_WHITE, ST7735_BLACK);
    this->setCursor(x + 30, y + 20);
    this->print("1  ");
    this->setCursor(x + 30, y + 1);
    this->print("2  ");
    this->setCursor(x + 30, y + 62);
    this->print("1  ");
    this->setCursor(x + 30, y + 82);
    this->print("2  ");
    ix = int(strom * 20);

    if (ix > 40) {
      ix = 40;
    }
    if (laden) {
      this->fillRect(x, y + 3, 10, 85, ST7735_WHITE);
      this->fillRect(x, y + 43 + ix, 10, 5, ST7735_GREEN);
    }  else {
      this->fillRect(x, y + 3, 10, 85, ST7735_WHITE);
      this->fillRect(x, y + 43 - ix, 10, 5, ST7735_RED);
    }
  } else if ((strom > 2) & (strom <= 20)) {
    this->setTextColor(ST7735_WHITE, ST7735_BLACK);
    this->setCursor(x + 30, y + 20);
    this->print("10 ");
    this->setCursor(x + 30, y + 1);
    this->print("20 ");
    this->setCursor(x + 30, y + 62);
    this->print("10 ");
    this->setCursor(x + 30, y + 82);
    this->print("20 ");
    ix = int(strom * 2);
    if (ix > 40) {
      ix = 40;
    }
    if (laden) {
      this->fillRect(x, y + 3, 10, 85, ST7735_WHITE);
      this->fillRect(x, y + 43 + ix, 10, 5, ST7735_GREEN);
    }  else {
      this->fillRect(x, y + 3, 10, 85, ST7735_WHITE);
      this->fillRect(x, y + 43 - ix, 10, 5, ST7735_RED);
    }
  } else if (strom > 20) {
    this->setTextColor(ST7735_WHITE, ST7735_BLACK);
    this->setCursor(x + 30, y + 20);
    this->print("100");
    this->setCursor(x + 30, y + 1);
    this->print("200");
    this->setCursor(x + 30, y + 62);
    this->print("100");
    this->setCursor(x + 30, y + 82);
    this->print("200");
    ix = int(strom * 0.2);
    if (ix > 40) {
      ix = 40;
    }
    if (laden) {
      this->fillRect(x, y + 3, 10, 85, ST7735_WHITE);
      this->fillRect(x, y + 43 + ix, 10, 5, ST7735_GREEN);
    }  else {
      this->fillRect(x, y + 3, 10, 85, ST7735_WHITE);
      this->fillRect(x, y + 43 - ix, 10, 5, ST7735_RED);
    }
  }

  this->setTextColor(ST7735_WHITE, ST7735_BLACK);
  this->setCursor(x - 5, 112);
  this->print(amp);
  this->print(" A");

}

void tft_van::drawAkku(int cap, int ti, int calib) {

  int x = XAKK;
  int y = YAKK;

  if (cap >= 90) {
    this->fillRect(x + 4, y + 11, 24, 7, ST7735_GREEN);
    this->fillRect(x + 4, y + 31, 27, 7, ST7735_GREEN);
    this->fillRect(x + 4, y + 45, 27, 7, ST7735_GREEN);
    this->fillRect(x + 4, y + 59, 27, 7, ST7735_GREEN);
    this->fillRect(x + 4, y + 73, 27, 7, ST7735_GREEN);

  } else if (cap >= 70) {
    this->fillRect(x + 4, y + 17, 27, 7, ST7735_WHITE);
    this->fillRect(x + 4, y + 31, 27, 7, ST7735_GREEN);
    this->fillRect(x + 4, y + 45, 27, 7, ST7735_GREEN);
    this->fillRect(x + 4, y + 59, 27, 7, ST7735_GREEN);
    this->fillRect(x + 4, y + 73, 27, 7, ST7735_GREEN);

  } else if (cap >= 50) {
    this->fillRect(x + 4, y + 17, 27, 7, ST7735_WHITE);
    this->fillRect(x + 4, y + 31, 27, 7, ST7735_WHITE);
    this->fillRect(x + 4, y + 45, 27, 7, ST7735_YELLOW);
    this->fillRect(x + 4, y + 59, 27, 7, ST7735_YELLOW);
    this->fillRect(x + 4, y + 73, 27, 7, ST7735_YELLOW);

  } else if (cap >= 30) {
    this->fillRect(x + 4, y + 17, 27, 7, ST7735_WHITE);
    this->fillRect(x + 4, y + 31, 27, 7, ST7735_WHITE);
    this->fillRect(x + 4, y + 45, 27, 7, ST7735_WHITE);
    this->fillRect(x + 4, y + 59, 27, 7, ST7735_YELLOW);
    this->fillRect(x + 4, y + 73, 27, 7, ST7735_YELLOW);

  } else {
    this->fillRect(x + 4, y + 17, 27, 7, ST7735_WHITE);
    this->fillRect(x + 4, y + 31, 27, 7, ST7735_WHITE);
    this->fillRect(x + 4, y + 45, 27, 7, ST7735_WHITE);
    this->fillRect(x + 4, y + 59, 27, 7, ST7735_WHITE);
    this->fillRect(x + 4, y + 73, 27, 7, ST7735_RED);
  }

  this->setTextColor(ST7735_WHITE, ST7735_BLACK);

  if (calib == 0) {
    this->setTextColor(ST7735_RED, ST7735_BLACK);
    this->setCursor(x + 6, y + 92);
    this->print(cap, 1);
    this->print(" %");
  } else {
    this->setTextColor(ST7735_WHITE, ST7735_BLACK);
    this->setCursor(x + 6, y + 92);
    this->print(cap, 1);
    this->print(" %");
  }

  /* expected time - die passt aber noch nicht
    setCursor(x + 4, 8);
    print(ti);
    print(" h    ");
  */
}
