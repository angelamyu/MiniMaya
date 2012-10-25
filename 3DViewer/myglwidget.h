#ifndef MYGLWIDGET
#define MYGLWIDGET

#include "glew.h"
#include <QPoint>
#include <QColorDialog>
#include <QMenu>
#include <QGLWidget>
#include <QTimer>
#include <QKeyEvent>
#include "../glm/glm.hpp"
#include "camera.h"
#include "Mesh.h"
#include "unitCube.h"
#include "listWrapper.h"
#include "Loader.h"
#include "lightDialog.h"
#include "Box.h"
#include  <QHoverEvent>
#include <iostream>
#include <fstream>
#include <string>
#include <QFileDialog>
#include <mySave.h>
#include "extrudeDialog.h"
#include "loadshader.h"
#include "doc.h"

using namespace std;

class MyGLWidget : public QGLWidget {
	Q_OBJECT
private:
	//vertex arrays needed for drawing
	unsigned int vbo;
	unsigned int cbo;
	unsigned int nbo;
	unsigned int ibo;

	//attributes
	unsigned int positionLocation;
	unsigned int normalLocation;
	unsigned int colorLocation;

	// uniforms
	unsigned int u_projMatrixLocation;
	unsigned int u_modelMatrixLocation;
	unsigned int u_lightPosLocation;
	
	//needed to compile and link and use the shaders
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;

	//Animation/transformation stuff
	QTimer* timer;

	int mesh_load;

	//helper function to read shader source and put it in a char array
	//thanks to Swiftless
	char* textFileRead(const char*);

	//some other helper functions from CIS 565
	void printLinkInfoLog(int);
	void printShaderInfoLog(int);

	glm::vec3 light; 
	glm::mat4 model; 
	glm::mat4 viewmat; 

	float rotation; 

	camera* cam; 

	float theta; 
	float phi; 
	float r; 

	glm::vec3 eRay; 
	glm::vec3 rRay; 

	FaceHE* selectedFace;
	FaceHE* hoveredFace; 
	Vertex* hoveringVertex; 
	Vertex* selectedVertex; 
	HalfEdge* hoveringHE; 
	HalfEdge* selectedHE; 
	HalfEdge* selectedHE2; 

	vector<glm::vec3> hoveringVertexPoints; 
	vector<glm::vec3> selectedVertexPoints; 
	vector<glm::vec3> hoveringHEPoints; 
	vector<glm::vec3> selectedHEPoints; 
	vector<glm::vec3> selectedHE2Points; 
	glm::vec3 cubeOrigin;

	bool hoveringFaceFlag; 
	bool hoveringVertexFlag; 
	bool hoveringHalfEdgeFlag; 
	bool selectedFaceFlag; 
	bool selectedVertexFlag; 
	bool selectedHalfEdgeFlag; 
	bool selectedHE2Flag;  
	unitCube* selectedCube; 
	bool selectedCubeFlag; 
	int selectedCubeIndex; 
	bool shiftPressed; 

	int findVertexID(Vertex*);

	//
	Mesh* cube;
	Box* box;
	int boxL,boxM,boxN;
	bool _boxEnabled;
	int currentAxis;
	int twistIndex;


public:
	MyGLWidget(QWidget*);
	~MyGLWidget(void);
	void initializeGL(void);
	void paintGL(void);
	void resizeGL(int, int);
	void createCube(glm::mat4);
	void createCubeFromMesh(glm::mat4);
	void createCubeFromMesh2(glm::mat4, unitCube* theCube);
	void keyPressEvent(QKeyEvent*);
	//glm::vec3 normalizeVec3(glm::vec3);
	bool rotatingFlag; 
	float leftRightFlip; 
	float upDownFlip; 
	float upVecFlip; 
	bool flipFlag; 
	void mousePressEvent(QMouseEvent *e);
	bool mousePressed; 
	void mouseReleaseEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	int x1; 
	int y1; 
	void wheelEvent(QWheelEvent*e);
	bool mouseFlipped; 
	//unitCube* cube; 
	void createRay(glm::mat4, glm::vec3, glm::vec3); 
	void createRay(glm::mat4, glm::vec3, glm::vec3, glm::vec3);
	void createRay(float,glm::mat4, glm::vec3, glm::vec3, glm::vec3); 
	vector<glm::vec3> calculateVertexPickingPoints(Vertex*, FaceHE*); 
	vector<glm::vec3> calculateHEPickingPoints(HalfEdge* h);
	bool checkHoveringSectionHasPoint(vector<glm::vec3> points, FaceHE* f, glm::vec3 check);
	int findHEID(HalfEdge*);
	lightDialog* ld;
	extrudeDialog* ed;
	loadshader* ls;
	void createGrid();
	bool grid;
	float distance;
	doc* d;
	


	public slots:
	void startCubeRotation(); 
	void stopCubeRotation(); 
	glm::vec3 calcCoordinates(); 
	void doUpdateGL(); 
	void gotAddVertexToEdge(HalfEdge*,Vertex* v);
	void doAddEdgeBetweenTwoFacesShareAVertex(FaceHE*,FaceHE*,HalfEdge*,HalfEdge*);
	void doSplitQuadIntoTwoTriangles(FaceHE*); 
	void doDeleteVertex(HalfEdge* );
	void checkFacePlanarity();
	void redrawOutlines(); 
	void newCube();
	void showContextMenu(const QPoint& pos);
	void subdivide();
	void callExtrude();
	void showDoc();

	void changeLight();
	void changeGrid();
	void addEdge(); 

	void resetCamera(); 
	void setRefPoint(QString);
	void snapView();

	//mesh Load
	void loadMesh(); 
	void saveMesh();
	void testLoader(glm::mat4);
	void drawBox(glm::mat4, Box* theBox);
	void drawPoint(glm::mat4 model, glm::vec3 loc,float a);
	void triangleMesh();
	void setDistance(float);

	void twist();
	void bend();
	void taper();
	void twistIndexSet(int);

	void showBox();
	void disableBox();
	void getLValue(int);
	void getMValue(int);
	void getNValue(int);
	void showEBox();


	void callLoadShader(QString);
	void loadShader(QString); 
	void setLightPos(QString); 

	void saveUserView(QString); 
	void userView(CAMERAS); 
	void frontView(); 
	void overheadView(); 
	void leftView(); 
	void rightView(); 
	void backView(); 
	void perspectiveView(); 
	void bottomView(); 

	void setXBox(int); 
	void setYBox(int); 
	void setZBox(int); 

	void setAxisX();
	void setAxisY();
	void setAxisZ();



signals: 
	void sendFaces(FACES); 
	void sendVertices(VERTICES); 
	void sendHalfEdges(EDGES); 
	void setFaceRow(int); 
	void setVertexRow(int); 
	void setHERow(int); 
	void addUserCam(CAMERAS,QString); 
	void resetSavedViews(); 
	void clearSHE(); 
	void setSecondHE(); 
	void sendSetX(int); 
	void sendSetY(int); 
	void sendSetZ(int); 
};

#endif