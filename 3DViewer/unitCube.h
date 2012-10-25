#ifndef UNITCUBE_H
#define UNITCUBE_H



#pragma once
#include "Vertex.h"
#include <vector>
#include "FaceHE.h"
#include "HalfEdge.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "Mesh.h"

class FaceHE; 
class HalfEdge; 


using namespace std;


class unitCube: public Mesh{
public:
	unitCube();
	unitCube(glm::vec3 loc, float a);
	~unitCube();

	float ab;

	glm::vec3 centerPoint;
	float* verticesCube; 
	float* normalsCube;
	float* colorsCube;
	unsigned int* indicesCube; 

	float* getVerticesCube(); 
	float* getNormalsCube();
	float* getColorsCube();
	unsigned int* getIndicesCube(); 

	

	void addVertexToEdge(HalfEdge* h, Vertex* v); 
	void addEdgeBetweenTwoFacesShareAVertex(FaceHE* FA,FaceHE* FB, HalfEdge* HEA0, HalfEdge* HEB0); 
	void splitQuadIntoTwoTriangles(FaceHE* FACE1); 
};

#endif 
