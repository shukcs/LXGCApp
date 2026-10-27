#==========================================================================
# LxGCApp 顶层 CMake 构建脚本
#   替代原 LxGCApp.pro (qmake subdirs 工程)
#   子工程顺序(依赖序): common-librarys -> protobuf -> vgmapplugin -> plant-protection-viewer
#==========================================================================
cmake_minimum_required(VERSION 3.16)

project(LxGCApp VERSION 1.0 LANGUAGES CXX)

#----------------------------------------------------------------------
# 选项
#----------------------------------------------------------------------
option(VG_ENABLE_BLUETOOTH "Enable bluetooth link (QGC_ENABLE_BLUETOOTH)" ON)

#----------------------------------------------------------------------
# 全局编译设置 (对应 common-librarys/libs.pri)
#----------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 11)          # CONFIG += c++11
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# 平台宏 (对应 libs.pri 的平台判定)
add_compile_definitions(__STDC_LIMIT_MACROS _TTY_NOWARN_)
if(ANDROID)
    add_compile_definitions(__android__ __mobile__)
elseif(IOS)
    add_compile_definitions(__ios__ __mobile__)
elseif(APPLE)
    add_compile_definitions(__macos__)
endif()

# Debug 构建宏 (libs.pri: DebugBuild -> UNITTEST_BUILD)
add_compile_definitions($<$<CONFIG:Debug>:UNITTEST_BUILD>)

# 编译警告设置
if(MSVC)
    add_compile_options(/W3 /wd4996 /wd4005 /wd4290 /Zc:strictStrings-)
    # Release: 保留调试信息便于收集崩溃转储
    add_compile_options($<$<CONFIG:Release>:/Zi>)
    add_link_options($<$<CONFIG:Release>:/DEBUG>)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall)
endif()

#----------------------------------------------------------------------
# 输出目录: <build>/output/debug|release (与原 qmake 输出结构一致)
#----------------------------------------------------------------------
set(_vg_out ${CMAKE_BINARY_DIR}/output/$<IF:$<CONFIG:Debug>,debug,release>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${_vg_out})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${_vg_out})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${_vg_out})

#----------------------------------------------------------------------
# Qt5 依赖 (汇总所有子工程用到的模块)
#----------------------------------------------------------------------
find_package(Qt5 5.5 REQUIRED COMPONENTS
    Core Gui Widgets Qml Quick Network Positioning Location Sql
    TextToSpeech SerialPort Xml Svg Concurrent
)
if(VG_ENABLE_BLUETOOTH)
    find_package(Qt5 REQUIRED COMPONENTS Bluetooth)
endif()
if(ANDROID)
    find_package(Qt5 REQUIRED COMPONENTS AndroidExtras)
endif()
if(WIN32)
    find_package(Qt5 QUIET COMPONENTS AxContainer)   # 可选，源码未实际使用
endif()

#----------------------------------------------------------------------
# 子工程 (按依赖顺序)
#----------------------------------------------------------------------
add_subdirectory(common-librarys)
add_subdirectory(protobuf)
add_subdirectory(vgmapplugin)
add_subdirectory(plant-protection-viewer)
