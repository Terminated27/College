#!/bin/sh
config-pin -q P8_09
config-pin P8_09 gpio
cd /sys/class/gpio/gpio69
echo in > direction
cat direction
echo 'GPIO Configured as Input'
