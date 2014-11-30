#ifndef REALWORLD_H
#define REALWORLD_H

#include "RouterPool.h"
#include "RealStation.h"
#include "RealSatellite.h"
#include <QVector>

class RealWorld
{
private:
    RouterPool* rp;
    QVector<RealSatellite*>* satellites;
    QVector<RealStation*>* stations;

public:
    RealWorld();
};

#endif // REALWORLD_H
