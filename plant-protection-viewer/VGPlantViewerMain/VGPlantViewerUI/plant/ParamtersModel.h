#ifndef __ParamtersModel_H__
#define __ParamtersModel_H__

#include <QAbstractListModel>
#include <QMap>

class ParamtersModel : public QAbstractListModel
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
    void Update();
protected:
    Q_INVOKABLE QVariant getValue(const QString &key)const;
    QStringList GetAllIds()const;
protected:
    int	rowCount(const QModelIndex & parent = QModelIndex())const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole)const override;
    QHash<int, QByteArray> roleNames(void) const override;
    //bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)override;
signals:
    void idSChanged();
private:
    QMap<QString, QVariant> m_parameters;
    QMap<QString, QVariant> m_visParameters;
    int m_maxItem = 1;
};

#endif //__ParamtersModel_H__
