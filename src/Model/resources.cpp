#include "resources.h"

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

QString Station::getName() const {return name;}
QString Station::getStatus() const {return status;}
int Station::getBwNeeded() const {return bwNeeded;}
int Station::getBwInUse() const {return bwInUse;}
QString Station::getIpAddress() const {return ipAddress;}
QString Station::getSatellite() const {return satellite;}

void Station::setName(QString newName) {name = newName;}
void Station::setBwNeeded(int newBwNeeded) {bwNeeded = newBwNeeded;}
void Station::setBwInUse(int newBwInUse) {bwInUse = newBwInUse;}
void Station::setIpAddress(QString newIpAddress) {ipAddress = newIpAddress;}
void Station::setSatellite(QString newSatellite) {satellite = newSatellite;}
void Station::setStatus(QString newStatus) {status = newStatus;}

Satellite::Satellite(QObject* parent)
{
    Q_UNUSED(parent);
}

Satellite::Satellite(QString name, QString status, int maxBw, int curBw, QString ipAddress, int stationCount, QObject* parent)
{
    Q_UNUSED(parent);
    setName(name);
    setStatus(status);
    setMaxBw(maxBw);
    setCurBw(curBw);
    setIpAddress(ipAddress);
    setStationCount(stationCount);
}

QString Satellite::getName() const {return name;}
QString Satellite::getStatus() const {return status;}
int Satellite::getMaxBw() const {return maxBw;}
int Satellite::getCurBw() const {return curBw;}
int Satellite::getAvalBw() const {return maxBw - curBw;}
int Satellite::getStationCount() const {return stationCount;}
QString Satellite::getIpAddress() const {return ipAddress;}

void Satellite::setName(QString newName) {name = newName;}
void Satellite::setMaxBw(int newMaxBw) {maxBw = newMaxBw;}
void Satellite::setCurBw(int newCurBw) {curBw = newCurBw;}
void Satellite::setIpAddress(QString newIpAddress) {ipAddress = newIpAddress;}
void Satellite::setStationCount(int newStationCount) {stationCount = newStationCount;}
void Satellite::setStatus(QString newStatus) {status = newStatus;}
