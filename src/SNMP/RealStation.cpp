#include "RealStation.h"

RealStation::RealStation(QString name, RealSatellite *sat, QString ip, int interface = 1) : name(name), sat(sat)
{
    router = new SnmpRouter(ip);
    router->selectInterface(interface);
}

int RealStation::inBwInUse()
{
    return router->getInBw();
}

int RealStation::outBwInUse()
{
    return router->getOutBw();
}

SnmpRouter* RealStation::getRouter()
{
    return router;
}

RealSatellite* RealStation::getSatellite()
{
    return sat;
}
