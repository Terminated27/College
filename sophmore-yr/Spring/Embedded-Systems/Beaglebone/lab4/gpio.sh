#!/bin/sh
config-pin -q P8_09
config-pin P8_09 gpio
cd /sys/class/gpio/gpio69
echo in > direction
cat direction
echo 'GPIO 2 Configured as Input'
config-pin -q P8_08
config-pin P8_08 gpio
cd /sys/class/gpio/gpio68
echo in > direction
cat direction
echo 'GPIO 1 Configured as Input'
