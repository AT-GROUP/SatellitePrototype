#ifndef MODEL_H
#define MODEL_H

#include <QVector>
#include "satellite.h"
#include "station.h"
#include <QTime>

class Model
{
    public:
        Model();
        ~Model();
        QVector<Station*>* stationList() const;
        QVector<Satellite*>* satelliteList() const;
        void processModelTact();
    private:
        QVector<Station*> *pStationList;
        QVector<Satellite*> *pSatelliteList;
        int tact;
        bool critHours;
        void loadInitState();

        void phase0();
        void phase1();
        void phase2();
        void phase3();



        /*
            Пока что не используется
            QTime *pTime;
            QTime *pBeginCritTime;
            QTime *pEndCritTime;
        */
};

#endif // MODEL_H
