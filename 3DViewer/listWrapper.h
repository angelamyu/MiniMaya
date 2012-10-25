#ifndef LISTWRAPPER_H
#define LISTWRAPPER_H

#pragma once
#include <QListWidget>
#include "FaceHE.h"
#include "Vertex.h"
#include "HalfEdge.h"
#include <vector>
#include <iostream>
#include <string>

class FaceHE; 
class HalfEdge; 

using namespace std;

typedef vector<HalfEdge*>* EDGES;
typedef vector<Vertex*>* VERTICES;
typedef vector<FaceHE*>* FACES;
typedef vector<float> CAMERAS; 

class listWrapper:public QListWidget{
	Q_OBJECT

public:
	typedef QListWidget super;
	listWrapper();
	listWrapper(QWidget*);
	~listWrapper();

	FACES faceVec; 
	VERTICES vertVec; 
	EDGES edgeVec; 

	int faceVecSize; 
	int vertVecSize; 
	int edgeVecSize; 

	HalfEdge* secondHE; 

	int currentRowTemp; 
	vector<CAMERAS> camStuff; 

public slots:
	void addFaces(FACES); 
	void addVertices(VERTICES); 
	void addEdges(EDGES); 
	void setX(int); 
	void setY(int); 
	void setZ(int); 
	void setRed(int); 
	void setGreen(int); 
	void setBlue(int); 
	void addVertexIntoEdge(); 
	void addEdgeTwoFacesUsingHalfEdges(); 
	void addSplitQuad(); 
	void addDeleteVertex(); 
	void setTheRow(int); 
	void testEdge();
	void addCam(CAMERAS,QString);
	void gotClickedCam(); 
	void clearSecondHE(); 
	void selectSecondHE(); 
signals:
	void updateGLWindow(); 
	void callAddVertexToEdge(HalfEdge*,Vertex*); 
	void callAddEdgeBetweenTwoFacesShareAVertex(FaceHE*,FaceHE*,HalfEdge*,HalfEdge*); 
	void callSplitFace(FaceHE*); 
	void callDeleteVertex(HalfEdge*); 
	void sendNum(int);
	void sendEdge(HalfEdge*);
	void sendCam(CAMERAS); 
};

#endif