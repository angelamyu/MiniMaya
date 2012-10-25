#ifndef CAMERA_H
#define CAMERA_H

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"

class camera{
private:
	glm::mat4 vm; 
public:
	camera();
	~camera();
	glm::mat4 calcViewMatrix(glm::vec3 eye, glm::vec3 center, glm::vec3 up); 
	glm::vec3 normalizeVec3(glm::vec3 a);

	//glm::mat4 rotationMatrix; 
	//glm::vec3 viewDirection; 
	glm::vec3 upDirection; 
	//glm::vec3 lookVector; 
	glm::vec3 eyePos; 
	glm::vec3 ref; 

	glm::vec3 calcUpVector(glm::vec3,glm::vec3); 
};

#endif 
