#include "RealGraphicsWidget.h"

RealGraphicsWidget::RealGraphicsWidget(RealStatisticCollector *sc, RealSatellite *sat, QWidget *parent) :
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
    refreshGraphData();
    xAxis->setLabel("Time");
    xAxis->setTickLabelType(QCPAxis::LabelType::ltDateTime);
    yAxis->setLabel("curBw");
    setMinimumSize(400, 300);
    period = 0;
    connect(sc, SIGNAL(dataUpdated()), this, SLOT(updateGraph()));
}

void RealGraphicsWidget::updateGraph()
{
    refreshGraphData();
    replot();
}

void RealGraphicsWidget::refreshGraphData()
{
    graph(0)->setData(statisticsData->first, statisticsData->second);
    if(period == 0)
        xAxis->setRange(statisticsData->first.front(), statisticsData->first.back());
    else
        xAxis->setRange(statisticsData->first.back() - period, statisticsData->first.back());
    yAxis->setRange(0, 1.1 * sat->maxBw());
}

void RealGraphicsWidget::setPeriod(Time p)
{
    period = p;
}
