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
    property var mission: landManager.curWPPlan.mission
    Flickable{
        id:                 flick
        anchors {top: parent.top; topMargin: 5; left: parent.left; leftMargin: 10; bottom: parent.bottom}
        width:              30
        clip:               true
        flickableDirection: Flickable.VerticalFlick
        contentHeight:      colContent.height
        contentWidth:       30
        Column {
            id:         colContent
            anchors.horizontalCenter: parent.horizontalCenter
            spacing:    10
            Repeater {
                model: mission.waypoints
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
        anchors {left: flick.right; leftMargin: 15; top: flick.top;}
        spacing: 10
        VGToolButton {
            width: 30
            height: 30
            iconName: "add"
            colNormal: transparent
            enabled:  landManager.curWPPlan
            onBtnClicked: {
                var c = mapManager.mapCenter
                curItem = mission.addWayPoint(curItem?curItem.sequence-1 : -1, c)
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
    }
}
