#include "FaceHE.h"
#include <iostream>

using namespace std;
FaceHE::FaceHE(){
	facept = NULL;
	mCFlag = false; 
}

FaceHE::FaceHE(HalfEdge* h ,glm::vec3 c , int i){
	heStart = h; 
	colors =c; 
	idF = i; 
	facept = NULL;
	mCFlag = false; 
}


FaceHE::FaceHE(HalfEdge* h ,myColor* c , int i){
	heStart = h; 
	mC=c;
	colors=c->kd;
	idF = i; 
	facept = NULL;
	mCFlag = true; 
}

FaceHE::~FaceHE(){

}

//finds previous edge
HalfEdge* FaceHE::findPrev(HalfEdge* h){
	HalfEdge* curr = h;
	while (curr->NEXT!=h){
		curr = curr->NEXT;
	}
	return curr;
}

//count # of HEs
int FaceHE::countNumberOfhalfEdges(){
	HalfEdge* curr = heStart;
	int count = 1;
	while(curr->NEXT!=heStart){
		curr = curr->NEXT;
		count++;
	}
	return count;
}

//returns true if it does contain that HE
bool FaceHE::containsHE(HalfEdge* h){
	HalfEdge* curr = heStart;
	for(int i =0; i<countNumberOfhalfEdges(); i++){
		if(curr == h){
			return true; 
		}
		curr = curr->NEXT;
	}
	return false;
}

//returns true if it does contain that Vertex
bool FaceHE::containsVertex(Vertex* v){
	HalfEdge* curr = heStart;
	for(int i =0; i<countNumberOfhalfEdges(); i++){
		if(curr->V == v){
			return true; 
		}
		curr = curr->NEXT;
	}
	return false;
}

//gets the HE at the "index" (heStart->...->ith index)
HalfEdge* FaceHE::getHE(int index) {
	HalfEdge* result = heStart;
	while (index > 0) {
		index--;
		result = result->NEXT;
	}
	return result;
}

//checks if the polygon contains the point the user clicked on
bool FaceHE::containsPoint(glm::vec3 p) {
	glm::vec3 p0 = heStart->V->coords;

	for (int i = 1; i < countNumberOfhalfEdges(); i++) {
		glm::vec3 p1 = getHE(i)->V->coords;
		glm::vec3 p2 = getHE(i + 1)->V->coords;
		if (triContainsPoint(p, p0, p1, p2)) {
			return true;
		}
	}
	return false;
}

//checks if point is in a triangular region
bool FaceHE::triContainsPoint(glm::vec3 p, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
	float totalarea = getTriArea(p1, p2, p3);
	float area1 = getTriArea(p, p1, p2)/totalarea;
	float area2 = getTriArea(p, p2, p3)/totalarea;
	float area3 = getTriArea(p, p1, p3)/totalarea;

	if (area1 + area2 + area3 - 1.0f < FLT_EPSILON) {
		return true;
	}
	else {
		return false;
 }
}

//gets area of a triangular area
float FaceHE::getTriArea(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
	glm::mat3 m1(
		p1.y, p1.z, 1,
		p2.y, p2.z, 1,
		p3.y, p3.z, 1
		);
	glm::mat3 m2(
		p1.z, p1.x, 1,
		p2.z, p2.x, 1,
		p3.z, p3.x, 1
		);
	glm::mat3 m3(
		p1.x, p1.y, 1,
		p2.x, p2.y, 1,
		p3.x, p3.y, 1
		);

	float area = 0.5f*sqrt(pow(glm::determinant(m1), 2.0f) + pow(glm::determinant(m2), 2.0f) + pow(glm::determinant(m3), 2.0f));
	return area;
}

//checks if planar, only for convex things I believe
bool FaceHE::checkFacePlanar(){
	HalfEdge* current = heStart; 
	HalfEdge* previous = findPrev(current); 

			glm::vec3 next = findPrev(current)->NEXT->NEXT->V->coords;
			glm::vec3 prev = findPrev(current)->V->coords;
			
			glm::vec3 vector2 = current->V->coords - prev;
			glm::vec3 vector1 = next - current->V->coords;
			
			glm::vec3 normcheck = glm::normalize(glm::cross(vector1, vector2));
			glm::vec3 norm = glm::normalize(glm::cross(vector1, vector2));

			HalfEdge* currentH = heStart; 
		HalfEdge* nextH = (heStart->NEXT);
		HalfEdge* prevH = (findPrev(heStart));

		while(isinf(normcheck.x)||isinf(normcheck.y)||isinf(normcheck.z)){
				currentH = currentH->NEXT; 
				nextH = nextH->NEXT; 
				prevH = prevH->NEXT; 
				vector1 = glm::vec3((currentH)->V->coords - (prevH)->V->coords);
				vector2 = glm::vec3((nextH)->V->coords - (currentH)->V->coords);
				normcheck = glm::cross(vector1, vector2); 
		}

	for(int i = 0; i < countNumberOfhalfEdges(); i++){
		 previous = findPrev(current); 

			next = findPrev(current)->NEXT->NEXT->V->coords;
			prev = findPrev(current)->V->coords;
			
			vector2 = current->V->coords - prev;
			vector1 = next - current->V->coords;
			
			norm = glm::normalize(glm::cross(vector1, vector2));



			if(!(norm.x==normcheck.x && norm.y==normcheck.y && norm.z == normcheck.z)&&(!isinf(norm.x)&&!isinf(norm.y)&&!isinf(norm.z))){
				return false; 
				break; 
			}

			current = findPrev(current)->NEXT->NEXT;
	}

}

