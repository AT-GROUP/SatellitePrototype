#include <QtGui>

#include "ConfigPages.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QGroupBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QDateTimeEdit>
#include "QStationItem.h"
#include "ModelVisualizer.h"

CommonSettings::CommonSettings(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *settingsGroup = new QGroupBox(tr("Common settings"));
    QCheckBox *setting1 = new QCheckBox(tr("One"));
    QCheckBox *setting2 = new QCheckBox(tr("Two"));
    QCheckBox *setting3 = new QCheckBox(tr("Three"));

    QVBoxLayout *settingsLayout = new QVBoxLayout;
    settingsLayout->addWidget(setting1);
    settingsLayout->addWidget(setting2);
    settingsLayout->addWidget(setting3);
    settingsGroup->setLayout(settingsLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(settingsGroup);
    mainLayout->addSpacing(12);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}



SatelliteSettings::SatelliteSettings(QVector<Satellite*> *pSatelliteList, QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *settingsGroup = new QGroupBox(tr("Station configuration"));

    QLabel *satelliteLabel = new QLabel(tr("Satellite:"));
    QComboBox *satelliteCombo = new QComboBox;

    for (QVector<Satellite*>::iterator it = pSatelliteList->begin(); it != pSatelliteList->end(); it++)
    {
        satelliteCombo->addItem((*it)->name());
    }

    QHBoxLayout *satelliteSettingsLayout = new QHBoxLayout;
    satelliteSettingsLayout->addWidget(satelliteLabel);
    satelliteSettingsLayout->addWidget(satelliteCombo);

    QVBoxLayout *configLayout = new QVBoxLayout;
    configLayout->addLayout(satelliteSettingsLayout);
    settingsGroup->setLayout(configLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(settingsGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

StationSettings::StationSettings(QVector<Station*> *pStationList, QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *settingsGroup = new QGroupBox(tr("Station configuration"));

    QLabel *stationLabel = new QLabel(tr("Station:"));
    QComboBox *stationCombo = new QComboBox;

    for (QVector<Station*>::iterator it = pStationList->begin(); it != pStationList->end(); it++)
    {
        stationCombo->addItem((*it)->name());
    }

    QHBoxLayout *stationSettingsLayout = new QHBoxLayout;
    stationSettingsLayout->addWidget(stationLabel);
    stationSettingsLayout->addWidget(stationCombo);

    QVBoxLayout *configLayout = new QVBoxLayout;
    configLayout->addLayout(stationSettingsLayout);
    settingsGroup->setLayout(configLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(settingsGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

class SettingsList : public QWidget
{
    SettingsList(QWidget* parent)
    {
        Q_UNUSED(parent);
    }
};
