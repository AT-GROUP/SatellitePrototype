#ifndef QSTATIONITEM_H
#define QSTATIONITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QTableWidget>
#include "../../src/Model/station.h"

class QStationItem: public QObject, public QGraphicsItemGroup
{
	Q_OBJECT
    private:
        QGraphicsEllipseItem *p_Ellipse;
		QGraphicsProxyWidget *proxy;
		QTableView *p_InfoList;
        Station *pStation;
		void updateColor();
		void setColor(QColor qColor);
    public:
        QStationItem(qreal x, qreal y, QString n, QObject* parent = 0);
        ~QStationItem();
		void updateFact(std::tuple<QString, QString, QString> info);
    protected:
        virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
        virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
        virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
	signals:
		void valueChanged(const QString& mess);
};

#endif // QSTATIONITEM_H
