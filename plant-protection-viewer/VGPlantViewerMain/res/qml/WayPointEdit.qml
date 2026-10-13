import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1

import VGGroundControl   1.0

Rectangle{
    clip:           true
    color:          "#F6F6F6"
    property var curItem: null
    property var curMission: null
    onVisibleChanged:   mapManager.centVis = visible
    Flickable{
        id:                 flick
        anchors {top: rowPoints.bottom; topMargin: 12; left: rowPoints.left; bottom: parent.bottom; bottomMargin: 12}
        width:              70
        clip:               true
        flickableDirection: Flickable.VerticalFlick
        contentHeight:      colContent.height
        contentWidth:       70
        Grid {
            id:         colContent
            anchors.horizontalCenter: parent.horizontalCenter
            columns: 2
            spacing:    10
            Repeater {
                model: curMission.waypoints
                Rectangle {
                    width: 30
                    height: width
                    radius:                 width/2
                    border {width:1; color: "#600000"}
                    color: object.selected ? "#008000" : "#FFFFFF"
                    Text{
                        anchors.fill: parent
                        text: object.sequence
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment:Text.AlignVCenter
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: object.selected = true
                        onDoubleClicked: object.releaseSafe()
                    }
                    Connections{
                        target: object
                        onSelectedChanged: {
                            if (object.selected)
                              curItem = object
                        }
                    }
                }
            }
        }
    }
    Row {
        id: rowPoints
        anchors {left: parent.left; leftMargin: 15; top: parent.top; topMargin: 5}
        spacing: 10
        VGComboBox {
            id: cmdWPType
            anchors.verticalCenter: parent.verticalCenter
            model: landManager.missionTypeNames()
            width: 120
            onCurrentTextChanged: landManager.curWPPlan.addType = currentText
        }
        VGToolButton {
            width: 30
            height: 30
            iconName: "add"
            colNormal: transparent
            enabled:  landManager.curWPPlan
            onBtnClicked: {
                var c = mapManager.mapCenter
                var idx = -1
                if (curItem){
                    idx = curItem.sequence
                    if (!cbBehind.checked)
                        idx = idx-1
                }
                curItem = landManager.curWPPlan.addWayPoint(c, idx)
            }
        }
        VGToolButton {
            anchors {left: flick.right; leftMargin: 15; top: flick.top;}
            width: 30
            height: 30
            iconName: "minus"
            colNormal: transparent
            enabled: curItem
            onBtnClicked: {
                if (curItem)
                    curItem.releaseSafe()
                curItem = null
            }
        }
        VGCheckBox {
            id:     cbBehind
            anchors.verticalCenter: parent.verticalCenter
            checked: true
            text:   qsTr("Insert behind current waypoint")
        }
    }
    Column {
        visible: curItem
        anchors {left: flick.right; leftMargin: 15; top: flick.top; right: parent.right; rightMargin: 15}
        spacing: 8
        Row {
            width: parent.width
            spacing: 10
            Text{
                width: parent.width/3
                text: qsTr("Command")
            }
            Text {
                width: parent.width*2/3-10
                text: curItem.cmdName
            }
        }
        Row {
            width: parent.width
            spacing: 15
            Text{
                width: parent.width/3
                text: qsTr("param1")
            }
            SpinBox {
                width: parent.width*2/3-10
                decimals: 7
                maximumValue: 1e7
                minimumValue: -1e7
                value: curItem.param1
                onValueChanged: curItem.param1 = value
            }
        }
        Row {
            width: parent.width
            spacing: 15
            Text{
                width: parent.width/3
                text: qsTr("param2")
            }
            SpinBox {
                width: parent.width*2/3-10
                decimals: 7
                maximumValue: 1e7
                minimumValue: -1e7
                value: curItem.param2
                onValueChanged: curItem.param2 = value
            }
        }
        Row {
            width: parent.width
            spacing: 15
            Text{
                width: parent.width/3
                text: qsTr("param3")
            }
            SpinBox {
                width: parent.width*2/3-10
                decimals: 7
                maximumValue: 1e7
                minimumValue: -1e7
                value: curItem.param3
                onValueChanged: curItem.param3 = value
            }
        }
        Row {
            width: parent.width
            spacing: 15
            Text{
                width: parent.width/3
                text: qsTr("param4")
            }
            SpinBox {
                width: parent.width*2/3-10
                decimals: 7
                maximumValue: 1e7
                minimumValue: -1e7
                value: curItem.param4
                onValueChanged: curItem.param4 = value
            }
        }
        Row {
            width: parent.width
            spacing: 15
            Text{
                width: parent.width/3
                text: qsTr("latitude")
            }
            SpinBox {
                width: parent.width*2/3-10
                decimals: 7
                maximumValue: 90
                minimumValue: -90
                value: curItem.latitude
                onValueChanged: curItem.latitude = value
            }
        }
        Row {
            width: parent.width
            spacing: 15
            Text{
                width: parent.width/3
                text: qsTr("longitude")
            }
            SpinBox {
                width: parent.width*2/3-10
                decimals: 7
                maximumValue: 180
                minimumValue: -180
                value: curItem.longitude
                onValueChanged: curItem.longitude = value
            }
        }
        Row {
            width: parent.width
            spacing: 15
            Text{
                width: parent.width/3
                text: qsTr("altitude")
            }
            SpinBox {
                width: parent.width*2/3-10
                decimals: 7
                maximumValue: 1e7
                value: curItem.rlAlt
                onValueChanged: curItem.rlAlt = value
            }
        }
    }
    Row{
        anchors{ bottom: flick.bottom; right: parent.right; rightMargin: 15}
        visible: !plantManager.oneKeyArm
        spacing: 15
        VGTextButton {
            enabled: curPlant && curPlant.status===VGPlantInformation.Connected
            strText:qsTr("Send route")//发送航线
            onBtnClicked: {
                if (curMission!==null)
                    curMission.sync2Vehicle()
            }
        }
        VGTextButton {
            enabled: curPlant && curPlant.missionValible
            strText:qsTr("Operation start")//启动作业
            onBtnClicked: root.btnMissionClicked()
        }
    }
}
