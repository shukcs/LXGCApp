import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import VGGroundControl   1.0

Rectangle{
    id:       root
    property  color     boardCol:       "#0b81ff"
    property  color     normalCoL:      "transparent"
    property  color     hoverCol:       "lightgray"
    property  alias     strText:        txt.text
    property  bool      bCheck:         false
    signal  btnClicked()

    implicitHeight:         txt.contentHeight*1.5
    implicitWidth:          height + txt.contentWidth
    border                  {color: boardCol; width: 2}
    color:                  (txt.bHover || bCheck) ? hoverCol : normalCoL
    radius:                 4
    Label{
        id:                         txt
        property  bool  bHover:     false
        anchors.centerIn:           parent
        font:                       vgMainPage.font()
        text:                       strText
        color:                      boardCol
    }
    MouseArea{
        anchors.fill:       parent
        hoverEnabled:       true
        onClicked:          root.btnClicked()
        onEntered:          txt.bHover=true
        onExited:           txt.bHover=false
    }
    onEnabledChanged:   border.color = enabled? boardCol : "gray"
}
