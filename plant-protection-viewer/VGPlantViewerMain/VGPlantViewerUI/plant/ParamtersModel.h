#ifndef __ParamtersModel_H__
#define __ParamtersModel_H__

#include <QAbstractListModel>
#include <QMap>

class ParamtersModel : public QAbstractListModel
{
public:
    ParamtersModel(QObject* parent = nullptr);
    ~ParamtersModel();

    int count(void) const;
    void insert(const QString &key, const QVariant &v);
    QVariant &operator[](const QString &);
    bool contains(const QString &)const;
    int indexOf(const QString &str);

    const QMap<QString, QVariant> &AllQObject()const;
protected:
    // Overrides from QAbstractListModel
    int	rowCount(const QModelIndex & parent = QModelIndex())const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole)const override;
    QHash<int, QByteArray> roleNames(void) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)override;
private:
    QMap<QString, QVariant> m_parameters;
};

#endif //__ParamtersModel_H__
