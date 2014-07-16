#include "GraphDialog.h"
#include <QBoxLayout>

GraphDialog::GraphDialog(QVector<Satellite *> *satellites, StatisticCollector *sc, QWidget *parent) :
    QDialog(parent)
{
    QHBoxLayout* layout = new QHBoxLayout;
    for(auto sat = satellites->begin(); sat != satellites->end(); ++sat)
    {
        GraphicsWidget* gw = new GraphicsWidget(sc, *sat, this);
        layout->addWidget(gw);
    }
    setLayout(layout);
    resize(800, 500);
}
