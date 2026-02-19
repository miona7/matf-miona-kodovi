#!/bin/bash

set -e  

mkdir -p build
cd build

cmake .. -DCMAKE_BUILD_TYPE=Debug 
make
make coverage

if [ -f coverage/index.html ]; then
    echo "--- opening coverage report in Google Chrome ---"
    google-chrome coverage/index.html
else
    echo "Coverage report not found! Check make coverage output."
fi