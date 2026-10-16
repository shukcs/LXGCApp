#include "ParametersMgr.h"
#include "ParameterLimit.h"
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>

ParametersMgr::ParametersMgr(QObject *parent) : QObject(parent)
{
}

void ParametersMgr::LoadParameters(const QDomElement &ele)
{
    QDomElement e = ele.firstChildElement("ParameterLimit");
    while (!e.isNull())
    {
        parseParameterLimit(e);
        e = e.nextSiblingElement("ParameterLimit");
    }
}

QStringList ParametersMgr::GetGroups() const
{
    QMap <QString, QList<ParaLimitAbs*> >::const_iterator itr = m_params.begin();
    QStringList ret;
    for (;itr!=m_params.end();++itr)
    {
        ret << itr.key();
    }
    return ret;
}

QVariant ParametersMgr::stringToVariant(const QString &id, const QString &val) const
{
    QVariant ret;
    if (ParaLimitAbs *parm = _getParemeterLimit(id))
    {
        ret = parm->ValueFromString(val);
        if (parm->IsScope() && (ret > parm->GetBiggest() || ret < parm->Getleast()))
            return QVariant();
    }
 
    return ret;
}

QStringList ParametersMgr::getParams(const QString &group) const
{
    QString str = group.isEmpty() ? "undef" : group;
    QMap <QString, QList<ParaLimitAbs*> >::const_iterator itr = m_params.find(str);
    QStringList ret;
    if (itr == m_params.end())
        return ret;

    for (ParaLimitAbs *item : itr.value())
    {
        ret << item->GetId();
    }
    return ret;
}

ParaLimitAbs::ParamType ParametersMgr::getType(const QString &id) const
{
    if (auto parm = _getParemeterLimit(id))
        return (ParaLimitAbs::ParamType)parm->GetType();

    return ParaLimitAbs::ParamUnknow;
}

QString ParametersMgr::getName(const QString &id) const
{
    if (ParaLimitAbs *parm = _getParemeterLimit(id))
        return parm->GetName();

    return QString();
}

bool ParametersMgr::hasParam(const QString &id, const QString &group) const
{
    return _getParemeterLimit(id, group) != NULL;
}

bool ParametersMgr::isParamReadonly(const QString &id) const
{
    if (ParaLimitAbs *parm = _getParemeterLimit(id))
        return parm->IsReadOnly();

    return true;
}

bool ParametersMgr::isScope(const QString &id) const
{
    if (ParaLimitAbs *parm = _getParemeterLimit(id))
        return parm->IsScope();

    return false;
}

QString ParametersMgr::getLeast(const QString &id) const
{
    if (ParaLimitAbs *parm = _getParemeterLimit(id))
        return parm->ValueToString(parm->Getleast());

    return QString();
}

QString ParametersMgr::getBiggest(const QString &id) const
{
    if (ParaLimitAbs *parm = _getParemeterLimit(id))
        return parm->ValueToString(parm->GetBiggest());

    return QString();
}

QStringList ParametersMgr::getDscribes(const QString &id) const
{
    if (ParaLimitAbs *parm = _getParemeterLimit(id))
        return parm->GetDescribes();

    return QStringList();
}

int ParametersMgr::getVarIndex(const QString &id, const QVariant &val) const
{
    if (ParaLimitAbs *parm = _getParemeterLimit(id))
        return parm->GetPropertyIndex(val);

    return -1;
}

QString ParametersMgr::getStrValue(const QString &id, QVariant val)
{
	if (!val.isValid())
		return QString();
	if (ParaLimitAbs *parm = _getParemeterLimit(id))	
		return parm->ValueToString(val);

	return QString("%1").arg(val.toUInt()) + tr("Origin");//"原始"
}

QString ParametersMgr::GetGroup(const QString &id) const
{
    QMap <QString, QList<ParaLimitAbs*> >::const_iterator itr = m_params.begin();
    for (; itr != m_params.end(); ++itr)
    {
        for (ParaLimitAbs *item : itr.value())
        {
            if (item && item->GetId() == id)
                return itr.key();
        }
    }
    return QString();
}

QStringList ParametersMgr::GetAllInSameGroup(const QString &id) const
{
    QMap <QString, QList<ParaLimitAbs*> >::const_iterator itr = m_params.begin();
    for (; itr != m_params.end(); ++itr)
    {
        for (ParaLimitAbs *item : itr.value())
        {
            if (item && item->GetId() == id)
                return getParams(itr.key());
        }
    }
    return QStringList();
    
}

QStringList ParametersMgr::GetLables() const
{
    return m_labels;
}

void ParametersMgr::ParameterAdd(const QString &id)
{
    auto idx = id.indexOf("_") - 1;
    while (idx >= 0)
    {
        if ('0' <= id.at(idx) && id.at(idx) <= '9')
            idx--;
        else
            break;
    }
    if (idx >= 0)
        _addLabel(id.left(idx + 1));
}

QVariant ParametersMgr::getValue(const QString &id, int index) const
{
    if (ParaLimitAbs *parm = _getParemeterLimit(id))
        return parm->GetValue(index);

    return QVariant();
}

void ParametersMgr::parseParameterLimit(const QDomElement &e)
{
    QString str = e.attribute("type");
    ParaLimitAbs *param = NULL;

    if ("float" == str)
        param = new ParameterFloat;
    else if ("int" == str)
        param = new ParameterInt;
    else if ("uint" == str)
        param = new ParameterU32;
    else if ("bool" == str)
        param = new ParameterU32;

    if (param)
    {
        param->ParseContent(e);
        m_params[e.attribute("group", "undef")].push_back(param);
    }
}

ParaLimitAbs *ParametersMgr::_getParemeterLimit(const QString &id, const QString &group)const
{
    if (!group.isEmpty())
    {
        QMap <QString, QList<ParaLimitAbs*> >::const_iterator itr = m_params.find(group);
        for (ParaLimitAbs *item : itr.value())
        {
            if (item && item->GetId() == id)
                return item;
        }
        return NULL;
    }
    QMap <QString, QList<ParaLimitAbs*> >::const_iterator itr = m_params.begin();
    for (; itr != m_params.end(); ++itr)
    {
        for (ParaLimitAbs *item : itr.value())
        {
            if (item && item->GetId() == id)
                return item;
        }
    }
    return NULL;
}

void ParametersMgr::_addLabel(const QString &label)
{
    auto itr = m_labels.begin();
    for (; itr != m_labels.end(); ++itr)
    {
        if (*itr == label)
            return;
        if (*itr > label)
        {
            m_labels.insert(itr, label);
            emit labelsChanged();
            break;
        }
    }
    if (itr == m_labels.end())
    {
        m_labels.insert(itr, label);
        emit labelsChanged();
    }
}
