#ifndef SNMPROUTER_H
#define SNMPROUTER_H

#include <string>
#include <list>
#include <QProcess>

using namespace std;

class SnmpRouter
{
private:
    long long ifInOctets, ifOutOctets;
    long long ifInBw, ifOutBw;
    string ip;
    int interface;
    int timeDelta;

    void update();
public:
    SnmpRouter(string ip);
    list<string> getInterfaceList();
    void selectInterface(int index);
    long long getBw();
};

#endif // SNMPROUTER_H
