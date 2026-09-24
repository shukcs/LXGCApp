#include "VGWayPointPlan.h"
#include <QDateTime>
#include "MapItemFactory.h"
#include "VGCoordinate.h"
#include "VGApplication.h"
#include "VGMapManager.h"
#include "VGVehicleMission.h"
#include "VGGlobalFun.h"
#include "VGMainPage.h"
#include "QmlObjectListModel.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//VGWayPointPlan
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VGWayPointPlan::VGWayPointPlan(QObject *p, const QString &n) : SingleTriggerItem<MapAbstractItem>(p)
, m_name(n), m_time(0), m_route(new VGVehicleMission(this))
{
    connect(m_route->GetWayPoints(), &QmlObjectListModel::countChanged, this, &VGWayPointPlan::wpCountChanged);
}

// VGWayPointPlan::VGWayPointPlan(const VGWayPointPlan &oth) : SingleTriggerItem<MapAbstractItem>(oth)
// , m_name(oth.m_name), m_commet(oth.m_commet), m_time(oth.m_time), m_route(new VGVehicleMission(this))
// {
// 
// }

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


void VGWayPointPlan::EndEdit()
{
    Show(true);
    SetSelected(true);
    m_time = QDateTime::currentMSecsSinceEpoch();
    emit wayPointFinished();
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

VGVehicleMission *VGWayPointPlan::getRoute()const
{
    return m_route;
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

