#include "GraphicsWidget.h"

GraphicsWidget::GraphicsWidget(StatisticCollector *sc, Satellite *sat, QWidget *parent) :
    QCustomPlot(parent)
{
    statisticsData = sc->getData(sat);
    this->sat = sat;
    QCPItemText* satName = new QCPItemText(this);
    addItem(satName);
    satName->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    satName->position->setType(QCPItemPosition::ptAxisRectRatio);
    satName->position->setCoords(0.5, 0);
    satName->setText(sat->name());
    satName->setFont(QFont(font().family(), 16));
    satName->setPen(QPen(Qt::black));
    addGraph();
    graph(0)->setData(statisticsData->first, statisticsData->second);
}
