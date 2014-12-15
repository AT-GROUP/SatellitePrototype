#include "RealWorld.h"
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include <iostream>

#define INTERVAL 1000

RealWorld::RealWorld()
{
    rp = new RouterPool();
    timer = new QTimer(this);
    satellites = vector<RealSatellite*>();
    stations = vector<RealStation*>();
    loadInitData();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

void RealWorld::start()
{
    timer->start(INTERVAL);
}

void RealWorld::stop()
{
    timer->stop();
}

void RealWorld::update()
{
    rp->updateRouters();
    for(RealSatellite* sat : satellites)
    {
        sat->setCurInBw(0);
    }
    for(RealStation* station : stations)
    {
        station->getSatellite()->incCurInBw(station->outBwInUse());
        station->getSatellite()->incCurOutBw(station->inBwInUse());
    }
    qDebug() << "Satellite " << satellites.front()->name() << " : " << satellites.front()->curInBw() << ", " << satellites.front()->curOutBw();
    qDebug() << "Satellite " << satellites.back()->name() << " : " << satellites.back()->curInBw() << ", " << satellites.back()->curOutBw();
}

void RealWorld::loadInitData()
{
    QFile* pFile = new QFile("init2.xml");
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
                satellites.push_back(new RealSatellite(attrs.value("name").toString(), attrs.value("maxBw").toInt(), attrs.value("maxBw").toInt()));
            if (xml.name() == "station")
            {
                QString s = attrs.value("ip").toString();
                SnmpRouter* r = new SnmpRouter(s);
                r->selectInterface(0);
                rp->addRouter(r);
                stations.push_back(new RealStation(attrs.value(("name")).toString(), satellites.back(), r));
            }
        }
    }
    pFile->close();
    delete pFile;
}
