#include "station.h"


Station::Station(QString name, Satellite* satellite, QPair<int,int> pos, QString ipAddress, int bwNeeded, int bwInUse, QString status, QObject* parent)
    :QObject(parent)
{
    setName(name);
    setSatellite(satellite);
    setStatus(status);
    setBwInUse(bwInUse);
    setBwNeeded(bwNeeded);
    setIpAddress(ipAddress);
    pos_ = new QPointF(pos.first, pos.second);
}

QString Station::name() const
{
    return name_;
}

QString Station::status() const
{
    return status_;
}

int Station::bwNeeded() const
{
    return bwNeeded_;
}

int Station::bwInUse() const
{
    return bwInUse_;
}

QString Station::ipAddress() const
{
    return ipAddress_;
}
Satellite * Station::satellite() const
{
    return satellite_;
}

void Station::setName(QString newName)
{
    name_ = newName;
}

void Station::setBwNeeded(int newBwNeeded)
{
    bwNeeded_ = newBwNeeded;
}

void Station::setBwInUse(int newBwInUse)
{
    bwInUse_ = newBwInUse;
}

void Station::setIpAddress(QString newIpAddress)
{
    ipAddress_ = newIpAddress;
}

void Station::setSatellite(Satellite *newSatellite)
{
    satellite_ = newSatellite;
}

void Station::setStatus(QString newStatus)
{
    status_ = newStatus;
}

QPointF * Station::pos() const
{
    return pos_;
}
