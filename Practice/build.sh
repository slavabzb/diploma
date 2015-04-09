#!/bin/bash
echo "CONFIGURING"

if [ ! -d "Build_Debug" ]; then
  mkdir Build_Debug
fi

cd Build_Debug

cmake -DCMAKE_BUILD_TYPE=Debug ../

echo "BUILDING"
make

if [ "$1" != "NOTEST" ]; then
  echo "TESTING"
  ./MatrixTester
fi

echo "DONE"
