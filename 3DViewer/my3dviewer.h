#ifndef STARTERCODE_H
#define STARTERCODE_H

#include <QtGui/QMainWindow>
#include "ui_my3dviewer.h"


class My3DViewer : public QMainWindow
{
	Q_OBJECT

public:
	My3DViewer(QWidget *parent = 0, Qt::WFlags flags = 0);
	~My3DViewer();


public slots:
	void slInitialize(); 
	void exitWindow();

private:
	Ui::My3DViewerClass ui;
};

#endif // STARTERCODE_H
