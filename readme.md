# Multivan Energy Monitor (MEMO)

An easy energy monitor for use in campers or vans. In this project the control and display unit was integrated in a Volkswagen T4 Multivan instead of the commonly used climatic control at the rear seats.
In campers/vans it is very common to have two different electric energy sources, one for starting the engine and supplying necessary nets to the car and one for the camping net. Both are usauyll connected via a releais.
The monitor is able to display to power flow from/to these two power source by connecting a HELLA IBS (Integrated Battery Sensor) to each battery.

![alt text](https://raw.githubusercontent.com/duronflo/MEMO/master/Bilder/2020-01-01%2017_19_12-Window.png)

A simple arduino project (based on MEGA2650 with Macchina M2 car interface board) which reads battery information (via HELLA IBS) from a lin bus and displays it on a small 1.8" tft display.

This project uses inspiration and code snipets from follwing projecs: 
- https://github.com/frankschoeniger/LIN_Interface/#    Interface with Display for IBS using Arduino which bases on: https://www.kastenwagenforum.de/forum/threads/diy-hella-ibs-batteriecomputer.31724/ 
- https://github.com/gandrewstone/LIN
- https://github.com/duronflo/MuMon
- https://github.com/duronflo/LIN



https://github.com/duronflo/MEMO/blob/master/Bilder/2020-01-01%2017_19_12-Window.png
https://raw.githubusercontent.com/duronflo/MEMO/master/Bilder/2020-01-01%2017_19_12-Window.png