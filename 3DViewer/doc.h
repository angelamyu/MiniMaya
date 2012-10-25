#ifndef DOC_H
#define DOC_H

#include <QDialog>
#include "ui_doc.h"

class doc : public QDialog
{
	Q_OBJECT

public:
	doc();
	~doc();

private:
	Ui::doc ui;
};

#endif