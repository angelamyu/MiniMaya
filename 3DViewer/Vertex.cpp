#include "Vertex.h"

Vertex::Vertex(){
	original = true;
}

Vertex::Vertex(float a, float b, float c,int i){
	idV = i; 
	coords = glm::vec3(a,b,c);
	he = NULL;
	original = true;
	basisInitialized=false;
}

Vertex::~Vertex(){

}

Vertex* Vertex::copy(){
	Vertex* temp = new Vertex(); 
	temp->idV = idV; 
	temp->coords = coords; 
	temp->he = he->copy();
	temp->original = original;

	temp->s = s; 
	temp->u = u; 
	temp->t = t; 
	temp->basisInitialized = basisInitialized;
	return temp; 
}