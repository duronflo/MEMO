/*
  MEMO - Multivan Energy Montior

Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
*/

#include "settings.h"
#include "battery_info.h"
#include "tft_van.h"
#include "lin_ibs.h"

/**********************/
// Definition of hardware globally
/**********************/

// Lin_Ch1 and Lin_Ch2 for both IBS
lin_ibs LIN1_Starter(LinCh1);
lin_ibs LIN2_Living(LinCh2);

// SPI TFT 1.8"
tft_van tft;

// UserButton for switching screens
const int buttonPin = 55; // big button on bottom // 56 --> Left Buttons // 54 --> Right Buttons

/**********************/
// Definition of info and state variables
/**********************/

// holds battery information of each battery
batteryInfo batteryInfoStarter;
batteryInfo batteryInfoLiving;
// initial state variable for statemachine
state_t state = ST_BATT_LIVING;


// the setup function runs once when you press reset or power the board
void setup() 
{


  // Initialize 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  tft.setRotation(3);
  tft.fillScreen(ST7735_BLACK);
  //tft.initStartupScreen();
  
  // Initialize LIN interfaces
  lin_ibs LIN1_Starter(LinCh1);
  lin_ibs LIN2_Living(LinCh2);
  
  // Initialize UART via USB
  Serial.begin(9600);
 
  pinMode(buttonPin, INPUT);
  pinMode(12, OUTPUT);
  
  // set battery configuration
  //LIN1_Starter.sendConfiguration(1, 95);
  //LIN2_Living.sendConfiguration(2, 70);
}

// the loop function runs over and over again forever
void loop() {
  // put your main code here, to run repeatedly:


  //LIN1_Starter.sendConfiguration(1, 95);
  LIN1_Starter.readBatteryValues(&batteryInfoStarter);
  LIN2_Living.readBatteryValues(&batteryInfoLiving);

  runDisplayStateMachine();  

  delay(66);

  Serial.print(batteryInfoStarter.cntRecvInvalidMsgs);
  Serial.print("\n");

  Serial.print(batteryInfoLiving.cntRecvInvalidMsgs);
  Serial.print("\n");


}


bool isButtonNextPushed()
{
    int oldButtonState, newButtonState;   
    oldButtonState = digitalRead(buttonPin);
    delay(10);
    newButtonState = digitalRead(buttonPin);
    
    if (newButtonState == HIGH && (newButtonState == oldButtonState) ) {   // If button is pressed
      return true;  
    } else {
      return false; 
    }
}

 
void runDisplayStateMachine()
{
  switch( state ) {
    case ST_INIT:
      tft.updateStartupScreen();
      //LIN2_Living.sendConfiguration(1, 55);
      if( isButtonNextPushed() ) {
        tft.initBatteryInfoScreen(1);
        state = ST_BATT_STARTER;
        Serial.write("ST_INIT\n");
      }
      break;
 
    case ST_BATT_STARTER:
      tft.updateBatteryInfo(&batteryInfoStarter);
      if( isButtonNextPushed() ) {
        tft.initBatteryInfoScreen(0);
        state = ST_BATT_LIVING;
        Serial.write("ST_BATT_STARTER\n");
      }
      break;
 
    case ST_BATT_LIVING:
      tft.updateBatteryInfo(&batteryInfoLiving);
      if( isButtonNextPushed() ) {
        state = ST_INIT;
        tft.initStartupScreen();
        Serial.write("ST_BATT_LIVING\n");
      }
      break;

    case ST_CAR_INFO:
      if( isButtonNextPushed() ) {
        state = ST_INIT;
        tft.initStartupScreen();
        Serial.write("ST_CAR_INFO\n");
      }
      break;

  }
}
