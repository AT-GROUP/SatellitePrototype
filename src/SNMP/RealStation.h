#ifndef REALSTATION_H
#define REALSTATION_H

#include "SnmpRouter.h"
#include "RealSatellite.h"
#include <QString>

class RealStation
{
private:
    SnmpRouter* router;
    QString name;
    RealSatellite* sat;
public:
    RealStation(QString name, RealSatellite* sat, SnmpRouter* router);
    int inBwInUse();
    int outBwInUse();
    //int bwInUse();
    SnmpRouter* getRouter();
    RealSatellite* getSatellite();
};

#endif // REALSTATION_H