//calculates t, for picking and ray generation
float FaceHE::calcT(glm::vec3 p1, glm::vec3 p2){
	if(checkFacePlanar()){
		glm::vec3 vector1 = glm::vec3((heStart)->V->coords - (findPrev(heStart))->V->coords);
		glm::vec3 vector2 = glm::vec3((heStart->NEXT)->V->coords - (heStart)->V->coords);

		glm::vec3 normal = glm::cross(vector1, vector2);
		glm::vec3 D = glm::normalize(p2-p1); 

		HalfEdge* current = heStart; 
		HalfEdge* next = (heStart->NEXT);
		HalfEdge* prev = (findPrev(heStart));

		while(isinf(normal.x)||isinf(normal.y)||isinf(normal.z)){
			current = current->NEXT; 
			next = next->NEXT; 
			prev = prev->NEXT; 
			vector1 = glm::vec3((current)->V->coords - (prev)->V->coords);
			vector2 = glm::vec3((next)->V->coords - (current)->V->coords);
			normal = glm::cross(vector1, vector2); 
		}

		float t = (glm::dot(normal, heStart->V->coords - p1)) / (glm::dot(normal, D)); 
		return t; 
	}
	else{

	}
}

float FaceHE::calcT(glm::vec3 p1, glm::vec3 p2, glm::vec3 v1, glm::vec3 v2){
	glm::vec3 vector1 = v1;
		glm::vec3 vector2 = v2;

		glm::vec3 normal = glm::cross(vector1, vector2);
		glm::vec3 D = glm::normalize(p2-p1); 

		HalfEdge* current = heStart; 
		HalfEdge* next = (heStart->NEXT);
		HalfEdge* prev = (findPrev(heStart));

		while(isinf(normal.x)||isinf(normal.y)||isinf(normal.z)){
			current = current->NEXT; 
			next = next->NEXT; 
			prev = prev->NEXT; 
			vector1 = glm::vec3((current)->V->coords - (prev)->V->coords);
			vector2 = glm::vec3((next)->V->coords - (current)->V->coords);
			normal = glm::cross(vector1, vector2); 
		}

		float t = (glm::dot(normal, heStart->V->coords - p1)) / (glm::dot(normal, D)); 
		return t; 
}

//get HE with vector V
HalfEdge* FaceHE::getEdgeThatPointsToV(Vertex* v){
	//you should always check that it has the vertex
	HalfEdge* result = heStart; 
	for(int i = 0; i< countNumberOfhalfEdges(); i++){
		if(result->V == v){
			break; 
		}
		else{
			result = result->NEXT; 
		}
	}
	return result; 
}

glm::vec3 FaceHE::calcNormal(){

		HalfEdge* current = heStart; 
		HalfEdge* previous = findPrev(current); 

		glm::vec3 next = current->NEXT->V->coords;
		glm::vec3 prev = findPrev(current)->V->coords;
			
		glm::vec3 vector2 = current->V->coords - prev;
		glm::vec3 vector1 = next - current->V->coords;
			
		glm::vec3 norm = glm::normalize(glm::cross(vector1, vector2));

		return norm;
}

void FaceHE::calcColorsFromMC(){
	if(mCFlag){
		mCFlag = false; 
		colors.x = mC->kd.x; 
		colors.y = mC->kd.y; 
		colors.z = mC->kd.z; 
	}
}

FaceHE* FaceHE::copy(){
	FaceHE* temp = new FaceHE(); 
	temp->mCFlag= mCFlag; 
	//temp->facept = facept->copy();

	temp->heStart =  heStart->copy(); //first halfedge stored
	temp->colors =  colors; 
	temp->mC = mC;
	temp->idF = idF; //face's id
	temp->t = t; 

	return temp; 
}