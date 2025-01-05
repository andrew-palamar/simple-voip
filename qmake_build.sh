#!/bin/bash

# Aqtinstall path. FixMe!
QMAKE_BIN="/opt/Qt/5.15.8/gcc_64/bin/qmake"

if [ -f ${QMAKE_BIN} ]; then
    ${QMAKE_BIN} &&
        make
else
    # OR use qmake from path
    qmake &&
        make
fi
