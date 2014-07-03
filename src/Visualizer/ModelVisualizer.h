#ifndef MODELVISUALIZER_H
#define MODELVISUALIZER_H

#include "QSatelliteItem.h"
#include "QStationItem.h"
#include <QWidget>
#include <QGraphicsView>
#include <QGridLayout>
#include <QListWidget>
#include <QXmlStreamReader>
#include <qmenubar.h>

class ModelVisualizer : public QWidget
{
    Q_OBJECT
	private:
        QGraphicsScene *pScene;
        QGraphicsView *pView;
        QGraphicsPixmapItem *pBackGroundPic;
        QGridLayout *pGridLayout;
        QListWidget *pEventList;
        QMenuBar *pMainMenu;

	public:
		explicit ModelVisualizer(QWidget *parent = 0);
		~ModelVisualizer();
        QAction *startSim;
        QAction *pauseSim;
        QAction *configure;
        QAction *showInfo;
        QAction *action5;
        QAction *action6;

        QMap<QString, QStationItem*> *pStationList;
        QMap<QString, QSatelliteItem*> *pSatelliteList;
	public slots:
		void addMessageToEventsList(const QString& message);
		void updateFromModelFile();
		void showGraphsWindow();
        void showConfigWindow();
	protected:
		virtual void wheelEvent(QWheelEvent* event);
	private:
		void mapZoom(qreal factor, QPointF centerPoint);
		void createMenu();
		void createView();
		void createWidgets();
		void createLayout();
		void addStations();
		std::tuple<QString, QString, QString> parseFacts(QXmlStreamReader& xml);
	signals:
		void pause();
};

#endif // MODELVISUALIZER_H
