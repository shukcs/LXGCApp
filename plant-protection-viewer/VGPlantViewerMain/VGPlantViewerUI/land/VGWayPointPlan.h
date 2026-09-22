#ifndef __VGWayPointPlan_H__
#define __VGWayPointPlan_H__

#include "MapAbstractItem.h"

class VGCoordinate;
class QGeoCoordinate;

class VGWayPointPlan : public SingleTriggerItem<MapAbstractItem>
{
    Q_OBJECT

    Q_PROPERTY(QString name READ GetName WRITE SetName NOTIFY nameChanged)
    Q_PROPERTY(int wpCount READ WPCount NOTIFY wpCountChanged)
    Q_PROPERTY(QString comment READ GetComment WRITE SetComment NOTIFY wpCountChanged)
    Q_PROPERTY(QVariantList path READ GetPath NOTIFY pathChanged)
public:
    explicit VGWayPointPlan(QObject *p=nullptr, const QString &n=QString());
    VGWayPointPlan(const VGWayPointPlan &oth);
    ~VGWayPointPlan();

    MapItemType ItemType()const;
    bool operator==(const MapAbstractItem &item)const;
    QVariantList GetPath()const;
    int WPCount()const;
    void SetWayPoints(const QList<QGeoCoordinate> &cs);
    void Show(bool b)override;
    QString GetName()const;
    void SetName(const QString &n);
    QString GetComment() const;
    void SetComment(const QString &c);
    Q_INVOKABLE void  AddWayPoint(const QGeoCoordinate &c);
protected:
    void addWayPoint(const QGeoCoordinate &c);
    void remove(VGCoordinate *wp);
    int ItemIndex(const MapAbstractItem *item)const override;
signals:
    void pathChanged(const QVariantList &);
    void wayPointFinished();
    void nameChanged(const QString &);
    void commentChanged(const QString &);
    void wpCountChanged(int);
private:
    QList<VGCoordinate *> m_wps;
    QVariantList m_path;
    QString m_name;
    QString m_commet;
};

#endif // __VGFLYPLAN_H__
