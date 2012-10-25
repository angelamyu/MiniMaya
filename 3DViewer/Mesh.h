#ifndef MESH_H
#define MESH_H

#pragma once
#include "Vertex.h"
#include <vector>
#include "FaceHE.h"
#include "HalfEdge.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include <iostream>
#include <sstream>
#include <QProgressDialog>


using namespace std;

class FaceHE; 
class HalfEdge; 

//template to check for #INF values
//template<typename T> inline bool isinf( T value ) {
   // return value != value;
//}

using namespace std;


class Mesh{

public:
	Mesh();
	Mesh(vector<Vertex*> v, vector<FaceHE*> f, vector<HalfEdge*> h);
	~Mesh();

	vector<Vertex*> vertices; 
	vector<FaceHE*> faces; 
	vector<HalfEdge*> halfEdges; 

	//storing the new edge vertex

	//the flattened arrays for GLWidget
	float* vertGL;
	float* normalGL;
	float* colorGL;
	unsigned int* indicesGL;

	int inNum, num;

	void createGL();

	int vertexIDCount; 
	int faceIDCount; 

	void addVertexToEdge(HalfEdge* h, Vertex* v); 
	void addEdgeBetweenTwoFacesShareAVertex(FaceHE* FA,FaceHE* FB, HalfEdge* HEA0, HalfEdge* HEB0); 
	void splitQuadIntoTwoTriangles(FaceHE* FACE1); 
	void deleteVertex(HalfEdge* h );
	void subdivideMesh();
	//helper methods for subdividing
	void facePoint(FaceHE*);
	glm::vec3 edgePoint(HalfEdge*);
	void vertexPoint(Vertex*);
	void newVertex(HalfEdge* h, Vertex* v);
	void extrude(FaceHE*, float);
	void extrudepts(FaceHE*, float);


	void deleteFaceFromVector(FaceHE* f); 
	void deleteHalfEdgeFromVector(HalfEdge* h);
	void deleteVertexFromVector(Vertex* v); 


	
};

#endif 
