#ifndef PAGES_H
#define PAGES_H

#include <QWidget>

class CommonSettings : public QWidget
{
    public:
        CommonSettings(QWidget *parent = 0);
};

class SatelliteSettings : public QWidget
{
    public:
        SatelliteSettings(QWidget *parent = 0);
};

class StationSettings : public QWidget
{
    public:
        StationSettings(QWidget *parent = 0);
};

#endif
