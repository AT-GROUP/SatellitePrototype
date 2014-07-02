#ifndef RESOURCES_H
#define RESOURCES_H

#include <QObject>

class Station : public QObject
{
    Q_OBJECT
    public:
        Station(QObject* parent = 0);
        Station(QString name, QString status = "Offline",
                int bwNeeded = 0, int bwInUse = 0,
                QString ipAddress = "192.168.1.1", QString satellite = "N/A",
                QObject* parent = 0);

        QString getName() const;
        QString getStatus() const;
        int getBwNeeded() const;
        int getBwInUse() const;
        QString getIpAddress() const;
        QString getSatellite() const;

        void setName(QString newName);
        void setBwNeeded(int newBwNeeded);
        void setBwInUse(int newBwInUse);
        void setIpAddress(QString newIpAddress);
        void setSatellite(QString newSatellite);
        void setStatus(QString newStatus);
    private:
        QString name;
        QString status;
        int bwNeeded;
        int bwInUse;
        QString ipAddress;
        QString satellite;
};

class Satellite : public QObject
{
    public:
        Satellite(QObject* parent = 0);
        Satellite(QString name, QString status = "Offline", int maxBw = 0,
                int curBw = 0, QString ipAddress = "192.168.1.1",
                int stationCount = 0, QObject* parent = 0);

        QString getName() const;
        QString getStatus() const;
        int getMaxBw() const;
        int getCurBw() const;
        int getAvalBw() const;
        QString getIpAddress() const;
        int getStationCount() const;

        void setName(QString newName);
        void setIp(QString newIp);
        void setMaxBw(int newMaxBw);
        void setCurBw(int newCurBw);
        void setIpAddress(QString newIpAddress);
        void setStationCount(int newStationCount);
        void setStatus(QString newStatus);
    private:
        QString name;
        QString ipAddress;
        int maxBw;
        int curBw;
        int stationCount;
        QString status;
};

#endif // RESOURCES_H
