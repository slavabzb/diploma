#!/bin/bash
echo "CONFIGURING"

if [ ! -d "Build_Debug" ]; then
  mkdir Build_Debug
fi

cd Build_Debug
if [ "$1" = "-t" ]; then
  cmake -DCMAKE_BUILD_TYPE=Debug -DTIME_TEST=ON ../
else
  cmake -DCMAKE_BUILD_TYPE=Debug -DTIME_TEST=OFF ../
fi

echo "BUILDING"
make

if [ "$1" = "-r" ] || [ "$2" = "-r" ]; then
  echo "TESTING"
  ./MatrixTester
fi

echo "DONE"
