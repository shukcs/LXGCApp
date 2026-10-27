# VGPlantViewerMain 主程序 (原 VGPlantViewerMain.pro + VGPlantViewerUI.pri)

#----------------------------------------------------------------------
# 源文件: 应用框架 + base 业务基础
#----------------------------------------------------------------------
set(VG_SOURCES
    main.cpp
    VGApplication.cpp
    VGDbManager.cpp
    VGNetManager.cpp
    VGTcpClient.cpp
    VGToolBox.cpp
    srcload/VGIconEngine.cpp
    srcload/VGImageProvider.cpp
    ../base/logHelper.cpp
    ../base/VGGlobalFun.cpp
    ../base/VGMavLinkCode.cpp
    ../base/ParameterLimit.cpp
    ../base/ParametersMgr.cpp
)

set(VG_HEADERS
    VGApplication.h
    VGDbManager.h
    VGNetManager.h
    VGTcpClient.h
    VGToolBox.h
    srcload/VGIconEngine.h
    srcload/VGImageProvider.h
    ../base/VGMavLinkCode.h
    ../base/logHelper.h
    ../base/QLog.h
    ../base/VGGlobalFun.h
    ../base/ParameterLimit.h
    ../base/ParametersMgr.h
)

#----------------------------------------------------------------------
# 源文件: VGPlantViewerUI 业务管理器 (原 VGPlantViewerUI.pri)
#----------------------------------------------------------------------
set(_ui VGPlantViewerUI)
list(APPEND VG_SOURCES
    ${_ui}/QmlObjectListModel.cc
    ${_ui}/VGLogDataObject.cpp
    ${_ui}/VGMainPage.cpp
    ${_ui}/VGMapManager.cpp
    ${_ui}/VGUIInstance.cpp
    ${_ui}/VGPlanningWorker.cpp
    ${_ui}/MapAbstractItem.cpp
    ${_ui}/MapItemFactory.cpp
    ${_ui}/land/VGLandManager.cpp
    ${_ui}/land/VGCoordinate.cpp
    ${_ui}/land/VGPolylineMapItem.cpp
    ${_ui}/land/VGLandPolyline.cpp
    ${_ui}/land/VGLandPolygon.cpp
    ${_ui}/land/VGMissionPlan.cpp
    ${_ui}/land/VGLandBoundary.cpp
    ${_ui}/land/VGLandInformation.cpp
    ${_ui}/land/VGSelectEdge.cpp
    ${_ui}/land/VGWayPointPlan.cpp
    ${_ui}/land/VGEdgeTip.cpp
    ${_ui}/plant/VGPlantInformation.cpp
    ${_ui}/plant/VGPlantManager.cpp
    ${_ui}/plant/VGVehicleMission.cpp
    ${_ui}/plant/VGMissionHistory.cpp
    ${_ui}/plant/VGMissionRecord.cpp
    ${_ui}/plant/VGSupportPolyline.cpp
    ${_ui}/plant/VGPlantEvents.cpp
    ${_ui}/plant/VGController.cpp
    ${_ui}/plant/VGVehicle.cpp
    ${_ui}/plant/VGVehicleLogManager.cpp
    ${_ui}/plant/VGVehicleManager.cpp
    ${_ui}/plant/MissionItem.cc
    ${_ui}/plant/MissionManager.cc
    ${_ui}/plant/ParamtersModel.cc
    ${_ui}/plant/VGBlock.cpp
    ${_ui}/qx/VGQXManager.cpp
    ${_ui}/survey/VGGetGpsLocation.cpp
    ${_ui}/survey/VGBDLocation.cpp
    ${_ui}/survey/VGBluetoothManager.cpp
    ${_ui}/survey/VGSurveyMonitor.cpp
    ${_ui}/audio/AudioWorker.cpp
    ${_ui}/friends/VGFriendsManager.cpp
    ${_ui}/friends/VGFriend.cpp
)

list(APPEND VG_HEADERS
    ${_ui}/QmlObjectListModel.h
    ${_ui}/VGLogDataObject.h
    ${_ui}/VGMainPage.h
    ${_ui}/VGMapManager.h
    ${_ui}/VGUIInstance.h
    ${_ui}/VGPlanningWorker.h
    ${_ui}/MapAbstractItem.h
    ${_ui}/MapItemFactory.h
    ${_ui}/land/VGLandManager.h
    ${_ui}/land/VGCoordinate.h
    ${_ui}/land/VGPolylineMapItem.h
    ${_ui}/land/VGLandPolyline.h
    ${_ui}/land/VGLandPolygon.h
    ${_ui}/land/VGMissionPlan.h
    ${_ui}/land/VGLandBoundary.h
    ${_ui}/land/VGLandInformation.h
    ${_ui}/land/VGSelectEdge.h
    ${_ui}/land/VGWayPointPlan.h
    ${_ui}/land/VGEdgeTip.h
    ${_ui}/plant/VGPlantInformation.h
    ${_ui}/plant/VGPlantManager.h
    ${_ui}/plant/VGVehicleMission.h
    ${_ui}/plant/VGSupportPolyline.h
    ${_ui}/plant/VGPlantEvents.h
    ${_ui}/plant/VGController.h
    ${_ui}/plant/VGMissionHistory.h
    ${_ui}/plant/VGMissionRecord.h
    ${_ui}/plant/MissionItem.h
    ${_ui}/plant/MissionManager.h
    ${_ui}/plant/VGVehicle.h
    ${_ui}/plant/VGVehicleLogManager.h
    ${_ui}/plant/VGVehicleManager.h
    ${_ui}/plant/ParamtersModel.h
    ${_ui}/plant/VGBlock.h
    ${_ui}/qx/VGQXManager.h
    ${_ui}/survey/VGGetGpsLocation.h
    ${_ui}/survey/VGBDLocation.h
    ${_ui}/survey/VGBluetoothManager.h
    ${_ui}/survey/VGSurveyMonitor.h
    ${_ui}/audio/AudioWorker.h
    ${_ui}/friends/VGFriendsManager.h
    ${_ui}/friends/VGFriend.h
)

