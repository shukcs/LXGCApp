import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1

import VGGroundControl   1.0

Rectangle {
    id:                             root
    anchors {fill: parent; bottomMargin: Qt.inputMethod.visible?Qt.inputMethod.anchorRectangle.height():0}
    color:                          "#1f000000"

    property string strHeader:     qsTr("Mission infomation")//qsTr("任务信息")
    property var routeInfo:        null

    signal clickedOK(var rt)

    MouseArea{
        anchors.fill:               parent
        onClicked:                  {}
        onWheel:                    {}
    }
    function confirm(){
        vgMainPage.onSigBack()
        if (!routeInfo) {
            var rt = landManager.preparePlanWayPoint()
            if (rt) {
                rt.name = txtName.text
                rt.comment = txtCmt.text
                emit:clickedOK(rt)
            }
        }
         else {
             routeInfo.name = txtName.text
             routeInfo.comment = txtCmt.text
             emit:clickedOK(routeInfo)
         }
    }
    function setWayPointPlan(rt) {
        routeInfo = rt
        if (routeInfo) {
            txtName.text = routeInfo.name
            txtCmt.text = routeInfo.comment
        }
    }
    function checkWholeInfo(){
        var bWhole = true
        if (txtName.text.length<1)
            bWhole = false

        txtConfirm.color = bWhole ? "#0b81ff":"gray"
        txtConfirm.enabled = bWhole
    }
    Rectangle{
        id:                             contentRect
        anchors.horizontalCenter:       parent.horizontalCenter
        anchors.verticalCenter:         parent.verticalCenter
        width:                          parent.width*2/3
        height:                         lyContent.height
        color:                          vgMainPage.backColor
        radius:                         4
        Column{
            id:                        lyContent
            width:                     parent.width
            Rectangle {
                width:  parent.width
                height: txtHeader.contentHeight*2
                color: "transparent"
                Label{
                    id:                         txtHeader
                    anchors {verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 20}
                    text:                       strHeader
                    font:                       vgMainPage.font(true)
                    color: "#0b81ff"
                }
                Rectangle{
                    height: 1
                    width:  parent.width
                    anchors.bottom: parent.bottom
                    color: "#C8C8C8"
                }
            }
            Rectangle {
                width:  parent.width
                height: txtHeader.contentHeight*2
                color: "transparent"
                Label{
                    anchors {verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 20}
                    text:                       qsTr("Mission name")//qsTr("任务名:")
                    font:                       vgMainPage.font()
                    color:                      "gray"
                }
                VGTextField{
                    id:                         txtName
                    anchors {verticalCenter: parent.verticalCenter; right: parent.right; rightMargin: 20}
                    width:                      parent.width*2/3
                    font:                       vgMainPage.font()
                    horizontalAlignment:        TextInput.AlignHCenter
                    onTextChanged:              checkWholeInfo()
                }
                Rectangle{
                    height: 1
                    width:  parent.width
                    anchors.bottom: parent.bottom
                    color: "#C8C8C8"
                }
            }
            Rectangle {
                width:  parent.width
                height: txtHeader.contentHeight*2
                color: "transparent"
                Label{
                    anchors.verticalCenter:     parent.verticalCenter
                    anchors.left:               parent.left
                    anchors.leftMargin:         20
                    text:                       qsTr("Comment:")//qsTr("注释:")
                    font:                       vgMainPage.font()
                    color:                      "gray"
                }
                VGTextField{
                    id:                         txtCmt
                    anchors {verticalCenter: parent.verticalCenter; right: parent.right; rightMargin: 20}
                    width:                      parent.width*2/3
                    font:                       vgMainPage.font()
                    horizontalAlignment:        TextInput.AlignHCenter
                }
                Rectangle{
                    height: 1
                    width:  parent.width
                    anchors.bottom: parent.bottom
                    color: "#C8C8C8"
                }
            }
            Rectangle {
                width:  parent.width
                height: txtHeader.contentHeight*3
                color: "transparent"
                Rectangle{
                    height: 1
                    width:  parent.width
                    anchors.bottom: parent.bottom
                    color: "#C8C8C8"
                }
            }
            Rectangle {
                width:  parent.width
                height: txtCancle.contentHeight*2
                color: "transparent"
                Row {
                    id:                         rowBtn
                    anchors.right:              parent.right
                    anchors.horizontalCenter:   parent.horizontalCenter
                    anchors.verticalCenter:     parent.verticalCenter
                    height:                     parent.height
                    spacing:                    10
                    Label {
                        id: txtCancle
                        text:   qsTr("Cancel")//qsTr("取消")
                        color:  "gray"
                        width:  parent.width/2-1
                        height: parent.height
                        font:   vgMainPage.font(true)
                        horizontalAlignment:    Text.AlignHCenter
                        verticalAlignment:      Text.AlignVCenter
                        MouseArea{
                            anchors.fill:   parent
                            onClicked:      vgMainPage.onSigBack()
                        }
                    }
                    Rectangle{
                        height: parent.height
                        width: 1
                        color: "#C8C8C8"
                    }
                    Label {
                        id: txtConfirm
                        text:       qsTr("OK")//qsTr("确定")
                        color:      enabled ? "#0b81ff":"gray"
                        width:      parent.width/2
                        enabled:    false
                        height:     parent.height
                        font:       vgMainPage.font(true)
                        horizontalAlignment:    Text.AlignHCenter
                        verticalAlignment:      Text.AlignVCenter
                        MouseArea{
                            id: mouseConfirm
                            anchors.fill:   parent
                            enabled:        true
                            onClicked:      confirm()
                        }
                    }
                }
            }
        }
    }
    onRouteInfoChanged:{
        if (!routeInfo)
            return
        cbbCropper.currentIndex = cbbCropper.find(routeInfo.cropper)
        cbbPesticide.currentIndex = cbbPesticide.find(routeInfo.pesticide)
        txtPrise.text = routeInfo.price
    }
    Connections{
        target: vgMainPage
        onSigShowPage: {
            root.visible = root === page
        }
    }
}
