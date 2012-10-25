#include "Mesh.h"
#include <iostream>



Mesh::Mesh(){
	vertGL = NULL;
	colorGL = NULL; 
	normalGL = NULL;
	indicesGL = NULL;
	vertexIDCount = 0; 
	faceIDCount = 0; 
}

Mesh::Mesh(vector<Vertex*> v, vector<FaceHE*> f, vector<HalfEdge*> h){
	vertices = v; 
	faces = f; 
	halfEdges = h; 
	vertGL = NULL;
	colorGL = NULL; 
	normalGL = NULL;
	indicesGL = NULL;
	vertexIDCount = 0; 
	faceIDCount = 0; 
}

Mesh::~Mesh(){

}



void Mesh::addVertexToEdge(HalfEdge* HE0, Vertex* VN){
	HalfEdge* symmetric = HE0->SYM;
	HalfEdge* symPointsToSameV = HE0->SYM->F->findPrev(symmetric); 
	Vertex* VPoint = HE0->V;

	HalfEdge *HENL = new HalfEdge(); //HE New Left//
	HalfEdge *HE1 = HE0->NEXT; //HE1 next edge HalfEdge to get next vertex//
	if(HE1->SYM) {
		HalfEdge *HE2 = HE1-> SYM; //HE2 other side of edge //
		HalfEdge *HENR = new HalfEdge(); //HE New Right//
		HENR->NEXT = HE2->NEXT;
		HE2->NEXT = HENR;
		HENL->SYM = HENR;
		HENR->F = HE2->F;
		HENR->SYM= HENL;
		HENR-> V = HE2->V;
		HE2->V = VN;
		halfEdges.push_back(HENR); 
	}
	
	HENL->NEXT = HE1;
	HE0->NEXT = HENL;
	HENL->F = HE0->F;
	HENL->V = VN;
	
	float xAvg = (HE0->V->coords.x + HE1->V->coords.x) / 2.0f;
	float yAvg = (HE0->V->coords.y + HE1->V->coords.y) / 2.0f;
	float zAvg = (HE0->V->coords.z + HE1->V->coords.z) / 2.0f;


	VN->coords.x = xAvg; 
	VN->coords.y = yAvg; 
	VN->coords.z = zAvg; 
	VN->idV = vertexIDCount++; 
	VN->he = HENL;
	vertices.push_back(VN); 
	halfEdges.push_back(HENL); 
	
	createGL(); 
}

void Mesh::addEdgeBetweenTwoFacesShareAVertex(FaceHE* FA,FaceHE* FB, HalfEdge* HEA0, HalfEdge* HEB0){
	if (HEA0->V != HEB0->V)  {
		return;
	}
	Vertex *V1 = new Vertex();
	HalfEdge *HENL = new HalfEdge(); //HE New Left //
	HalfEdge *HENR = new HalfEdge(); //HE New Right//
	HENL->NEXT = HEA0->NEXT;
	HEA0->NEXT = HENL;
	HENL->V = V1;
	HENL->F = HEA0->F; 
	//HENL->F = FA; //////// doesn't effect normal vec lighting
	HENL->SYM = HENR;
	HENR->NEXT = HEB0->NEXT;
	HEB0->NEXT = HENR;
	HENR->V = HEA0->V;
	HEB0->V = V1;
	HENR->F = HEB0->F; 
	//HENR->F = FB; ///////
	HENR->SYM = HENL;

	V1->coords.x = (HEA0->V->coords.x); 
	V1->coords.y = (HEA0->V->coords.y); 
	V1->coords.z = (HEA0->V->coords.z);  
	V1->he = HENL;
	V1->idV = vertexIDCount++; 

	HalfEdge* temp = HENR;
	for(int i = 1; i < HENR->F->countNumberOfhalfEdges(); i++){
		temp->NEXT->F=HENR->F;
		temp = temp->NEXT;
	}

	vertices.push_back(V1);
	halfEdges.push_back(HENL); 
	halfEdges.push_back(HENR); 
}

