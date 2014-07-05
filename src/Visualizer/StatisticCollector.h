#ifndef STATISTICCOLLECTOR_H
#define STATISTICCOLLECTOR_H

#include <unordered_map>
#include <list>
#include "../../src/Model/model.h"
#include <QVector>

typedef int Time;
typedef int Value;
typedef QVector<Time> Times; //using QVector because of QCustomPlot
typedef QVector<Value> Values;

class StatisticCollector
{
private:
    std::unordered_map<Satellite*, std::pair<Times, Values> > statistics;
public:
    StatisticCollector();
    void addData(Satellite* sat, Time t, Value v);
    std::pair<Times, Values>* getData(Satellite* sat);
};

#endif // STATISTICCOLLECTOR_H
