#!/bin/bash
NUM_STATIONS=$1

mkdir -p build
cd build
cmake ..
make
./networks $NUM_STATIONS
