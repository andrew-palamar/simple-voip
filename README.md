# simple-voip

Simple SIP Softphone using Qt5 QML (Quick) UI and PJSIP library.
Based on MetaVoIP v1.1.0 by Dominik Fehr. Original versions available - check GIT tags.


## Build 

### Install PJSIP library

Run `pjproject_install_from_git.sh` to install pjsip v2.15.1 to /usr/

### CMake variant

1. Run `cmake_build.sh`. Fix Qt path in script to appropriate. The binary should appear in **build/** directory.
2. To install app run `cmake --install build/`. This will copy simple-voip to **/usr/bin/simple-voip**
3. To build basic debian package using cpack run `cd build/; cpack`. This should create simple-voip-x.y.z-Linux.deb in **build/** dir.
4. TO clean remove **build/** directory.

### QMake variant
1. Run `qmake_build.sh`. Fix QMAKE_BIN path in script to appropriate.
2. To clean run `make distclean`

## Note

The W32 and android versions build are in TBD state. Feel free to fix it, or contact me to fix this.
