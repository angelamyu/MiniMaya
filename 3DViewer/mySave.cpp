#include "mySave.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

mySave::mySave(Mesh* m){
	save_mesh=m;

}

mySave::~mySave(){

}


int mySave::saveObj(const char* filename){
	std::string buffer;  
	std::map<int,int> vidMap;

	ofstream objFile;
	objFile.open (filename, ios::out | ios::app);
	
	//write vertices
	for (int i=0; i<save_mesh->vertices.size();i++){
		Vertex* v=save_mesh->vertices[i];
		objFile << "v " <<v->coords.x<<" "<<v->coords.y<<" "<<v->coords.z<<endl;
		vidMap[v->idV]=i+1;
	}
	//write faces
	for (int i=0; i<save_mesh->faces.size();i++){
		int n1, n2, n3,n4;
		FaceHE* f=save_mesh->faces[i];

		n1=vidMap[f->heStart->V->idV];
		n2=vidMap[f->heStart->NEXT->V->idV];
		n3=vidMap[f->heStart->NEXT->NEXT->V->idV];

		if (f->countNumberOfhalfEdges()==4){
			n4=vidMap[f->heStart->NEXT->NEXT->NEXT->V->idV];
			objFile << "f " <<n1<<" "<<n2<<" "<<n3<<" "<<n4<<endl;
		}
		
		objFile << "f " <<n1<<" "<<n2<<" "<<n3<<endl;
	}
	objFile.close();


return 1;
}