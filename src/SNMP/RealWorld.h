#ifndef REALWORLD_H
#define REALWORLD_H

#include "RouterPool.h"
#include "RealStation.h"
#include "RealSatellite.h"
#include <vector>

class RealWorld : public QObject
{
    Q_OBJECT
private:
    QTimer* timer;
    RouterPool* rp;
    vector<RealSatellite*> satellites;
    vector<RealStation*> stations;
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
