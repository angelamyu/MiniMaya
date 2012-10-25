#ifndef MYSAVE_H
#define MYSAVE_H


#include "Mesh.h"
#include <string>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"


class mySave{
public:
	Mesh* save_mesh;
	const char* filename;

public:
	mySave(Mesh*);
	~mySave();

	int saveObj(const char* filename);
};


#endif