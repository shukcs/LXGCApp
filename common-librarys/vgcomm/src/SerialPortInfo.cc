#include "SerialPortInfo.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

typedef struct {
    int                         vendorId;
    int                         productId;
    SerialPortInfo::BoardType_t boardType;
    QString                     name;
} BoardInfo_t;

typedef struct {
    QString                     regExp;
    SerialPortInfo::BoardType_t boardType;
    bool                        androidOnly;
} BoardRegExpApapt_t;

QList<BoardInfo_t>              s_boardInfoList;
QList<BoardRegExpApapt_t>        s_boardAdapts;
SerialPortInfo::SerialPortInfo(void) :
    QSerialPortInfo()
{
}

SerialPortInfo::SerialPortInfo(const QSerialPort &port) :
    QSerialPortInfo(port)
{
}

SerialPortInfo::BoardType_t SerialPortInfo::boardType() const
{
    if (isNull())
        return BoardTypeUnknown;

    _loadJsonData();

    auto vid = vendorIdentifier();
    auto pid = productIdentifier();
    for (const auto &itr : s_boardInfoList)
    {
        if (itr.vendorId == vid && (itr.productId == pid || pid == 0))
            return itr.boardType;
    }
    auto str = description();
    for (auto itr : s_boardAdapts)
    {
        if (str.contains(QRegExp(itr.regExp, Qt::CaseInsensitive)))
            return itr.boardType;
    }

    return BoardTypeUnknown;
}

QList<SerialPortInfo> SerialPortInfo::availablePorts(void)
{
    QList<SerialPortInfo>    list;

    foreach(QSerialPortInfo portInfo, QSerialPortInfo::availablePorts()) {
        list << *((SerialPortInfo*)&portInfo);
    }

    return list;
}

bool SerialPortInfo::boardTypePixhawk(void) const
{
    BoardType_t boardType = this->boardType();

    return boardType == BoardTypePX4FMUV1 || boardType == BoardTypePX4FMUV2 || boardType == BoardTypePX4FMUV4 || boardType == BoardTypePixhawk;
}

bool SerialPortInfo::isBootloader(void) const
{
    // FIXME: Check SerialLink bootloade detect code which is different
    return boardTypePixhawk() && description().contains("BL");
}

#ifndef __android__
// Added by qianyong of VIGA
bool SerialPortInfo::boardTypeGPS(void) const
{
    BoardType_t boardType = this->boardType();

	return boardType == BoardTypeUBloxGPS;
}

// Added by qianyong of VIGA
// 0-others,1-ublox,...
int SerialPortInfo::gpsType(void) const
{
	if (boardType() == BoardTypeUBloxGPS)
		return 1;
	else 
		return 0;
}
#endif

void SerialPortInfo::_loadJsonData()
{
    if (!s_boardInfoList.isEmpty())
        return;

    QFile file(QStringLiteral(":/res/USBBoardInfo.json"));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Unable to open board info json:" << file.errorString();
        return;
    }

    QByteArray  bytes = file.readAll();

    QJsonParseError jsonParseError;
    QJsonDocument   jsonDoc(QJsonDocument::fromJson(bytes, &jsonParseError));
    if (jsonParseError.error != QJsonParseError::NoError) {
        qWarning() << "Unable to parse board info json:" << jsonParseError.errorString();
        return;
    }
    QJsonObject json = jsonDoc.object();

    auto itrVer = json["version"];
    if (itrVer.isNull())
        return;
    auto itrTyep =json["fileType"];
    if (itrTyep.isNull())
        return;
    int version = itrVer.toInt();
    QString typr = itrTyep.toString();
    auto boardInfo = json["boardInfo"];
    if (!boardInfo.isArray())
        return;

    for (auto &itr : boardInfo.toArray())
    {
        auto item = itr.toObject();
        BoardInfo_t boardInfo;
        boardInfo.vendorId = item["vendorID"].toInt();
        boardInfo.productId = item["productID"].toInt();
        boardInfo.name = item["name"].toString();
        boardInfo.boardType = _boardClassStringToType(item["boardClass"].toString());
        s_boardInfoList << boardInfo;
    }
    auto adapt = json.find("boardDescriptionFallback");
    if (!adapt->isArray())
        return;

    for (auto &itr : adapt->toArray())
    {
        auto item = itr.toObject();
        BoardRegExpApapt_t regApapt;
        regApapt.regExp = item["regExp"].toString();
        regApapt.boardType = _boardClassStringToType(item["boardClass"].toString());
        regApapt.androidOnly = item["androidOnly"].toBool();

        s_boardAdapts << regApapt;
    }
}

SerialPortInfo::BoardType_t SerialPortInfo::_boardClassStringToType(const QString& boardClass)
{
    const static QMap<QString, BoardType_t> sStrTypes = {
        { "Pixhawk",   SerialPortInfo::BoardTypePixhawk },
        { "PX4 Flow",  SerialPortInfo::BoardTypePX4Flow },
        { "RTK GPS",   SerialPortInfo::BoardTypeRTKGPS },
        { "SiK Radio", SerialPortInfo::BoardTypeSiKRadio },
        { "OpenPilot", SerialPortInfo::BoardTypeOpenPilot },
    };
    auto itr = sStrTypes.find(boardClass);
    if (itr != sStrTypes.end())
        return itr.value();

    return BoardTypeUnknown;
}
