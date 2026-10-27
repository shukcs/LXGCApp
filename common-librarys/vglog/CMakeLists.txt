# vglog 日志库 (原 vglog.pro, QsLog)
add_library(vglog STATIC
    src/QsLog.cpp
    src/QsLogDest.cpp
    src/QsLogDestConsole.cpp
    src/QsLogDestFile.cpp
    include/QsLog.h
    include/QsLogDest.h
    include/QsLogDestConsole.h
    include/QsLogDestFile.h
    include/QsLogDisableForThisFile.h
    include/QsLogLevel.h
    include/vglog_global.h
)

target_compile_definitions(vglog PRIVATE VGLOG_LIBRARY QS_LOG_LINE_NUMBERS)
target_include_directories(vglog PUBLIC include PRIVATE .)
target_link_libraries(vglog PUBLIC Qt5::Core)
