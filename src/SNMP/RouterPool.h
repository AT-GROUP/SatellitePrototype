#ifndef ROUTERPOOL_H
#define ROUTERPOOL_H

#include <QMap>
#include "SnmpRouter.h"
#include <QObject>
#include <QTimer>

class RouterPool
{
private:
    QMap<QString, SnmpRouter*> routers;
public:
    RouterPool();
    void addRouter(SnmpRouter* router);
    SnmpRouter* getRouter(QString ip);
    void updateRouters();
};

#endif // ROUTERPOOL_H
