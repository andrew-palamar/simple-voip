#!/bin/bash

# Build and install pjproject on Linux. Works on Debian for sure.
sudo apt install git sudo \
&& git clone https://github.com/pjsip/pjproject.git third-party/pjproject_v2.15.1 -b 2.15.1 \
&& cd /third-party/pjproject_v2.15.1 \
&& ./configure --prefix=/usr --enable-shared \
&& make dep \
&& make clean \
&& make \
&& sudo make install
