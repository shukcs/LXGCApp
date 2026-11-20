/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/
#ifndef APMCompassCal_H
#define APMCompassCal_H

#include <QObject>
#include <QThread>
#include "mavlink.h"

typedef struct __mavlink_message mavlink_message_t;
class VGPlantInformation;
class CalWorkerThread;
class VGVehicle;
// Used to calibrate APM Stack compass by simulating PX4 Flight Stack firmware compass cal
// on the ground station side of things.
class APMCompassCal : public QObject
{
    Q_OBJECT
    
public:
    APMCompassCal();
    ~APMCompassCal();

    void startCalibration(VGPlantInformation *v);
    void cancelCalibration(void);
protected:
    void prcsMavlink(VGVehicle *v, const mavlink_message_t &message);
signals:
    void vehicleTextMessage(const QString &, int, const QString &);
private:
    void _handleMavlinkRawImu(const mavlink_message_t &message);
    void _handleMavlinkScaledImu2(const mavlink_message_t &message);
    void _handleMavlinkScaledImu3(const mavlink_message_t &message);

private:
    void _setSensorTransmissionSpeed(bool fast);
    void _stopCalibration(void);
    void _emitVehicleTextMessage(const QString& message);

    VGPlantInformation  *_vehicle;
    CalWorkerThread*    _calWorkerThread;
    float               _rgSavedCompassOffsets[3][3];
};

#endif

