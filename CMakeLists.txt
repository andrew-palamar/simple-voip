cmake_minimum_required(VERSION 3.5)

project(simple-voip VERSION 0.5.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Aqtinstall QT5 path. Set externally by bash script
# set(CMAKE_PREFIX_PATH "/opt/Qt/5.15.8/gcc_64/")

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Core Quick Multimedia REQUIRED)

# PJSIP LIB
find_package(PkgConfig REQUIRED)
pkg_check_modules(PJSIP libpjproject>=2.15 REQUIRED)
include_directories(${PJSIP_INCLUDE_DIRS})


set(SOURCES
    src/main.cpp
    src/MetaVoIP.cpp
    src/pjsip/MyAccount.cpp
    src/pjsip/MyCall.cpp
    src/pjsip/AudioDeviceManager.cpp
    src/backend.cpp
    src/buttons.cpp
)

set(HEADERS
    src/MetaVoIP.hpp
    src/pjsip/MyAccount.hpp
    src/pjsip/MyCall.hpp
    src/pjsip/AudioDeviceManager.hpp
    src/backend.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} qml.qrc images.qrc sounds.qrc)

target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

set(PJPROJECT_LIBRARY_ORDER
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
    # gsmcodec
    # ilbccodec
    # speex
    resample
    # srtp
)
# No way to use ${PJSIP_LIBRARIES} here. The order is important!
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick Qt5::Multimedia ${PJPROJECT_LIBRARY_ORDER})

if(UNIX AND NOT APPLE)
    add_compile_definitions(PJ_NATIVE_STRING_IS_UNICODE=1)
    add_compile_definitions(PJ_IS_LITTLE_ENDIAN=1)
    add_compile_definitions(PJ_IS_BIG_ENDIAN=0)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdeprecated")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wdeprecated")
endif()

# Installation target. Example: '-DCMAKE_INSTALL_PREFIX=/usr' - installs ${PROJECT_NAME} binary to /usr/bin/
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin)

# Debian package using cpack
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_CONTACT "Andrew Palamarchuk <orhalfmer@gmail.com>")
set(CPACK_GENERATOR DEB)
include(CPack)
