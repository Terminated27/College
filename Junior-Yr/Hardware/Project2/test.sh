#!/bin/bash

# Define the executable and base command
EXECUTABLE="./radixsort"
VALGRIND_CMD="valgrind --tool=cachegrind --cache-sim=yes"

# Argument variations for D1: format "size,assoc,blocksize"
D1_VARIANTS=(
    "1024,1,128"
    "1024,2,128"
    "1024,4,128"
    "1024,8,128"
)
# Number of repetitions for each configuration
REPEAT=5

# Loop through each configuration
for D1 in "${D1_VARIANTS[@]}"; do
    echo "Running with D1=$D1"

    # Repeat the run REPEAT times
    for ((i = 1; i <= REPEAT; i++)); do
        echo "  Run #$i"

        # Run the command and filter output
        $VALGRIND_CMD --D1=$D1 $EXECUTABLE 2>&1 | grep -E 'D1\s+misses:'
    done
    echo ""
done
