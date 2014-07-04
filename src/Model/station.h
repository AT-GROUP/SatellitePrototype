#ifndef STATION_H
#define STATION_H

#include <QObject>
#include "satellite.h"
#include <QPointF>

class Station : public QObject
{
    Q_OBJECT
    public:
        Station(QString name, Satellite *satellite, QPair<int,int> pos,
                QString ipAddress = "192.168.1.1", int bwNeeded = 0, int bwInUse = 0,
                QString status = "Offline", QObject* parent = 0);

        QString name() const;
        QString ipAddress() const;
        int bwNeeded() const;
        int bwInUse() const;
        Satellite* satellite() const;
        QString status() const;
        QPointF* pos() const;

        void setName(QString newName);
        void setBwNeeded(int newBwNeeded);
        void setBwInUse(int newBwInUse);
        void setIpAddress(QString newIpAddress);
        void setSatellite(Satellite *newSatellite);
        void setStatus(QString newStatus);
    private:
        QString name_;
        QString status_;
        int bwNeeded_;
        int bwInUse_;
        QString ipAddress_;
        Satellite *satellite_;
        QPointF *pos_;
};

#endif // STATION_H
