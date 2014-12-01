#include "RealStation.h"

RealStation::RealStation(QString name, RealSatellite *sat, SnmpRouter *router) : router(router), name(name), sat(sat)
{
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
