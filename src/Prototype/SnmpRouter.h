#ifndef SNMPROUTER_H
#define SNMPROUTER_H

#include <QObject>
#include <string>
#include <list>
#include <QProcess>

using namespace std;

class SnmpRouter : public QObject
{
    Q_OBJECT
private:
    long long ifInOctets, ifOutOctets;
    long long ifInBw, ifOutBw;
    string ip;
    int interface;
    int timeDelta;
public:
    explicit SnmpRouter(string ip, QObject *parent = 0);
    list<string> getInterfaceList();
    void selectInterface(int index);
    long long getBw();

signals:

public slots:
    void update();
};

#endif // SNMPROUTER_H
