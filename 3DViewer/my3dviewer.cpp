#include "my3dviewer.h"

My3DViewer::My3DViewer(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
}

My3DViewer::~My3DViewer()
{

}

void My3DViewer::slInitialize()
{
setWindowOpacity(1);
}

void My3DViewer::exitWindow(){
    exit(0);
}
