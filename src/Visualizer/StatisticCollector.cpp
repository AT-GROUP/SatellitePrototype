#include "StatisticCollector.h"

StatisticCollector::StatisticCollector()
{
}

void StatisticCollector::addData(Satellite* sat, Time t, Value v)
{
    statistics[sat].first.push_back(t);
    statistics[sat].second.push_back(v);
}

Data* StatisticCollector::getData(Satellite* sat)
{
    return &statistics[sat];
}
