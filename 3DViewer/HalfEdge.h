#ifndef HALFEDGE_H
#define HALFEDGE_H

#pragma once
#include "FaceHE.h"
#include "Vertex.h"

class FaceHE; 
class Vertex;

class HalfEdge{
public:
	HalfEdge(); 
	HalfEdge(FaceHE* f,Vertex* v ,HalfEdge* n ,HalfEdge* s);
	~HalfEdge();
	bool traversed;
	Vertex* edgept;

	HalfEdge* NEXT; 
	HalfEdge* SYM; 
	FaceHE* F; 
	Vertex* V; 
	HalfEdge* getPrev();
	HalfEdge* copy();
};

#endif 