void Mesh::splitQuadIntoTwoTriangles(FaceHE* FACE1){
	if(FACE1->countNumberOfhalfEdges() != 4){
		return; 
	}
	HalfEdge* HE0 = FACE1->heStart; //starting edge//
	FaceHE *FACE2 = new FaceHE();
	FACE2->colors = FACE1->colors;
	HalfEdge *HEL = new HalfEdge(); //HE New Left //
	HalfEdge *HER = new HalfEdge(); //HE New Right//
	HEL->F = FACE1;
	HER->F = FACE2;
	FACE2->heStart = HER; //FACE1 still points to its starting edge HE0, //
	//and will contain the new HEL in its loop; //
	//new FACE2 points to HER as its new starting edge//
	HEL->SYM = HER;
	HER->SYM = HEL;
	HEL->V = HE0->NEXT->NEXT->V;
	HEL->NEXT = HE0->NEXT->NEXT->NEXT;
	HER->NEXT = HE0->NEXT;
	HER->NEXT->NEXT->NEXT = HER;
	HE0->NEXT = HEL;
	HER->V = HE0->V;

	FACE2->idF=faceIDCount++; 

	faces.push_back(FACE2); 
	halfEdges.push_back(HEL); 
	halfEdges.push_back(HER); 
}

//deletes from faces
void Mesh::deleteFaceFromVector(FaceHE* f){
	for(int i = 0; i < faces.size(); i++){
			if(faces[i] == f){
				faces.erase(faces.begin() + i);
			}
	}
}

//deletes from halfEdges
void Mesh::deleteHalfEdgeFromVector(HalfEdge* h){
	for(int i = 0; i < halfEdges.size(); i++){
			if(halfEdges[i] == h){
				halfEdges.erase(halfEdges.begin() + i); 
			}
	}
}

//deletes from vertices
void Mesh::deleteVertexFromVector(Vertex* v){
	for(int i = 0; i < vertices.size(); i++){
	
			if(vertices[i] == v){
				vertices.erase(vertices.begin() + i); 
			}
	}
}

//needs fixing... more than the quick fix I made, lol
void Mesh::deleteVertex(HalfEdge* e){
vector<HalfEdge*> toBeDeleted;
 HalfEdge* e_next = e->NEXT;
 HalfEdge* temp = e->NEXT->SYM;
 if(!temp && e->SYM){
    temp = e->SYM->getPrev();
 }
 deleteFaceFromVector(e->F);
 deleteVertexFromVector (e->V);
 toBeDeleted.push_back(e);
 toBeDeleted.push_back(e->NEXT);
 while (e_next != e) {
  toBeDeleted.push_back(e_next);
  e_next = e_next->NEXT;
 }

 while (temp && temp != e) {
  //delete all halfedges on the same face as this halfedge
  HalfEdge* temp_next = temp->NEXT;
  //temp_next->sym->sym = NULL; //remove sym pointer from neighbor
  while (temp_next && temp_next != temp) {
   toBeDeleted.push_back(temp_next);
   temp_next = temp_next->NEXT;
  }
  toBeDeleted.push_back(temp);
  //delete the face
  deleteFaceFromVector(temp->F);
  //go to next halfedge on the next face
  temp = temp->NEXT->SYM;
 }
 for (int i = 0; i < toBeDeleted.size(); i++) {
   if(toBeDeleted[i]->SYM){
      toBeDeleted[i]->SYM->SYM = NULL;
   }
   //modify the vertex pointer to an halfedge
   if(toBeDeleted[i] == toBeDeleted[i]->V->he){
	   if( toBeDeleted[i]->NEXT->SYM){
		   toBeDeleted[i]->V->he = toBeDeleted[i]->NEXT->SYM;}
	   else if (toBeDeleted[i]->SYM){
		   if(toBeDeleted[i]->SYM->getPrev()){
			   toBeDeleted[i]->V->he = toBeDeleted[i]->SYM->getPrev();}}
   else{
         deleteVertexFromVector(toBeDeleted[i]->V);
   }
   }
  deleteHalfEdgeFromVector(toBeDeleted[i]);
 }
}		
		
		

