#ifndef FACEHE_H
#define FACEHE_H

#pragma once
#include "HalfEdge.h"
#include "Vertex.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "myColor.h"

class HalfEdge; 
class Vertex; 

template<typename T> inline bool isinf( T value ) {
    return value != value;
}

class FaceHE{
public:
	FaceHE(); 
	FaceHE(HalfEdge*,glm::vec3, int);
	FaceHE(HalfEdge*, myColor*,int);
	~FaceHE();
	Vertex* facept;

	HalfEdge* heStart; //first halfedge stored
	glm::vec3 colors; 
	myColor* mC;
	int idF; //face's id
	float t; 
	
	HalfEdge* findPrev(HalfEdge*);
	HalfEdge* getHE(int index);
	bool containsHE(HalfEdge*); 
	bool containsVertex(Vertex*); 
	bool containsPoint(glm::vec3 p);
	bool triContainsPoint(glm::vec3 p, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
	static float getTriArea(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
	int countNumberOfhalfEdges(); 
	HalfEdge* getEdgeThatPointsToV(Vertex* v); 
	glm::vec3 calcNormal();

	bool checkFacePlanar(); 
	float calcT(glm::vec3, glm::vec3); 
	float calcT(glm::vec3, glm::vec3, glm::vec3, glm::vec3);

	bool mCFlag; 
	void calcColorsFromMC(); 
	FaceHE* copy(); 
};

#endif 
