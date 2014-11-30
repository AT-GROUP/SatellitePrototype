#include "SnmpRouter.h"
#include <sstream>

SnmpRouter::SnmpRouter(string ip, QObject *parent) :
    QObject(parent)
{
    this->ip = ip;
    timeDelta = 1000;
}

std::list<std::string> &split(const std::string &s, char delim, std::list<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}


std::list<std::string> split(const std::string &s, char delim)
{
    std::list<std::string> elems;
    split(s, delim, elems);
    return elems;
}

list<string> SnmpRouter::getInterfaceList()
{
    list<string> res;
    QString snmpProgram = "snmpwalk";
    QStringList params;
    params << "-c" <<  "public" <<
           "-v" << "2c" << "81.200.86.82" <<
           ".1.3.6.1.2.1.2.2.1.2";
    QProcess* snmp = new QProcess();
    snmp->start(snmpProgram, params);
    snmp->waitForFinished();
    char buf[256];
    while(snmp->canReadLine())
    {
        snmp->readLine(buf, sizeof(buf));
        res.push_back(split(string(buf), ' ').back());
    }
    delete snmp;
    return res;
}

void SnmpRouter::selectInterface(int index)
{
    interface = index + 1;
}

void SnmpRouter::update()
{
    QString snmpProgram = "snmpget";
    QStringList params;
    QString ifOctetsMIBforInterface = ".1.3.6.1.2.1.2.2.1.10." +
            QString::number(interface);
    params << "-c" <<  "public" <<
           "-v" << "2c" << "81.200.86.82" <<
           ifOctetsMIBforInterface;
    QProcess* snmp = new QProcess();
    snmp->start(snmpProgram, params);
    snmp->waitForFinished();
    char buf[256];
    snmp->readLine(buf, sizeof(buf));
    long long ifInOctets = atoll(split(string(buf), ' ').back().c_str());
    ifInBw = (ifInOctets - this->ifInOctets)*1000 / timeDelta;
    delete snmp;

    ifOctetsMIBforInterface = ".1.3.6.1.2.1.2.2.1.16." +
            QString::number(interface);
    params.clear();
    params << "-c" <<  "public" <<
           "-v" << "2c" << "81.200.86.82" <<
           ifOctetsMIBforInterface;
    snmp = new QProcess();
    snmp->start(snmpProgram, params);
    snmp->waitForFinished();
    snmp->readLine(buf, sizeof(buf));
    long long ifOutOctets = atoll(split(string(buf), ' ').back().c_str());
    ifInBw = (ifOutOctets - this->ifOutOctets)*1000 / timeDelta;
    delete snmp;
}
