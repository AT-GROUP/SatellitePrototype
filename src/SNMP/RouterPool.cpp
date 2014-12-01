#include "RouterPool.h"
//#include <iostream>
#include <QtConcurrent/QtConcurrent>

#define INTERVAL 1000

void updateRouter(SnmpRouter* router)
{
    router->update(INTERVAL);
    //cout << "router " << router->getIp() << " : " << router->getBw() << endl;
}

RouterPool::RouterPool()
{}

void RouterPool::addRouter(SnmpRouter *router)
{
    //cout << "Adding router " << router->getIp() << endl;
    routers.insert(router->getIp(), router);
}

SnmpRouter* RouterPool::getRouter(QString ip)
{
    return routers[ip];
}

void RouterPool::updateRouters()
{
    QtConcurrent::map(routers, updateRouter);
}
