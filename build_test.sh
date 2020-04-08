#!/bin/sh

if [ -d build ]; then
    rm -rf build
fi
mkdir build && cd build && cmake -DBuildTests=ON .. && make && CTEST_OUTPUT_ON_FAILURE=1 make test
