#ifndef __VGWayPointPlan_H__
#define __VGWayPointPlan_H__

#include "MapAbstractItem.h"

class VGCoordinate;
class QGeoCoordinate;
class VGVehicleMission;

class VGWayPointPlan : public SingleTriggerItem<MapAbstractItem>
{
    Q_OBJECT

    Q_PROPERTY(QString name READ GetName WRITE SetName NOTIFY nameChanged)
    Q_PROPERTY(int wpCount READ WPCount NOTIFY wpCountChanged)
    Q_PROPERTY(QString comment READ GetComment WRITE SetComment NOTIFY wpCountChanged)
    Q_PROPERTY(QString timeCrt READ GetCreateTime)
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
    Q_INVOKABLE void EndEdit();

    void showContent(bool b)override;
    QString GetCreateTime()const;
protected:
    Q_INVOKABLE VGVehicleMission *getRoute()const;
signals:
    void pathChanged(const QVariantList &);
    void wayPointFinished();
    void nameChanged(const QString &);
    void commentChanged(const QString &);
    void wpCountChanged();
private:
    qint64              m_time;
    VGVehicleMission    *m_route;
    QString m_name;
    QString m_commet;
};

#endif // __VGFLYPLAN_H__
