# share 航线规划算法库 (原 share.pro)
#   纯 C++/STL 实现, 不依赖 Qt (原工程 QT -= gui core)

add_library(share STATIC
    cppsrc/ShareFunction.cpp
    cppsrc/RouteStruct.cpp
    cppsrc/RoutePlanning.cpp
    ShareFunction.h
    RouteStruct.h
    RoutePlanning.h
    share_global.h
)

target_compile_definitions(share PRIVATE SHARE_LIBRARY)
target_include_directories(share PUBLIC .)
