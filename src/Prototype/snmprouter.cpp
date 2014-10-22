#include "snmprouter.h"

std::list<std::string> &split(const std::string &s, char delim, std::list<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::list<std::string> split(const std::string &s, char delim) {
    std::list<std::string> elems;
    split(s, delim, elems);
    return elems;
}

SnmpRouter::SnmpRouter(string ip)
{
    this->ip = ip;
    timeDelta = 1000;
}

list<string> SnmpRouter::getInterfaceList()
{
    list<string> res;
    string snmpProgram = "snmpwalk";
    QStringList params;
    params << "-c" <<  "public" <<
           "-v" << "2c" << "81.200.86.82" <<
           ".1.3.6.1.2.1.2.2.1.2";
    QProcess* snmp = new QProcess();
    snmp->start(snmpProgram, params);
    snmp->waitForFinished();
    char buf[256];
    while(snmpGet->canReadLine())
    {
        snmp.readLine(buf, sizeof(buf));
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
    string snmpProgram = "snmpget";
    QStringList params;
    string ifOctetsMIBforInterface = ".1.3.6.1.2.1.2.2.1.10." +
            std::to_string(interface);
    params << "-c" <<  "public" <<
           "-v" << "2c" << "81.200.86.82" <<
           ifOctetsMIBforInterface;
    QProcess* snmp = new QProcess();
    snmp->start(snmpProgram, params);
    snmp->waitForFinished();
    char buf[256];
    snmp.readLine(buf, sizeof(buf));
    long long ifInOctets = atoll(split(string(buf), ' ').back().c_str());
    ifInBw = (ifInOctets - this->ifInOctets)*1000 / timeDelta;
    delete snmp;

    string ifOctetsMIBforInterface = ".1.3.6.1.2.1.2.2.1.16." +
            std::to_string(interface);
    params << "-c" <<  "public" <<
           "-v" << "2c" << "81.200.86.82" <<
           ifOctetsMIBforInterface;
    snmp = new QProcess();
    snmp->start(snmpProgram, params);
    snmp->waitForFinished();
    char buf[256];
    snmp.readLine(buf, sizeof(buf));
    long long ifOutOctets = atoll(split(string(buf), ' ').back().c_str());
    ifInBw = (ifOutOctets - this->ifOutOctets)*1000 / timeDelta;
    delete snmp;
}


