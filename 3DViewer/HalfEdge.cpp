#include "HalfEdge.h"

HalfEdge::HalfEdge(){
	traversed = false;
	edgept = NULL;
	F= NULL;
	V = NULL;
	SYM = NULL;
	NEXT = NULL;
}

HalfEdge::HalfEdge(FaceHE* f,Vertex* v ,HalfEdge* n,HalfEdge* s){
	F = f; 
	V = v; 
	NEXT = n; 
	SYM = s;
	traversed = false;
	edgept = NULL;
}

HalfEdge::~HalfEdge(){

}

HalfEdge* HalfEdge::getPrev(){ 
	HalfEdge* check = NEXT; //start checking from the next one
    while (check->NEXT != this){ 
	  check = check->NEXT;
	}
	return check; 
}

HalfEdge* HalfEdge::copy(){
	HalfEdge* temp = new HalfEdge(); 


	temp->traversed = traversed;
	temp->edgept = edgept->copy();

	temp->NEXT = temp->NEXT->copy(); 
	temp->SYM = temp->SYM->copy(); 
	//temp->F;//copy 
	temp->V = temp->V->copy(); 

	return temp; 
}