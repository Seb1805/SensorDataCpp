# SensorDataCpp
Reading sensor data from SenseHAT

This project can only be build and run on linux(tested on RaspberryPI OS)

Dependencies:


SenseHat (https://github.com/PhilippeSimier/SenseHat/tree/master)


RITMULib(https://github.com/smukkejohan/RTIMULib)


ncurses(https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/intro.html)


after installing the required dependencies the project can be compiled with below command


run the following command(s):

cd to the folder where ungabunga is located


run this command in the folder: g++ ungabunga.cpp -lncurses -lmenu -l SenseHat -l RITMULib -o ungabunga


run the following command: ./ungabunga
