#ifndef REALSATELLITE_H
#define REALSATELLITE_H

#include <QString>

class RealSatellite
{
private:
    QString name;
public:
    RealSatellite(QString name, int maxInBw, int maxOutBw);
};

#endif // REALSATELLITE_H
