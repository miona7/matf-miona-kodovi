#!/bin/bash

set -e  

echo "--- building project with coverage flags ---"

mkdir -p build
cd build

cmake .. -DCMAKE_BUILD_TYPE=Debug 
make

echo "--- running tests ---"
./runTest

echo "--- generating coverage report ---"

lcov --capture --directory CMakeFiles/runTest.dir/stringLib/test --output-file coverage.info

genhtml coverage.info --output-directory coverage_html

google-chrome coverage_html/index.html
