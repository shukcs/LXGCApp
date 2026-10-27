# LxGCApp Code Wiki

> 植保无人机地面站（Ground Control Station, GCS）—— 基于 Qt/QML 的跨平台应用，集成 MAVLink 飞控通信、DAS Protobuf 云端数据链与离线地图引擎。

---

## 目录

- [1. 项目概述](#1-项目概述)
- [2. 整体架构](#2-整体架构)
- [3. 仓库结构与构建系统](#3-仓库结构与构建系统)
- [4. 模块详解](#4-模块详解)
  - [4.1 protobuf —— DAS 业务协议库](#41-protobuf--das-业务协议库)
  - [4.2 mavlink —— 飞控协议头文件库](#42-mavlink--飞控协议头文件库)
  - [4.3 common-librarys —— 公共基础库](#43-common-librarys--公共基础库)
  - [4.4 vgmapplugin —— 离线地图插件](#44-vgmapplugin--离线地图插件)
  - [4.5 plant-protection-viewer —— 主程序](#45-plant-protection-viewer--主程序)
- [5. 关键类与函数说明](#5-关键类与函数说明)
- [6. 依赖关系](#6-依赖关系)
- [7. 数据流与协议流](#7-数据流与协议流)
- [8. 构建与运行方式](#8-构建与运行方式)

---

## 1. 项目概述

**LxGCApp** 是一款植保（农业喷洒）无人机地面站软件，技术源头为 QGroundControl（QGC）的裁剪与二次开发，面向农业作业场景增加了地块测绘、航线规划、作业队管理、云端协同等业务能力。

| 属性 | 说明 |
|---|---|
| 语言 / 框架 | C++11 / Qt 5（Qt Quick/QML 为主 UI） |
| 构建系统 | qmake（`.pro` subdirs 工程），兼容 MSVC 2010–2015 / GCC / Clang |
| 目标平台 | Windows、Linux、macOS、Android、iOS |
| 飞控协议 | MAVLink v1.0 / v2.0（C 头文件库） |
| 云端协议 | 自定义 DAS 协议（Google Protobuf v2.5.0 序列化，TCP 传输） |
| 地图 | 自研 Qt Location 插件（瓦片缓存于 SQLite），支持 Google/高德/百度/Bing/OSM 等 |

**核心业务**：地块测绘（Survey）→ 边界管理（Land）→ 航线规划（Mission Planning）→ 植保作业监控（Plant Protection）→ 数据同步到云服务器。

---

## 2. 整体架构

```
┌─────────────────────────────────────────────────────────────────────┐
│                    VGPlantViewerMain (主程序 EXE)                    │
│  ┌───────────────────────────────────────────────────────────────┐  │
│  │  QML UI 层 (res/qml/*.qml, 约 84 个页面/组件)                  │  │
│  │  main.qml → HomePage / LogginPage / OperationPage / ...       │  │
│  └──────────────────────────┬────────────────────────────────────┘  │
│                             │ QQmlContext 属性注入                  │
│  ┌──────────────────────────▼────────────────────────────────────┐  │
│  │  C++ 业务层 (VGPlantViewerUI/*)                                │  │
│  │  VGUIInstance · VGMapManager · VGLandManager · VGPlantManager │  │
│  │  VGVehicleManager · VGVehicle · VGSurveyMonitor · ...         │  │
│  └──────┬───────────────┬────────────────┬──────────────────────┘  │
│         │               │                │                         │
│  VGNetManager      VGToolBox        VGDbManager (独立线程)           │
│  (DAS/TCP 云端)    (mavlink 链路)   (SQLite 本地缓存)                │
└─────────┼───────────────┼────────────────┼─────────────────────────┘
          │               │                │
┌─────────▼───────┐ ┌─────▼──────┐  ┌──────▼───────┐
│ protobuf 静态库 │ │ vgcomm     │  │ Qt Sql       │
│ (DAS 协议)      │ │ LinkManager│  └──────────────┘
└─────────────────┘ │ MAVLink    │
                    │ Protocol   │
┌─────────────────┐ └─────┬──────┘
│ vgmapplugin     │       │ Serial / UDP / TCP / Bluetooth
│ (Qt Location    │       ▼
│  插件+瓦片缓存) │   无人机 (MAVLink)          云服务器 (DAS/TCP)
└─────────────────┘
        ▲
│ vgbase / vglog (基础工具 + 日志)
```

**架构要点**：

1. **单例应用入口**：`VGApplication`（继承 `QApplication` + `Application` 抽象）聚合所有管理器。
2. **QML/C++ 桥接**：`VGUIInstance` 创建 `QQmlApplicationEngine`，通过 `rootContext()->setContextProperty` 注入 `vgToolbox`、`linkManager`、`bltManager` 等；各 Manager 以 `Q_PROPERTY` + `Q_INVOKABLE` 暴露给 QML。
3. **双通信栈**：
   - **MAVLink 栈**（直连无人机）：`LinkManager` 管理串口/UDP/TCP/蓝牙链路，`MAVLinkProtocol` 解包，`VGVehicle` 代表一架飞机。
   - **DAS 栈**（云端协同）：`VGNetManager` 经 `VGTcpClient` 连接服务器，用 protobuf 消息做登录、地块/航线/作业同步、远程控机。
4. **多线程**：DB 操作在独立 `QThread`；日志下载、瓦片缓存（`QGCCacheWorker`）也都有独立线程。

---

## 3. 仓库结构与构建系统

### 3.1 顶层结构

```
LXGCApp/
├── LxGCApp.pro               # TEMPLATE=subdirs，构建 4 个子工程
├── README.md
├── protobuf/                 # DAS 协议（protobuf v2.5.0 源码 + das.pb.*）
├── mavlink/                  # MAVLink v1.0、v2.0 生成的 C 头文件
├── common-librarys/          # 公共库：vglog / vgbase / vgcomm
├── vgmapplugin/              # Qt Location 地图服务插件（静态库）
└── plant-protection-viewer/  # 主程序
    ├── base/                 # 业务基础类（MavLink 编解码、参数、日志）
    ├── share/                # 航线规划算法库（RoutePlanning 等）
    ├── PX4/                  # PX4 自定义飞行模式头文件
    └── VGPlantViewerMain/    # 应用入口、核心 Manager、QML 资源
        ├── main.cpp
        ├── VGApplication.*   # 应用单例
        ├── VGNetManager.*    # 云端 DAS 协议管理
        ├── VGDbManager.*     # 本地 SQLite 缓存
        ├── VGToolBox.*       # MAVLink 链路工具箱
        ├── VGTcpClient.*     # TCP 客户端
        ├── srcload/          # 图标引擎 / 图片 Provider
        ├── res/qml/          # 84 个 QML 页面/组件
        ├── res/image/        # 图片资源
        ├── VGPlantViewerUI/  # 业务管理器（land/plant/survey/qx/friends/audio）
        ├── android/          # Android 清单与 Java 桥
        └── UavParamsAndEvents.xml  # 无人机参数限值与事件定义
```

### 3.2 构建组织

**构建系统：CMake**（根目录 [CMakeLists.txt](file:///d:/work/LXGCApp/CMakeLists.txt)，原 qmake `.pro/.pri` 文件仍保留可参考）。

CMake 目标依赖顺序：

```
common-librarys(vglog/vgbase/vgcomm) → protobuf → vgmapplugin → plant-protection-viewer(share → VGPlantViewerMain)
```

- 顶层 [CMakeLists.txt](file:///d:/work/LXGCApp/CMakeLists.txt)：平台宏（`__STDC_LIMIT_MACROS`/`__mobile__`/`__android__` 等，对应原 libs.pri）、C++11、AUTOMOC/AUTORCC、输出目录（`output/debug|release`）、Qt5 模块查找、`VG_ENABLE_BLUETOOTH` 选项。
- 各静态库与主程序产物统一输出到 `<build>/output/{debug,release}`；主程序链接：`vgbase vgcomm vglog share protobuf vgmapplugin`。
- Debug 构建定义 `UNITTEST_BUILD`；Release 保留 `/Zi`+`/DEBUG` 调试符号（便于崩溃转储）。
- 目录与 CMake 文件一一对应：每个子模块目录下均有各自的 `CMakeLists.txt`。

---

## 4. 模块详解

### 4.1 protobuf —— DAS 业务协议库

**路径**：`protobuf/` ｜ **产物**：静态库 `protobuf` ｜ [protobuf.pro](file:///d:/work/LXGCApp/protobuf/protobuf.pro)

内嵌 **Google Protobuf v2.5.0 完整源码**（`google/protobuf/**`），并编译业务协议 `das.pb.cc`（由 `protobuf-v2.5.0/das.proto` 生成）。

- `das.proto` 定义了 **DAS（数据链/农业服务）协议**，命名空间 `das::proto`，覆盖：心跳（`PostHeartBeat`/`AckHeartBeat`）、身份认证、设备同步、任务/程序下发、**无人机状态（`UavStatus`）**、**航线（`OperationRoute`）**、**作业（`OperationPlan`/`OperationDescription`）**、**地块（`ParcelDescription`/`ParcelSurveyInformation`/`Outline`）**、控制指令、好友消息等。
- `das.proto` 中部分 bytes 字段直接标注 *"mavlink协议中的payload"* —— 即 **DAS 通道可承载 MAVLink 数据**（服务器中转控机指令）。
- 使用方：`VGNetManager`（云端收发）、`plant-protection-viewer` 各业务管理器。

### 4.2 mavlink —— 飞控协议头文件库

**路径**：`mavlink/v1.0`、`mavlink/v2.0`

标准 MAVLink 生成的 C 头文件库（含 `common` 等 dialect），主程序 INCLUDE 指向 `mavlink/v2.0/common`。使用方：

- `vgcomm` 的 `MAVLinkProtocol`（解包/心跳/丢包统计）
- `base/VGMavLinkCode.*`（业务侧 mavlink 消息编解码：heartbeat、command、mission、parameter、GPS、spray、账号等）
- `VGVehicle`、`VGVehicleManager`、`MissionManager` 等

### 4.3 common-librarys —— 公共基础库

#### 4.3.1 vglog —— 日志库（QsLog）

**路径**：`common-librarys/vglog` ｜ 静态库，源自 QsLog。

- 核心类 `QsLog::Logger`（单例）：`addDestination()` / `setLoggingLevel()` / `enqueueWrite()`。
- 提供宏 `QLOG_TRACE/DEBUG/INFO/WARN/ERROR/FATAL`（带行号），是全局日志入口；目的地含文件/调试输出（`QsLogDest*`）。
- 主程序 `main.cpp` 依据设置调用 `InitSystemLog()` 将日志写入 `vgPlantLog/` 目录。

#### 4.3.2 vgbase —— 基础工具

**路径**：`common-librarys/vgbase` ｜ 静态库，仅依赖 QtCore。

- `base.h`：`BASE::groundTime*()` 地面站时间工具函数族。
- `Application` 抽象接口类：`VGApplication` 的公共基类，暴露设置/路径等通用能力。

#### 4.3.3 vgcomm —— 通信链路库

**路径**：`common-librarys/vgcomm` ｜ 静态库，依赖 `Qt concurrent/serialport/network(/bluetooth)`。

| 类 | 职责 |
|---|---|
| `LinkInterface` | 链路抽象基类：`isConnected()`、`writeBytes()`、`bytesReceived` 信号、`communicationError` |
| `LinkManager` | 链路总管：串口枚举（`serialPorts`）、`openUdp()/openTcp()`、`autoLinkPX4()`、`DeleteLink()`、`getMavlinkProtocol()`；QML 以 `linkManager` 访问 |
| `SerialLink` | 串口链路（QSerialPort），默认波特率 57600 |
| `UDPLink` / `TCPLink` | UDP（默认本地 14550）/ TCP 链路 |
| `BluetoothLink` | 蓝牙链路（`QGC_ENABLE_BLUETOOTH` 时编译） |
| `MAVLinkProtocol` | MAVLink 解包核心：`receiveBytes()` 逐字节状态机解析、心跳检测（`vehicleHeartbeatInfo`）、丢包统计（`receiveLossChanged`）、系统/组件 ID、多路复用与鉴权设置 |
| `LinkCommand` | 链路命令封装 |
| `VgNetWork` | 网络辅助 |

### 4.4 vgmapplugin —— 离线地图插件

**路径**：`vgmapplugin/` ｜ 静态库 ｜ [vgmapplugin.pro](file:///d:/work/LXGCApp/vgmapplugin/vgmapplugin.pro)
**依赖**：`Qt location-private positioning-private network sql`，源自 QGC 地图引擎。

实现 Qt Location 插件接口，主程序 `main.cpp` 用 `Q_IMPORT_PLUGIN(VGGeoServiceProviderFactory)` 静态注册（插件元数据 `vg_maps_plugin.json`）。

| 类 | 职责 |
|---|---|
| `VGGeoServiceProviderFactory` | 插件入口（`QGeoServiceProviderFactory`），`createMappingManagerEngine()` 返回瓦片引擎 |
| `QGeoTiledMappingManagerEngineQGC` | 瓦片地图管理引擎：设定缩放范围、256×256 瓦片、注册地图类型表、创建 fetcher、配置内存/磁盘缓存 |
| `QGeoTileFetcherQGC` / `QGeoMapReplyQGC` | 瓦片请求与应答：`getTileImage()` → `UrlFactory::getTileURL()` |
| `QGeoCodingManagerEngineQGC` / `QGeoCodeReplyQGC` | 地理编码 |
| `QGCMapEngine`（`getQGCMapEngine()` 单例） | 引擎核心：缓存调度、URL 工厂、User-Agent、缓存路径、网络状态 |
| `UrlFactory`（QGCMapUrlEngine） | 瓦片 URL 构建；`MapType` 枚举覆盖 **Google 地图/卫星、OpenStreetMap、Bing（街道/卫星）、高德 AMap、百度、MapQuest、MapBox** 等；按服务商设置 Referrer |
| `QGCCacheWorker` | 独立线程的 SQLite 瓦片缓存：保存/读取/下载列表/删除/修剪/**离线包导入导出** |
| `VGMapGlobalFunction` | 地图全局辅助函数 |

### 4.5 plant-protection-viewer —— 主程序

#### 4.5.1 子目录职责

| 目录 | 性质 | 职责 |
|---|---|---|
| `base/` | 源码被主程序直接编译 | `VGMavLinkCode`（mavlink 业务编解码）、`ParametersMgr`+`ParameterLimit`（参数限值，读 `UavParamsAndEvents.xml`）、`QLog/logHelper`（日志）、`JQChecksum`（校验）、`VGGlobalFun`、`VGMacro`（全局宏：组织名/设置文件名等） |
| `share/` | 静态库 `share`（[share.pro](file:///d:/work/LXGCApp/plant-protection-viewer/share/share.pro)） | 航线规划算法：`RoutePlanning`、`RouteStruct`、`ShareFunction` |
| `PX4/` | 头文件 | `px4_custom_mode.h` PX4 自定义飞行模式位定义 |
| `VGPlantViewerMain/` | 应用 EXE | 见下 |

#### 4.5.2 启动流程（[main.cpp](file:///d:/work/LXGCApp/plant-protection-viewer/VGPlantViewerMain/main.cpp)）

1. `Q_IMPORT_PLUGIN(VGGeoServiceProviderFactory)` 注册静态地图插件；开启 HiDPI。
2. 桌面端用 `QSharedMemory` 做单实例检查。
3. 构造 `VGApplication`（设置应用名/组织名、加载翻译 `VigaApp.qm`、`_initSettings()` 写默认 INI：串口 57600、UDP 14550、电池告警 30% 等、`_initMember()` 创建各管理器）。
4. 按设置启用系统日志（`InitSystemLog` → `vgPlantLog/`）。
5. `initApp()`：向 QML 注入 `vgToolbox/linkManager/bltManager` → `getQGCMapEngine()->init()` → 创建 `VGDbManager` 并移入独立线程、打开 `VGDBCache/vgdbCache.db` → `m_toolBox->connectLink()` 建立链路 → `_initParamsAndEvents()` 解析 `UavParamsAndEvents.xml`。
6. `initUI()`：`VGUIInstance::createQml()` 加载 **`qrc:/qml/main.qml`**。
7. `app.exec()` 进入事件循环。

#### 4.5.3 C++ 业务层（VGPlantViewerUI/，按域分组）

| 分组 | 类 | 职责 |
|---|---|---|
| 根 | `VGUIInstance` | QML 引擎持有者；`createQml()` 加载 main.qml；聚合全部 UI 域管理器 |
| 根 | `VGMainPage` | 主页面桥接（Qml 提示 `SetQmlTip`、消息框、PC 模式判断） |
| 根 | `VGMapManager` | 地图状态中心：地图类型/中心点/缩放/比例尺/地图项（`MapAbstractItem`）集合与选中；`QmlObjectListModel` 供 QML 绑定 |
| 根 | `MapAbstractItem` / `MapItemFactory` / `QmlObjectListModel` | 地图要素抽象基类（`MapItemType`、`DescribeMap` 描述）、工厂与 QML 列表模型 |
| 根 | `VGLogDataObject` | 飞控日志数据对象 |
| land/ | `VGLandManager` | 地块管理总控；接收 DB 查询结果 `onQueryItem`；`GetBDLocation()` |
| land/ | `VGLandInformation` / `VGLandBoundary` / `VGLandPolygon` / `VGLandPolyline` / `VGCoordinate` / `VGOutline` | 地块信息、边界、多边形、折线、坐标（含高斯/里程计算）、轮廓 |
| land/ | `VGMissionPlan` / `VGWayPointPlan` / `VGSelectEdge` / `VGEdgeTip` / `VGPolylineMapItem` | 航线规划数据、航点计划、选边/缩边等编辑要素 |
| plant/ | `VGPlantManager` | 植保机队 QML 管理：添加/搜索/删除飞机、当前/测绘机、语音播报开关、QX SDK 开关等大量 `Q_PROPERTY` |
| plant/ | `VGPlantInformation` | 单架植保机业务信息（绑定、状态、作业） |
| plant/ | `VGVehicleManager` | mavlink 车辆管理：车辆增删、活动车辆（`activeVehicle`）切换 |
| plant/ | `VGVehicle` | **一架无人机的完整抽象**（详见 §5） |
| plant/ | `MissionManager` / `MissionItem` | mavlink 任务（航点）上传/下载协议状态机、任务项 |
| plant/ | `VGVehicleMission` | 业务侧航线（与 `MissionManager` 同步） |
| plant/ | `VGController` | 作业控制器（响应参数变化） |
| plant/ | `VGPlantEvents` | 无人机事件定义（解析 XML，用于事件播报） |
| plant/ | `VGMissionHistory` / `VGMissionRecord` | 作业历史/记录 |
| plant/ | `VGVehicleLogManager` | 飞控日志列表查询与下载（独立线程） |
| plant/ | `VGBlock` / `VGSupportPolyline` / `ParamtersModel` | 地块分块、辅助线、参数模型 |
| survey/ | `VGSurveyMonitor` | 测绘过程监控（测绘机打点、实时边界） |
| survey/ | `VGBDLocation` / `VGGetGpsLocation` / `VGBluetoothManager` | 北斗/GPS 定位、蓝牙 GPS 设备接入 |
| qx/ | `VGQXManager` | 千寻（QXWZ）高精度定位账号/SDK 管理 |
| friends/ | `VGFriendsManager` / `VGFriend` | 站内好友/消息（经 DAS 服务器） |
| audio/ | `AudioWorker` | 语音播报队列（Qt TextToSpeech） |

---

## 5. 关键类与函数说明

### 5.1 `VGApplication`（[VGApplication.h](file:///d:/work/LXGCApp/plant-protection-viewer/VGPlantViewerMain/VGApplication.h)）

应用单例（`#define qvgApp qobject_cast<VGApplication*>(qApp)`），聚合所有子系统。

- `initApp()` / `initUI()`：两阶段初始化（见 §4.5.2）。
- 访问器：`toolbox()` `linkManager()` `mavLink()` `mapManager()` `dbManager()` `netManager()` `landManager()` `plantManager()` `vehicleManager()` `qxManager()` `parameters()` `plantEvents()` `controller()` `friendsManager()`。
- `GetDefualtPath()`：数据目录（应用目录下 `VGPlantViewerMain/`，失败回退 home/AppData）。
- `speakNotice()` / `SetQmlTip()` / `SetMessageBox()`：语音与 UI 提示。
- `notify()` 重写：截获 Android 返回键/窗口关闭，发 `sigBack()`。

### 5.2 `VGToolBox`（[VGToolBox.h](file:///d:/work/LXGCApp/plant-protection-viewer/VGPlantViewerMain/VGToolBox.h)）

MAVLink 侧"工具箱"（对应 QGC 的 QGCToolbox），QML 上下文名 `vgToolbox`。

- 持有：`LinkManager`、`MAVLinkProtocol`、`VGVehicleManager`、`VGBluetoothManager`、`AudioWorker`、`VGVehicleLogManager`。
- `connectLink()`：按配置建立链路；`SpeakNotice()/countVoiceQue()`：语音队列；`sltRequestLogData()` 等：日志下载中转。

### 5.3 `VGNetManager`（[VGNetManager.h](file:///d:/work/LXGCApp/plant-protection-viewer/VGPlantViewerMain/VGNetManager.h)）

云端 DAS 协议管理器（QML 属性：connectState/host/port/userId/autoLoggin 等），经 `VGTcpClient` 与服务器通信，心跳保活、断线自动重登。

- 会话：`loggin()`/`registerUser()`/`disConnect()`。
- 业务请求：`requestBindUav()`、`requestUavInfo()`、`requestLandinfo()`、`requestOperationPlan()`、`requestPlanning()`。
- 上行：`uploadMission()`（向无人机同步航线，经服务器中转）、`UploadItem()`（地块/航线上传）、`SendControlUav()`（mavlink 消息/任务/参数转发）、`SendNetWork(protobuf::Message)`。
- 下行分发：`_processLoggin/_processSurveyLands/_processOparetionPlan/_processUav2Gc/_processAckControl2Uav/_processPlantState/...` 等 20+ 个 protobuf 消息处理器，结果以信号（`receiveUavProto`、`receiveMissionInfo`、`receiveGSMsg`）送达各 Manager。
- 数据转换：`parseLand()/parseBoundary()/tranceBoundary()`（protobuf ↔ 地块对象）。

### 5.4 `VGDbManager`（[VGDbManager.h](file:///d:/work/LXGCApp/plant-protection-viewer/VGPlantViewerMain/VGDbManager.h)）

本地 SQLite 缓存（运行于独立 QThread，`CreateDb("VGDBCache/vgdbCache.db")`）。

- 对外（跨线程信号槽）：`SaveItemSafe()/DeleteItemSafe()/QueryItems()/UpdateDb()`。
- 表：测绘表（`_createTableSurvey`）、边界表（`_createTableBoundary`）、航线表（`_createTableRoute`）；`updateTables()` 做老库结构升级。
- 序列化：`polygonSeriers()/polylineSeriers()/coordinateSeriers()` 将几何对象写入 BLOB。

### 5.5 `VGVehicle`（[VGVehicle.h](file:///d:/work/LXGCApp/plant-protection-viewer/VGPlantViewerMain/VGPlantViewerUI/plant/VGVehicle.h)）

单架无人机完整抽象，对应 QGC 的 Vehicle。

- 标识/链路：`sysID()`、`vehicleType()`（`MAVTYPESURVEY` 表示测绘机）、`priorityLink()`、`sendMessage()`、`sendRTCM()`。
- 控制：`sendMavCommand()/sendMavCommandInt()`（带重发队列 `m_mavCommandQueue`）、`setArmed()`、`SetFlightMode()`。
- 任务：`syncPlanFlight()`、`loadFromVehicle()`、`missionManager()`。
- 参数：`prcsVehicleParameter()/getParameter()/getParametesList()`。
- 消息处理：`_mavlinkMessageReceived()` 分发 → `_handleHeartbeat/_handleGlobalPositon/_handleSysStatus/_handleBattery/_handleLogEntry/_handleLogData/_handleParameter/_handleCommandAck/...`。
- 断线：`setConnectionLostEnabled()`、心跳超时 `_connectionLostTimeout()`。
- 信号：`postionChanged/batterryStatus/flightModeChanged/updateLogList/receivedLogData/sychMissionFinish/recvSuspend...` 全部送达 QML。

### 5.6 通信与协议支撑

| 类 | 关键函数 | 说明 |
|---|---|---|
| `LinkManager` (vgcomm) | `serialPorts()/openUdp()/openTcp()/autoLinkPX4()` | 链路生命周期管理 |
| `MAVLinkProtocol` (vgcomm) | `receiveBytes(link, bytes)` → `messageReceived` 信号 | 字节流 → `mavlink_message_t` |
| `VGMavLinkCode` (base) | heartbeat/command/mission/parameter/GPS/spray 编解码静态方法 | 业务层 mavlink 封装 |
| `UrlFactory` (vgmapplugin) | `getTileURL(type, x, y, zoom)` | 多源瓦片 URL |
| `QGCMapEngine` (vgmapplugin) | `getQGCMapEngine()->init()` | 瓦片缓存引擎单例 |

---

## 6. 依赖关系

### 6.1 构建依赖（库间）

```
                ┌────────┐
                │ vgbase │（基础工具）
                └───┬────┘
      ┌─────────────┼──────────────────┐
      ▼             ▼                  ▼
┌──────────┐  ┌───────────┐     ┌────────────┐
│ vgcomm   │  │ vgmapplugin│     │  vglog     │
│(依赖mavlink│  │(依赖 vgbase)│     └─────┬──────┘
│ 头文件)   │  └─────┬─────┘           │
└────┬─────┘        │                 │
     │   ┌──────────┴─────────────────┘
     ▼   ▼
┌──────────────────────┐   ┌───────────┐   ┌────────┐
│ VGPlantViewerMain(EXE)│←──│  share(lib)│   │protobuf│
│  链接: vgbase/vgcomm/  │   └───────────┘   │  (lib) │
│  vglog/share/protobuf/ │←─────────────────┘
│  vgmapplugin          │
└──────────────────────┘
```

### 6.2 第三方/系统依赖

- **Qt 5 模块**：core gui widgets qml quick network positioning location(+private) sql texttospeech serialport xml svg bluetooth(可选) androidextras(Android) axcontainer(Windows)。
- **MAVLink**：v1.0/v2.0 生成头文件（仅头文件，不编译）。
- **Protobuf v2.5.0**：源码内嵌编译为静态库（无外部依赖）。
- **SQLite**：经 QtSql（瓦片缓存 + 业务缓存）。
- **Java/Android**：`android/src/QGCActivity.java` 桥接。

---

## 7. 数据流与协议流

### 7.1 无人机直连（MAVLink）

```
无人机 ⇄ 串口/UDP/TCP/蓝牙
   → LinkInterface(SerialLink/UDPLink/...)
   → MAVLinkProtocol::receiveBytes() 解包
   → messageReceived 信号
   → VGVehicle::_mavlinkMessageReceived() 分派处理
   → 属性/信号更新 → QML 界面刷新
控制反向：QML → VGPlantManager/VGVehicle → sendMavCommand/sendMessage → LinkManager → 链路 → 无人机
```

### 7.2 云端协同（DAS over TCP + Protobuf）

```
VGNetManager ⇄ VGTcpClient ⇄ 云服务器
  上行：SendNetWork(protobuf) —— 登录、心跳、地块/航线/作业上传、绑定、好友消息
  下行：sltAckInfo() → _processXxx() 按消息号分派 → 各 Manager 信号
  远程控机：SendControlUav(mavlink_message_t) → 打包进 das.proto 的 mavlink payload 字段 → 服务器转发给无人机
```

### 7.3 地图瓦片

```
QML Map 元素 → Qt Location → VGGeoServiceProviderFactory
  → QGeoTiledMappingManagerEngineQGC → QGeoTileFetcherQGC
  → UrlFactory::getTileURL() → 命中 SQLite 缓存(QGCCacheWorker) 或 网络下载 → 缓存入库
```

### 7.4 本地持久化

```
业务对象(MapAbstractItem: 地块/边界/航线)
  ⇄ VGDbManager(独立线程, SQLite vgdbCache.db)
  查询结果 sigQueryItem → VGLandManager::onQueryItem → QML 模型
```

---

## 8. 构建与运行方式

### 8.1 环境要求

- **Qt 5.x**（建议 5.5+；需安装 location/serialport/texttospeech/bluetooth 等模块，验证环境为 Qt 5.11.3 MSVC2015）
- **CMake ≥ 3.16**
- 编译器：Windows MSVC 2015+；Linux GCC；macOS clang（x86_64）；Android 需对应 Qt for Android 环境

### 8.2 构建步骤（CMake）

```bash
# 配置（指定 Qt5 安装前缀；Windows 默认生成 VS 工程）
cmake -S . -B build -DCMAKE_PREFIX_PATH=D:/Qt/Qt5.11.3/5.11.3/msvc2015

# 构建（Debug；Release 用 --config Release）
cmake --build build --config Debug --parallel
```

- 产物输出：`build/output/debug/`（或 `release/`），含 `VGPlantViewerMain.exe` 与全部静态库。
- 构建后自动将 `UavParamsAndEvents.xml`、`VigaApp.qm` 复制到可执行文件旁。
- 选项：`-DVG_ENABLE_BLUETOOTH=ON/OFF` 控制蓝牙链路支持（默认 ON）。
- 构建顺序由 CMake 依赖图保证：vglog/vgbase/vgcomm → protobuf → vgmapplugin → share → VGPlantViewerMain。
- 原有 qmake 工程文件（`*.pro/*.pri`）仍保留，可与 CMake 互为参照。

### 8.3 运行

1. `VigaApp.qm`（翻译）与 `UavParamsAndEvents.xml`（参数/事件定义）已由 CMake 自动复制到可执行文件同目录。
2. 直接运行主程序；桌面端单实例（重复启动会提示并退出）。
3. 首次运行自动创建数据目录 `<exe>/VGPlantViewerMain/`，含：
   - INI 设置文件（串口 57600、UDP 14550、是否记日志等默认值）
   - `vgPlantLog/` 系统日志
   - `VGDBCache/vgdbCache.db` 地块/航线本地缓存
4. 使用流程：登录云账号（`LogginPage`）→ 连接无人机（串口/UDP/TCP/蓝牙）→ 测绘地块或导入 → 规划航线 → 植保作业监控。

### 8.4 Android 说明

- `android/` 含 `AndroidManifest.xml`、`QGCActivity.java`、USB 设备过滤器 `device_filter.xml`（数传/飞控 USB 直连）。
- 返回键由 `VGApplication::notify()` 截获转发 QML（`sigBack`）。

---

## 附：术语表

| 术语 | 含义 |
|---|---|
| GCS | Ground Control Station，地面控制站 |
| MAVLink | 无人机飞控标准通信协议（本项目用 v2.0 common dialect） |
| DAS | 自定义云端数据链协议（protobuf 定义，见 das.proto） |
| QGC | QGroundControl，本项目地图/链路/车辆层的代码源头 |
| QX / QXWZ | 千寻位置高精度定位服务（VGQXManager） |
| 测绘(Survey) | 用带定位设备采集地块边界的过程 |
| 植保(Plant Protection) | 农药喷洒作业，本软件的核心场景 |
| 瓦片缓存 | 地图瓦片存 SQLite，支持离线地图包导入导出 |
