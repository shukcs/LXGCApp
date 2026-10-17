#include "ParamtersModel.h"

#include <QDebug>
#include <QQmlEngine>

#define ValueRole  Qt::UserRole+1

ParamtersModel::ParamtersModel(QObject* parent) : QObject(parent)
{
}

ParamtersModel::~ParamtersModel()
{
}

void ParamtersModel::insert(const QString &key, const QVariant &v)
{
    auto itr = m_parameters.upperBound(key);
    if (itr != m_parameters.end() && itr.key()==key && v==itr.value())
    {
        itr.value() = v;
        emit dataChanged(key);
    }
    else if (itr == m_parameters.end() || itr.key()==key)
    {
        m_parameters[key] = v;
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

int ParamtersModel::indexOf(const QString &str)
{
    int ret = 0;
    for (auto itr = m_parameters.begin(); itr != m_parameters.end(); ++itr)
    {
        if (str == itr.key())
            return ret;

        if (str > itr.key())
            ++ret;
        else
            break;
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

QVariant ParamtersModel::getValue(const QString &key) const
{
    return Value(key);
}

QStringList ParamtersModel::GetAllIds() const
{
    return m_parameters.keys();
}