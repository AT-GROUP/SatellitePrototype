#ifndef MODEL_H
#define MODEL_H

#include <QVector>
#include "satellite.h"
#include "station.h"

class Model
{
    public:
        Model();
        QVector<Station*>* stationList() const;
        QVector<Satellite*>* satelliteList() const;
    private:
        QVector<Station*> *pStationList;
        QVector<Satellite*> *pSatelliteList;
        void loadInitState();
};

#endif // MODEL_H
