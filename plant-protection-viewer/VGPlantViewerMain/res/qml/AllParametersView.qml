import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1

import VGGroundControl   1.0

Rectangle {
    id:                     rctAllParams
    clip:                   true
    property string strSearch:    ""
    Column {
        id: colLabel
        anchors {top:parent.top; bottom: parent.bottom; left: parent.left}
        width:          200
        spacing:        4
        Row {
            id:         rowSearch
            spacing:        6
            VGTextField {
                id: editSrc
                height:             parent.height
                width:              120
                bBorder:            true
                placeholderText:    qsTr("Search")//qsTr("搜索")
            }
            VGTextButton {
                enabled:    plantManager.connected
                visible:    !parameters.isParamReadonly(modelData) && !paramEdit.visible
                strText:    qsTr("clear")//qsTr("清除")
                onBtnClicked: editSrc.text = ""
            }
        }
        Rectangle{
            anchors {top: rowSearch.bottom; topMargin: 4}
            id: sprr
            color: "#C8C8C8"
            height: 1
            width:  parent.width
        }
        Flickable {
            id:                     flickCnt
            anchors {top: sprr.bottom; topMargin: 4; bottom: parent.bottom}
            clip:                   true
            width:                  parent.width
            contentWidth:           width
            contentHeight:          colBt.height
            flickableDirection:     Flickable.VerticalFlick
            Column {
                id:      colBt
                spacing: 6
                anchors.horizontalCenter: parent.horizontalCenter
                Repeater{
                    model: parameters.labels
                    VGTextButton {
                        id: btn
                        width:      flickCnt.width-12
                        enabled:    plantManager.connected
                        strText:    modelData//qsTr("修改")
                        onBtnClicked: strSearch = modelData
                    }
                }
            }
        }
    }
    Flickable {
        id:                     flickParas
        anchors {top: parent.top; bottom: parent.bottom; right:parent.right; left: colLabel.right; leftMargin: 20}
        clip:                   true
        contentWidth:           width
        contentHeight:          colParas.height
        flickableDirection:     Flickable.VerticalFlick
        property var curPlant:  plantManager.currentPlant
        /*Column {
            id:                 colParas
            spacing: 6
            visible: curPlant
            anchors.horizontalCenter: parent.horizontalCenter
            Repeater{
                model: /*curPlant ? curPlant.getParamtersModel().idS : 0
                Row {
                    visible: true
                    spacing: 10
                    Label: {
                        text: modelData
                    }
                }
            }
        }*/
    }
}
