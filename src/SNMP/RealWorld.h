#ifndef REALWORLD_H
#define REALWORLD_H

#include "RouterPool.h"
#include "RealStation.h"
#include "RealSatellite.h"
#include <QVector>

class RealWorld : public QObject
{
    Q_OBJECT
private:
    QTimer* timer;
    RouterPool* rp;
    QVector<RealSatellite*>* satellites;
    QVector<RealStation*>* stations;
    void loadInitData();
public:
    RealWorld();
    void start();
    void stop();
public slots:
    void update();
signals:
};

#endif // REALWORLD_H
