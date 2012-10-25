#include "unitCube.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"

unitCube::unitCube():Mesh(){
	vertexIDCount = 8; 
	faceIDCount = 6; 

	for(int i = 0; i<6; i++){
		faces.push_back(new FaceHE());

		for (int j = 0; j<4; j++){
			halfEdges.push_back(new HalfEdge());
		 } 
	}

 faces[0]->idF = 0;
 faces[1]->idF = 1;
 faces[2]->idF = 2;
 faces[3]->idF = 3;
 faces[4]->idF = 4;
 faces[5]->idF = 5;

 faces[0]->heStart = halfEdges[0];
 faces[1]->heStart = halfEdges[4];
 faces[2]->heStart = halfEdges[8];
 faces[3]->heStart = halfEdges[12];
 faces[4]->heStart = halfEdges[16];
 faces[5]->heStart = halfEdges[20];

 faces[0]->colors = glm::vec3(1,1,1);
 faces[1]->colors = glm::vec3(1,0,0);
 faces[2]->colors = glm::vec3(0,1,0);
 faces[3]->colors = glm::vec3(0,0,1);
 faces[4]->colors = glm::vec3(0,1,1);
 faces[5]->colors = glm::vec3(1,0,1);

 for (int i = 0; i<8; i++){
  Vertex* newv = new Vertex();
  newv->idV = i;
  vertices.push_back(newv);

 }

 vertices[0]->coords = glm::vec3(-1,1,-1);
 vertices[1]->coords = glm::vec3(1,1,-1);
 vertices[2]->coords = glm::vec3(-1,1,1);
 vertices[3]->coords = glm::vec3(1,1,1);
 vertices[4]->coords = glm::vec3(-1,-1,1);
 vertices[5]->coords = glm::vec3(1,-1,1);
 vertices[6]->coords = glm::vec3(-1,-1,-1);
 vertices[7]->coords = glm::vec3(1,-1,-1);

 //vertices pointer to halfedges
 vertices[0]->he = halfEdges[0];
 vertices[1]->he = halfEdges[3];
 vertices[2]->he = halfEdges[1];
 vertices[3]->he = halfEdges[2];
 vertices[4]->he = halfEdges[6];
 vertices[5]->he = halfEdges[10];
 vertices[6]->he = halfEdges[5];
 vertices[7]->he = halfEdges[14];
 



 
 halfEdges[0]->NEXT = halfEdges[1];
 halfEdges[1]->NEXT = halfEdges[2];
 halfEdges[2]->NEXT = halfEdges[3];
 halfEdges[3]->NEXT = halfEdges[0];
 halfEdges[4]->NEXT = halfEdges[5];
 halfEdges[5]->NEXT = halfEdges[6];
 halfEdges[6]->NEXT = halfEdges[7];
 halfEdges[7]->NEXT = halfEdges[4];
 halfEdges[8]->NEXT = halfEdges[9];
 halfEdges[9]->NEXT = halfEdges[10];
 halfEdges[10]->NEXT = halfEdges[11];
 halfEdges[11]->NEXT = halfEdges[8];
 halfEdges[12]->NEXT = halfEdges[13];
 halfEdges[13]->NEXT = halfEdges[14];
 halfEdges[14]->NEXT = halfEdges[15];
 halfEdges[15]->NEXT = halfEdges[12];
 halfEdges[16]->NEXT = halfEdges[17];
 halfEdges[17]->NEXT = halfEdges[18];
 halfEdges[18]->NEXT = halfEdges[19];
 halfEdges[19]->NEXT = halfEdges[16];
 halfEdges[20]->NEXT = halfEdges[21];
 halfEdges[21]->NEXT = halfEdges[22];
 halfEdges[22]->NEXT = halfEdges[23];
 halfEdges[23]->NEXT = halfEdges[20];

 
  halfEdges[0]->SYM=halfEdges[16]; //
  halfEdges[1]->SYM=halfEdges[4]; //
  halfEdges[2]->SYM=halfEdges[8]; //
  halfEdges[3]->SYM=halfEdges[12]; //
  halfEdges[16]->SYM=halfEdges[0]; //
  halfEdges[17]->SYM=halfEdges[15]; //
  halfEdges[18]->SYM=halfEdges[22];
  halfEdges[19]->SYM=halfEdges[5]; //
  halfEdges[4]->SYM=halfEdges[1]; //
  halfEdges[5]->SYM=halfEdges[19];
  halfEdges[6]->SYM=halfEdges[21]; //
  halfEdges[7]->SYM=halfEdges[9]; //
  halfEdges[8]->SYM=halfEdges[2]; //
  halfEdges[9]->SYM=halfEdges[7]; //
  halfEdges[10]->SYM=halfEdges[20];
  halfEdges[11]->SYM=halfEdges[13]; //
  halfEdges[12]->SYM=halfEdges[3]; //
  halfEdges[13]->SYM=halfEdges[11]; //
  halfEdges[14]->SYM=halfEdges[23];
  halfEdges[15]->SYM=halfEdges[17];
  halfEdges[20]->SYM=halfEdges[10]; //
  halfEdges[21]->SYM=halfEdges[6]; //
  halfEdges[22]->SYM=halfEdges[18];
  halfEdges[23]->SYM=halfEdges[14]; //

 halfEdges[0]->V = vertices[0];
 halfEdges[1]->V = vertices[2];
 halfEdges[2]->V = vertices[3];
 halfEdges[3]->V = vertices[1];
 halfEdges[4]->V = vertices[0];
 halfEdges[5]->V = vertices[6];
 halfEdges[6]->V = vertices[4];
 halfEdges[7]->V = vertices[2];
 halfEdges[8]->V = vertices[2];
 halfEdges[9]->V = vertices[4];
 halfEdges[10]->V = vertices[5];
 halfEdges[11]->V = vertices[3];
 halfEdges[12]->V = vertices[3];
 halfEdges[13]->V = vertices[5];
 halfEdges[14]->V = vertices[7];
 halfEdges[15]->V = vertices[1];
 halfEdges[16]->V = vertices[1];
 halfEdges[17]->V = vertices[7];
 halfEdges[18]->V = vertices[6];
 halfEdges[19]->V = vertices[0];
 halfEdges[20]->V= vertices[4];
 halfEdges[21]->V = vertices[6];
 halfEdges[22]->V = vertices[7];
 halfEdges[23]->V = vertices[5];


 halfEdges[0]->F = faces[0];
 halfEdges[1]->F = faces[0];
 halfEdges[2]->F = faces[0];
 halfEdges[3]->F = faces[0];
 halfEdges[4]->F = faces[1];
 halfEdges[5]->F = faces[1];
 halfEdges[6]->F = faces[1];
 halfEdges[7]->F = faces[1];
 halfEdges[8]->F = faces[2];
 halfEdges[9]->F = faces[2];
 halfEdges[10]->F = faces[2];
 halfEdges[11]->F = faces[2];
 halfEdges[12]->F = faces[3];
 halfEdges[13]->F = faces[3];
 halfEdges[14]->F = faces[3];
 halfEdges[15]->F = faces[3];
 halfEdges[16]->F = faces[4];
 halfEdges[17]->F = faces[4];
 halfEdges[18]->F = faces[4];
 halfEdges[19]->F = faces[4];
 halfEdges[20]->F = faces[5];
 halfEdges[21]->F = faces[5];
 halfEdges[22]->F = faces[5];
 halfEdges[23]->F = faces[5];

 
 }



 unitCube::unitCube(glm::vec3 loc, float a):Mesh(){
	 float x,y,z;
	x=loc.x;
	y=loc.y;
	z=loc.z;

	ab=a;
	centerPoint=loc;

	vertexIDCount = 8; 
	faceIDCount = 6; 

	for(int i = 0; i<6; i++){
		faces.push_back(new FaceHE());

		for (int j = 0; j<4; j++){
			halfEdges.push_back(new HalfEdge());
		 } 
	}

	faces[0]->idF = 0;
	faces[1]->idF = 1;
	faces[2]->idF = 2;
	faces[3]->idF = 3;
	faces[4]->idF = 4;
	faces[5]->idF = 5;

	faces[0]->heStart = halfEdges[0];
	 faces[1]->heStart = halfEdges[4];
	faces[2]->heStart = halfEdges[8];
	 faces[3]->heStart = halfEdges[12];
	faces[4]->heStart = halfEdges[16];
	 faces[5]->heStart = halfEdges[20];

	faces[0]->colors = glm::vec3(0,1,1);
	 faces[1]->colors = glm::vec3(0,1,1);
	 faces[2]->colors = glm::vec3(0,1,1);
	faces[3]->colors = glm::vec3(0,1,1);
	faces[4]->colors = glm::vec3(0,1,1);
	faces[5]->colors = glm::vec3(0,1,1);

	 for (int i = 0; i<8; i++){
		Vertex* newv = new Vertex();
		newv->idV = i;
		 vertices.push_back(newv);

	}

	 vertices[0]->coords = glm::vec3(x-a,y+a,z-a);
	vertices[1]->coords = glm::vec3(x+a,y+a,z-a);
	vertices[2]->coords = glm::vec3(x-a,y+a,z+a);
	 vertices[3]->coords = glm::vec3(x+a,y+a,z+a);
	 vertices[4]->coords = glm::vec3(x-a,y-a,z+a);
	 vertices[5]->coords = glm::vec3(x+a,y-a,z+a);
	 vertices[6]->coords = glm::vec3(x-a,y-a,z-a);
	 vertices[7]->coords = glm::vec3(x+a,y-a,z-a);

	//vertices pointer to halfedges
	vertices[0]->he = halfEdges[0];
	vertices[1]->he = halfEdges[3];
	vertices[2]->he = halfEdges[1];
	 vertices[3]->he = halfEdges[2];
	 vertices[4]->he = halfEdges[6];
	 vertices[5]->he = halfEdges[10];
	 vertices[6]->he = halfEdges[5];
	vertices[7]->he = halfEdges[14];
 



 
	halfEdges[0]->NEXT = halfEdges[1];
	halfEdges[1]->NEXT = halfEdges[2];
	halfEdges[2]->NEXT = halfEdges[3];
	halfEdges[3]->NEXT = halfEdges[0];
	 halfEdges[4]->NEXT = halfEdges[5];
	 halfEdges[5]->NEXT = halfEdges[6];
	 halfEdges[6]->NEXT = halfEdges[7];
	 halfEdges[7]->NEXT = halfEdges[4];
	 halfEdges[8]->NEXT = halfEdges[9];
	 halfEdges[9]->NEXT = halfEdges[10];
	halfEdges[10]->NEXT = halfEdges[11];
	 halfEdges[11]->NEXT = halfEdges[8];
	 halfEdges[12]->NEXT = halfEdges[13];
	halfEdges[13]->NEXT = halfEdges[14];
	 halfEdges[14]->NEXT = halfEdges[15];
	 halfEdges[15]->NEXT = halfEdges[12];
	 halfEdges[16]->NEXT = halfEdges[17];
	 halfEdges[17]->NEXT = halfEdges[18];
	 halfEdges[18]->NEXT = halfEdges[19];
	halfEdges[19]->NEXT = halfEdges[16];
	halfEdges[20]->NEXT = halfEdges[21];
	 halfEdges[21]->NEXT = halfEdges[22];
	 halfEdges[22]->NEXT = halfEdges[23];
	 halfEdges[23]->NEXT = halfEdges[20];

 
	 halfEdges[0]->SYM=halfEdges[16]; //
	 halfEdges[1]->SYM=halfEdges[4]; //
	 halfEdges[2]->SYM=halfEdges[8]; //
	 halfEdges[3]->SYM=halfEdges[12]; //
	 halfEdges[16]->SYM=halfEdges[0]; //
	 halfEdges[17]->SYM=halfEdges[15]; //
	 halfEdges[18]->SYM=halfEdges[22];
	  halfEdges[19]->SYM=halfEdges[5]; //
	 halfEdges[4]->SYM=halfEdges[1]; //
	 halfEdges[5]->SYM=halfEdges[19];
	 halfEdges[6]->SYM=halfEdges[21]; //
	 halfEdges[7]->SYM=halfEdges[9]; //
	 halfEdges[8]->SYM=halfEdges[2]; //
	 halfEdges[9]->SYM=halfEdges[7]; //
	 halfEdges[10]->SYM=halfEdges[20];
	 halfEdges[11]->SYM=halfEdges[13]; //
	 halfEdges[12]->SYM=halfEdges[3]; //
	 halfEdges[13]->SYM=halfEdges[11]; //
	  halfEdges[14]->SYM=halfEdges[23];
	 halfEdges[15]->SYM=halfEdges[17];
	  halfEdges[20]->SYM=halfEdges[10]; //
	  halfEdges[21]->SYM=halfEdges[6]; //
	 halfEdges[22]->SYM=halfEdges[18];
	  halfEdges[23]->SYM=halfEdges[14]; //

	halfEdges[0]->V = vertices[0];
	 halfEdges[1]->V = vertices[2];
	halfEdges[2]->V = vertices[3];
	halfEdges[3]->V = vertices[1];
	halfEdges[4]->V = vertices[0];
	 halfEdges[5]->V = vertices[6];
	halfEdges[6]->V = vertices[4];
	 halfEdges[7]->V = vertices[2];
	halfEdges[8]->V = vertices[2];
	halfEdges[9]->V = vertices[4];
	 halfEdges[10]->V = vertices[5];
	halfEdges[11]->V = vertices[3];
	 halfEdges[12]->V = vertices[3];
	 halfEdges[13]->V = vertices[5];
	 halfEdges[14]->V = vertices[7];
	halfEdges[15]->V = vertices[1];
	halfEdges[16]->V = vertices[1];
	 halfEdges[17]->V = vertices[7];
	 halfEdges[18]->V = vertices[6];
	 halfEdges[19]->V = vertices[0];
	 halfEdges[20]->V= vertices[4];
	 halfEdges[21]->V = vertices[6];
	halfEdges[22]->V = vertices[7];
	 halfEdges[23]->V = vertices[5];


	 halfEdges[0]->F = faces[0];
	halfEdges[1]->F = faces[0];
	halfEdges[2]->F = faces[0];
	halfEdges[3]->F = faces[0];
 halfEdges[4]->F = faces[1];
 halfEdges[5]->F = faces[1];
 halfEdges[6]->F = faces[1];
 halfEdges[7]->F = faces[1];
 halfEdges[8]->F = faces[2];
 halfEdges[9]->F = faces[2];
 halfEdges[10]->F = faces[2];
 halfEdges[11]->F = faces[2];
 halfEdges[12]->F = faces[3];
 halfEdges[13]->F = faces[3];
 halfEdges[14]->F = faces[3];
 halfEdges[15]->F = faces[3];
 halfEdges[16]->F = faces[4];
 halfEdges[17]->F = faces[4];
 halfEdges[18]->F = faces[4];
 halfEdges[19]->F = faces[4];
 halfEdges[20]->F = faces[5];
 halfEdges[21]->F = faces[5];
 halfEdges[22]->F = faces[5];
 halfEdges[23]->F = faces[5];
 
 
 
 
 
 }
