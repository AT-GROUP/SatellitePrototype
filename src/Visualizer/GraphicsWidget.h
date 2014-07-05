#ifndef GRAPHICSWIDGET_H
#define GRAPHICSWIDGET_H

#include <QWidget>
#include "StatisticCollector.h"
#include "qcustomplot.h"

class GraphicsWidget : public QCustomPlot
{
    Q_OBJECT
private:
    Data* statisticsData;
    Satellite* sat;
public:
    explicit GraphicsWidget(StatisticCollector* sc, Satellite* sat, QWidget *parent = 0);

signals:

public slots:

};

#endif // GRAPHICSWIDGET_H
