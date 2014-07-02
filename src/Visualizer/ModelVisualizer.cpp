#include "ModelVisualizer.h"
#include <QWheelEvent>
#include <QMenuBar>
#include <QToolButton>
#include <tuple>
#include <qlist.h>
#include <qdebug.h>
#include <qsignalmapper.h>
#include "ConfigDialog.h"

ModelVisualizer::ModelVisualizer(QWidget *parent):
    QWidget(parent)
{
    createWidgets();
    createView();
    createMenu();
    createLayout();
    addStations();
}

ModelVisualizer::~ModelVisualizer()
{
    delete pScene;
    delete pView;
    delete pGridLayout;
    delete pEventList;
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
    pStationList = new QMap<QString, QStationItem*>();
    pStationList->insert("Station1", new QStationItem(800,200, "Station1"));
    pStationList->insert("Station2", new QStationItem(840,250, "Station2"));
    pStationList->insert("Station3", new QStationItem(370,250, "Station3"));
    pStationList->insert("Station4", new QStationItem(400,277, "Station4"));
    pStationList->insert("Station5", new QStationItem(450,250, "Station5"));
    pStationList->insert("Station6", new QStationItem(200,400, "Station6"));
    pStationList->insert("Station7", new QStationItem(700,240, "Station7"));
    pStationList->insert("Station8", new QStationItem(1000,250, "Station8"));
    pStationList->insert("Station9", new QStationItem(905,470, "Station9"));
    for (QMap<QString, QStationItem*>::iterator it = pStationList->begin(); it != pStationList->end(); it++)
    {
         pScene->addItem((*it));
         connect((*it), SIGNAL(valueChanged(const QString&)), this, SLOT(addMessageToEventsList(const QString&)));
    }

    pSatelliteList = new QMap<QString, QSatelliteItem*>();
    pSatelliteList->insert("Intelsat", new QSatelliteItem(200,100, "Intelsat"));
    pSatelliteList->insert("Yamal", new QSatelliteItem(600,0, "Yamal"));
    pSatelliteList->insert("AM3", new QSatelliteItem(1000,100, "AM3"));
    for (QMap<QString, QSatelliteItem*>::iterator it = pSatelliteList->begin(); it != pSatelliteList->end(); it++)
	{
         pScene->addItem((*it));
		 connect((*it), SIGNAL(valueChanged(const QString&)), this, SLOT(addMessageToEventsList(const QString&)));
	}
}

void ModelVisualizer::addMessageToEventsList(const QString& message)
{
    pEventList->addItem(message);
    pEventList->scrollToBottom();
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

void ModelVisualizer::updateFromModelFile()
{
    QFile* file = new QFile("BB2.xml");
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QXmlStreamReader xml(file);
	while ((!xml.atEnd()) && (!xml.hasError()))
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() != "fact")
                continue;
			std::tuple<QString, QString, QString> attr = (parseFacts(xml));
            if (pStationList->contains(std::get<0>(attr)))
			{
                pStationList->value(std::get<0>(attr))->updateFact(attr);
			}
            if (pSatelliteList->contains(std::get<0>(attr)))
			{
                pSatelliteList->value(std::get<0>(attr))->updateFact(attr);
			}
        }
    }
    pEventList->addItem("Model updated");
    pEventList->scrollToBottom();
}

std::tuple<QString, QString, QString> ModelVisualizer::parseFacts(QXmlStreamReader& xml)
{
    QXmlStreamAttributes attributes = xml.attributes();
    if ((attributes.hasAttribute("AttrPath"))&&(attributes.hasAttribute("Value")))
    {
        return std::make_tuple(attributes.value("AttrPath").toString().split('.').at(0), attributes.value("AttrPath").toString().split('.').at(1), attributes.value("Value").toString());
    }
}

void ModelVisualizer::showGraphsWindow()
{
    // ЗДЕСЬ БУДЕТ ВЫЗЫВАТЬСЯ ГРАФОПОСТРОИТЕЛЬ
}

void ModelVisualizer::showConfigWindow()
{
    ConfigDialog* g1 = new ConfigDialog(this);
    g1->show();
}
