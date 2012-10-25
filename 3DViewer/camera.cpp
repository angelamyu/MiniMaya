#include "camera.h"

camera::camera(){
	upDirection = glm::vec3(0,1,0); 
	eyePos = glm::vec3(3.53553,0.0f,3.53553); 
	ref = glm::vec3(0,0,0); 
}

camera::~camera(){

}

glm::vec3 camera::normalizeVec3(glm::vec3 a){
	float mag = sqrt(a[0] * a.x + a.y*a.y + a.z*a.z); 
	float xn = a.x / mag;
	float yn = a.y / mag; 
	float zn = a.z / mag; 
	return glm::vec3(xn,yn,zn); 
}

glm::mat4 camera::calcViewMatrix(glm::vec3 eye, glm::vec3 center, glm::vec3 up){
	/// up is 0,1,0
	eyePos = eye; 
	upDirection = up; 
	ref = center; 
	glm::vec3 f = glm::normalize(center - eye);
	glm::vec3 u = glm::normalize(up);
	glm::vec3 s = glm::normalize(glm::cross(f, u));
        u = glm::cross(s, f);

        vm[0][0] = s[0];
        vm[1][0] = s[1];
        vm[2][0] = s[2];
        vm[0][1] = u[0];
        vm[1][1] = u[1];
        vm[2][1] = u[2];
        vm[0][2] =-f[0];
        vm[1][2] =-f[1];
        vm[2][2] =-f[2];
        vm[3][0] =-1* glm::dot(s, eye);
        vm[3][1] =-1 * glm::dot(u, eye);
        vm[3][2] =  glm::dot(f, eye);
      

		return vm; 
}


glm::vec3 camera::calcUpVector(glm::vec3 eye, glm::vec3 center){
	glm::vec3 lookV = glm::normalize(center - eye);
	glm::vec3 temp = glm::cross(lookV, glm::vec3(0,1,0));
	upDirection = glm::cross(lookV, temp);
	return glm::cross(lookV, temp); 
}