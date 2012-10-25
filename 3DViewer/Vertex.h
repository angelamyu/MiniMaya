#ifndef VERTEX_H
#define VERTEX_H

#pragma once
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include <vector>
#include "HalfEdge.h"

using namespace std;

class HalfEdge;

class Vertex{
	//Q_OBJECT
public:
	Vertex(); 
	Vertex(float,float,float,int);
	~Vertex();

	int idV; 
	glm::vec3 coords; 
	HalfEdge* he;
	bool original;

	float s,t,u;
	bool basisInitialized;
	Vertex* copy(); 
};

#endif 
