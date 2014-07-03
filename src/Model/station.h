#ifndef STATION_H
#define STATION_H

#include <QObject>

class Station : public QObject
{
    Q_OBJECT
    public:
        Station(QObject* parent = 0);
        Station(QString name, QString ipAddress = "192.168.1.1", int bwNeeded = 0,
                int bwInUse = 0, QString satellite = "N/A", QString status = "Offline",
                QObject* parent = 0);

        QString name() const;
        QString ipAddress() const;
        int bwNeeded() const;
        int bwInUse() const;
        QString satellite() const;
        QString status() const;

        void setName(QString newName);
        void setBwNeeded(int newBwNeeded);
        void setBwInUse(int newBwInUse);
        void setIpAddress(QString newIpAddress);
        void setSatellite(QString newSatellite);
        void setStatus(QString newStatus);
    private:
        QString name_;
        QString status_;
        int bwNeeded_;
        int bwInUse_;
        QString ipAddress_;
        QString satellite_;
};

#endif // STATION_H
