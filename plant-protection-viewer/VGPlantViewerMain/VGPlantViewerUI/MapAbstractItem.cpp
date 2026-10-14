#include "MapAbstractItem.h"
#include <QMetaProperty>
#include "MapItemFactory.h"
#include "VGApplication.h"
#include "VGMapManager.h"
#include "VGNetManager.h"
#include "VGGlobalFun.h"
#include "VGDbManager.h"
#include "QmlObjectListModel.h"

MapAbstractItem::MapAbstractItem(QObject *parent, int id) : QObject(parent)
, m_id(id), m_bShowBelonged(true)
, m_bVisible(false)
, m_width(2)
, m_modelParent(NULL)
{
    SetParentItem(dynamic_cast<MapAbstractItem*>(parent));
    connect(this, &MapAbstractItem::selectedChanged, this, &MapAbstractItem::onSelectedChanged);
}

MapAbstractItem::MapAbstractItem(const MapAbstractItem &oth) : QObject(NULL)
, m_id(oth.m_id)
, m_bVisible(oth.m_bVisible)
, m_color(oth.m_color)
, m_width(oth.m_width)
, m_parentItem(NULL)
, m_modelParent(NULL)
, m_bShowBelonged(true)
{
    connect(this, &MapAbstractItem::selectedChanged, this, &MapAbstractItem::onSelectedChanged);
}

MapAbstractItem::~MapAbstractItem()
{
    if (m_modelParent)
        m_modelParent->removeOne(this);
}

void MapAbstractItem::SetColor(const QColor &)
{
}

QColor MapAbstractItem::GetColor() const
{
    return Qt::transparent;
}

void MapAbstractItem::SetBorderColor(const QColor &col)
{
    if (m_color != col)
    {
        m_color = col;
        emit borderColorChanged(col);
    }
}

QColor MapAbstractItem::GetBorderColor() const
{
    return m_color;
}

QColor MapAbstractItem::GetItemColor() const
{
	return QColor();
}

bool MapAbstractItem::GetSelected() const
{
    if (VGMapManager *mgr = qvgApp->mapManager())
        return mgr->IsItemSelecte(this);

    return false;
}

void MapAbstractItem::SetSelected(bool b)
{
    if (b == GetSelected())
        return;

    if (VGMapManager *mgr = qvgApp->mapManager())
    {
        mgr->SetItemSelected(this, b);
        if (b)
            mgr->InsertItem(this);
    }
    showContent(b);
    emit itemColorChanged(GetItemColor());
    emit selectedChanged(b);
}

void MapAbstractItem::SetVisible(bool b)
{
    if (m_bVisible != b)
    {
        m_bVisible = b;
        emit visibleChanged(b);
    }
}

bool MapAbstractItem::GetVisible() const
{
    if (m_parentItem)
        return m_bVisible && m_parentItem->GetVisible();

    return m_bVisible;
}

int MapAbstractItem::GetId() const
{
    return m_id;
}

void MapAbstractItem::SetId(int id)
{
    if (m_id != id)
    {
        m_id = id;
        emit idChanged(id);
    }
}

int MapAbstractItem::GetWidth() const
{
    return m_width;
}

void MapAbstractItem::SetWidth(int w)
{
    if (m_width != w)
    {
        m_width = w;
        emit widthChanged(w);
    }
}

void MapAbstractItem::Show(bool b)
{
    _show(b);
    showContent(b);
}

void MapAbstractItem::showContent(bool)
{
}

int MapAbstractItem::ItemIndex(const MapAbstractItem *) const
{
    return -1;
}

bool MapAbstractItem::save(bool bCloud)
{
    if (!bCloud)
    {
        VGDbManager *db = qvgApp->dbManager();
        if (!db)
            return false;

        db->SaveItemSafe(this);
        return true;
    }
    else if (VGNetManager *netMgr = qvgApp->netManager())
    {  
        connect(netMgr, &VGNetManager::sigSaveResult, this, &MapAbstractItem::onUploadChanged);
        return netMgr->UploadItem(this);
    }
    return false;
}

bool MapAbstractItem::CompareItemList(const QList<MapAbstractItem*> &ls1, const QList<MapAbstractItem*> &ls2)
{
    if (ls1.count() != ls2.count())
        return false;

    QList<MapAbstractItem*>::const_iterator itr = ls1.begin();
    QList<MapAbstractItem*>::const_iterator itr2 = ls2.begin();
    for (; itr != ls1.end(); ++itr, ++itr2)
    {
        if (**itr != **itr2)
            return false;
    }

    return true;
}

bool MapAbstractItem::IsContain(const DescribeMap &m1, const DescribeMap &m2)
{
    DescribeMap::const_iterator itr = m2.begin();
    for (; itr != m2.end(); ++itr)
    {
        if (itr.value() != m1[itr.key()])
            return false;
    }
    return true;
}

