#ifndef ROUTERPOOL_H
#define ROUTERPOOL_H

#include <QMap>
#include "SnmpRouter.h"
#include <QObject>
#include <QTimer>

class RouterPool : QObject
{
    Q_OBJECT
private:
    QMap<string, SnmpRouter*> routers;
    QTimer* timer;
public:
    RouterPool(QObject* parent);
    void addRouter(SnmpRouter* router);
    SnmpRouter* getRouter(string ip);
    void start();
    void stop();
signals:

public slots:
    void updateRouters();
};

#endif // ROUTERPOOL_H
