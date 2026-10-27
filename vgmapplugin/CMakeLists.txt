# vgmapplugin 地图插件静态库 (原 vgmapplugin.pro)
#   Qt Location 服务插件实现, 主程序通过 Q_IMPORT_PLUGIN(VGGeoServiceProviderFactory) 静态注册

add_library(vgmapplugin STATIC
    QGCMapEngine.cpp
    QGCMapTileSet.cpp
    QGCMapUrlEngine.cpp
    QGCTileCacheWorker.cpp
    QGeoCodeReplyQGC.cpp
    QGeoCodingManagerEngineQGC.cpp
    QGeoMapReplyQGC.cpp
    QGeoServiceProviderPluginQGC.cpp
    QGeoTileFetcherQGC.cpp
    QGeoTiledMappingManagerEngineQGC.cpp
    VGMapGlobalFunction.cpp
    QGCMapEngine.h
    QGCMapEngineData.h
    QGCMapTileSet.h
    QGCMapUrlEngine.h
    QGCTileCacheWorker.h
    QGeoCodeReplyQGC.h
    QGeoCodingManagerEngineQGC.h
    QGeoMapReplyQGC.h
    QGeoServiceProviderPluginQGC.h
    QGeoTileFetcherQGC.h
    QGeoTiledMappingManagerEngineQGC.h
    VGMapGlobalFunction.h
    vg_maps_plugin.json
)

target_include_directories(vgmapplugin PUBLIC .)
target_link_libraries(vgmapplugin
    PUBLIC
        vgbase
        Qt5::Widgets
        Qt5::Network
        Qt5::Positioning
        Qt5::Location
        Qt5::Sql
    PRIVATE
        Qt5::LocationPrivate      # 原工程 QT += location-private
        Qt5::PositioningPrivate   # 原工程 QT += positioning-private
)
