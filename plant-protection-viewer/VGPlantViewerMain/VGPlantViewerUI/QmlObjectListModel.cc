#include "QmlObjectListModel.h"
#include "MapAbstractItem.h"

#include <QDebug>
#include <QQmlEngine>

#define ObjectRole  Qt::UserRole
#define TextRole  (Qt::UserRole + 1)

QmlObjectListModel::QmlObjectListModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

QmlObjectListModel::QmlObjectListModel(QmlObjectListModel &model)
    : QAbstractListModel(model.parent())
    , m_lsObject(model.m_lsObject)
{
}

QmlObjectListModel::~QmlObjectListModel()
{
    for (QObject *obj : m_lsObject)
    {
		if (MapAbstractItem *item = dynamic_cast<MapAbstractItem *>(obj))
			item->SetParentModel(nullptr);
    }
}

//QObject *QmlObjectListModel::get(int index) const
//{
//    if (index<0 || index>=m_lsObject.count())
//        return nullptr;
//
//    return m_lsObject.at(index);
//}

int QmlObjectListModel::rowCount(const QModelIndex&) const
{
    return m_lsObject.count();
}

QVariant QmlObjectListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    
    if (index.row() >= m_lsObject.count()) {
        return QVariant();
    }
    
    if (role == ObjectRole)
        return QVariant::fromValue(m_lsObject[index.row()]);
    if (role == TextRole)
        return QString(m_lsObject[index.row()]->metaObject()->className());

    return QVariant();
}

QHash<int, QByteArray> QmlObjectListModel::roleNames(void) const
{
    static QHash<int, QByteArray> hash = { { ObjectRole ,"object" },{ TextRole,"className" } };
    return hash;
}

bool QmlObjectListModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.isValid() && role == ObjectRole) {
        m_lsObject.replace(index.row(), value.value<QObject*>());
        emit dataChanged(index, index);
        return true;
    }
    
    return false;
}

QObject *QmlObjectListModel::operator[](int index)
{
    if (index < 0 || index >= m_lsObject.count())
        return nullptr;

    return m_lsObject.at(index);
}

const QObject* QmlObjectListModel::operator[](int index) const
{
    if (index<0 || index>=m_lsObject.count())
        return nullptr;

    return m_lsObject.at(index);
}

bool QmlObjectListModel::contains(QObject* object) const
{
    return m_lsObject.contains(object);
}

int QmlObjectListModel::indexOf(const QObject *object)
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

void QmlObjectListModel::clear(bool bDelObj)
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

QObject *QmlObjectListModel::removeAt(int i)
{
    if (i < 0 || i >= m_lsObject.count())
        return nullptr;

    beginRemoveRows(QModelIndex(), i, i);
    QObject *removedObject = m_lsObject.takeAt(i);
    endRemoveRows();
    emit countChanged();

    if (MapAbstractItem *item = qobject_cast<MapAbstractItem*>(removedObject))
        item->SetParentModel(nullptr);

    return removedObject;
}

QObject *QmlObjectListModel::removeOne(QObject *object)
{
    return removeAt(m_lsObject.indexOf(object));
}

void QmlObjectListModel::removeItmes(const QObjectList &objects)
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

QObject* QmlObjectListModel::removeLast()
{
    if (m_lsObject.isEmpty())
        return nullptr;

    return removeOne(m_lsObject.last());
}

void QmlObjectListModel::insert(int i, QObject *object)
{
    if (!object || m_lsObject.contains(object))
        return;

    if (i < 0 || i > m_lsObject.count())
        i = m_lsObject.count();
    
    ///QQmlEngine::setObjectOwnership(object, QQmlEngine::CppOwnership);

    beginInsertRows(QModelIndex(), i, i);
    m_lsObject.insert(i, object);
    endInsertRows();
    emit countChanged();
}


void QmlObjectListModel::insertList(const QObjectList &objects, int i)
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

void QmlObjectListModel::setList(const QList<QObject *> &lstObject)
{
    for(int i = 0; i < lstObject.size(); i++)
    {
        append(lstObject.at(i));
    }
}

void QmlObjectListModel::append(QObject* object)
{
    insert(m_lsObject.count(), object);
}

int QmlObjectListModel::count(void) const
{
    return rowCount();
}

void QmlObjectListModel::deleteListAndContents(void)
{
    for (int i=0; i<m_lsObject.count(); i++) {
        m_lsObject[i]->deleteLater();
    }
    deleteLater();
}

void QmlObjectListModel::clearAndDeleteContents(void)
{
    for (int i=0; i<m_lsObject.count(); i++) {
        m_lsObject[i]->deleteLater();
    }
    clear();
}

void QmlObjectListModel::resetModelBegin()
{
    beginResetModel();
}

void QmlObjectListModel::resetModelEnd()
{
    endResetModel();
}

bool QmlObjectListModel::hasItem(const MapAbstractItem &item) const
{
    QList<QObject*>::const_iterator itr = m_lsObject.begin();
    for (; itr != m_lsObject.end(); ++itr)
    {
        if (*itr == &item || *(MapAbstractItem*)(*itr) == item)
            return true;
    }
    return false;
}

QObject *QmlObjectListModel::Last() const
{
    return !m_lsObject.isEmpty() ? m_lsObject.last():nullptr;
}

QObject * QmlObjectListModel::First() const
{
    return !m_lsObject.isEmpty() ? m_lsObject.first() : nullptr;
}

void QmlObjectListModel::removeAll(QObject *obj)
{
    m_lsObject.removeAll(obj);
}

const QList<QObject*> & QmlObjectListModel::AllQObject() const
{
    return m_lsObject;
}

bool QmlObjectListModel::IsEmpty() const
{
    return m_lsObject.isEmpty();
}

bool QmlObjectListModel::operator!=(const QmlObjectListModel &oth) const
{
    return !(oth == *this);
}

bool QmlObjectListModel::operator==(const QmlObjectListModel &oth) const
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
