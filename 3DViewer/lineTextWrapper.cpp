#include "lineTextWrapper.h"


lineTextWrapper::lineTextWrapper(){

}

lineTextWrapper::lineTextWrapper(QWidget* parent) : QLineEdit(parent){

}

lineTextWrapper::~lineTextWrapper(){

}

void lineTextWrapper::gotClickedShaderName(){
	emit signalShaderN(text());
}

void lineTextWrapper::gotClickedLightPos(){
	QString text = this->text();
	signalLightPos(text);
}

void lineTextWrapper::gotClickedRefPoint(){
	QString text = this->text(); 
	emit signalRefPoint(text); 
}

void lineTextWrapper::gotClickedCam(){
	QString text = this->text();
	emit signalSaveCam(text); 
}

void lineTextWrapper::gotDistance(){
    QString text = this->text();
	if(!(text.isEmpty() || text.isNull())){
	float num = text.toFloat();
	emit signalDistance(num);
	}
}