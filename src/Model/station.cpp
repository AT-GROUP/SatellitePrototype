#include "station.h"

Station::Station(QObject* parent)
{
    Q_UNUSED(parent);
}

Station::Station(QString name, QString status, int bwNeeded, int bwInUse, QString ipAddress, QString satellite, QObject* parent)
{
    Q_UNUSED(parent);
    setName(name);
    setStatus(status);
    setBwInUse(bwInUse);
    setBwNeeded(bwNeeded);
    setIpAddress(ipAddress);
    setSatellite(satellite);
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
QString Station::satellite() const
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

void Station::setSatellite(QString newSatellite)
{
    satellite_ = newSatellite;
}

void Station::setStatus(QString newStatus)
{
    status_ = newStatus;
}
