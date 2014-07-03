#include "model.h"

Model::Model()
{
    pSatelliteList = new QVector<Satellite*>();
    pStationList = new QVector<Station*>();
}

QVector<Station*>* Model::stationList() const
{
    return pStationList;
}

QVector<Satellite*>* Model::satelliteList() const
{
    return pSatelliteList;
}

void Model::loadInitState ()
{

}
