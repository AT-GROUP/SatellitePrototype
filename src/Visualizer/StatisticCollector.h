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

#define EPSILON 1e-10

class StatisticCollector
{
private:
    std::unordered_map<Satellite*, Data> statistics;
public:
    StatisticCollector(QVector<Satellite*>* satellites, Time t);
    void addData(Satellite* sat, Time t);
    Data* getData(Satellite* sat);
};

#endif // STATISTICCOLLECTOR_H
