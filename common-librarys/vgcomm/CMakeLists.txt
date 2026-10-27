# vgcomm 通信链路库 (原 vgcomm.pro)
#   串口/UDP/TCP(/蓝牙) 链路 + MAVLink 协议解包

set(VGCOMM_SOURCES
    src/LinkCommand.cc
    src/LinkManager.cc
    src/MAVLinkProtocol.cc
    src/SerialPortInfo.cc
    src/SerialLink.cc
    src/TCPLink.cc
    src/UDPLink.cc
    src/LinkInterface.cc
    src/LinkCommand.h
    src/LinkInterface.h
    src/LinkManager.h
    src/MAVLinkProtocol.h
    src/SerialPortInfo.h
    src/SerialLink.h
    src/TCPLink.h
    src/UDPLink.h
    src/vgcomm_global.h
)

if(VG_ENABLE_BLUETOOTH)
    list(APPEND VGCOMM_SOURCES src/BluetoothLink.cc src/BluetoothLink.h)
endif()

add_library(vgcomm STATIC ${VGCOMM_SOURCES})

target_compile_definitions(vgcomm PRIVATE VGCOMM_LIBRARY)
target_include_directories(vgcomm
    PUBLIC
        src
        ${CMAKE_SOURCE_DIR}/mavlink/v2.0/common
        ${CMAKE_SOURCE_DIR}/mavlink/v2.0
    PRIVATE
        .
)
target_link_libraries(vgcomm PUBLIC
    vgbase
    Qt5::Core
    Qt5::Concurrent
    Qt5::SerialPort
    Qt5::Network
)

if(VG_ENABLE_BLUETOOTH)
    target_compile_definitions(vgcomm PUBLIC QGC_ENABLE_BLUETOOTH)
    target_link_libraries(vgcomm PUBLIC Qt5::Bluetooth)
endif()
