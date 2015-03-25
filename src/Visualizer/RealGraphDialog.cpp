#include "RealGraphDialog.h"
#include <QBoxLayout>

RealGraphDialog::RealGraphDialog(RealWorld* mod, RealStatisticCollector *sc, QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout* outerLayout = new QVBoxLayout;
    //periods
    QHBoxLayout* periodsLayout = new QHBoxLayout;
    addPeriod(periodsLayout, "10 min");
    addPeriod(periodsLayout, "1 hour");
    addPeriod(periodsLayout, "1 day");
    addPeriod(periodsLayout, "1 week");
    addPeriod(periodsLayout, "1 month");
    addPeriod(periodsLayout, "all")->setChecked(true);
    outerLayout->addLayout(periodsLayout);
    outerLayout->setAlignment(periodsLayout, Qt::AlignLeft);

    //curBw
    QHBoxLayout* graphicsLayout = new QHBoxLayout;
    QVector<RealSatellite*>* satellites = mod->satelliteList();
    for(auto sat = satellites->begin(); sat != satellites->end(); ++sat)
    {
        RealGraphicsWidget* gw = new RealGraphicsWidget(sc, *sat, this);
        graphicsLayout->addWidget(gw);
        graphs.push_back(gw);
    }
    outerLayout->addLayout(graphicsLayout);

    //tables
    QHBoxLayout* tablesLayout = new QHBoxLayout;
    for(auto sat = satellites->begin(); sat != satellites->end(); ++sat)
    {
        RealStationDataTable* tw = new RealStationDataTable(sc, *sat, mod, this);
        tablesLayout->addWidget(tw);
    }
    outerLayout->addLayout(tablesLayout);

    setLayout(outerLayout);
    resize(1280, 700);
}

QRadioButton* RealGraphDialog::addPeriod(QLayout* l, QString text)
{
    QRadioButton* tmp;
    tmp = new QRadioButton(text, this);
    connect(tmp, SIGNAL(clicked()), this, SLOT(setPeriod()));
    l->addWidget(tmp);
    periods.push_back(tmp);
    return tmp;
}

void RealGraphDialog::setPeriod()
{
    for(QRadioButton* rad : periods)
    {
        if(rad->isChecked())
        {
            Time p;
            if(rad->text() == QString("10 min"))
                p = 10*60;
            else if(rad->text() == QString("1 hour"))
                p = 1*60*60;
            else if(rad->text() == QString("1 day"))
                p = 24*60*60;
            else if(rad->text() == QString("1 week"))
                p = 7*24*60*60;
            else if(rad->text() == QString("1 month"))
                p = 30*24*60*60;
            else
                p = 0;
            for(RealGraphicsWidget* gw : graphs)
                gw->setPeriod(p);
        }
    }
}
