#include "VGWayPointPlan.h"
#include "MapItemFactory.h"
#include "VGCoordinate.h"
#include "VGApplication.h"
#include "VGMapManager.h"
#include "VGGlobalFun.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//VGWayPointPlan
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VGWayPointPlan::VGWayPointPlan(QObject *p, const QString &n) : SingleTriggerItem<MapAbstractItem>(p)
, m_name(n)
{
}

VGWayPointPlan::VGWayPointPlan(const VGWayPointPlan &oth) : SingleTriggerItem<MapAbstractItem>(oth)
, m_name(oth.m_name), m_commet(oth.m_commet)
{
    for (auto itr : oth.m_wps)
    {
        addWayPoint(itr->GetCoordinate());
    }
}

VGWayPointPlan::~VGWayPointPlan()
{
    qDeleteAll(m_wps);
}

MapAbstractItem::MapItemType VGWayPointPlan::ItemType() const
{
    return Type_WayPointPlan;
}

QVariantList VGWayPointPlan::GetPath() const
{
    return m_path;
}

int VGWayPointPlan::WPCount() const
{
    return m_wps.size();
}

void VGWayPointPlan::AddWayPoint(const QGeoCoordinate &c)
{
    addWayPoint(c);
    emit pathChanged(m_path);
    emit wpCountChanged(WPCount());
}

void VGWayPointPlan::SetWayPoints(const QList<QGeoCoordinate> &cs)
{
    if (cs.isEmpty() && m_path.isEmpty())
        return;
    m_path.clear();
    qDeleteAll(m_wps);
    m_wps.clear();
    for (auto &itr : cs)
    {
        addWayPoint(itr);
    }
    emit pathChanged(m_path);
    emit wpCountChanged(WPCount());
}

void VGWayPointPlan::Show(bool b)
{
    SingleTriggerItem<MapAbstractItem>::Show(b);
    for (auto itr : m_wps)
    {
        itr->Show(b);
    }
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

void VGWayPointPlan::addWayPoint(const QGeoCoordinate &c)
{
    if (auto cr = new VGCoordinate(c, VGCoordinate::WayPoint, this))
    {
        m_wps << cr;
        m_path << QVariant::fromValue(c);
        connect(cr, &VGCoordinate::coordinateChanged, this, [=](const QGeoCoordinate &c) {
            auto idx = m_wps.indexOf(static_cast<VGCoordinate*>(sender()));
            if (idx >= 0 && m_path.size() > idx)
            {
                m_path[idx].fromValue(c);
                emit pathChanged(m_path);
            }
        });
        connect(cr, &QObject::destroyed, this, [=] {
            remove(static_cast<VGCoordinate*>(sender()));
        });
    }
}

void VGWayPointPlan::remove(VGCoordinate *wp)
{
    auto idx = m_wps.indexOf(wp);
    if (idx >= 0)
    {
        m_wps.removeAt(idx);
        m_path.removeAt(idx);
        emit wpCountChanged(WPCount());
        emit pathChanged(m_path);
        for (auto it = m_wps.begin() + idx; it != m_wps.end(); ++it)
        {
            (*it)->indexChanged();
        }
    }
}

int VGWayPointPlan::ItemIndex(const MapAbstractItem *item) const
{
    if (item->GetId() == VGCoordinate::WayPoint)
        return m_wps.indexOf((VGCoordinate*)item);

    return -1;
}

bool VGWayPointPlan::operator==(const MapAbstractItem &item) const
{
    if (item.ItemType() == Type_WayPointPlan)
    {
        auto p = static_cast<const VGWayPointPlan*>(&item);
        if (p->m_wps.size() != m_wps.size())
            return false;
        auto itr2 = p->m_wps.begin();
        for (auto itr = m_wps.begin(); itr != m_wps.end(); ++itr)
        {
            if (**itr != **itr2)
                return false;
        }
        return true;
    }
    return false;
}


DECLARE_ITEM_FACTORY(VGWayPointPlan)

