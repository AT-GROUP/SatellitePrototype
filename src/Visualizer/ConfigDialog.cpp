#include <QtGui>

#include "ConfigDialog.h"
#include "ConfigPages.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

ConfigDialog::ConfigDialog(QWidget* parent)
{
    Q_UNUSED(parent);

    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setIconSize(QSize(96, 84));
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(128);
    contentsWidget->setSpacing(12);
    contentsWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    pagesWidget = new QStackedWidget;
    pagesWidget->addWidget(new CommonSettings);
    pagesWidget->addWidget(new SatelliteSettings);
    pagesWidget->addWidget(new StationSettings);
    pagesWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QPushButton *closeButton = new QPushButton(tr("Apply and close"));

    createIcons();
    contentsWidget->setCurrentRow(0);

    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    //buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    //mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Config Dialog"));
}

void ConfigDialog::createIcons()
{
    QListWidgetItem *commonConfigButton = new QListWidgetItem(contentsWidget);
    commonConfigButton->setIcon(QIcon(":settings"));
    commonConfigButton->setText(tr("Configuration"));
    commonConfigButton->setTextAlignment(Qt::AlignHCenter);
    commonConfigButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *satellitesButton = new QListWidgetItem(contentsWidget);
    satellitesButton->setIcon(QIcon(":satellite"));
    satellitesButton->setText(tr("Satellites"));
    satellitesButton->setTextAlignment(Qt::AlignVCenter);
    satellitesButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *stationsButton = new QListWidgetItem(contentsWidget);
    stationsButton->setIcon(QIcon(":station"));
    stationsButton->setText(tr("Stations"));
    stationsButton->setTextAlignment(Qt::AlignHCenter);
    stationsButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    connect(contentsWidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}

void ConfigDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;
    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}
