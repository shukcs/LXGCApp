import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1

import VGGroundControl   1.0

/*
  * 子页面: 地块测绘页面，包括地块测绘所有子页面和子页面的控制；
  *
*/

VGValueShow {
    id:                             root
    anchors.fill:       parent

    property var    flyRoute:       null
    property bool   editInfo:       true
    signal opration(var rt)

    onFlyRouteChanged: {
        if (!flyRoute)
            return

        strHeader = flyRoute.actId
        addValue(qsTr("Land"), flyRoute.landName + "("+flyRoute.area.toFixed(2)+qsTr("acre)"))//地块 \ 亩)
        addValue(qsTr("Crop"), flyRoute.cropper)
        addValue(qsTr("Poison"), flyRoute.pesticide)
        addValue(qsTr("Prize(Y/A)"), flyRoute.price.toFixed(1))//单价(元/亩)
        addValue(qsTr("Sprinkle width"), flyRoute.sprinkleWidth.toFixed(1))//喷幅
        addValue(qsTr("Block safe distance(m)"), flyRoute.blockSafe.toFixed(1))//障碍物安全距离(m)
        addValue(qsTr("Boundary safe distance(m)"), flyRoute.outlineSafe.toFixed(1))//边界安全距离(m)
        addValue(qsTr("Angle(degree)"), flyRoute.angle.toFixed(0))//角度(°)
        addValue(qsTr("Creator"), flyRoute.user)//"创建人"
        addValue(qsTr("Create time"), flyRoute.planTime)//创建时间

        addButton(qsTr("Operate"), "#0b81ff")//
        addButton(qsTr("Delete"), "#E64331")//
    }
    onClickedBtn:{
        if (!flyRoute)
            return
        if (str === qsTr("Operate")) {
            emit: opration(flyRoute)
        }
        else if (str === qsTr("Delete")) {
            flyRoute.selected = false
            flyRoute.releaseSafe()
        }
        vgMainPage.onSigBack()
    }
    Connections{
        target:         vgMainPage
        onSigBack:      if (root===page)vgMainPage.onSigBack()
        onSigShowPage:  root.visible = root === page
    }
}
