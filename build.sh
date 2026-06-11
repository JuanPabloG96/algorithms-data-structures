#!/bin/bash

# clean and change directorie
rm -rf build/*
cd build
# run cmake
cmake ..
# compile and generate json
bear -- make
