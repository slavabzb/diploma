#!/bin/bash
echo "CONFIGURING"
cd Build_Debug
cmake -DCMAKE_BUILD_TYPE=Debug ../
echo "BUILDING"
make
echo "TESTING"
./Diploma
echo "DONE"
