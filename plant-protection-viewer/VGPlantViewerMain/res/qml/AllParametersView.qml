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
        spacing:        4
        anchors {top:parent.top; bottom: parent.bottom; left: parent.left}
        width:          200
        Row {
            id:         rowSearch
            spacing:        6
            VGTextField {
                id: editSrc
                height:             parent.height
                bBorder:            true
                placeholderText:    qsTr("Search")//qsTr("搜索")
            }
            VGTextButton {
                enabled:    plantManager.connected
                visible:    !parameters.isParamReadonly(modelData) && !paramEdit.visible
                strText:    qsTr("cleatr")//qsTr("清除")
                onBtnClicked: editSrc.text = ""
            }
        }
        Rectangle{
            anchors.bottom: parent.bottom
            color: "#C8C8C8"
            height: 1
            width:  parent.width
        }
        Flickable {
            id:                     flickCnt
            anchors {top: rowSearch.bottom; bottom: parent.bottom}
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
                        width:      flickCnt.width-4
                        enabled:    plantManager.connected
                        strText:    modelData//qsTr("修改")
                        onBtnClicked: strSearch = modelData
                    }
                }
            }
        }
    }
}
