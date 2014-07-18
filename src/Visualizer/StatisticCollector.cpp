#include "StatisticCollector.h"
//#include <cstdio>

StatisticCollector::StatisticCollector(QVector<Satellite *> *satellites, Time t) : QObject()
{
    timer = new QTimer(this);
    for(auto sat = satellites->begin(); sat != satellites->end(); sat++)
        addData(*sat, 0); //0 is temporary
    connect(timer, SIGNAL(timeout()), this, SLOT(fetchData()));
}

void StatisticCollector::addData(Satellite* sat, Time t)
{
    if (statistics.find(sat) != statistics.end())
    {
        if (statistics[sat].first.size() >= 2)
            if (statistics[sat].second.back() == statistics[sat].second[statistics[sat].second.size() - 2])
            {
                if (sat->curBw() == statistics[sat].second.back())
                {
                    statistics[sat].first.pop_back();
                    statistics[sat].second.pop_back();
                }
            }
        //statistics[sat].first.push_back(t);
        //statistics[sat].second.push_back(statistics[sat].second.back());
    }
    statistics[sat].first.push_back(t);
    statistics[sat].second.push_back(sat->curBw());
    emit(dataUpdated());
}

Data* StatisticCollector::getData(Satellite* sat)
{
    return &statistics[sat];
}

void StatisticCollector::start()
{
    timer->start(100);
}

void StatisticCollector::pause()
{
    timer->stop();
}

void StatisticCollector::fetchData()
{
    static Time time = 0;
    time += INTERVAL / 1000;
    for(auto sat = statistics.begin(); sat != statistics.end(); ++sat)
    {
        addData(sat->first, time);
    }
}
