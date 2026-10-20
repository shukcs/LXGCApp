#include "VGPlantEvents.h"
#include <QDomElement>
#include <QDateTime>
#include "QSettings"
#include "VGApplication.h"

#define EventString(lv) #lv
#define MaxEventSeq 1024

VGPlantEvent::VGPlantEvent(const QString &id, VGPlantEventDescribe *evt): QObject(NULL)
, m_time(QDateTime::currentMSecsSinceEpoch()), m_strUav(id)
, m_strDesc(evt ? evt->GetTip() : QString()), m_leave(evt?evt->GetLeave() : Event_Info)
, m_bVisible(true)
{
}

VGPlantEvent::VGPlantEvent(const QString &id, const QString &des, Event_Leave lv) : QObject(NULL)
, m_time(QDateTime::currentMSecsSinceEpoch()), m_strUav(id)
, m_strDesc(des), m_leave(lv), m_bVisible(true)
{

}

QString VGPlantEvent::GetDescribe() const
{
    return m_strDesc;
}

Event_Leave VGPlantEvent::GetLeave() const
{
    return m_leave;
}

void VGPlantEvent::SetVisible(bool b)
{
    if (m_bVisible == b)
        return;

    m_bVisible = b;
    emit visibleChanged();
}

QColor VGPlantEvent::GetEventColor() const
{
    return QColor(m_leave==Event_Fatal ? "#c81e06" : "#A0A0FF");
}

QString VGPlantEvent::GetEvent() const
{
    if (m_strDesc.isEmpty())
        return QString();

    if (m_strUav.isEmpty())
        return  QString("(%1): %2").arg(QDateTime::fromMSecsSinceEpoch(m_time).toString("hh:mm:ss"), m_strDesc);

    return QString("(%1)%2: \r\n%3").arg(QDateTime::fromMSecsSinceEpoch(m_time).toString("hh:mm:ss"), m_strUav, m_strDesc);
}

bool VGPlantEvent::IsVisible() const
{
    return m_bVisible;
}

void VGPlantEvent::remove()
{
    emit removed(this);
}

QString VGPlantEvent::GetEventString(Event_Leave lv)
{
    switch (lv)
    {
    case Event_Info:
        return EventString(Event_Info);
    case Event_SpeakInfo:
        return EventString(Event_SpeakInfo);
    case Event_Fatal:
        return EventString(Event_Fatal);
    default:
        break;
    }
    return QString();
}
/////////////////////////////////////////////////////////////////////////
//VGPlantEventDescribe
/////////////////////////////////////////////////////////////////////////
VGPlantEventDescribe::VGPlantEventDescribe()
    : m_leave(Event_Info), m_evtID(-1)
{
}

QString VGPlantEventDescribe::GetTip() const
{
    return m_tip;
}

Event_Leave VGPlantEventDescribe::GetLeave() const
{
    return m_leave;
}

int VGPlantEventDescribe::GetEventID() const
{
    return m_evtID;
}

VGPlantEventDescribe *VGPlantEventDescribe::Parse(const QDomElement &e)
{
    int id = e.attribute("event", "-1").toInt();
    if (id < 0)
        return NULL;

    QString tip = e.attribute("tip");
    Event_Leave leave = transLeave(e.attribute("leave"));
    if (VGPlantEventDescribe *ret = new VGPlantEventDescribe)
    {
        ret->m_evtID = id;
        ret->m_tip = tip;
        ret->m_leave = leave;
        return ret;
    }

    return NULL;
}

Event_Leave VGPlantEventDescribe::transLeave(const QString &lv)
{
    for (int i = Event_Info; i<Event_End; ++i)
    {
        if (0==lv.compare(VGPlantEvent::GetEventString((Event_Leave)i)))
            return (Event_Leave)i;
    }
    return Event_Info;
}
/////////////////////////////////////////////////////////////////////////
//VGPlantEvents
/////////////////////////////////////////////////////////////////////////
VGPlantEvents::VGPlantEvents(QObject *p/*=NULL*/):QObject(p)
, m_bShowAll(true), m_events(new QmlObjectListModel(this))
{
    _loadConfig();
}

VGPlantEvents::~VGPlantEvents()
{
    if (!m_events)
        return;

    while (m_events->count()>0)
    {
        delete m_events->removeAt(0);
    }
    delete m_events;
}

void VGPlantEvents::Parse(const QDomElement &e)
{
    QDomElement UavEvents = e.firstChildElement("UavEvents");
    if (UavEvents.isNull())
        return;

    QDomElement UavEven = UavEvents.firstChildElement("UavEvent");
    while (!UavEven.isNull())
    {
        VGPlantEventDescribe *dscr = VGPlantEventDescribe::Parse(UavEven);
        if (dscr && m_eventDscrs.find(dscr->GetEventID()) == m_eventDscrs.end())
            m_eventDscrs[dscr->GetEventID()] = dscr;
        else
            delete dscr;

        UavEven = UavEven.nextSiblingElement("UavEvent");
    }
}

void VGPlantEvents::AddEvent(const QString &id, int eId)
{
    auto itr = m_eventDscrs.find(eId);
    if (itr == m_eventDscrs.end())
        itr = m_eventDscrs.find(MaxEventSeq);

    if (itr != m_eventDscrs.end())
    {
        if (VGPlantEvent *evt = new VGPlantEvent(id, *itr))
            _addEvent(evt);
    }
}

void VGPlantEvents::AddEvent(const QString &id, const QString &desc, Event_Leave lv)
{
    if (VGPlantEvent *evt = new VGPlantEvent(id, desc, lv))
    {
        if (!m_bShowAll && (*m_events)[0])
            m_events->value<VGPlantEvent*>(0)->SetVisible(false);

        _addEvent(evt);
    }
}

QmlObjectListModel *VGPlantEvents::GetEvents()
{
    return m_events;
}

bool VGPlantEvents::IsShowAll() const
{
    return m_bShowAll;
}

void VGPlantEvents::SetShowAll(bool b)
{
    if (m_bShowAll == b)
        return;
    m_bShowAll = b;
    emit showAllChanged();

    if (!m_events)
        return;

    auto &evts = m_events->AllQObject();
    for (auto itr = evts.begin(); itr != evts.end(); ++itr)
    {
        VGPlantEvent *evt = (VGPlantEvent *)*itr;
        evt->SetVisible(b || itr==evts.begin());
    }
    _saveConfig();
}

void VGPlantEvents::_addEvent(VGPlantEvent *evt)
{
    m_events->insert(0, evt);
    while (m_events->count() > 100)
    {
        delete m_events->removeLast();
    }
    connect(evt, &VGPlantEvent::removed, this, &VGPlantEvents::onEventRemoved);
    if (evt->GetLeave() != Event_Info)
        qvgApp->speakNotice(evt->GetDescribe());
}

void VGPlantEvents::onEventRemoved(VGPlantEvent *e)
{
    delete m_events->removeOne(e);
    if (!m_bShowAll && !m_events->IsEmpty())
        (m_events->value<VGPlantEvent *>(0))->SetVisible(true);
}

void VGPlantEvents::_saveConfig()
{
    if (QSettings *st = qvgApp->GetSettings())
    {
        st->beginGroup("UavEvents");
        st->setValue("showAll", m_bShowAll);
        st->endGroup();
    }
}

void VGPlantEvents::_loadConfig()
{
    if (QSettings *st = qvgApp->GetSettings())
    {
        st->beginGroup("UavEvents");
        m_bShowAll = st->value("showAll", true).toBool();
        st->endGroup();
    }
}