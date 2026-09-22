/*=====================================================================
 
 QGroundControl Open Source Ground Control Station
 
 (c) 2009 - 2015 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 
 This file is part of the QGROUNDCONTROL project
 
 QGROUNDCONTROL is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 QGROUNDCONTROL is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with QGROUNDCONTROL. If not, see <http://www.gnu.org/licenses/>.
 
 ======================================================================*/

#ifndef SerialPortInfo_H
#define SerialPortInfo_H

#include "vgcomm_global.h"
#include <QLoggingCategory>

#ifdef __android__
    #include "qserialportinfo.h"
#else
    #include <QSerialPortInfo>
#endif


Q_DECLARE_LOGGING_CATEGORY(SerialPortInfoLog)

/// QGC's version of Qt QSerialPortInfo. It provides additional information about board types
/// that QGC cares about.
class VGCOMMSHARED_EXPORT SerialPortInfo : public QSerialPortInfo
{
public:
    typedef enum {
        BoardTypePX4FMUV1,
        BoardTypePX4FMUV2,
        BoardTypePX4FMUV4,
        BoardTypePixhawk,
        BoardTypePX4Flow,
        BoardTypeOpenPilot,
        BoardTypeRTKGPS,
        BoardTypeSiKRadio,
        BoardTypeUBloxGPS,      ///ÒÆ¶¯GPS
        BoardTypeUnknown,
    } BoardType_t;

    SerialPortInfo(void);
    SerialPortInfo(const QSerialPort & port);

    /// Override of QSerialPortInfo::availablePorts
    static QList<SerialPortInfo> availablePorts(void);

    BoardType_t boardType(void) const;

    /// @return true: board is a Pixhawk board
    bool boardTypePixhawk(void) const;

    /// @return true: Board is currently in bootloader
    bool isBootloader(void) const;

#ifndef __android__
	// Added by qianyong of VIGA
	bool boardTypeGPS(void) const;
	int gpsType(void) const;
#endif
private:
    static BoardType_t _boardClassStringToType(const QString& boardClass);
    static void _loadJsonData();
};

#endif