#----------------------------------------------------------------------
# 可执行目标 (qmake app 模板, Windows 下为窗口程序)
#----------------------------------------------------------------------
if(WIN32)
    add_executable(VGPlantViewerMain WIN32 ${VG_SOURCES} ${VG_HEADERS} VGPlantViewer.qrc)
elseif(APPLE)
    add_executable(VGPlantViewerMain MACOSX_BUNDLE ${VG_SOURCES} ${VG_HEADERS} VGPlantViewer.qrc)
else()
    add_executable(VGPlantViewerMain ${VG_SOURCES} ${VG_HEADERS} VGPlantViewer.qrc)
endif()

#----------------------------------------------------------------------
# 头文件路径 (原 INCLUDEPATH)
#----------------------------------------------------------------------
target_include_directories(VGPlantViewerMain PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/mavlink/v2.0/common
    ${CMAKE_SOURCE_DIR}/mavlink/v2.0
    ${CMAKE_SOURCE_DIR}/common-librarys/vgbase/src
    ${CMAKE_SOURCE_DIR}/common-librarys/vgcomm/src
    ${CMAKE_SOURCE_DIR}/protobuf
    ${CMAKE_CURRENT_SOURCE_DIR}/../share
    ${CMAKE_CURRENT_SOURCE_DIR}/../base
    ${CMAKE_SOURCE_DIR}/vgmapplugin
    ${CMAKE_CURRENT_SOURCE_DIR}/../PX4
    ${CMAKE_CURRENT_SOURCE_DIR}/VGPlantViewerUI
    ${CMAKE_CURRENT_SOURCE_DIR}/VGPlantViewerUI/land
    ${CMAKE_CURRENT_SOURCE_DIR}/VGPlantViewerUI/plant
    ${CMAKE_CURRENT_SOURCE_DIR}/VGPlantViewerUI/survey
    ${CMAKE_CURRENT_SOURCE_DIR}/VGPlantViewerUI/qx
)

#----------------------------------------------------------------------
# 编译宏
#----------------------------------------------------------------------
target_compile_definitions(VGPlantViewerMain PRIVATE QT_DEPRECATED_WARNINGS)
if(VG_ENABLE_BLUETOOTH)
    target_compile_definitions(VGPlantViewerMain PRIVATE QGC_ENABLE_BLUETOOTH)
endif()

#----------------------------------------------------------------------
# 链接库 (原 LIBS += -lvgbase -lvgcomm -lvglog -lshare -lprotobuf -lvgmapplugin)
#----------------------------------------------------------------------
target_link_libraries(VGPlantViewerMain PRIVATE
    vgbase
    vgcomm
    vglog
    share
    protobuf
    vgmapplugin          # 静态地图插件, main.cpp 中 Q_IMPORT_PLUGIN 引用
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Qml
    Qt5::Quick
    Qt5::Network
    Qt5::Positioning
    Qt5::Location
    Qt5::Sql
    Qt5::TextToSpeech
    Qt5::SerialPort
    Qt5::Xml
    Qt5::Svg
    Qt5::LocationPrivate
    Qt5::PositioningPrivate
)

if(VG_ENABLE_BLUETOOTH)
    target_link_libraries(VGPlantViewerMain PRIVATE Qt5::Bluetooth)
endif()
if(ANDROID)
    target_link_libraries(VGPlantViewerMain PRIVATE Qt5::AndroidExtras)
endif()
if(WIN32 AND Qt5AxContainer_FOUND)
    target_link_libraries(VGPlantViewerMain PRIVATE Qt5::AxContainer)
endif()

#----------------------------------------------------------------------
# 部署辅助: 将运行时所需文件复制到可执行文件目录
#   (对应原 .pro 中 Android INSTALLS; 桌面端需与 exe 同目录)
#----------------------------------------------------------------------
add_custom_command(TARGET VGPlantViewerMain POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/UavParamsAndEvents.xml
        $<TARGET_FILE_DIR:VGPlantViewerMain>/UavParamsAndEvents.xml
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/VigaApp.qm
        $<TARGET_FILE_DIR:VGPlantViewerMain>/VigaApp.qm
)
