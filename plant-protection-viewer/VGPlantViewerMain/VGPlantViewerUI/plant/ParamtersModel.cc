#include "ParamtersModel.h"

#include <QDebug>
#include <QQmlEngine>

#define ValueRole  Qt::UserRole+1

ParamtersModel::ParamtersModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

ParamtersModel::~ParamtersModel()
{
}

int ParamtersModel::rowCount(const QModelIndex &) const
{ 
    return m_parameters.count();
}

QVariant ParamtersModel::data(const QModelIndex &index, int role) const
{
    if (index.row()<0 || index.row()>=rowCount())
        return QVariant();
    
    if (role == ValueRole)
        return (m_parameters.begin()+ index.row()).value();
    if (role == Qt::DisplayRole)
        return (m_parameters.begin() + index.row()).key();

    return QVariant();
}

QHash<int, QByteArray> ParamtersModel::roleNames(void) const
{
    static QHash<int, QByteArray> hash = { { ValueRole ,"object" },{ Qt::DisplayRole,"text" } };
    return hash;
}

bool ParamtersModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    return false;
}

QObject *ParamtersModel::operator[](int index)
{
    return get(index);
}

const QObject* ParamtersModel::operator[](int index) const
{
    return get(index);
}

bool ParamtersModel::contains(QObject* object) const
{
    return m_lsObject.contains(object);
}

int ParamtersModel::indexOf(const QObject *object)
{
    int i = 0;
    for (QObject *itr : m_lsObject)
    {
        if (itr == object)
            return i;
        ++i;
    }

    return -1;
}

void ParamtersModel::clear(bool bDelObj)
{
    if (m_lsObject.isEmpty())
        return;
    beginRemoveRows(QModelIndex(), 0, m_lsObject.count()-1);
    while (!m_lsObject.isEmpty())
    {
        QObject *obj = m_lsObject.takeFirst();
        if (bDelObj)
        {
            if (auto it = qobject_cast<MapAbstractItem*>(obj))
                it->SetParentModel(nullptr);
            obj->deleteLater();
        }
    }
    endRemoveRows();
    emit countChanged();
}

QObject *ParamtersModel::removeAt(int i)
{
    if (i < 0 || i >= m_lsObject.count())
        return NULL;

    beginRemoveRows(QModelIndex(), i, i);
    QObject *removedObject = m_lsObject.takeAt(i);
    endRemoveRows();
    emit countChanged();

    if (MapAbstractItem *item = qobject_cast<MapAbstractItem*>(removedObject))
        item->SetParentModel(NULL);

    return removedObject;
}

QObject *ParamtersModel::removeOne(QObject *object)
{
    return removeAt(m_lsObject.indexOf(object));
}

void ParamtersModel::removeItmes(const QObjectList &objects)
{
    int count = 0;
    int nBeg = -1;
    QObjectList rvms;
    QList<QObject*>::iterator itr = m_lsObject.begin();
    for (int i = 0; itr != m_lsObject.end(); ++itr, ++i)
    {
        if (objects.contains(*itr))
        {
            if (nBeg < 0)
                nBeg = i;

            if (MapAbstractItem *item = qobject_cast<MapAbstractItem*>(*itr))
                item->SetParentModel(nullptr);

            ++count;
        }
        else if (nBeg >= 0)
        {
            beginRemoveRows(QModelIndex(), nBeg, nBeg+count-1);
            m_lsObject.erase(m_lsObject.begin() + nBeg, itr);
            endRemoveRows();
            nBeg = -1;
            i -= count;
            count = 0;
            emit countChanged();
        }
    }

    if (itr == m_lsObject.end() && nBeg >= 0)
    {
        beginRemoveRows(QModelIndex(), nBeg, nBeg+count-1);
        m_lsObject.erase(m_lsObject.begin() + nBeg, itr);
        endRemoveRows();
        emit countChanged();
    }
}

void ParamtersModel::insert(int i, QObject *object)
{
    if (!object || m_lsObject.contains(object))
        return;

    if (i < 0 || i > m_lsObject.count())
        i = m_lsObject.count();
    
    QQmlEngine::setObjectOwnership(object, QQmlEngine::CppOwnership);

    beginInsertRows(QModelIndex(), i, i);
    m_lsObject.insert(i, object);
    endInsertRows();
    emit countChanged();
}


void ParamtersModel::insertList(const QObjectList &objects, int i)
{
	if (objects.size() <= 0)
		return;

	if (i < 0 || i > m_lsObject.count())
		i = m_lsObject.count();

	beginInsertRows(QModelIndex(), i, i + objects.size() -1);
	for (QObject *itr : objects)
	{
		m_lsObject.insert(i++, itr);
	}
    endInsertRows();
    emit countChanged();
}

void ParamtersModel::setList(const QList<QObject *> &lstObject)
{
    for(int i = 0; i < lstObject.size(); i++)
    {
        append(lstObject.at(i));
    }
}

void ParamtersModel::append(QObject* object)
{
    insert(m_lsObject.count(), object);
}

int ParamtersModel::count(void) const
{
    return rowCount();
}

bool ParamtersModel::hasItem(const MapAbstractItem &item) const
{
    QList<QObject*>::const_iterator itr = m_lsObject.begin();
    for (; itr != m_lsObject.end(); ++itr)
    {
        if (*itr == &item || *(MapAbstractItem*)(*itr) == item)
            return true;
    }
    return false;
}

QObject *ParamtersModel::lastObject() const
{
    return m_lsObject.count() > 0 ? m_lsObject.last():NULL;
}

void ParamtersModel::removeAll(QObject *obj)
{
    m_lsObject.removeAll(obj);
}

const QList<QObject*> & ParamtersModel::AllQObject() const
{
    return m_lsObject;
}

bool ParamtersModel::operator!=(const ParamtersModel &oth) const
{
    return !(oth == *this);
}

bool ParamtersModel::operator==(const ParamtersModel &oth) const
{
    if (m_lsObject.count() != oth.m_lsObject.count())
        return false;

    QList<QObject*>::const_iterator itr = m_lsObject.begin();
    QList<QObject*>::const_iterator itr2 = oth.m_lsObject.begin();
    for (; itr != m_lsObject.end() && itr2 != oth.m_lsObject.end(); ++itr, ++itr2)
    {
        if (*(MapAbstractItem*)(*itr) != *(MapAbstractItem*)(*itr2))
            return false;
    }

    return true;
}