//creates float[] to send to the shader
void Mesh::createGL(){
	vector<float> v;
	vector<float> n;
	vector<float> c;
	vector<unsigned int> in;


	int vertCount = 0;


	for(int i = 0; i<faces.size();i++){
		FaceHE* currFace = faces[i];
		int count = currFace->countNumberOfhalfEdges();


		HalfEdge* curredge = currFace->heStart;

		for (int i = 0; i<count-2; i++){
			in.push_back(vertCount);
			in.push_back(vertCount+1+i);
			in.push_back(vertCount+2+i);
		}

		for (int j = 0; j<count; j++){
			/*c.push_back(currFace->colors.x);
			c.push_back(currFace->colors.y);
			c.push_back(currFace->colors.z);
			c.push_back(1.0f);
			*/
			v.push_back(curredge->V->coords.x);
			v.push_back(curredge->V->coords.y);
			v.push_back(curredge->V->coords.z);
			v.push_back(1.0f);
		
			HalfEdge* previous = currFace->findPrev(curredge); 

			glm::vec3 next = currFace->findPrev(curredge)->NEXT->NEXT->V->coords;
			glm::vec3 prev = currFace->findPrev(curredge)->V->coords;
			
			glm::vec3 vector2 = curredge->V->coords - prev;
			glm::vec3 vector1 = next - curredge->V->coords;
			
			glm::vec3 norm = glm::normalize(glm::cross(vector1, vector2));

			int breakcount = 0;
			while(isinf(norm.x)||isinf(norm.y)||isinf(norm.z)){
				next = currFace->findPrev(previous)->NEXT->NEXT->V->coords; 
				prev = currFace->findPrev(previous)->V->coords; 
				
				vector2 = previous->V->coords - prev;
				vector1 = next - previous->V->coords;
				
			    norm = glm::normalize(glm::cross(vector1, vector2));
				previous = currFace->findPrev(previous);
				if (breakcount > 10) {
					norm = glm::vec3(0,0,0);
					break;
				}
				else breakcount++;
			}
			
			n.push_back(norm.x);
			n.push_back(norm.y);
			n.push_back(norm.z);
			n.push_back(0.0f);


			currFace->calcColorsFromMC(); 
			c.push_back(currFace->colors.x);
			c.push_back(currFace->colors.y);
			c.push_back(currFace->colors.z);
			c.push_back(1.0f);

			curredge = currFace->findPrev(curredge)->NEXT->NEXT;

			vertCount++;
		}
	}

	if (normalGL) 
		delete[] normalGL;
	if (indicesGL) 
		delete[] indicesGL;
	if (vertGL) 
		delete[] vertGL;
	if (colorGL) 
		delete[] colorGL;

	normalGL = new float[n.size()];
	colorGL = new float[c.size()];
	vertGL = new float[v.size()];
	indicesGL = new unsigned int[in.size()];
	inNum = in.size();
	num = v.size()/4;

	for (int p = 0; p<in.size();p++){
		indicesGL[p] = in[p];
	}

	for (int p = 0; p<v.size(); p++){
		vertGL[p] = v[p];
		normalGL[p] = n[p];
		colorGL[p] = c[p]; 
	}
}

void Mesh::subdivideMesh(){
	int num = 0;
	int n = halfEdges.size();
	int m = vertices.size();
	int fn = faces.size();
	QProgressDialog pd;
	pd.setCancelButtonText("Cancel");
	pd.setRange(0, fn+fn+m+n+fn+25);
    pd.setWindowTitle("Subdivision");
	pd.setLabelText("Running Program");
	pd.open();


	for (int ii = 0; ii < fn; ii++) {
		FaceHE* f = faces[ii];
		this->facePoint(f); //compute face points
		pd.setValue(num++);
	}
	
	//store a temporary vector of halfedges in the current face
	vector<vector<HalfEdge*>> hes;
	for (int ii = 0; ii < fn; ii++) {
		vector<HalfEdge*> he;
		FaceHE* f = faces[ii];
		int n = f->countNumberOfhalfEdges();
		for (int jj = 0; jj < n; jj++) {
			HalfEdge* e = f->getHE(jj);
			he.push_back(e);
			this->edgePoint(e); //compute each edge point
			if (!(e->SYM) || !(e->SYM->traversed)) e->traversed = true;
		}
		hes.push_back(he);
		pd.setValue(num++);
	}

	//move the original points to the appropriate locations
	for (int ii = 0; ii < m; ii++) {
		Vertex* v = vertices[ii];
		this->vertexPoint(v);
		pd.setValue(num++);
	}
	//insert all the edge points
	for (int ii = 0; ii < n; ii++) {
		if (!(halfEdges[ii]->traversed)) {
			HalfEdge* sym = halfEdges[ii]->SYM;
			Vertex* v = new Vertex();
			newVertex(halfEdges[ii]->getPrev(), v);
			v->coords.x = halfEdges[ii]->edgept->coords.x;
			v->coords.y = halfEdges[ii]->edgept->coords.y;
			v->coords.z = halfEdges[ii]->edgept->coords.z;
			v->idV = vertexIDCount++;
			halfEdges[ii]->edgept = v;
			sym->edgept = v;
		}
			pd.setValue(num++);
	}


	for (int ii = 0; ii < fn; ii++) {
		FaceHE* f = faces[ii];
		vector<FaceHE*> newfaces; //to store new faces. used for sym pairings.
		newfaces.push_back(f);
		//vertices.push_back(f->facept);
		f->facept->he = hes[ii][0];
		for (int jj = 0; jj < hes[ii].size(); jj++) {
			FaceHE* newf = NULL;
			if (jj == 0) newf = f;
			else {
				newf = new FaceHE();
				newf->colors = f->colors;
				faces.push_back(newf);
				newfaces.push_back(newf);
				newf->idF = this->faceIDCount++;
			}

			HalfEdge* he1 = hes[ii][jj];
			HalfEdge* he2 = hes[ii][jj]->NEXT;
			HalfEdge* he3 = new HalfEdge();
			HalfEdge* he4 = new HalfEdge();
			halfEdges.push_back(he3);
			halfEdges.push_back(he4);
			newf->heStart = he1;
			he1->F = newf;
			he2->F = newf;
			he3->F = newf;
			he4->F = newf;
			he2->NEXT = he3;
			he3->NEXT = he4;
			he4->NEXT = he1;
			he3->V = f->facept;
			f->facept->he = he3;
			he4->V = he1->edgept;
			he1->edgept->he = he4;
			pd.setValue(num++);
		}
		for (int ii = 0; ii < newfaces.size(); ii++) {
			HalfEdge* a = newfaces[ii]->getHE(2);
			HalfEdge* b = (HalfEdge*)(11);
			if (ii + 1 < newfaces.size()) b = newfaces[ii + 1]->getHE(3);
			else b = newfaces[0]->getHE(3);
			a->SYM = b;
			b->SYM = a;
		}
		pd.setValue(num+=25);
	}

}

