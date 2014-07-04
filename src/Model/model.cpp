#include "model.h"
#include <QFile>
#include <QXmlStreamReader>

Model::Model()
{
    pSatelliteList = new QVector<Satellite*>();
    pStationList = new QVector<Station*>();
    loadInitState();
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
}
