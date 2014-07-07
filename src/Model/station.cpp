#include "station.h"


Station::Station(QString name, Satellite* satellite, QPair<int,int> pos, QString ipAddress, int bwNeeded, int bwInUse, QString status, QObject* parent)
    :QObject(parent)
{
    setName(name);
    setSatellite(satellite);
    setStatus(status);
    bwNeeded_ = bwNeeded;
    bwInUse_ = bwInUse;
    setIpAddress(ipAddress);
    callChance = 2;
    failureChance = 1;
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
    emit attrChanged(QPair<QString,QString>("Name",name_));
}

void Station::setBwNeeded(int newBwNeeded)
{
    bwNeeded_ = newBwNeeded;
    emit attrChanged(QPair<QString,QString>("BwNeeded",QString::number(bwNeeded_)));
}

void Station::setBwInUse(int newBwInUse)
{
    satellite_->setCurBw(satellite_->curBw() - bwInUse_ + newBwInUse);
    bwInUse_ = newBwInUse;
    emit attrChanged(QPair<QString,QString>("BwInUse",QString::number(bwInUse_)));
}

void Station::setIpAddress(QString newIpAddress)
{
    ipAddress_ = newIpAddress;
    emit attrChanged(QPair<QString,QString>("IpAddress",ipAddress_));
}

void Station::setSatellite(Satellite *newSatellite)
{
    satellite_ = newSatellite;
    emit attrChanged(QPair<QString,QString>("Satellite",satellite_->name()));
}

void Station::setStatus(QString newStatus)
{
    status_ = newStatus;
    if (status_ == "Offline")
    {
        setBwNeeded(0);
        return;
    }
    if (status_ == "Online") setBwNeeded(5);
    if (status_ == "Calling") setBwNeeded(512);
    if (status_ == "Stand_by") setBwNeeded(512);
    if (status_ == "Connected") setBwNeeded(512);
    emit attrChanged(QPair<QString,QString>("Status",status_));
}

QPointF * Station::pos() const
{
    return pos_;
}

void Station::refreshData()
{
    emit attrChanged(QPair<QString,QString>("Name",name_));
    emit attrChanged(QPair<QString,QString>("IpAddress",ipAddress_));
    emit attrChanged(QPair<QString,QString>("BwNeeded",QString::number(bwNeeded_)));
    emit attrChanged(QPair<QString,QString>("BwInUse",QString::number(bwInUse_)));
    emit attrChanged(QPair<QString,QString>("Satellite",satellite_->name()));
    emit attrChanged(QPair<QString,QString>("Status",status_));
}
