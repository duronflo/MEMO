# Multivan Energy Monitor (MEMO)

A easy energy monitor for use in campers or vans. In this project the control and display unit was integrated in a Volkswagen T4 Multivan instead of the commonly used climatic control at the rear seats.
In campers/vans it is very common to have two different energey sources, one for starting the engine and suppliny necessary nets to the car and one for the camping net. Both are usauyll connected via a releais.
The monitor is able to display to power flow from/to these two power source by connecting a HELLA IBS (Integrated Battery Sensor) to each battery.


A simple arduino project (based on MEGA2650 with Macchina M2 car interface board) which reads battery information (via HELLA IBS) from a lin bus and displays it on a small 1.8" tft display.

This project uses ideas and code snipets from: https://github.com/frankschoeniger/LIN_Interface/# 