void Mesh::facePoint(FaceHE* face){
    Vertex* fpt = new Vertex();
	glm::vec3 pos = glm::vec3(0.0f,0.0f,0.0f);
	HalfEdge* current = face->heStart;
	int num = face->countNumberOfhalfEdges();
	for(int i = 0 ; i < num; i++){
	    pos = pos + current->V->coords; // add the position together
		current = current->NEXT;
	}
	pos = glm::vec3(pos[0]/num,pos[1]/num,pos[2]/num); // get the average
	fpt->coords = pos;
	fpt->original = false;
	fpt->idV = vertexIDCount++;
	//what about the halfEdge????
	face->facept = fpt; // set the facefpt;
	vertices.push_back(fpt);
}

glm::vec3 Mesh::edgePoint(HalfEdge* edge){
	Vertex* fpt1 = edge->F->facept;
	Vertex* fpt2 = edge->SYM->F->facept;
	Vertex* prev = edge->getPrev()->V;
	Vertex* curr = edge->V;
	glm::vec3 newPos = fpt1->coords + fpt2->coords + prev->coords + curr->coords;
	newPos = glm::vec3(newPos[0]/4,newPos[1]/4,newPos[2]/4);
	edge->edgept = new Vertex();
	edge->edgept->idV = this->vertexIDCount;
	edge->edgept->coords.x = newPos.x;
	edge->edgept->coords.y = newPos.y;
	edge->edgept->coords.z = newPos.z;
	//halfedge??
	return newPos;
}

void Mesh::vertexPoint(Vertex* v){
    HalfEdge* start = v->he;
	HalfEdge* next = start->NEXT->SYM;

	FaceHE* current = start->F;
	glm::vec3 averF = current->facept->coords;
	glm::vec3 averE = start->edgept->coords;
	float n = 1;
	while(next != start){
		averE = averE + next->edgept->coords;
	    current = next->F;
		averF = averF + current->facept->coords;
		next = next->NEXT->SYM;
		n+=1;
	}
	averF = glm::vec3(averF[0]/(n*n),averF[1]/(n*n),
		averF[2]/(n*n));
	averE = glm::vec3(averE[0]/(n*n), averE[1]/(n*n), 
		averE[2]/(n*n));
	glm::vec3 control = v->coords;
	float num = (n-2)/n;
	float num1 = 1.0f/3.0f;
	control = 
		glm::vec3(num*control[0],num*control[1],
		num*control[2]);
	v->coords = averF + averE + control;

}



