#ifndef SATELLITE_H
#define SATELLITE_H

#include <QObject>

class Satellite : public QObject
{
    public:
        Satellite(QObject* parent = 0);
        Satellite(QString name, QString ipAddress = "192.168.1.1",
                  int maxBw = 0, int curBw = 0, int stationCount = 0,
                  QString status = "Offline", QObject* parent = 0);

        QString name() const;
        QString ipAddress() const;
        int maxBw() const;
        int curBw() const;
        int avalBw() const;
        int stationCount() const;
        QString status() const;

        void setName(QString newName);
        void setIpAddress(QString newIpAddress);
        void setMaxBw(int newMaxBw);
        void setCurBw(int newCurBw);
        void setStationCount(int newStationCount);
        void setStatus(QString newStatus);
    private:
        QString name_;
        QString ipAddress_;
        int maxBw_;
        int curBw_;
        int stationCount_;
        QString status_;
};

#endif // SATELLITE_H
