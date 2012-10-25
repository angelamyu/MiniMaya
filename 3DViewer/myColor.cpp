#include "myColor.h"

myColor::myColor(){
	ka=glm::vec3(0.2,0.2,0.2);
	kd=glm::vec3(0.8,0.8,0.8);
	ks=glm::vec3(0.0,0.0,1.0);

}

myColor::myColor(glm::vec3 ka1,glm::vec3 kd1,glm::vec3 ks1){
	ka=ka1;
	kd=kd1;
	ks=ks1;
}


myColor::~myColor(){



}

myColor* myColor::copy(){
	myColor* temp = new myColor(); 
	temp->ka = ka; 
	temp->kd = kd;
	temp->ks = ks;
	return temp; 
}