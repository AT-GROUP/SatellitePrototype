#ifndef REALGRAPHICSWIDGET_H
#define REALGRAPHICSWIDGET_H

#include <QWidget>
#include "../SNMP/RealStatisticCollector.h"
#include "qcustomplot.h"

class RealGraphicsWidget : public QCustomPlot
{
    Q_OBJECT
private:
    Data* statisticsData;
    RealSatellite* sat;
    Time period;

    void refreshGraphData();
public:
    explicit RealGraphicsWidget(RealStatisticCollector* sc, RealSatellite* sat, QWidget *parent = 0);
    void setPeriod(Time p);
signals:

public slots:
    void updateGraph();

};

#endif // REALGRAPHICSWIDGET_H
