#include "extrudeDialog.h"

extrudeDialog::extrudeDialog(){
	ui.setupUi(this);
}
extrudeDialog::~extrudeDialog(){
}

void extrudeDialog::signalDist(float num){
   emit sendDistance(num);
}