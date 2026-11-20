import QtQuick 2.0
import QtQuick.Controls 2.0

import VGGroundControl   1.0

Item {
    id:             root
    implicitWidth:  (img.width>rct.width ? img.width : rct.width)
    implicitHeight: img.height + rct.height + 1

    property alias iconName:    img.iconName
    property alias strText:     name.text
    property alias icSz:        img.width
    property alias icRot:       img.rotation

    VGImage {
        id:         img
        anchors {top: parent.top; horizontalCenter: parent.horizontalCenter}
        width:      24
        height:     width
        bMosEnable: false
    }
    Rectangle {
        id: rct
        anchors {bottom: parent.bottom; horizontalCenter: parent.horizontalCenter}
        height: rowCmb.height
        width:  rowCmb.width
        color:  "transparent"
        enabled: plantManager.currentPlant
        Row {
            id: rowCmb
            anchors.centerIn: rct
            spacing: 4
            Text {
                id: name
                font:                   vgMainPage.font()
                height:                 vgMainPage.fontHeight(font)
                horizontalAlignment:    Text.AlignHCenter
                verticalAlignment:      Text.AlignVCenter
            }
            VGImage {
                anchors.verticalCenter: name.verticalCenter
                rotation:   tmRotate.indRotate
                width:      height
                height:     12
                iconName:   "arrow_down"
                bImgNormal: enabled
                bMosEnable: false
            }
            Timer{
                id: tmRotate
                property int indRotate: 0
                interval:           5
                repeat:             true
                onTriggered: {
                    indRotate += popup.visible ? 9 : -9
                    if(indRotate>=90) {
                        indRotate = 90
                        stop()
                    }
                    else if(indRotate<=0) {
                        indRotate = 0
                        stop()
                    }
                }
            }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: popup.open()
        }
    }
    Popup {
        id: popup
        x:  0
        y:  root.height+1
        modal: true
        focus: true
        clip:  true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        contentItem: Rectangle {
            id:                     content
            clip:                   true
            width:                  col.width+10
            height:                 col.height+10
            color:                  "transparent"
            anchors{topMargin: 1; leftMargin: 6; rightMargin: 6; bottomMargin: 8}
            Column {
                id: col
                spacing: 5
                anchors.centerIn: parent
                Repeater {
                    id: rptBtn
                    model:  plantManager.flyModes()
                    delegate: VGTextButton{
                        visible:    btnVisible
                        width:      implicitWidth<col.width ? col.width : implicitWidth
                        strText:    flyName
                        bCheck:     flyName===name.text
                        onBtnClicked:  {
                            plantManager.currentPlant.setFlyMode(flyType)
                            popup.close()
                        }
                    }
                }
            }
        }
        background: Rectangle {
            color: "transparent"
            anchors.fill: parent
            BorderImage {
                anchors.fill:parent
                border { left: 5; top: 0; right: 5; bottom: 7 }
                horizontalTileMode: BorderImage.Stretch
                verticalTileMode:   BorderImage.Stretch
                smooth: true
                source: "qrc:/images/shadow.png"
            }
            Rectangle{
                anchors{fill:parent; leftMargin: 5; rightMargin: 5; bottomMargin: 7}
                color: "#F0FFFFFF"
            }
        }
        onVisibleChanged: tmRotate.start()
    }
}
