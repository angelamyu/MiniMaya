#include "loadshader.h"

loadshader::loadshader(){
	ui.setupUi(this);
}
loadshader::~loadshader(){
}

void loadshader::signalname(QString name){
 emit sendName(name);
}