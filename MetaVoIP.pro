###
#BASIC
###
QT       += core gui widgets quick multimedia

TARGET = MetaVoIP
TEMPLATE = app

###
#CONFIG
###
linux || win32 {
CONFIG += c++11
}

android {
CONFIG += mobility
}

###
#DEFINES
###
linux || win32 {
DEFINES += PJ_NATIVE_STRING_IS_UNICODE=1 \
           PJ_IS_LITTLE_ENDIAN=1 \
           PJ_IS_BIG_ENDIAN=0 \

DEFINES -= UNICODE
}

win32 {
DEFINES     +=  PJ_WIN32=1
}

android{
DEFINES += PJ_IS_LITTLE_ENDIAN=1 \
           PJ_IS_BIG_ENDIAN=0
}

###
#SOURCE FILES
###
SOURCES += main.cpp\
        mainwindow.cpp \
    MetaVoIP.cpp \
    MyAccount.cpp \
    MyCall.cpp

HEADERS  += mainwindow.h \
    MetaVoIP.h \
    MyAccount.h \
    MyCall.h

FORMS    += mainwindow.ui

###
#INCLUDES
###
#INCLUDEPATH += $$PWD/pjproject-2.4/pjsip/include \
#               $$PWD/pjproject-2.4/pjlib/include \
#               $$PWD/pjproject-2.4/pjlib-util/include \
#               $$PWD/pjproject-2.4/pjmedia/include \
#               $$PWD/pjproject-2.4/pjnath/include

###
#OTHER FILES
###
win32 {
    RC_FILE = icon.rc
 }

android {
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

    DISTFILES += \
        android/AndroidManifest.xml \
        android/res/values/libs.xml \
        android/build.gradle
}

winrt {
    WINRT_MANIFEST.capabilities += internetClientServer

    FONTS = \
           $$[QT_HOST_PREFIX/src]/lib/fonts/DejaVuSans.ttf \
           $$[QT_HOST_PREFIX/src]/lib/fonts/DejaVuSans-Bold.ttf \
           $$[QT_HOST_PREFIX/src]/lib/fonts/DejaVuSans-BoldOblique.ttf \
            $$[QT_HOST_PREFIX/src]/lib/fonts/DejaVuSansMono.ttf \
            $$[QT_HOST_PREFIX/src]/lib/fonts/DejaVuSansMono-Bold.ttf \
            $$[QT_HOST_PREFIX/src]/lib/fonts/DejaVuSansMono-BoldOblique.ttf \
            $$[QT_HOST_PREFIX/src]/lib/fonts/DejaVuSansMono-Oblique.ttf \
            $$[QT_HOST_PREFIX/src]/lib/fonts/DejaVuSans-Oblique.ttf \
            $$[QT_HOST_PREFIX/src]/lib/fonts/DejaVuSerif.ttf \
            $$[QT_HOST_PREFIX/src]/lib/fonts/DejaVuSerif-Bold.ttf \
            $$[QT_HOST_PREFIX/src]/lib/fonts/DejaVuSerif-BoldOblique.ttf \
            $$[QT_HOST_PREFIX/src]/lib/fonts/DejaVuSerif-Oblique.ttf
}

##########
#LIBS
##########
linux {
# LIBS += -L$$PJSIP_DIR/lib
# LIBS += -lpj -lpjlib-util -lpjsua -lpjsua2 -lpjsip-ua -lpjsip-simple -lpjmedia-codec -lpjmedia -lpjmedia-audiodev -lpjnath -lg7221codec -lgsmcodec -lilbccodec -lspeex -lresample -lsrtp
LIBS += -lpj -lpjlib-util -lpjsua -lpjsua2 -lpjsip-ua -lpjsip-simple -lpjmedia-codec -lpjmedia -lpjmedia-audiodev -lpjnath -lresample -lg7221codec
}

# FixMe!
win32 {
LIBS += -L$$PWD/pjproject-2.4/lib \
        -llibpjproject-i386-Win32-vc8-Release-Dynamic \
        -lpjlib-util-i386-Win32-vc8-Release-Dynamic \
        -lpjsua2-lib-i386-Win32-vc8-Release-Dynamic \
        -lpjsua-lib-i386-Win32-vc8-Release-Dynamic \
        -lpjsip-ua-i386-Win32-vc8-Release-Dynamic \
        -lpjsip-simple-i386-Win32-vc8-Release-Dynamic \
        -lpjsip-core-i386-Win32-vc8-Release-Dynamic \
        -lpjmedia-codec-i386-Win32-vc8-Release-Dynamic \
        -lpjmedia-i386-Win32-vc8-Release-Dynamic \
        -lpjmedia-codec-i386-Win32-vc8-Release-Dynamic \
        -lpjmedia-audiodev-i386-Win32-vc8-Release-Dynamic \
        -lpjnath-i386-Win32-vc8-Release-Dynamic \
        -lpjlib-i386-Win32-vc8-Release-Dynamic \
        -llibbaseclasses-i386-Win32-vc8-Release-Dynamic \
        -llibg7221codec-i386-Win32-vc8-Release-Dynamic \
        -llibportaudio-i386-Win32-vc8-Release-Dynamic \
        -llibgsmcodec-i386-Win32-vc8-Release-Dynamic \
        -llibilbccodec-i386-Win32-vc8-Release-Dynamic \
        -llibspeex-i386-Win32-vc8-Release-Dynamic \
        -llibresample-i386-Win32-vc8-Release-Dynamic \
        -llibmilenage-i386-Win32-vc8-Release-Dynamic \
        -llibsrtp-i386-Win32-vc8-Release-Dynamic \
        -lwinmm \
        -lole32 \
        -lws2_32 \
        -lwsock32 \
        -lgdi32
}

# FixMe!
android {
LIBS += -L$$PWD/pjproject-2.4/lib \
    #-lpjmedia-audiodev-arm-unknown-linux-androideabi \
    #-lpjmedia-videodev-arm-unknown-linux-androideabi \
    #-lpjsip-arm-unknown-linux-androideabi \
    -lpjsua2-arm-unknown-linux-androideabi \
    -lpjsua-arm-unknown-linux-androideabi \
    -lpjsip-simple-arm-unknown-linux-androideabi \
    -lpjsdp-arm-unknown-linux-androideabi \
    -lpjmedia-arm-unknown-linux-androideabi \
    -lpjsip-arm-unknown-linux-androideabi \
    -lpjmedia-audiodev-arm-unknown-linux-androideabi \
    -lpjsip-ua-arm-unknown-linux-androideabi \
    -lpjnath-arm-unknown-linux-androideabi \
    -lpjmedia-codec-arm-unknown-linux-androideabi \
    -lpj-arm-unknown-linux-androideabi \
    -lpjmedia-arm-unknown-linux-androideabi \
    -lilbccodec-arm-unknown-linux-androideabi \
    -lgsmcodec-arm-unknown-linux-androideabi \
    -lspeex-arm-unknown-linux-androideabi \
    -lresample-arm-unknown-linux-androideabi \
    -lsrtp-arm-unknown-linux-androideabi \
    -lpj-arm-unknown-linux-androideabi \
    -lpjlib-util-arm-unknown-linux-androideabi
    #-lg7221codec-arm-unknown-linux-androideabi \
}

RESOURCES += \
    images.qrc \
    sounds.qrc

# Add the -Wdeprecated warning
QMAKE_CXXFLAGS += -Wdeprecated
QMAKE_CFLAGS += -Wdeprecated

