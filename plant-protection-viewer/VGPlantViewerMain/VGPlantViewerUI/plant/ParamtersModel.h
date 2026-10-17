#ifndef __ParamtersModel_H__
#define __ParamtersModel_H__

#include <QObject>
#include <QVariant>
#include <QMap>

class ParamtersModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList idS READ GetAllIds NOTIFY idSChanged)
public:
    ParamtersModel(QObject* parent = nullptr);
    ~ParamtersModel();

    void insert(const QString &key, const QVariant &v);
    const QVariant  &Value(const QString &key)const;
    const QVariant &operator[](const QString &)const;
    bool Contains(const QString &)const;
    int indexOf(const QString &str);
    void SetMax(int count);
    bool IsFull()const;
    const QMap<QString, QVariant> &AllQObject()const;
protected:
    Q_INVOKABLE QVariant getValue(const QString &key)const;
    QStringList GetAllIds()const;
signals:
    void dataChanged(const QString &id);
    void idSChanged();
private:
    QMap<QString, QVariant> m_parameters;
    int m_maxItem = 1;
};

#endif //__ParamtersModel_H__
