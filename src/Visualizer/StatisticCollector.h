#ifndef STATISTICCOLLECTOR_H
#define STATISTICCOLLECTOR_H

#include <unordered_map>
#include <list>
#include "../../src/Model/model.h"

typedef int Time;
typedef int Value;

class StatisticCollector
{
private:
    std::unordered_map<Satellite*, std::list<std::pair<Time, Value> > > statistics;
public:
    StatisticCollector();
};

#endif // STATISTICCOLLECTOR_H
