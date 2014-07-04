#include "QSatelliteItem.h"
#include "InfoTableModel.h"
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QHeaderView>
#include <tuple>

QSatelliteItem::QSatelliteItem(Satellite *satellite, QObject *parent)
    :QObject(parent),QGraphicsItemGroup()
{
    icon = new QGraphicsPixmapItem(QPixmap(":satellite"));
	addToGroup(icon);
    pSatellite = satellite;

    setPos(*pSatellite->pos());
    setAcceptHoverEvents(true);
    icon->setVisible (true);

    QString n = pSatellite->name();

    pInfoList = new QTableView();
    pInfoList->setModel(new InfoTableModel(n));
    pInfoList->setAutoScroll (false);
    pInfoList->horizontalHeader()->hide();
    pInfoList->verticalHeader()->hide();

    updateFact(std::make_tuple(n, "name", pSatellite->name()));
    updateFact(std::make_tuple(n, "ipAddress", pSatellite->ipAddress()));
    updateFact(std::make_tuple(n, "maxBw",  QString::number(pSatellite->maxBw())));
    updateFact(std::make_tuple(n, "curBw", QString::number(pSatellite->curBw())));
    updateFact(std::make_tuple(n, "stationCount", QString::number(pSatellite->stationCount())));
    updateFact(std::make_tuple(n, "status", pSatellite->status()));
}

QSatelliteItem::~QSatelliteItem()
{
	delete icon;
    delete pInfoList;
}

void QSatelliteItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (acceptHoverEvents())
    {
        setAcceptHoverEvents(false);
        event->accept();
        return;
    }
    setAcceptHoverEvents(true);
    event->accept();
}

void QSatelliteItem::hoverEnterEvent (QGraphicsSceneHoverEvent *event)
{
   // ToDo: Fix warning "QGraphicsProxyWidget::setWidget: cannot embed widget *XXXXX; already embedded"
   proxy = icon->scene()->addWidget(pInfoList);
   proxy->setPos(event->scenePos());
   proxy->resize (190,190);

   pInfoList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   pInfoList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   pInfoList->show();

   event->accept();
}

void QSatelliteItem::hoverLeaveEvent (QGraphicsSceneHoverEvent *event)
{    
    pInfoList->hide();
    event->accept();
}

void QSatelliteItem::updateFact(std::tuple<QString, QString, QString> info)
{
	QString satelliteName, attrName, attrValue;
	std::tie(satelliteName, attrName, attrValue) = info;
    if (satelliteName == pSatellite->name())
	{
        InfoTableModel* tempModel = (InfoTableModel*) pInfoList->model();
        if (attrName == "name")
        {
            pSatellite->setName(attrValue);
            tempModel->updateData(std::make_tuple(0,attrName,attrValue));
        }
		if (attrName == "ipAddress")
        {
            pSatellite->setIpAddress(attrValue);
            tempModel->updateData(std::make_tuple(1,attrName,attrValue));
        }
        if (attrName == "stationCount")
        {
            if (QString::number(pSatellite->stationCount()) != attrValue) emit valueChanged(pSatellite->name() + " " + attrName + " changed to " + attrValue);
            pSatellite->setStationCount(attrValue.toInt());
            tempModel->updateData(std::make_tuple(2,attrName,attrValue));
        }
		if (attrName == "maxBw")
		{
            if (QString::number(pSatellite->maxBw()) != attrValue) emit valueChanged(pSatellite->name() + " " + attrName + " changed to " + attrValue);
            pSatellite->setMaxBw(attrValue.toInt());
            tempModel->updateData(std::make_tuple(3,attrName,attrValue));
		}
        if (attrName == "curBw")
        {
            if (QString::number(pSatellite->curBw()) != attrValue) emit valueChanged(pSatellite->name() + " " + attrName + " changed to " + attrValue);
            pSatellite->setCurBw(attrValue.toInt());
            tempModel->updateData(std::make_tuple(4,attrName,attrValue));
        }
		if (attrName == "status")
		{
            if (pSatellite->status() != attrValue) emit valueChanged(pSatellite->name() + " " + attrName + " changed to " + attrValue);
            pSatellite->setStatus(attrValue);
            tempModel->updateData(std::make_tuple(5,attrName,attrValue));
		}
	}
}

Satellite * QSatelliteItem::satellite() const
{
    return pSatellite;
}
