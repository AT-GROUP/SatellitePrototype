#include "ModelVisualizer.h"
#include <QWheelEvent>
#include <QMenuBar>
#include <QToolButton>
#include <tuple>
#include <qlist.h>
#include <qdebug.h>
#include <qsignalmapper.h>
#include "ConfigDialog.h"
#include "GraphDialog.h"
#include "../../src/Model/satellite.h"
#include <QMessageBox>

ModelVisualizer::ModelVisualizer(QWidget *parent):
    QWidget(parent)
{
    pModel = new Model();
    //tmp
    pWorld = new RealWorld();
    //tmp
    createWidgets();
    createView();
    createMenu();
    createLayout();
    addStations();
    initStatistics();
}

ModelVisualizer::~ModelVisualizer()
{
    delete pScene;
    delete pView;
    delete pGridLayout;
    delete pEventList;
    delete pModel;
    delete pMainMenu;
}

void ModelVisualizer::createWidgets()
{
    pScene = new QGraphicsScene();
    pEventList = new QListWidget();
    pEventList->setFixedWidth(200);
    pEventList->autoScrollMargin();
    pBackGroundPic = new QGraphicsPixmapItem(QPixmap(":background"));
    pScene->addItem(pBackGroundPic);
}

void ModelVisualizer::createView()
{
    pView = new QGraphicsView();
    pView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    pView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    pView->setMouseTracking(true);
    pView->setScene(pScene);
}

void ModelVisualizer::createMenu()
{
    QSignalMapper* mSigmapper = new QSignalMapper(this);
    pMainMenu = new QMenuBar();
    startSim = new QAction("Continue simulation", this);
    startSim->setData(QString("Simulation continued"));
    connect(startSim, SIGNAL(triggered()), mSigmapper, SLOT(map()));
    pMainMenu->addAction(startSim);
    mSigmapper->setMapping(startSim, startSim->data().toString());
    pauseSim = new QAction("Pause simulation", this);
    pauseSim->setData(QString("Simulation paused"));
    connect(pauseSim, SIGNAL(triggered()), mSigmapper, SLOT(map()));
    mSigmapper->setMapping(pauseSim, pauseSim->data().toString());
    pMainMenu->addAction(pauseSim);
    configure = new QAction("Configure model", this);
    configure->setData(QString("Not done yet"));
    connect(configure, SIGNAL(triggered()), this, SLOT(showConfigWindow()));
    pMainMenu->addAction(configure);
    mSigmapper->setMapping(configure, configure->data().toString());
    showInfo = new QAction("Show information", this);
    connect(showInfo, SIGNAL(triggered()), this, SLOT(showGraphsWindow()));
    pMainMenu->addAction(showInfo);
    connect(mSigmapper, SIGNAL(mapped(QString)), this, SLOT(addMessageToEventsList(const QString&)));

    connect(pModel, SIGNAL(showRecomendation(const QString&)), this, SLOT(showMessageWindow(const QString&)));
}

void ModelVisualizer::createLayout()
{
    pGridLayout = new QGridLayout();
    pGridLayout->addWidget(pView, 1, 0);
    pGridLayout->addWidget(pEventList, 1, 1);
    pGridLayout->addWidget (pMainMenu, 0, 0, 1, 0);
    setLayout(pGridLayout);
}

void ModelVisualizer::addStations()
{
    for (QVector<Station*>::iterator it = pModel->stationList()->begin(); it != pModel->stationList()->end(); it++)
    {
        QStationItem *adding = new QStationItem((*it));
        pScene->addItem(adding);
        connect(adding, SIGNAL(valueChanged(const QString&)), this, SLOT(addMessageToEventsList(const QString&)));
    }
    for (QVector<Satellite*>::iterator it = pModel->satelliteList()->begin(); it != pModel->satelliteList()->end(); it++)
    {
        QSatelliteItem *adding = new QSatelliteItem((*it));
        pScene->addItem(adding);
        connect(adding, SIGNAL(valueChanged(const QString&)), this, SLOT(addMessageToEventsList(const QString&)));
    }
}

void ModelVisualizer::initStatistics()
{
    QVector<Satellite*>* sats = pModel->satelliteList();
    statistics = new StatisticCollector(sats, 0);
    statistics->start();
}

void ModelVisualizer::addMessageToEventsList(const QString& message)
{
    pEventList->addItem(message);
    pEventList->scrollToBottom();
    //temp workaround for Issue #8
    if(message.compare("Simulation paused") == 0)
    {
        statistics->pause();
    }
    else if (message.compare("Simulation continued") == 0)
    {
        statistics->start();
    }
    //
}

void ModelVisualizer::wheelEvent(QWheelEvent * event)
{
    // ToDo: Fix max zoom and zoom position
    if (event->modifiers().testFlag(Qt::ControlModifier))
    {
        int numSteps = event->delta() / 15 / 8;
        if (numSteps == 0)
        {
            event->ignore();
            return;
        }
        qreal sc = pow(1.25, numSteps);
        this->mapZoom(sc, pView->mapToScene(event->pos()));
        event->accept();
    }
}

void ModelVisualizer::mapZoom(qreal factor, QPointF centerPoint)
{
    pView->scale(factor, factor);
    pView->centerOn(centerPoint);
}

void ModelVisualizer::showGraphsWindow()
{
    GraphDialog* gd = new GraphDialog(pModel, statistics, this);
    gd->show();
}

void ModelVisualizer::showConfigWindow()
{
    ConfigDialog* g1 = new ConfigDialog(pModel->stationList(), pModel->satelliteList(), this);
    g1->show();
}

void ModelVisualizer::processModelTact()
{
    pModel->processModelTact();
}

void ModelVisualizer::showMessageWindow(const QString &recomendation)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Apply recomendation?", recomendation, QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        qDebug() << "Yes was clicked";
    }
    else
        {
            qDebug() << "Yes was *not* clicked";
        }
}
