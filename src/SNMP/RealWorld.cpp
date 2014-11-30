#include "RealWorld.h"
#include <QXmlStreamReader>
#include <QFile>

#define INTERVAL 1000

RealWorld::RealWorld()
{
    rp = new RouterPool();
    timer = new QTimer(this);
    satellites = new QVector<RealSatellite*>();
    stations = new QVector<RealStation*>();
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
    for(RealSatellite* sat : *satellites)
    {
        sat->setCurInBw(0);
    }
    for(RealStation* station : *stations)
    {
        station->getSatellite()->incCurInBw(station->outBwInUse());
        station->getSatellite()->incCurOutBw(station->inBwInUse());
    }
}

void RealWorld::loadInitData()
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
                satellites->append(new RealSatellite(attrs.value("name").toString(), attrs.value("maxBw").toInt(), attrs.value("maxBw").toInt()));
            if (xml.name() == "station")
            {
                stations->append(new RealStation(attrs.value(("name")).toString(), satellites->last(), QString("192.168.1.1"), 1));
                rp->addRouter(stations->last()->getRouter());
            }
        }
    }
    pFile->close();
    delete pFile;
}
