#ifndef __PARAMETER_LIMIT_H__
#define __PARAMETER_LIMIT_H__

#include <QVariant>
#include <QString>
#include <QPair>
#include <QList>
#include <QMetaType>

class QDomElement;
class ParaLimitAbs {
    Q_GADGET
    Q_ENUMS(ParamType)
    Q_PROPERTY(QString name READ GetName WRITE SetName)
    Q_PROPERTY(bool readOnly READ IsReadOnly WRITE SetReadOnly)
    Q_PROPERTY(QStringList describe READ GetDescribes)
    Q_PROPERTY(QVariant value READ GetValue)
public:
    enum ParamType {
        ParamUnknow = QVariant::Invalid,
        ParamBool = QVariant::Bool,
        ParamInt = QVariant::Int,
        ParamUInt = QVariant::UInt,
        ParamFloat = QVariant::Double,
    };
    enum ParamStat{
        Normal,
        Base16,
        IPType,
        Readonly = 1<<4,
        Stict = Readonly<<1,
        ListVal = Stict<<1,
    };
    typedef QPair<QVariant, QString> ValuePair;
public:
    ParaLimitAbs();
    virtual~ParaLimitAbs() {}

    QString GetId()const;
    void SetId(const QString &id);
    QString GetName()const;
    void SetName(const QString &str);
    void SetScope(bool b);
    bool IsScope()const;
    void SetReadOnly(bool b);
    bool IsReadOnly()const;
    void SetStrict(bool b);
    bool IsStrict()const;
    int GetShowType()const;
    void AddValue(const QVariant &val, const QString &describe = QString());

    QStringList GetDescribes()const;
    bool IsInScope(const QVariant &val)const;
    QVariant GetValue(int idx)const;
    virtual int GetType()const = 0;
    virtual int GetPropertyIndex(const QVariant &val)const = 0;
    void ParseContent(const QDomElement &e);
    void SetBiggest(const QVariant &val);
    QVariant GetBiggest()const;
    void SetLeast(const QVariant &v);
    QVariant Getleast()const;
public:
    QString ValueToString(const QVariant &val);
    QVariant ValueFromString(const QString &str);
protected:
    void setShowType(int tp);
    void parseShowType(const QString &s);
    int GetIndexOf(const QVariant &val)const;
protected:
    uint32_t                m_stat;
    QString                 m_id;
    QString                 m_name;
    QList<ValuePair>        m_vCanValues;
};

template<class T>
class ParameterLimit : public ParaLimitAbs {
public:
    ParameterLimit() : ParaLimitAbs(){ }
    int GetType()const
    {
        return qMetaTypeId<T>();
    }
    int GetPropertyIndex(const QVariant &val)const
    {
        if (IsScope() || m_vCanValues.size() < 1 || val.type() != GetType())
            return -1;

        if (!IsStrict())
            return GetIndexOf(val);

        QList<ValuePair>::const_iterator itr = m_vCanValues.begin();
        T v = val.value<T>();
        T last = itr->first.value<T>();
        if (v <= last)
            return 0;
        itr++;
        for (int i = 1; itr != m_vCanValues.end(); ++i, ++itr)
        {
            T tmp = itr->first.value<T>();
            if (v <= (tmp + last) / 2)
                return i - 1;
            last = tmp;
        }

        return m_vCanValues.size() - 1;
    }
};
typedef ParameterLimit<float> ParameterFloat;
typedef ParameterLimit<int> ParameterInt;
typedef ParameterLimit<uint32_t> ParameterU32;

Q_DECLARE_METATYPE(ParameterFloat)
Q_DECLARE_METATYPE(ParameterInt)
Q_DECLARE_METATYPE(ParameterU32)
#endif // __PARAMETER_LIMIT_H__
