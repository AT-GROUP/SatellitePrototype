#ifndef ROUTERPOOL_H
#define ROUTERPOOL_H

#include <QMap>
#include "SnmpRouter.h"
#include <QObject>
#include <QTimer>

class RouterPool
{
private:
    QMap<string, SnmpRouter*> routers;
public:
    RouterPool();
    void addRouter(SnmpRouter* router);
    SnmpRouter* getRouter(string ip);
    void updateRouters();
};

#endif // ROUTERPOOL_H
