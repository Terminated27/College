#!/bin/sh
config-pin -q P9_16
config-pin P9_16 pwm
cd /sys/class/pwm/pwmchip4/pwm-4\:1
echo 1000000000 > period
echo 250000000 > duty_cycle
echo 1 > enable
echo 'PWM Configured & Started'
