#include "ParamtersModel.h"
#include <QDebug>
#include <QQmlEngine>
#include "ParametersMgr.h"
#include <VGApplication.h>

#define ValueRole  Qt::UserRole+1
#define ValueType  Qt::UserRole+2
#define VisiRole  Qt::UserRole+3

ParamtersModel::ParamtersModel(QObject* p) : QAbstractListModel(p)
{
}

ParamtersModel::~ParamtersModel()
{
}

void ParamtersModel::insert(const QString &key, const QVariant &v)
{
    m_parameters[key] = v;
    if (!qvgApp->parameters()->IsShowParam(key))
        return;

    int idxUpbound = indexOf(key);
    auto ptr = idxUpbound >= 0 ? &m_visParameters[idxUpbound] : nullptr;
    if (ptr && ptr->first==key)
    {
        if (v != ptr->second)
        {
            ptr->second = v;
            emit dataChanged(index(idxUpbound), index(idxUpbound));
        }
    }
    else
    {
        auto idx = ptr ? idxUpbound : m_visParameters.count();
        beginInsertRows(QModelIndex(), idx, idx);
        m_visParameters.insert(idx, QPair<QString, QVariant>(key, v));
        endInsertRows();
        emit idSChanged();
    }
}

const QVariant &ParamtersModel::Value(const QString &key)const
{
    auto itr = m_parameters.find(key);
    if (itr != m_parameters.end())
        return itr.value();

    static QVariant v;
    return v;
}

const QVariant &ParamtersModel::operator[](const QString &key)const
{
    return Value(key);
}

bool ParamtersModel::Contains(const QString &key) const
{
    auto itr = m_parameters.find(key);
    return (itr != m_parameters.end());
}

int ParamtersModel::indexOf(const QString &str, bool upBound)
{
    int ret = 0;
    for (auto &itr : m_visParameters)
    {
        if (str < itr.first)
            return upBound ? ret : -1;
        if (str == itr.first)
            return ret;

        ++ret;
    }
    return -1;
}

void ParamtersModel::SetMax(int count)
{
    if (count>m_maxItem)
        m_maxItem = count;
}

bool ParamtersModel::IsFull() const
{
    return m_maxItem <= m_parameters.count();
}

const QMap<QString, QVariant> &ParamtersModel::AllQObject() const
{
    return m_parameters;
}

void ParamtersModel::Update()
{
    if (!m_visParameters.isEmpty())
    {
        beginRemoveRows(QModelIndex(), 0, m_visParameters.count() - 1);
        m_visParameters.clear();
        endRemoveRows();
    }

    auto ins = m_visParameters;
    for (auto itr = m_parameters.begin(); itr != m_parameters.end(); ++itr)
    {
        if (qvgApp->parameters()->IsShowParam(itr.key()))
            ins << QPair<QString, QVariant &>(itr.key(), itr.value());
    }
    if (!ins.isEmpty())
    {
        beginInsertRows(QModelIndex(), 0, ins.count() - 1);
        m_visParameters = ins;
        endInsertRows();
    }
}

QVariant ParamtersModel::getValue(const QString &key) const
{
    return Value(key);
}

QStringList ParamtersModel::GetAllIds() const
{
    return m_parameters.keys();
}

int ParamtersModel::rowCount(const QModelIndex &/*= QModelIndex()*/) const
{
    return m_visParameters.size();
}

QVariant ParamtersModel::data(const QModelIndex & index, int role /*= Qt::DisplayRole*/) const
{
    auto row = index.row();
    if (row < 0 || row >= m_visParameters.count())
        return QVariant();

    auto &itr = m_visParameters.at(row);
    switch (role)
    {
    case Qt::DisplayRole:
        return itr.first;
    case ValueRole:
        return ParametersMgr::typProp(itr.second);
    case ValueType:
        return qvgApp->parameters()->GetTypeCmt(itr.first, itr.second);
    case Qt::ToolTipRole:
        return qvgApp->parameters()->GetDescribe(itr.first);
    default:
        break;
    }
    return QVariant();
}

QHash<int, QByteArray> ParamtersModel::roleNames(void) const
{
    static QHash<int, QByteArray> hash = { { ValueRole ,"object" },{ Qt::DisplayRole,"idText" }
        , { ValueType, "valType"}, { Qt::ToolTipRole, "desc"}
    };
    return hash;
}
