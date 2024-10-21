#!/bin/bash

# Filename: ex18.sh
#
# Problem: Find the highest number for each line and print it. 
cat ex18.input | awk '{
	max = 0
	for (i = 0; i < NF; i ++)
		if (max < $(i+1))
			max = $(i+1)
	print(max)
	}'
