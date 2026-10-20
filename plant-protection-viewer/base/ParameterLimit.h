#ifndef __PARAMETER_LIMIT_H__
#define __PARAMETER_LIMIT_H__

#include <QVariant>
#include <QString>
#include <QPair>
#include <QList>
#include <QMetaType>

class QDomElement;
class ParaLimitAbs
{
public:
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
    Q_INVOKABLE bool IsInScope(const QVariant &val)const;
    QVariant GetValue(int idx)const;
    void ParseContent(const QDomElement &e);
    void SetBiggest(const QVariant &val);
    QVariant GetBiggest()const;
    void SetLeast(const QVariant &v);
    QVariant Getleast()const;
    virtual int GetType()const = 0;
    virtual int GetPropertyIndex(const QVariant &val)const = 0;
    static QVariant ValueFromString(const QString &val, int tp);
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
    int GetType()const override
    {
        return qMetaTypeId<T>();
    }
    int GetPropertyIndex(const QVariant &val)const override
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
typedef ParameterLimit<long> ParameterI32;
typedef ParameterLimit<uint32_t> ParameterU32;
typedef ParameterLimit<short> ParameterI16;
typedef ParameterLimit<unsigned short> ParameterU16;
typedef ParameterLimit<int8_t> ParameterI8;
typedef ParameterLimit<uint8_t> ParameterU8;
#endif // __PARAMETER_LIMIT_H__
