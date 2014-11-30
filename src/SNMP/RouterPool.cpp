#include "RouterPool.h"
#include <iostream>
#include <QtConcurrent/QtConcurrent>

#define INTERVAL 1000

void updateRouter(SnmpRouter* router)
{
    router->update(INTERVAL);
    cout << "router " << router->getIp() << " : " << router->getBw() << endl;
}

RouterPool::RouterPool(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateRouters()));
}

void RouterPool::start()
{
    timer->start(INTERVAL);
}

void RouterPool::stop()
{
    timer->stop();
}

void RouterPool::addRouter(SnmpRouter *router)
{
    //cout << "Adding router " << router->getIp() << endl;
    routers.insert(router->getIp(), router);
}

SnmpRouter* RouterPool::getRouter(string ip)
{
    return routers[ip];
}

void RouterPool::updateRouters()
{
    /*cout << routers.size() << endl;
    for(auto it = routers.begin(); it != routers.end(); ++it)
    {
        cout << (*it)->getIp() << ':' << (*it)->getBw() << endl;
    }
    cout.flush();
    system("sleep 1");*/
    QtConcurrent::map(routers, updateRouter);
}
