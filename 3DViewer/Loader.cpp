#include "loader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"

using namespace std;



Loader::Loader(const char* filename1){
	vid=0;
	fid=0;
	hid=0;
	filename=filename1;
	currColor=new myColor();
	
}

Loader::~Loader(){

}


//Helper Method: generate vertex from a line
Vertex* Loader::processVertex(string buffer){
	istringstream line(buffer);
	string temp;
	float x,y,z;
	line >> temp >> x >> y >> z;
	Vertex* v=new Vertex(x,y,z,getVid());
	return v;
}

//Helper Method: generate normal from a line
glm::vec3 Loader::processNormal(string buffer){
	istringstream line(buffer);
	string temp;
	float x,y,z;
	line >> temp >> x >> y >> z;
	return glm::vec3(x,y,z);
}

int mtlLoad(string buffer){
	istringstream line(buffer);
	string temp,mtlfilename;
	line >> temp >> mtlfilename;
	ifstream mtlFile (mtlfilename);



	return -1;
}

int Loader::getVid(){
	vid++;
	return vid;
}

int Loader::getFid(){
	fid++;
	return fid;
}

HalfEdge* Loader::getSym(int v1, int v2, int hid){
	
	set<int> vPair;
	int matchId;
    vPair.insert(v1);
    vPair.insert(v2);


	map<set<int>, int>::iterator i = symMap.find(vPair);

	if (i != symMap.end()){
		matchId=symMap[vPair];
		heList[matchId]->SYM=heList[hid];
		symMap.erase(i);
		return heList[matchId];
	}
	else{
		symMap[vPair]=hid;
		return NULL;
	}


}

int Loader::setFace(int v1, int v2, int v3){
	
	int hid1=hid;
	int hid2=hid+1;
	int hid3=hid+2;

	v1-=1;
	v2-=1;
	v3-=1;

	HalfEdge* he1=new HalfEdge();
	HalfEdge* he2=new HalfEdge();
	HalfEdge* he3=new HalfEdge();

	he1->NEXT=he2;
	he2->NEXT=he3;
	he3->NEXT=he1;

	he1->V=vList[v2];
	he2->V=vList[v3];
	he3->V=vList[v1];

	heList.push_back(he1);
	heList.push_back(he2);
	heList.push_back(he3);

	if (vList[v1]->he==NULL)
		vList[v1]->he=heList[hid3];

	if (vList[v2]->he==NULL)
		vList[v2]->he=heList[hid1];

	if (vList[v3]->he==NULL)
		vList[v3]->he=heList[hid2];
	
	
	heList[hid1]->SYM=getSym(v1,v2,hid1);
	heList[hid2]->SYM=getSym(v2,v3,hid2);
	heList[hid3]->SYM=getSym(v3,v1,hid3);

	//FaceHE* f=new FaceHE(he1,glm::vec3(0,0,1),getFid());

	FaceHE* f=new FaceHE(he1,currColor,getFid());
	f->heStart=heList[hid1];
	fList.push_back(f);

	hid+=3;

	heList[hid1]->F=fList[fid-1];
	heList[hid2]->F=fList[fid-1];
	heList[hid3]->F=fList[fid-1];

	return 1;
}

int Loader::processFace(string buffer){
	istringstream line(buffer);
	string temp,str1;
	
	int v1=-1;
	int v2=-1;
	int v3=-1;
	int v4=-1;
	int v5=-1;

	line >> temp >> v1 >> v2 >> v3 >> v4 >> v5;

	if (v5!=-1){
		return -1;
	}
	if (v4!=-1){
		setFace(v1, v2, v4);
		setFace(v2, v3, v4);
	}
	else{
		setFace(v1,v2,v3);	
	}
	return 1;
}

void Loader::processMaterial(string buffer){
	int first_mtl=0;
	string mtlname;
	myColor* newColor=new myColor();
	std::string mbuffer;   
	istringstream line(buffer);
	string temp,mtlFileName;

	line >> temp >>mtlFileName;

	ifstream mtlFile (mtlFileName);

	if (mtlFile.is_open()){
		while (mtlFile.good()) 
          {
			  getline(mtlFile,mbuffer);
	
			  if (mbuffer.length()<1) {
				if (first_mtl!=0){
						mtlMap[mtlname]=new myColor(newColor->ka,newColor->kd,newColor->ks);
				}
			  
			  }
			  else
			  //newmtl
			  if (mbuffer[0] == 'n' && mbuffer[1]== 'e' && mbuffer[2]=='w'){
					istringstream line2(mbuffer);
					string temp2;
					line2 >> temp2 >> mtlname;
					first_mtl=1;

			  }
			  else
			  if (mbuffer[0] == 'K' && mbuffer[1]== 'a'){
				    istringstream line2(mbuffer);
					string temp2;
					float v1,v2,v3;
					line2 >> temp2 >> v1>> v2>> v3;
					newColor->ka=glm::vec3(v1,v2,v3);
			  }
			  else
			  if (mbuffer[0] == 'K' && mbuffer[1]== 'd'){
				    istringstream line2(mbuffer);
					string temp2;
					float v1,v2,v3;
					line2 >> temp2 >> v1>> v2>> v3;
					newColor->kd=glm::vec3(v1,v2,v3);
			  }
				else
			   if (mbuffer[0] == 'K' && mbuffer[1]== 's'){
				    istringstream line2(mbuffer);
					string temp2;
					float v1,v2,v3;
					line2 >> temp2 >> v1>> v2>> v3;
					newColor->ks=glm::vec3(v1,v2,v3);
			   }

		}
	}

}

void Loader::processUseMtl(string mbuffer){
	istringstream line(mbuffer);
	string temp,str1;
	line >> temp >> str1;

	if (mtlMap.count(str1)>0)
		currColor=mtlMap[str1];

}

//Obj file loader, return a mesh
int Loader::loadObj(){
	  std::string buffer;           
                                        

         
      // Open file
      ifstream objFile (filename);

	  if (objFile.is_open())
      {
          
		  // While the file is open, read the file
		  while (objFile.good()) 
          {
			  getline(objFile,buffer);
			

              // Check if this line holds vertex information. If the line starts 
              // with "v ", we will use it.
			  if (buffer.length()<1) {}
			  else
              if (buffer[0] == 'v' && buffer[1] == ' ' )
              {
                  vList.push_back(processVertex(buffer));

              }
			  else
			  // Check if the line holds face formation. If its starts with
              // "f" if a face.
              if (buffer[0] == 'f' && buffer[1] == ' ')
              {
                 //fList.push_back(processFace(buffer));
				  processFace(buffer);
              }
			  else
			  //'mtllib'
			  if (buffer[0] == 'm' && buffer[1]== 't' && buffer[2]=='l'){
					processMaterial(buffer);
			  }

			  else
				  if (buffer[0]=='u' && buffer[1]=='s' && buffer[2]=='e'){
					processUseMtl(buffer);
				  }

           
          }
          // Finished with reading the file, close it
          objFile.close();
      }
	  else {
		  return -1;
		}
      
	m=new Mesh(vList,fList,heList);


	return 1;
}


Mesh* Loader::getMesh(){
	return m;
}