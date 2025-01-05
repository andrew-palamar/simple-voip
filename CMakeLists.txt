cmake_minimum_required(VERSION 3.5)

project(MetaVoIP VERSION 1.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Aqtinstall QT5 path. Could be commented if Deb package used
set(CMAKE_PREFIX_PATH "/opt/Qt/5.15.8/gcc_64/")

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Core Gui Widgets Quick Multimedia REQUIRED)

# set(PJSIP_DIR "${CMAKE_SOURCE_DIR}/third-party/pjproject/x86_64-unknown-linux-gnu")

set(SOURCES
    main.cpp
    mainwindow.cpp
    MetaVoIP.cpp
    MyAccount.cpp
    MyCall.cpp
    buttons.cpp
    sip.cpp
)

set(HEADERS
    mainwindow.h
    MetaVoIP.h
    MyAccount.h
    MyCall.h
)

set(FORMS
    mainwindow.ui
)

set(RESOURCES
    images.qrc
    sounds.qrc
)

# set(PJPROJECT_INCLUDE_DIRS "${PJSIP_DIR}/include")
# set(PJPROJECT_LIBRARY_DIRS "${PJSIP_DIR}/lib")
# include_directories(${PJPROJECT_INCLUDE_DIRS})
# link_directories(${PJPROJECT_LIBRARY_DIRS})


set(LIBRARY_FILES 
    pj
    pjlib-util
    pjsua
    pjsua2
    pjsip-ua
    pjsip-simple
    pjmedia-codec
    pjmedia
    pjmedia-audiodev
    pjnath
    g7221codec
    gsmcodec
    ilbccodec
    speex
    resample
    srtp
)


add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${FORMS} ${RESOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Gui Qt5::Widgets Qt5::Quick Qt5::Multimedia ${LIBRARY_FILES})


qt5_add_resources(RES_SOURCES "${CMAKE_SOURCE_DIR}/resources.qrc")

if(UNIX AND NOT APPLE)
    add_compile_definitions(PJ_NATIVE_STRING_IS_UNICODE=1)
    add_compile_definitions(PJ_IS_LITTLE_ENDIAN=1)
    add_compile_definitions(PJ_IS_BIG_ENDIAN=0)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdeprecated")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wdeprecated")
endif()
