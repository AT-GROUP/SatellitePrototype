#include "satellite.h"

Satellite::Satellite(QObject* parent)
    :QObject(parent)
{
}

Satellite::Satellite(QString name, QString ipAddress, int maxBw, int curBw, int stationCount, QString status, QObject* parent)
    :QObject(parent)
{
    setName(name);
    setStatus(status);
    setMaxBw(maxBw);
    setCurBw(curBw);
    setIpAddress(ipAddress);
    setStationCount(stationCount);
}

QString Satellite::name() const
{
    return name_;
}

QString Satellite::status() const
{
    return status_;
}

int Satellite::maxBw() const
{
    return maxBw_;
}

int Satellite::curBw() const
{
    return curBw_;
}

int Satellite::avalBw() const
{
    return maxBw_ - curBw_;
}

int Satellite::stationCount() const
{
    return stationCount_;
}

QString Satellite::ipAddress() const
{
    return ipAddress_;
}

void Satellite::setName(QString newName)
{
    name_ = newName;
}

void Satellite::setMaxBw(int newMaxBw)
{
    maxBw_ = newMaxBw;
}

void Satellite::setCurBw(int newCurBw)
{
    curBw_ = newCurBw;
}

void Satellite::setIpAddress(QString newIpAddress)
{
    ipAddress_ = newIpAddress;
}

void Satellite::setStationCount(int newStationCount)
{
    stationCount_ = newStationCount;
}

void Satellite::setStatus(QString newStatus)
{
    status_ = newStatus;
}
