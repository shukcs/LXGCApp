import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1

import VGGroundControl   1.0

Rectangle{
    clip:           true
    property var    wplan:       null
    property bool   bEditValue:  false
    signal editRouteInfo(var rt)
    signal finishPlan()
    signal exitPlan()

    Rectangle{
        id: rectHeader
        anchors     {left: parent.left; right: parent.right; top: parent.top}
        height:     tabFunc.height+seperator.height
        visible:    !bEditValue
        color:      "transparent"
        VGImage {
            id: backImg
            anchors {left: parent.left; leftMargin: 10; verticalCenter: tabFunc.verticalCenter}
            width:      30
            height:     width
            iconName:   "backb"
            onImgClicked: {emit:exitPlan()}
        }
        VGTabHeader {
            id:                     tabFunc
            txtFont:                vgMainPage.font(true)
            anchors {top: parent.top; left:backImg.right; leftMargin: 5}
            currentIndex: 1
            Component.onCompleted: {
                addTab(qsTr("Information")) //"信息"
                addTab(qsTr("WayPoints"))   //"参数"
            }
            onCurrentChanged: {
                flickable.contentX = idx*flickable.width
            }
        }
        Text {
            id: txtSave
            anchors {right: parent.right; rightMargin: 15; verticalCenter: tabFunc.verticalCenter}
            enabled:   tabFunc.getCurrentIndex()!==1 || (wplan && wplan.valide)
            color:     enabled ? "black":"gray"
            text:      tabFunc.currentIndex===1 ? qsTr("Save") : qsTr("Next")//qsTr("保存") : qsTr("下一步")
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if (tabFunc.currentIndex === 1 && wplan)
                        emit:finishPlan()
                    else
                        tabFunc.setCurrent(1)
                }
            }
        }
        Rectangle{
            id:                     seperator
            anchors.top:            tabFunc.bottom
            anchors.left:           parent.left
            anchors.right:          parent.right
            height:                 1
            color:                  "#D3D3D3"
        }
    }
    Flickable{
        id:                 flickable
        anchors {top: rectHeader.bottom; left: parent.left; bottom: parent.bottom}
        width:              parent.width
        clip:               true
        flickableDirection: Flickable.HorizontalFlick
        contentHeight:      height
        contentWidth:       rowContent.width
        visible:            !bEditValue
        contentX:           tabFunc.currentIndex*parent.width
        Row {
            id:     rowContent
            height: parent.height
            Rectangle {
                height:             parent.height
                width:              flickable.width
                color:              "transparent"
                VGValueItem{
                    id:             valPesticide
                    strKey:         qsTr("Name")//qsTr("名称")
                    strValue:       wplan ? wplan.name : ""
                    enabled:        wplan && wplan.itemType===MapAbstractItem.Type_WayPointPlan
                    anchors {left: parent.left; leftMargin: 5; top: parent.top; topMargin: 10; right: parent.horizontalCenter; rightMargin: 2}
                    onClickedBtn:   {emit:editRouteInfo(wplan)}
                }
                VGValueItem{
                    strKey:         qsTr("Comment")//qsTr("注释")
                    strValue:       wplan ? wplan.comment : ""
                    enabled:        wplan
                    anchors {left: parent.horizontalCenter; leftMargin: 2; top: parent.top; topMargin: 10; right: parent.right; rightMargin: 5}
                    onClickedBtn:           {emit:editRouteInfo(wplan)}
                }
            }
            Rectangle {
                height:             parent.height
                width:              flickable.width
                color:              "transparent"
                enabled:            wplan
            }
        }
        onMovementEnded:    {
            var idx = contentX<width/2? 0 : (contentX<width*3/2?1:2)
            tabFunc.setCurrent(idx)
        }
    }
}
