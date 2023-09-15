# SensorDataCpp
Reading sensor data from SenseHAT

This project can only be build and run on linux(tested on RaspberryPI OS)

Dependencies:
SenseHat (https://github.com/PhilippeSimier/SenseHat/tree/master)
RITMULib(https://github.com/smukkejohan/RTIMULib)
ncurses

run the following command
g++ ungabunga.cpp -lncurses -lmenu -l SenseHat -l RITMULib -o ungabunga
