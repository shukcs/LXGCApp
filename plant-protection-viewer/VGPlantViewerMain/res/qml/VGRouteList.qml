import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1

import VGGroundControl   1.0

Rectangle{
    radius:                 6
    border.width:           1
    border.color:   "#EEEEEE"
    clip:           true

    signal selectRoute(var rt)
    signal createClick(var tp)
    signal operationClick()
    signal detailRout(var rt)
    signal listFold();
    Text {
        id: txtInf
        anchors {verticalCenter: btnCreate.verticalCenter; left: parent.left; leftMargin: 15}
        text:                   qsTr("My missions list")//我的任务列表
        font:                   vgMainPage.font()
        color:                  "#0b81ff"
    }
    ExclusiveGroup { id: groupTp }
    Row {
        anchors {verticalCenter: btnCreate.verticalCenter; left: txtInf.right; leftMargin: 10}
        spacing: 6
        VGRadioButton {
            text: qsTr("Survey mission")//qsTr("规划任务")
            ftText: vgMainPage.font()
            exclusiveGroup: groupTp
            checked: true
            onClicked: {
                colBoundary.visible = checked
                colRouteM.visible = !checked
            }
        }
        VGRadioButton {
            text: qsTr("WayPoint mission")//qsTr("航点任务")
            ftText: vgMainPage.font()
            exclusiveGroup: groupTp
            onClicked: {
                colBoundary.visible = !checked
                colRouteM.visible = checked
            }
        }
    }
    VGTextButton {
        id:                     btnCreate
        anchors{right:imgFold.left; rightMargin: 10; top: parent.top; topMargin: 6}
        strText:                qsTr("Create mission")//创建任务
        onBtnClicked:           {emit:createClick(colBoundary.visible ? MapAbstractItem.Type_MissionInfo:MapAbstractItem.Type_WayPointPlan)}
    }
    VGImage{
        id: imgFold
        width:      30
        height:     width
        iconName: "fold"
        anchors {right: parent.right; rightMargin: 10; verticalCenter: btnCreate.verticalCenter}
        onImgClicked:       {emit:listFold()}
   }
    Flickable {
        id:                     routeCol
        clip:                   true
        anchors {top: btnCreate.bottom; topMargin: 2; left: parent.left; right: parent.right; bottom: parent.bottom}
        contentHeight:          colBoundary.height
        contentWidth:           width
        flickableDirection:     Flickable.VerticalFlick
        Column{
            id: colBoundary
            visible:                    true
            spacing:                    4
            Rectangle{
                color:      "transparent"
                width:      routeCol.width
                height:     1
            }
            Repeater{
                model: mapManager.getSpecItems(MapAbstractItem.Type_MissionInfo)
                delegate: Rectangle{
                    width:          routeCol.width
                    height:         itemLand1.height+10
                    color:          object.itemColor
                    visible:        object.visible
                    border          {width: 1; color: object.selected ? "#b7C2FF":"transparent"}
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {emit:selectRoute(object)}
                    }
                    Column{
                        id:         itemLand1
                        clip:       true
                        spacing:    4
                        anchors {left: parent.left; leftMargin: 10; right: itemLand2.left; rightMargin: 5; top: parent.top; topMargin: 5}
                        Text {
                            id: bdAddress
                            text:               object.actId
                            font:               vgMainPage.littleFont()
                            color:              "#0b81ff"
                        }
                        Text {
                            id: txtBlock
                            text:               qsTr("Poison:")+object.pesticide//药剂:
                            font:               vgMainPage.littleFont()
                            color:              "#605C5B"
                        }
                    }
                    Column{
                        id:         itemLand2
                        clip:       true
                        spacing:    4
                        anchors.centerIn:   parent
                        width:      (parent.width)/3
                        Text {
                            text:               qsTr("Land:")+object.landName+"(" + object.area.toFixed(2) + qsTr("Acre)")
                            font:               vgMainPage.littleFont()
                            color:              "#605C5B"
                        }
                        Text {
                            text:               qsTr("Crop:")+object.cropper//作物
                            font:               vgMainPage.littleFont()
                            color:              "#605C5B"
                        }
                    }
                    VGImage{
                        anchors {right: parent.right; rightMargin: 10; verticalCenter: parent.verticalCenter}
                        width:      parent.height-10
                        height:     width
                        iconName:	"detail"
                        onImgClicked: {
                            object.selected = true
                            emit:selectRoute(object)
                            emit:detailRout(object)
                        }
                    }
                }
            }
        }
        Column{
            id: colRouteM
            visible:                    false
            spacing:                    4
            Rectangle{
                color:      "transparent"
                width:      routeCol.width
                height:     1
            }
            Repeater{
                model: mapManager.getSpecItems(MapAbstractItem.Type_WayPointPlan)
                delegate: Rectangle{
                    width:          routeCol.width
                    height:         itemLand1.height+10
                    color:          object.itemColor
                    visible:        object.visible
                    border          {width: 1; color: object.selected ? "#b7C2FF":"transparent"}
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {emit:selectRoute(object)}
                    }
                    VGImage{
                        anchors {right: parent.right; rightMargin: 10; verticalCenter: parent.verticalCenter}
                        width:      parent.height-10
                        height:     width
                        iconName:	"detail"
                        onImgClicked: {
                            object.selected = true
                            emit:selectRoute(object)
                            emit:detailRout(object)
                        }
                    }
                    Column{
                        id:         colWp1
                        clip:       true
                        spacing:    4
                        anchors {left: parent.left; leftMargin: 10}
                        width: parent.width/4
                        Text {
                            text:               object.name
                            font:               vgMainPage.littleFont()
                            color:              "#0b81ff"
                        }
                        Text {
                            text:               qsTr("Waypoint count: ")+object.wpCount//航点数:
                            font:               vgMainPage.littleFont()
                            color:              "#605C5B"
                        }
                    }
                    Column{
                        id:         colWp2
                        clip:       true
                        spacing:    4
                        anchors {left: colWp1.right; leftMargin: 10}
                        width: parent.width/2
                        Text {
                            text:               object.name
                            font:               vgMainPage.littleFont()
                            color:              "#0b81ff"
                        }
                        Text {
                            text:               qsTr("Waypoint count: ")+object.wpCount//航点数:
                            font:               vgMainPage.littleFont()
                            color:              "#605C5B"
                        }
                    }
                }
            }
        }
    }
}

