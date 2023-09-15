# SensorDataCpp
Reading sensor data from SenseHAT

This project can only be build and run on linux(tested on RaspberryPI OS)

Dependencies:
SenseHat
RITMULib
ncurses

run the following command
g++ ungabunga.cpp -lncurses -lmenu -l SenseHat -l RITMULib -o ungabunga
