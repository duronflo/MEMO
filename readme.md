# Multivan Energy Monitor (MEMO)

Multivan Energy Monitor (MEMO) is an easy energy monitor which easily displays the energy information of batteries integrated in a car, campervan or RV. In this project a display including its control buttion have been integrated in a climatic control unit from a Volkswagen T4 Multivan at the rear seats. The energy information of the battery itself are read via LIN bus from a so called Integrated-Battery-Sensor (IBS). The IBS technology is currently used in almost every car and it is directly connected on battery minus pole. It has a current, voltage and temperature sensing unit and sends these information - including some other useful eg. State of charge, state of health - in cyclic way to the energy management unit in the car. For a camper/RV it is common to use to two different batteries, one for starting the engine und the other one for supplying the camping stuff (lights, fridge, charger,...). Attached you can see some pictures of the project.

![alt text](https://raw.githubusercontent.com/duronflo/MEMO/master/Bilder/2020-01-01%2017_19_12-Window.png)
![alt text](https://raw.githubusercontent.com/duronflo/MEMO/master/Bilder/2020-01-01%2016_56_33-Window.png)
![alt text](https://raw.githubusercontent.com/duronflo/MEMO/master/Bilder/IMG_20200102_171716_354.jpg | width 200)
![alt text](https://raw.githubusercontent.com/duronflo/MEMO/master/Bilder/IMG_20200222_160845_241.jpg | width 200)

In this project a Arduino MEGA 2560 has been used. Furthermore a Macchina M2 car interface board was used in order to have a proper connection to car bord net (12V power supply circuit, 2x 12V LIN channel). The Arduino itslelf was connected to a small 1.8" tft display. The buttons of the former climatic module were also cabled to the arduino.

This project uses inspiration and code snipets from follwing projecs: 
- https://github.com/frankschoeniger/LIN_Interface/#    Interface with Display for IBS using Arduino which bases on: https://www.kastenwagenforum.de/forum/threads/diy-hella-ibs-batteriecomputer.31724/ 
- https://github.com/gandrewstone/LIN
- https://github.com/duronflo/MuMon
- https://github.com/duronflo/LIN



