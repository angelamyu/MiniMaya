#ifndef LIGHTDIALOG_H
#define LIGHTDIALOG_H

#include <QDialog>
#include "ui_lightdialog.h"

class lightDialog : public QDialog
{
	Q_OBJECT

public:
	lightDialog();
	~lightDialog();

public slots:
    void getPos(QString);

signals:
	void sendPos(QString);

private:
	Ui::Dialog ui;

};

#endif