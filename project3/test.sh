#!/bin/bash

# Test script for first part of Molecular Dynamics Program

# Compile the program
#gcc -o part1 src/code.c -lm

./compile.sh

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed. Please check your code."
    exit 1
fi

# Prepare test cases
echo "Preparing test cases..."
echo "3" > inp.txt
echo "0.0    0.0    0.0    39.948" >> inp.txt
echo "0.0    0.0    0.5    39.948" >> inp.txt
echo "0.1    0.2   -0.5    39.948" >> inp.txt

# Run the program
echo "Running the program..."
#./part1
./main.o

# Check the output
if [ $? -ne 0 ]; then
    echo "Program execution failed. Check for runtime errors."
    exit 1
fi

echo "Test completed successfully. Verify the output manually for correctness."
echo "OUtput file is output.xyz"