void MapAbstractItem::onUploadChanged(const DescribeMap &result)
{
    if (VGNetManager *netMgr = qobject_cast<VGNetManager *>(sender()))
    {
        netMgr->disconnect(SIGNAL(sigSaveResult(const DescribeMap &)), this);
        processSaveReslt(result);
    }
}

bool MapAbstractItem::operator!=(const MapAbstractItem &item) const
{
    return !(*this == item);
}

MapAbstractItem * MapAbstractItem::Clone(QObject *parent) const
{
    if (MapAbstractItem *ret = MapItemFactory::CreateItem(metaObject()->className(), parent))
    {
        *ret = *this;
        return ret;
    }

    return NULL;
}

int MapAbstractItem::CountChildren() const
{
    return 0;
}


int MapAbstractItem::GetShowType() const
{
    return Show_LineAndPoint;
}

void MapAbstractItem::SetShowType(int)
{
}

void MapAbstractItem::SetParentItem(MapAbstractItem *parent)
{
    m_parentItem = parent;
    setParent(parent);
}

MapAbstractItem *MapAbstractItem::GetParentItem() const
{
    return m_parentItem;
}

MapAbstractItem * MapAbstractItem::childAt(int)const
{
    return nullptr;
}

void MapAbstractItem::releaseSafe()
{
    if (VGDbManager *db = qvgApp->dbManager())
        db->DeleteItemSafe(this);
    if (VGNetManager *nm = qvgApp->netManager())
        nm->DeleteItemSafe(this);

    SetVisible(false);
    if (VGMapManager *mgr = qvgApp->mapManager())
        mgr->RemoveItem(this);
    deleteLater();
}

void MapAbstractItem::foldChildren(bool)
{
}

void MapAbstractItem::_show(bool b)
{
    if (VGMapManager *mgr = qvgApp->mapManager())
    {
        if (b)
        {
            int idx = m_parentItem ? m_parentItem->ItemIndex(this) : -1;
            if (idx >= 0)
                --idx;
            mgr->InsertItem(this, idx);
        }
        else if (m_modelParent)
        {
            m_modelParent->removeOne(this);
            m_modelParent = nullptr;
        }
    }
}

void MapAbstractItem::InsertTo(QmlObjectListModel *model, int idx /*= -1*/)
{
    if (m_modelParent)
        m_modelParent->removeOne(this);
    m_modelParent = model;
    if (m_modelParent && !m_modelParent->contains(this))
        m_modelParent->insert(idx, this);
}

MapAbstractItem &MapAbstractItem::operator=(const MapAbstractItem &item)
{
    const QMetaObject *mo = item.metaObject();
    for (int i = 0; i < mo->propertyCount(); ++i)
    {
        QMetaProperty p = mo->property(i);
        if (!p.isWritable())
            continue;

        setProperty(p.name(), p.read(&item));
    }

    return *this;
}

void MapAbstractItem::processSaveReslt(const DescribeMap &)
{
}

void MapAbstractItem::SetParentModel(QmlObjectListModel *model)
{
    if (m_modelParent == model)
        return;
    if (m_modelParent)
        disconnect(SIGNAL(destroyed(QObject*)), m_modelParent);
    if (model)
        connect(this, &QObject::destroyed, model, &QmlObjectListModel::removeAll);
    m_modelParent = model;
}

bool MapAbstractItem::IsShowBelonged() const
{
    return m_bShowBelonged;
}

void MapAbstractItem::SetShowBelonged(bool b)
{
    if (b == m_bShowBelonged)
        return;

    m_bShowBelonged = b;
    if (m_parentItem)
        m_parentItem->showContent(b);

    emit showBelongedChanged(b);
}

MapAbstractItem *MapAbstractItem::FindParentByProperty(const DescribeMap &)const
{
    return NULL;
}

void MapAbstractItem::UpdateDB()const
{
    if (VGDbManager *db = qvgApp->dbManager())
        db->UpdateDb(this);
}

void MapAbstractItem::SetUploaded(bool)
{
}

bool MapAbstractItem::IsUpLoaded() const
{
    return false;
}

void MapAbstractItem::SetSaveLocal(bool)
{
}

bool MapAbstractItem::IsSaveLocal() const
{
    return false;
}

void MapAbstractItem::onSelectedChanged(bool)
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//SingleTriggerItem
//////////////////////////////////////////////////////////////////////////////////////////////////////////
SingleTriggerItem::SingleTriggerItem(QObject *parent, int id /*= -1*/) : MapAbstractItem(parent, id)
, m_colorNormal(246, 246, 246), m_colorSelected(205, 230, 255)
{
}

SingleTriggerItem::SingleTriggerItem(const SingleTriggerItem &oth) : MapAbstractItem(oth)
, m_colorNormal(oth.m_colorNormal), m_colorSelected(oth.m_colorSelected)
{
}

void SingleTriggerItem::SetItemColor(const QColor &nor, const QColor sel)
{
    m_colorNormal = nor;
    m_colorSelected = sel;
}

QColor SingleTriggerItem::GetItemColor() const
{
    return GetSelected() ? m_colorSelected : m_colorNormal;
}
