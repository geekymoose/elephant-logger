#!/bin/bash

set -x
set -v
set -e

mkdir build || true
cd build

cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
      -Delephant_examples=ON \
      ..

make
make runExample1
make runExample2
