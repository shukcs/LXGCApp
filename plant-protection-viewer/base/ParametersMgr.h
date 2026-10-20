#ifndef __PARAMETERS_LIMIT_H__
#define __PARAMETERS_LIMIT_H__

#include <QObject>
#include <QList>
#include <QMap>
#include "ParameterLimit.h"

class QDomElement;
class QVariant;
class ParamtersModel;
class ParametersMgr : public QObject
{
    Q_OBJECT
    Q_ENUMS(ParamType)
    Q_PROPERTY(QStringList groups READ GetGroups CONSTANT)
    Q_PROPERTY(QStringList labels READ GetLables NOTIFY labelsChanged)
    Q_PROPERTY(ParamtersModel *params READ GetParasModel NOTIFY parasChanged)
    Q_PROPERTY(QString button READ GetButton WRITE SetButton NOTIFY buttonChanged)
    Q_PROPERTY(QString search READ GetSearch WRITE SetSearch NOTIFY searchChanged)
public:
    enum ParamType {
        ParamUnknow = QVariant::Invalid,
        ParamBool = QVariant::Bool,
        ParamInt = QMetaType::Long,
        ParamUInt = QMetaType::ULong,
        ParamInt8 = QMetaType::SChar,
        ParamUint8 = QMetaType::UChar,
        ParamInt16 = QMetaType::Short,
        ParamUint16 = QMetaType::UShort,
        ParamFloat = QMetaType::Float,
    };
public:
    explicit ParametersMgr(QObject *parent = NULL);
    void LoadParameters(const QDomElement &ele);

    QStringList GetGroups()const;
    QVariant stringToVariant(const QString &id, const QString &val)const;
    QVariant getValue(const QString &id, int index)const;
    int getVarIndex(const QString &id, const QVariant &val)const;

    QString getStrValue(const QString &id, QVariant key);
    QString GetGroup(const QString &id)const;
    QStringList GetAllInSameGroup(const QString &id)const;
    QStringList GetLables()const;
    void ParameterAdd(const QString &id);

    Q_INVOKABLE bool isParamReadonly(const QString &id)const;
    bool hasParam(const QString &id, const QString &group = QString())const;
    Q_INVOKABLE QStringList getParams(const QString &group)const;
    static QString typeName(const QVariant &v);
    static QVariant typProp(const QVariant &v);
    void SetParasModel(ParamtersModel *m);
    bool IsShowParam(const QString &paramID)const;
protected:
    Q_INVOKABLE ParamType getType(const QString &id)const;
    Q_INVOKABLE QString getName(const QString &id)const;
    Q_INVOKABLE bool isScope(const QString &id)const;
    Q_INVOKABLE QString getLeast(const QString &id)const;
    Q_INVOKABLE QString getBiggest(const QString &id)const;
    Q_INVOKABLE QStringList getDscribes(const QString &id)const;

    ParamtersModel *GetParasModel()const;
    QString GetButton()const;
    void SetButton(const QString &str);
    QString GetSearch()const;
    void SetSearch(const QString &str);
private:
    void parseParameterLimit(const QDomElement &e);
    ParaLimitAbs *_getParemeterLimit(const QString &id, const QString &group = QString())const;
    void _addLabel(const QString &lab);
signals:
    void labelsChanged();
    void parasChanged();
    void buttonChanged(const QString &button);
    void searchChanged();
private:
    QMap <QString, QList<ParaLimitAbs*> >   m_params;
    QStringList                             m_labels;
    ParamtersModel                          *m_curParams=nullptr;
    QString                                 m_curButton;
    QString                                 m_search;
};

#endif // __PARAMETER_LIMIT_H__
