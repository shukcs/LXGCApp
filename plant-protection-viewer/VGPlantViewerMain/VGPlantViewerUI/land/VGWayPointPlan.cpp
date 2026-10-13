#include "VGWayPointPlan.h"
#include <QDateTime>
#include <mavlink.h>
#include "MapItemFactory.h"
#include "VGCoordinate.h"
#include "VGApplication.h"
#include "VGMapManager.h"
#include "VGVehicleMission.h"
#include "VGGlobalFun.h"
#include "VGMainPage.h"
#include "QmlObjectListModel.h"
#include "VGLandManager.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//VGWayPointPlangetDiscsItem
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VGWayPointPlan::VGWayPointPlan(QObject *p, const QString &n) : SingleTriggerItem<MapAbstractItem>(p)
, m_name(n), m_time(0), m_route(new VGVehicleMission(this))
{
    connect(m_route->GetWayPoints(), &QmlObjectListModel::countChanged, this, &VGWayPointPlan::wpCountChanged);
    SetAddType(VGLandManager::getDiscsItem().key(MAV_CMD_NAV_WAYPOINT));
    connect(m_route, &QObject::destroyed, this, [=] { m_route = nullptr;  deleteLater(); });
}

VGWayPointPlan::~VGWayPointPlan()
{
    delete m_route;
}

MapAbstractItem::MapItemType VGWayPointPlan::ItemType() const
{
    return Type_WayPointPlan;
}

int VGWayPointPlan::WPCount() const
{
    return m_route ? m_route->CountMissionItems() : 0;
}


void VGWayPointPlan::endEdit()
{
    Show(true);
    SetSelected(true);
    m_time = QDateTime::currentMSecsSinceEpoch();
    emit timeChanged();
    emit wayPointFinished();
    emit newPlanChanged();
}

VGMissionItem *VGWayPointPlan::addWayPoint(const QGeoCoordinate &c, int idx /*= -1*/)
{
    if (auto cmd = m_route ? VGLandManager::getDiscsItem().value(m_addType, 0) : 0)
        return m_route->AddWayPoint(idx, VGGlobalFunc::toGps(c), cmd);

    return nullptr;
}

void VGWayPointPlan::showContent(bool b)
{
    if (m_route)
        m_route->Show(b);
}

QString VGWayPointPlan::GetCreateTime() const
{
    return VGMainPage::GetTimeString(m_time);
}

void VGWayPointPlan::SetSelected(bool b)
{
    MapAbstractItem::SetSelected(b);
    if (!m_route)
        return;

    m_route->Show(b);
}

void VGWayPointPlan::SetMissionItems(const QList<MissionItem *> &items)
{
    if (m_route)
        m_route->SetMissionItems(items);
}

VGVehicleMission * VGWayPointPlan::GetMission() const
{
    return m_route;
}

VGVehicleMission *VGWayPointPlan::getRoute()const
{
    return m_route;
}

QString VGWayPointPlan::GetAddType() const
{
    return m_addType;
}

void VGWayPointPlan::SetAddType(const QString &str)
{
    if (m_addType != str && VGLandManager::getDiscsItem().value(str, 0))
    {
        m_addType = str;
        emit addTypeChanged();
    }
}

bool VGWayPointPlan::IsNewPlan() const
{
    return !qvgApp->landManager()->Contains(this);
}

QString VGWayPointPlan::GetName() const
{
    return m_name;
}

void VGWayPointPlan::SetName(const QString &n)
{
    if (m_name != n)
    {
        m_name = n;
        emit nameChanged(n);
    }
}

QString VGWayPointPlan::GetComment() const
{
    return m_commet;
}

void VGWayPointPlan::SetComment(const QString &c)
{
    if (m_commet != c)
    {
        m_commet = c;
        emit commentChanged(c);
    }
}

bool VGWayPointPlan::operator==(const MapAbstractItem &item) const
{
    if (item.ItemType() == Type_WayPointPlan)
        return *m_route == item;

    return false;
}

DECLARE_ITEM_FACTORY(VGWayPointPlan)

