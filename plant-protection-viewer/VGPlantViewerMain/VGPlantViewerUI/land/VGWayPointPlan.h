#ifndef __VGWayPointPlan_H__
#define __VGWayPointPlan_H__

#include "MapAbstractItem.h"

class VGCoordinate;
class QGeoCoordinate;
class VGVehicleMission;
class VGMissionItem;
class MissionItem;

class VGWayPointPlan : public SingleTriggerItem
{
    Q_OBJECT

    Q_PROPERTY(QString name READ GetName WRITE SetName NOTIFY nameChanged)
    Q_PROPERTY(int wpCount READ WPCount NOTIFY wpCountChanged)
    Q_PROPERTY(QString comment READ GetComment WRITE SetComment NOTIFY wpCountChanged)
    Q_PROPERTY(QString timeCrt READ GetCreateTime NOTIFY timeChanged)
    Q_PROPERTY(VGVehicleMission* mission READ getRoute CONSTANT)
    Q_PROPERTY(QString addType READ GetAddType WRITE SetAddType NOTIFY addTypeChanged)
    Q_PROPERTY(bool newPlan READ IsNewPlan NOTIFY newPlanChanged)
public:
    explicit VGWayPointPlan(QObject *p=nullptr, const QString &n=QString());
    //VGWayPointPlan(const VGWayPointPlan &oth);
    ~VGWayPointPlan();

    MapItemType ItemType()const;
    bool operator==(const MapAbstractItem &item)const;
    int WPCount()const;
    QString GetName()const;
    void SetName(const QString &n);
    QString GetComment() const;
    void SetComment(const QString &c);
    Q_INVOKABLE void endEdit();
    Q_INVOKABLE VGMissionItem *addWayPoint(const QGeoCoordinate &c, int idx = -1);

    void showContent(bool b)override;
    QString GetCreateTime()const;
    void SetSelected(bool b)override;
    void SetMissionItems(const QList<MissionItem *> &items);
    VGVehicleMission *GetMission()const;
protected:
    VGVehicleMission *getRoute()const;
    QString GetAddType()const;
    void SetAddType(const QString &);
    bool IsNewPlan()const;
signals:
    void pathChanged(const QVariantList &);
    void wayPointFinished();
    void nameChanged(const QString &);
    void commentChanged(const QString &);
    void wpCountChanged();
    void addTypeChanged();
    void timeChanged();
    void newPlanChanged();
private:
    qint64              m_time;
    VGVehicleMission    *m_route;
    QString m_name;
    QString m_commet;
    QString m_addType;
};

#endif // __VGFLYPLAN_H__
