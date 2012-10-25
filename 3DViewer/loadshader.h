#ifndef LOADSHADER_H
#define LOADSHADER_H

#include <QDialog>
#include "ui_loadshader.h"

class loadshader : public QDialog
{
	Q_OBJECT

public:
	loadshader();
	~loadshader();

public slots:
		void signalname(QString);
signals:
		void sendName(QString);

private:
	Ui::ShaderLoader ui;
};

#endif