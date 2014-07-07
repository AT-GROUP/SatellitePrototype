#include "StatisticCollector.h"

StatisticCollector::StatisticCollector(QVector<Satellite *> *satellites, Time t)
{
    timer = new QTimer(this);
    for(auto sat = satellites->begin(); sat != satellites->end(); sat++)
        addData(*sat, t);
}

void StatisticCollector::addData(Satellite* sat, Time t)
{
    if (statistics.find(sat) != statistics.end())
    {
        statistics[sat].first.push_back(t);
        statistics[sat].second.push_back(statistics[sat].second.back());
    }
    statistics[sat].first.push_back(t);
    statistics[sat].second.push_back(sat->curBw());
}

Data* StatisticCollector::getData(Satellite* sat)
{
    return &statistics[sat];
}

void StatisticCollector::start()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(fetchData()));
    timer->start(INTERVAL);
}

void StatisticCollector::fetchData()
{
    static Time time = 0;
    time += INTERVAL;
    for(auto sat = statistics.begin(); sat != statistics.end(); ++sat)
    {
        addData(sat->first, time);
    }
}
