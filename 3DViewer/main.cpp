#include "my3dviewer.h"
#include <QtGui/QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
	
	 QApplication a(argc, argv);

	 QPixmap pixmap("splash.png");
	 QSplashScreen splash(pixmap,Qt::WindowStaysOnTopHint);
     //splash.show();
     qApp->processEvents();//This is used to accept a click on the screen so that user can cancel the screen
	 
	My3DViewer w;
	
	QTimer::singleShot(1000, &splash, SLOT(close()));
	QTimer::singleShot(9000, &w, SLOT(slInit())); 
	w.show();
	//splash.finish(&w);
	return a.exec();


}

