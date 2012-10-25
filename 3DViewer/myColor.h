#ifndef MYCOLOR_H
#define MYCOLOR_H

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"

class myColor{
public:
	glm::vec3 ka,kd,ks;

public:
	myColor();
	myColor(glm::vec3,glm::vec3,glm::vec3);
	~myColor();

	myColor* copy(); 
};


#endif