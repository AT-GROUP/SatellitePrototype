#include "QStationItem.h"
#include "InfoTableModel.h"
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QHeaderView>
#include <tuple>

QStationItem::QStationItem(qreal x, qreal y, QString n, QObject* parent)
    :QObject(parent),QGraphicsItemGroup()
{
    p_Ellipse = new QGraphicsEllipseItem(QRectF(-5,-5,5,5));
    p_Ellipse->setPen(QColor(Qt::red));
    addToGroup(p_Ellipse);
    setPos(x,y);
    setAcceptHoverEvents(true);

    p_InfoList = new QTableView();
    p_InfoList->setModel(new InfoTableModel(n));
    p_InfoList->setAutoScroll (false);
    p_InfoList->horizontalHeader()->hide();
    p_InfoList->verticalHeader()->hide();

    pStation = new Station(n);

    updateFact(std::make_tuple(n, "name", pStation->name()));
    updateFact(std::make_tuple(n, "ipAddress", pStation->ipAddress()));
    updateFact(std::make_tuple(n, "bwInUse", QString::number(pStation->bwInUse())));
    updateFact(std::make_tuple(n, "bwNeeded", QString::number(pStation->bwNeeded())));
    updateFact(std::make_tuple(n, "satellite", pStation->satellite()));
    updateFact(std::make_tuple(n, "status", pStation->status()));
}

QStationItem::~QStationItem()
{
    delete p_Ellipse;
	delete p_InfoList;
}

void QStationItem::updateColor()
{
    QString status = pStation->status();
    if (status == "Calling")
    {
        setColor(Qt::red);
        return;
    }
    if (status == "StandBy")
    {
        setColor(Qt::yellow);
        return;
    }
    if (status == "Online")
    {
        setColor(Qt::green);
        return;
    }
    if (status == "Offline")
    {
        setColor(Qt::black);
        return;
    }
    if (status == "Connected")
    {
        setColor(Qt::blue);
        return;
    }
    setColor(Qt::transparent);
}

void QStationItem::setColor(QColor qColor)
{
    p_Ellipse->setBrush((QBrush(qColor)));
}

void QStationItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
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

void QStationItem::hoverEnterEvent (QGraphicsSceneHoverEvent *event)
{
   // ToDo: Fix warning "QGraphicsProxyWidget::setWidget: cannot embed widget *XXXXX; already embedded"
   proxy = p_Ellipse->scene()->addWidget(p_InfoList);
   proxy->setPos(event->scenePos());
   proxy->resize (190,190);

   p_InfoList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   p_InfoList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   p_InfoList->show();

   event->accept();
}

void QStationItem::hoverLeaveEvent (QGraphicsSceneHoverEvent *event)
{    
    p_InfoList->hide();
    event->accept();
}

void QStationItem::updateFact(std::tuple<QString, QString, QString> info)
{
	QString stationName, attrName, attrValue;
	std::tie(stationName, attrName, attrValue) = info;
    if (stationName == pStation->name())
	{
        InfoTableModel* tempModel = (InfoTableModel*) p_InfoList->model();
        if (attrName == "name")
        {
            pStation->setName(attrValue);
            tempModel->updateData(std::make_tuple(0,attrName,attrValue));
        }
        if (attrName == "ipAddress")
        {
            pStation->setIpAddress(attrValue);
            tempModel->updateData(std::make_tuple(1,attrName,attrValue));
        }
		if (attrName == "bwInUse")
		{
            if (QString::number(pStation->bwInUse()) != attrValue) emit valueChanged(pStation->name() + " " + attrName + " changed to " + attrValue);
            pStation->setBwInUse(attrValue.toInt());
            tempModel->updateData(std::make_tuple(2,attrName,attrValue));
		}
		if (attrName == "bwNeeded")
		{
            if (QString::number(pStation->bwNeeded()) != attrValue) emit valueChanged(pStation->name() + " " + attrName + " changed to " + attrValue);
            pStation->setBwNeeded(attrValue.toInt());
            tempModel->updateData(std::make_tuple(3,attrName,attrValue));
		}
		if (attrName == "satellite")
        {
            pStation->setSatellite(attrValue);
            tempModel->updateData(std::make_tuple(4,attrName,attrValue));
        }
		if (attrName == "status")
		{
            if (pStation->status() != attrValue) emit valueChanged(pStation->name() + " " + attrName + " changed to " + attrValue);
            pStation->setStatus(attrValue);
			updateColor();
            tempModel->updateData(std::make_tuple(5,attrName,attrValue));
		}
	}
}
