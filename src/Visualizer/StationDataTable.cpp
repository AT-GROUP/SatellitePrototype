#include "StationDataTable.h"
#include <QStringList>
#include <cstdio> //for debug

StationDataTable::StationDataTable(StatisticCollector* sc, Satellite *sat, Model *mod, QWidget *parent) :
    QTableWidget(parent)
{
    this->sat = sat;
    this->mod = mod;
    setColumnCount(5);
    QStringList captions = {"name", "ipAddress", "bwNeeded", "bwInUse", "status"};
    setHorizontalHeaderLabels(captions);
    refreshData();
    connect(sc, SIGNAL(dataUpdated()), this, SLOT(refreshData()));
}

void StationDataTable::refreshData()
{
    model()->removeRows(0, rowCount());
    for(auto station = mod->stationList()->begin(); station != mod->stationList()->end(); ++station)
    {
        if((*station)->satellite() == sat)
        {
            insertRow(0);
            //printf("For satellite %s added station %s\n", sat->name().toLocal8Bit().data(), (*station)->name().toLocal8Bit().data());
            setItem(0, 0, new QTableWidgetItem((*station)->name()));
            setItem(0, 1, new QTableWidgetItem((*station)->ipAddress()));
            setItem(0, 2, new QTableWidgetItem(QString::number((*station)->bwNeeded())));
            setItem(0, 3, new QTableWidgetItem(QString::number((*station)->bwInUse())));
            setItem(0, 4, new QTableWidgetItem((*station)->status()));
        }
    }
}
