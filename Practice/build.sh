#!/bin/bash
echo "CONFIGURING"

if [ ! -d ../../EmTester-build-debug ]; then
  mkdir ../../EmTester-build-debug
fi
cd ../../EmTester-build-debug

cmake -DCMAKE_BUILD_TYPE=Debug ../Diploma/Practice

echo "BUILDING"
make

if [ "$1" = "-r" ]; then
  echo "TESTING"
  ./EmTester
fi

echo "DONE"
