# vgbase 基础工具库 (原 vgbase.pro)
add_library(vgbase STATIC
    src/base.cc
    src/base.h
    src/vgbase_global.h
)

target_compile_definitions(vgbase PRIVATE VGBASE_LIBRARY)
target_include_directories(vgbase PUBLIC src)
target_link_libraries(vgbase PUBLIC Qt5::Core)
