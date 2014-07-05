#ifndef STATISTICCOLLECTOR_H
#define STATISTICCOLLECTOR_H

#include <unordered_map>
#include <list>
#include "../../src/Model/model.h"
#include <QVector>

typedef double Time;
typedef double Value;
typedef QVector<Time> Times; //using QVector<double> because of QCustomPlot
typedef QVector<Value> Values;
typedef std::pair<Times, Values> Data;

class StatisticCollector
{
private:
    std::unordered_map<Satellite*, Data> statistics;
public:
    StatisticCollector();
    void addData(Satellite* sat, Time t, Value v);
    Data* getData(Satellite* sat);
};

#endif // STATISTICCOLLECTOR_H
