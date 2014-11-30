#include "SnmpRouter.h"
#include <sstream>
#include <QProcess>

const long long MAX_32BIT = 4294967296;

SnmpRouter::SnmpRouter(string ip): ip(ip),interface(0),ifInOctets(0),ifOutOctets(0)
{}

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

string SnmpRouter::getIp()
{
    return ip;
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

void SnmpRouter::update(int timeDelta)
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
    if(this->ifInOctets == 0)
        this->ifInOctets = ifInOctets;
    if(ifInOctets < this->ifInOctets)
        this->ifInOctets -= MAX_32BIT;
    ifInBw = (ifInOctets - this->ifInOctets)*1000 / timeDelta;
    this->ifInOctets = ifInOctets;
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
    if(this->ifOutOctets == 0)
        this->ifOutOctets = ifOutOctets;
    if(ifOutOctets < this->ifOutOctets)
        this->ifOutOctets -= MAX_32BIT;
    ifOutBw = (ifOutOctets - this->ifOutOctets)*1000 / timeDelta;
    this->ifOutOctets = ifOutOctets;
    delete snmp;
}

long long SnmpRouter::getInOctets()
{
    return ifInOctets;
}

long long SnmpRouter::getOutOctets()
{
    return ifOutOctets;
}

long long SnmpRouter::getInBw()
{
    return ifInBw;
}

long long SnmpRouter::getOutBw()
{
    return ifOutBw;
}

long long SnmpRouter::getBw()
{
    return ifInBw + ifOutBw; //temp
}
