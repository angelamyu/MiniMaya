#ifndef EXTRUDEDIALOG_H
#define EXTRUDEDIALOG_H

#include <QDialog>
#include "ui_extrudedialog.h"

class extrudeDialog : public QDialog
{
	Q_OBJECT

public:
	extrudeDialog();
	~extrudeDialog();
	public slots:
		void signalDist(float);
signals:
		void sendDistance(float);

private:
	Ui::SetDistance ui;
};

#endif