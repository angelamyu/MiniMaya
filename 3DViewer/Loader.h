#ifndef LOADER_H
#define LOADER_H
#include <string>
#include "Mesh.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include <map>
#include <set>
#include "myColor.h"

class Loader{

public:
	const char* filename;
	Loader(const char* filename);
	~Loader();

	std::vector<Vertex*> vList;  
    std::vector<FaceHE*> fList;            
    std::vector<HalfEdge* > heList;  
	std::vector<glm::vec3 > nList; 

	std::map<set<int>, int> symMap;
	std::map<string, myColor*> mtlMap;

	
	Mesh* getMesh();
	int Loader::loadObj();
	
	int mtlLoad(string buffer);

private:
	int vid;
	int fid;
	long hid; 
	Mesh* m;
	myColor* currColor;

	//OBJ loader and its helper methods
	

private:
	Vertex* processVertex(string buffer);
	glm::vec3 processNormal(string buffer);
	void processMaterial(string buffer);
	void processUseMtl(string buffer);
	int processFace(string buffer);
	HalfEdge* getSym(int v1,int v2, int hid);
	int setFace(int v1, int v2, int v3);
	int getVid();
	int getFid();
	
	


};



#endif