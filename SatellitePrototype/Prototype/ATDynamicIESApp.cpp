#include <QtCore/QTimer>
#include "ATDynamicIESApp.h"
#include "ModelVisualizer.h"
#include "Wrapper.h"

ATDynamicIESApp::ATDynamicIESApp(int & argc ,char** argv)
	:QApplication(argc, argv)
{	
    pVisualizer = new ModelVisualizer();
    pWrapper = new Wrapper();
	pTickTimer = new QTimer(this);
	connect(pTickTimer, SIGNAL(timeout()), this, SLOT(reachNextState()));
    pWrapper->configurate();
	pTickTimer->start(500);
	state = 0;
    connect(pVisualizer->startSim, SIGNAL(triggered()), pTickTimer, SLOT(start()));
    connect(pVisualizer->pauseSim, SIGNAL(triggered()), pTickTimer, SLOT(stop()));
}

ATDynamicIESApp::~ATDynamicIESApp()
{
	pTickTimer->stop();
	delete pTickTimer;
    delete pVisualizer;
    delete pWrapper;
}

ModelVisualizer* ATDynamicIESApp::getVisualazer()
{
    return pVisualizer;
}

void ATDynamicIESApp::reachNextState()
{
	switch (state)
	{
		case 0:
            pWrapper->processModelTact();
			++state;
			break;
		case 1:
            pWrapper->processSolversTact();
			++state;
			break;
		case 2:
            pVisualizer->updateFromModelFile();
			state = 0;
			break;
	}
}
