#ifndef SNMPROUTER_H
#define SNMPROUTER_H

#include <string>
#include <list>
#include <QString>

using namespace std;

class SnmpRouter
{
private:
    string ip;
    int interface;
    long long ifInOctets, ifOutOctets;
    long long ifInBw, ifOutBw;
public:
    explicit SnmpRouter(QString ip);
    list<string> getInterfaceList();
    void selectInterface(int index);
    long long getBw();
    long long getInOctets();
    long long getOutOctets();
    long long getInBw();
    long long getOutBw();
    void update(int timeDelta);
    string getIp();
};

#endif // SNMPROUTER_H