void Mesh::newVertex(HalfEdge* HE0, Vertex* VN){
	HalfEdge* HE1 = HE0->NEXT;             //HE1 next edge HalfEdge to get next vertex//  
	HalfEdge* HE2 = HE1->SYM;             //HE2 other side of edge //  
	HalfEdge* HENL = new HalfEdge();     //HE New Left//  
	HalfEdge* HENR = new HalfEdge();     //HE New Right// 
	HalfEdge* HE2P = HE2->getPrev();
	//Vertex* VN = new Vertex(0,0,0,vertexIDCount++);
	vertices.push_back(VN);
	halfEdges.push_back(HENL);
	halfEdges.push_back(HENR);
	VN->he = HENL;
	HENL->NEXT = HE1;  
	HE0->NEXT = HENL;  
	HENR->NEXT = HE2;  
	HENL->SYM = HE2;
	HENR->SYM = HE1;
	HE2->SYM = HENL;
	HE1->SYM = HENR;
	HENL->F = HE0->F;  
	HENR->F = HE2->F;  
	HENL->V = VN;  
	HENR->V = VN; 
	HE2P->NEXT = HENR;  
	VN->coords.x = (HE0->V->coords.x + HE1->V->coords.x)/2.0f; 
	VN->coords.y = (HE0->V->coords.y + HE1->V->coords.y)/2.0f; 
	VN->coords.z = (HE0->V->coords.z + HE1->V->coords.z)/2.0f;
	
	createGL(); 
}


void Mesh::extrude(FaceHE* selected, float n){
//check if the face is planar	
if(selected->checkFacePlanar()){
	//create the new faces
	HalfEdge* current = selected->heStart;
	int num = selected->countNumberOfhalfEdges();
	for(int i = 0 ; i < num;i++){
	 	HalfEdge* currSym = current->SYM;
		FaceHE* newF = new FaceHE();
		newF->colors = currSym->F->colors;
		newF->idF = faceIDCount++;

		 HalfEdge* newE1 = new HalfEdge();
		 HalfEdge* newE2 = new HalfEdge();
		 HalfEdge* newE3 = new HalfEdge();
		 HalfEdge* newE4 = new HalfEdge();

		 //set the faces of the halfEdges
		 newF->heStart = newE1;
		 newE1->F = newF;
		 newE2->F = newF;
		 newE3->F = newF;
		 newE4->F = newF;

		 //set the NEXT of the halfEdges
		 newE1->NEXT = newE2;
		 newE2->NEXT = newE3;
		 newE3->NEXT = newE4;
		 newE4->NEXT = newE1;

		 //set the V of the halfEdges

		 Vertex* newV1 = new Vertex();
		 Vertex* newV2 = new Vertex();
	
		 newV1->coords = currSym->V->coords;
		 newV2->coords = current->V->coords;
		 newV1->idV = vertexIDCount++;
		 newV2->idV = vertexIDCount++;
		 
		 newE1->V = newV2;
		 newE2->V = current->V;
		 newE3->V = current->getPrev()->V;
		 newE4->V= newV1;

		 //modify the old halfedges

		 currSym->getPrev()->V = newV2;
		 currSym->V = newV1;
		 
		 
		 //just in case: change the hestart of the vertices
		 newV2->he = newE1;
		 current->V->he = newE2;
		 current->getPrev()->V->he = newE3;
		 newV1->he = newE4;

		 //begin to set up SYM
		 current->SYM = newE3;
		 currSym->SYM = newE1;
		 newE3->SYM = current;
		 newE1->SYM = currSym;

		 //add the newly created items into the list
		 faces.push_back(newF);
		 vertices.push_back(newV1);
		 vertices.push_back(newV2);
		 halfEdges.push_back(newE1);
		 halfEdges.push_back(newE2);
		 halfEdges.push_back(newE3);
		 halfEdges.push_back(newE4);

		 current = current->NEXT;
	}
	extrudepts(selected,n);
	for(int i = num ; i > 1; i--){
	   FaceHE* currF = faces[faces.size()-i];
	   FaceHE* nextF = faces[faces.size()- i + 1];
	   currF->heStart->NEXT->SYM = nextF->heStart->getPrev();
	   nextF->heStart->getPrev()->SYM = currF->heStart->NEXT;
	}
	   FaceHE* currF = faces[faces.size()-1];
	   FaceHE* nextF = faces[faces.size()- num];
	   currF->heStart->NEXT->SYM = nextF->heStart->getPrev();
	   nextF->heStart->getPrev()->SYM = currF->heStart->NEXT;
}
}

void Mesh::extrudepts(FaceHE* selected, float n){
	//calculate the displacement
	glm::vec3 d = -selected->calcNormal();
	d = glm::vec3(d[0]*n, d[1]*n, d[2]*n);
    
	//recalculate the position of that face
	HalfEdge* current = selected->heStart;
    for(int i = 0 ; i < selected->countNumberOfhalfEdges();i++){
		Vertex* v = current->V;
		v->coords = v->coords + d;
	    current = current -> NEXT;
	}
    
}