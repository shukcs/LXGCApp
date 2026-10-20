import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1

import VGGroundControl   1.0

Rectangle {
    id:                     rctAllParams
    clip:                   true
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
                text:               parameters.search
                onEditingFinished:  parameters.search = text
            }
            VGTextButton {
                enabled:    plantManager.connected
                visible:    !parameters.isParamReadonly(modelData) && !paramEdit.visible
                strText:    qsTr("clear")//qsTr("清除")
                onBtnClicked: parameters.search = ""
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
                anchors.horizontalCenter: parent.horizontalCenter
                spacing:    6
                enabled:    plantManager.connected
                Repeater{
                    model: parameters.labels
                    VGTextButton {
                        id: btn
                        width:      flickCnt.width-12
                        strText:    modelData//qsTr("修改")
                        bCheck:     modelData===parameters.button
                        onBtnClicked: parameters.button = modelData
                    }
                }
            }
        }
    }
    Flickable {
        id:                     flickParas
        anchors {top: parent.top; bottom: parent.bottom; right:parent.right; left: colLabel.right; leftMargin: 20; rightMargin: 12}
        clip:                   true
        contentWidth:           width
        contentHeight:          colParas.height
        flickableDirection:     Flickable.VerticalFlick
        Column {
            id:         colParas
            spacing:    6
            visible:    parameters.params
            width:      parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            Repeater{
                model: parameters.params
                DoubleValidator{
                    id: valDouble
                    decimals: 7
                }
                IntValidator{
                    id: valInt
                }
                Row {
                    width:                  colParas.width
                    height:                 25
                    spacing: 12
                    Label {
                        id: idF
                        anchors {verticalCenter: parent.verticalCenter}
                        width: 220
                        text: idText+" ("+valType+")"
                    }
                    VGTextField {
                        anchors {verticalCenter: parent.verticalCenter}
                        width: 150
                        bBorder: true
                        text: "Float"===valType ? object.toFixed(6) : object
                        validator:  "Float"===valType ? valDouble : valInt
                        onEditingFinished: plantManager.setParameter(idText, text)
                    }
                }
            }
        }
    }
}
