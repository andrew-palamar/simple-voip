#!/bin/bash

QT_PATH="/opt/Qt/5.15.8/gcc_64/"
# Build app in build directory
# add Qt5 prefix
cmake -B build -DCMAKE_PREFIX_PATH="${QT_PATH}"
cmake --build build/
