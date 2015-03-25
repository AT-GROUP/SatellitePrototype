#ifndef REALGRAPHDIALOG_H
#define REALGRAPHDIALOG_H

#include <QDialog>
#include <QRadioButton>
#include "../SNMP/RealWorld.h"
#include "RealGraphicsWidget.h"
#include "RealStationDataTable.h"

class RealGraphDialog : public QDialog
{
    Q_OBJECT
private:
    QList<QRadioButton*> periods;
    QList<RealGraphicsWidget*> graphs;

    QRadioButton *addPeriod(QLayout *l, QString text);
public:
    explicit RealGraphDialog(RealWorld* mod, RealStatisticCollector* sc, QWidget *parent = 0);

signals:

public slots:
    void setPeriod();
};

#endif // REALGRAPHDIALOG_H
