#include "lightDialog.h"

lightDialog::lightDialog(){
	ui.setupUi(this);
}
lightDialog::~lightDialog(){
}

void lightDialog::getPos(QString pos){
 emit sendPos(pos);
}