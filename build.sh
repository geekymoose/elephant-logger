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
make run_ex_simple_usage
make run_ex_multi_classes
make run_ex_file_output
make run_ex_logger_categories_filters
