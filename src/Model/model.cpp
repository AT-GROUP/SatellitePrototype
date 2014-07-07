#include "model.h"
#include <QFile>
#include <QXmlStreamReader>

Model::Model()
{
    pSatelliteList = new QVector<Satellite*>();
    pStationList = new QVector<Station*>();
    tact = 0;
    loadInitState();
}
Model::~Model()
{
    delete pSatelliteList;
    delete pStationList;
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
    QFile* pFile = new QFile("init.xml");
    if (!pFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QXmlStreamReader xml(pFile);
    while ((!xml.atEnd()) && (!xml.hasError()))
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement)
        {
            QXmlStreamAttributes attrs = xml.attributes();
            if (xml.name() == "satellite")
                pSatelliteList->append(new Satellite(attrs.value("name").toString(),attrs.value("maxBw").toInt(),
                                                 QPair<int,int>(attrs.value("posX").toInt(),attrs.value("posY").toInt())));
            if (xml.name() == "station")
                pStationList->append(new Station(attrs.value("name").toString(),pSatelliteList->last(),
                                                 QPair<int,int>(attrs.value("posX").toInt(),attrs.value("posY").toInt())));
        }
    }
    pFile->close();
    delete pFile;
}

void Model::processModelTact()
{
    tact++;
    if (tact % 9 == 0) phase0 ();
    phase1();
    phase2();
    phase3();
}

void Model::phase0()
{
    if (critHours)
    {
        critHours = false;
        for (QVector<Station*>::iterator it = pStationList->begin(); it != pStationList->end(); it++)
            (*it)->setStatus("Online");
    }
    else
    {
        critHours = true;
        for (QVector<Station*>::iterator it = pStationList->begin(); it != pStationList->end(); it++)
            (*it)->setStatus("Calling");
    }
}

void Model::phase1()
{
    for (QVector<Satellite*>::iterator it = pSatelliteList->begin(); it != pSatelliteList->end(); it++)
    {
        if ((*it)->status() == "Offline") continue;
        (*it)->setCurBw((*it)->maxBw());
        (*it)->setStatus("Online");/*
        if ((*it)->maxBw()/((*it)->stationCount()+1) >= 512)
        {
            (*it)->setvalBw() = 512;
        }
        if ((*it)->maxBw()/((*it)->stationCount()+1) >= 384)
        {
            (*it)->avalBw() = 384;
        }
        if ((*it)->maxBw/((*it)->stationCount+1) >= 256)
        {
            (*it)->avalBw = 256;
        }
        if ((*it)->maxBw/((*it)->stationCount+1) < 256)
        {
            (*it)->avalBw = 256;
            (*it)->status = "Overload";
        }*/
        (*it)->setStationCount(0);
    }
}

void Model::phase2()
{
    for (QVector<Station*>::iterator it = pStationList->begin(); it != pStationList->end(); it++)
    {
        if ((*it)->status() == "Online") (*it)->setBwNeeded(random()%5);
        if ((*it)->status() == "Offline")
        {
            (*it)->setBwNeeded(0);
            return;
        }
        if ((*it)->status() == "Calling") (*it)->setBwNeeded(512);
        if ((*it)->status() == "StandBy") (*it)->setBwNeeded(512);
        if ((*it)->status() == "Connected") (*it)->setBwNeeded(512);
        (*it)->satellite()->setStationCount((*it)->satellite()->stationCount()+1);
    }
}

void Model::phase3()
{
    for (QVector<Station*>::iterator it = pStationList->begin(); it != pStationList->end(); it++)
    {
        if ((*it)->status() == "Online")
        {
            (*it)->setBwInUse((*it)->bwNeeded());
        }
        if ((*it)->status() == "Offline") (*it)->setBwInUse(0);
        if ((*it)->status() == "Calling")
        {
            if ((*it)->satellite()->curBw() > 256)
            {
                (*it)->setStatus("Connected");
            }
            else
            {
                (*it)->setStatus("StandBy");
            }
        }
        if ((*it)->status() == "StandBy")
        {
            (*it)->setBwInUse(0);
            if ((*it)->satellite()->curBw() > 256)
            {
                (*it)->setStatus("Connected");
            }
        }
        if ((*it)->status() == "Connected")
        {
            (*it)->setBwNeeded(512);
            (*it)->setBwInUse(256);
        }
    }
}
