#ifndef GRAPHDIALOG_H
#define GRAPHDIALOG_H

#include <QDialog>
#include "GraphicsWidget.h"

class GraphDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GraphDialog(QVector<Satellite*>* satellites, StatisticCollector* sc, QWidget *parent = 0);

signals:

public slots:

};

#endif // GRAPHDIALOG_H
