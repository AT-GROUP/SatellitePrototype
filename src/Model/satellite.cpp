#include "satellite.h"

Satellite::Satellite(QString name, int maxBw, QPair<int,int> pos, QString ipAddress, int curBw, int stationCount, QString status, QObject* parent)
    :QObject(parent)
{
    setName(name);
    setStatus(status);
    maxBw_ = maxBw;
    curBw_ = curBw;
    setIpAddress(ipAddress);
    setStationCount(stationCount);
    pos_ = new QPointF(pos.first, pos.second);
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
    emit attrChanged(QPair<QString,QString>("Name",name_));
}

void Satellite::setMaxBw(int newMaxBw)
{
    maxBw_ = newMaxBw;
    emit attrChanged(QPair<QString,QString>("MaxBw",QString::number(maxBw_)));
}

void Satellite::setCurBw(int newCurBw)
{
    curBw_ = newCurBw;
    emit attrChanged(QPair<QString,QString>("CurBw",QString::number(curBw_)));
}

void Satellite::setIpAddress(QString newIpAddress)
{
    ipAddress_ = newIpAddress;
    emit attrChanged(QPair<QString,QString>("IpAddress",ipAddress_));
}

void Satellite::setStationCount(int newStationCount)
{
    stationCount_ = newStationCount;
    emit attrChanged(QPair<QString,QString>("StationCount",QString::number(stationCount_)));
}

void Satellite::setStatus(QString newStatus)
{
    status_ = newStatus;
    emit attrChanged(QPair<QString,QString>("Status",status_));
}

QPointF * Satellite::pos() const
{
    return pos_;
}

void Satellite::refreshData()
{
    emit attrChanged(QPair<QString,QString>("Name",name_));
    emit attrChanged(QPair<QString,QString>("IpAddress",ipAddress_));
    emit attrChanged(QPair<QString,QString>("MaxBw",QString::number(maxBw_)));
    emit attrChanged(QPair<QString,QString>("CurBw",QString::number(curBw_)));
    emit attrChanged(QPair<QString,QString>("StationCount",QString::number(stationCount_)));
    emit attrChanged(QPair<QString,QString>("Status",status_));
}
