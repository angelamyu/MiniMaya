#ifndef LINETEXTWRAPPER
#define LINETEXTWRAPPER

#include <QLineEdit>
#include "../glm/glm.hpp"

class lineTextWrapper:public QLineEdit{
	Q_OBJECT

public:
	typedef QLineEdit super;
	lineTextWrapper();
	lineTextWrapper(QWidget*); 
	~lineTextWrapper();

public slots:
	void gotClickedShaderName();
	void gotClickedLightPos();
	void gotClickedRefPoint();
	void gotClickedCam(); 
	void gotDistance();
signals:
	void signalShaderN(QString); 
	void signalLightPos(QString);
	void signalRefPoint(QString); 
	void signalSaveCam(QString);
	void signalDistance(float);
};

#endif