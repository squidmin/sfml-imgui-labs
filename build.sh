#!/bin/bash

if [ -d "cmake-build-debug" ]; then
    rm -rf cmake-build-debug
    mkdir cmake-build-debug
fi

cd cmake-build-debug

cmake -DCMAKE_CXX_COMPILER=/usr/bin/c++ ..

cmake --build .
