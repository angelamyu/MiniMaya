#include "myglwidget.h"
#include <cmath>
#include <iostream>
#include "../glm/gtc/matrix_transform.hpp"
using namespace std;

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif
#define DEG2RAD (M_PI/180.0)

MyGLWidget::MyGLWidget(QWidget* parent) : QGLWidget(parent) {
	setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
    this, SLOT(showContextMenu(const QPoint&)));
	//This starter code uses a timer to make a square rotate without
	//user intervention.  You can remove this.
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
	timer->start(17);

	//We can set our vertex attributes rather than requesting their locations
	//I chose to do so in this constructor, maybe you would in your init() function?
	grid = true;
	positionLocation = 0;
	normalLocation = 1;
	colorLocation = 2;
	light = glm::vec3(3,5,3);
	model = glm::mat4(1.0);
	viewmat = glm::mat4(); 
	rotation = 1.5; 
	cam = new camera(); 
	theta = 90.0f; 
	phi = 45.0f; 
	r = 5; 
	setFocusPolicy(Qt::StrongFocus);
	rotatingFlag = false; 
	leftRightFlip = 1; 
	upDownFlip = 1; 
	upVecFlip = 1; 
	flipFlag = false; 
	mousePressed = false; 
	x1 = 0; 
	y1 = 0; 
	mouseFlipped = false; 
	cube = new unitCube();
	

	setMouseTracking(true); 
	hoveredFace = NULL;
	hoveringFaceFlag = false; 
	hoveringVertexFlag = false; 
	hoveringHalfEdgeFlag = false; 
	selectedFaceFlag = false; 
	selectedHalfEdgeFlag = false; 
	selectedVertexFlag = false;
	cubeOrigin = glm::vec3(0,0,0); 
	hoveringHE = NULL; 
	selectedHE = NULL; 

	hoveredFace = NULL;
	hoveringFaceFlag = false; 
	hoveringVertexFlag = false; 
	hoveringHalfEdgeFlag = false; 
	selectedFaceFlag = false; 
	selectedHalfEdgeFlag = false; 
	selectedHE2Flag = false; 
	selectedVertexFlag = false;
	cubeOrigin = glm::vec3(0,0,0); 
	hoveringHE = NULL; 
	selectedHE = NULL; 
	selectedHE2 = NULL; 
	shiftPressed = false; 
	distance = 0;
	selectedCube = NULL; 
	selectedCubeFlag = false; 
	selectedCubeIndex = -1; 

	mesh_load=0;
	ld = new lightDialog();
	ed = new extrudeDialog();
	ls = new loadshader();
	d = new doc();

	boxL=2;
	boxM=2;
	boxN=2;
	box=new Box(cube,boxL,boxM,boxN);
	_boxEnabled=false;

	currentAxis=1;
	twistIndex=1;

	connect(ld, SIGNAL(sendPos(QString)),
    this, SLOT(setLightPos(QString)));
	connect(ed, SIGNAL(sendDistance(float)),
    this, SLOT(setDistance(float)));
	connect(ls, SIGNAL(sendName(QString)),
    this, SLOT(callLoadShader(QString)));
}

MyGLWidget::~MyGLWidget() {
	//Release your resources, just like you'd delete pointers
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &cbo);
	glDeleteBuffers(1, &nbo);
	glDeleteBuffers(1, &ibo);

	//Tear down the shader program in reverse of building it
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(shaderProgram);
}

//this is the function i referred to as "init" in my lecture - Cory
void MyGLWidget::initializeGL() {
	//Initialize GLEW to get access to latest OpenGL support on your computer
	//GLEW 1.7.0 supplied with this starter code, it's always a good idea to update
	//about once every year or so as OpenGL is updated
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		cerr << "GLEW is not initialized!";
	}
	
	//Create the VBOs and IBO we'll be using to render images in OpenGL
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &cbo);
	glGenBuffers(1, &nbo);
	glGenBuffers(1, &ibo);
	
	//Everybody does this
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	glDepthFunc(GL_LEQUAL);
	
	//here is stuff for setting up our shaders
	const char* fragFile = "diffuseFrag.frag";
	const char* vertFile = "diffuseVert.vert";
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	shaderProgram = glCreateProgram();
	
	//load up the source, compile and link the shader program
	const char* vertSource = textFileRead(vertFile);
	const char* fragSource = textFileRead(fragFile);
	glShaderSource(vertexShader, 1, &vertSource, 0);
	glShaderSource(fragmentShader, 1, &fragSource, 0);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	//For your convenience, i decided to throw in some compiler/linker output helper functions
	//from CIS 565
	GLint compiled;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		printShaderInfoLog(vertexShader);
	} 
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		printShaderInfoLog(fragmentShader);
	} 

	//set the attribute locations for our shaders
	glBindAttribLocation(shaderProgram, positionLocation, "vs_position");
	glBindAttribLocation(shaderProgram, normalLocation, "vs_normal");
	glBindAttribLocation(shaderProgram, colorLocation, "vs_color");

	//finish shader setup
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//check for linking success
	GLint linked;
	glGetProgramiv(shaderProgram,GL_LINK_STATUS, &linked);
	if (!linked) 
	{
		printLinkInfoLog(shaderProgram);
	}

	//Get the uniform locations for our shaders, unfortunately they can not be set by us, we have
	u_modelMatrixLocation = glGetUniformLocation(shaderProgram, "u_modelMatrix");
	u_projMatrixLocation = glGetUniformLocation(shaderProgram, "u_projMatrix");
	

	//Always remember that it doesn't do much good if you don't have OpenGL actually use the shaders
	glUseProgram(shaderProgram);

	// Initialize Lighting
	u_lightPosLocation  = glGetUniformLocation(shaderProgram, "u_lightPos");
	
	QString qstr("diffuse");
	loadShader(qstr); 

	selectedFace = NULL;
	hoveringFaceFlag = false; 
	hoveringVertexFlag = false; 
	hoveringHalfEdgeFlag = false; 


	emit sendFaces(&(cube->faces)); 
	emit sendVertices(&(cube->vertices)); 
	emit sendHalfEdges(&(cube->halfEdges)); 
}

void MyGLWidget::loadShader(QString fileName){
	//Release your resources, just like you'd delete pointers
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &cbo);
	glDeleteBuffers(1, &nbo);
	glDeleteBuffers(1, &ibo);

	//Tear down the shader program in reverse of building it
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(shaderProgram);

	

	QByteArray ba = (fileName.toLatin1());
	const char* filename = (const char*)(ba.data());
	std::string f = filename; 
	std::string frag = "Frag.frag"; 
	std::string vert = "Vert.vert"; 
	

	//here is stuff for setting up our shaders
	std::string fragFull = f+frag; 
	std::string vertFull = f+vert; 
	const char* fragFile = (fragFull).c_str();
	const char* vertFile = (vertFull).c_str();
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	shaderProgram = glCreateProgram();
	
	//load up the source, compile and link the shader program
	const char* vertSource = textFileRead(vertFile);
	const char* fragSource = textFileRead(fragFile);
	glShaderSource(vertexShader, 1, &vertSource, 0);
	glShaderSource(fragmentShader, 1, &fragSource, 0);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	//For your convenience, i decided to throw in some compiler/linker output helper functions
	//from CIS 565
	GLint compiled;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		printShaderInfoLog(vertexShader);
	} 
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		printShaderInfoLog(fragmentShader);
	} 

	//set the attribute locations for our shaders
	glBindAttribLocation(shaderProgram, positionLocation, "vs_position");
	glBindAttribLocation(shaderProgram, normalLocation, "vs_normal");
	glBindAttribLocation(shaderProgram, colorLocation, "vs_color");

	//finish shader setup
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//check for linking success
	GLint linked;
	glGetProgramiv(shaderProgram,GL_LINK_STATUS, &linked);
	if (!linked) 
	{
		printLinkInfoLog(shaderProgram);
	}

	//Get the uniform locations for our shaders, unfortunately they can not be set by us, we have
	u_modelMatrixLocation = glGetUniformLocation(shaderProgram, "u_modelMatrix");
	u_projMatrixLocation = glGetUniformLocation(shaderProgram, "u_projMatrix");
	

	//Always remember that it doesn't do much good if you don't have OpenGL actually use the shaders
	glUseProgram(shaderProgram);

	// Initialize Lighting
	u_lightPosLocation  = glGetUniformLocation(shaderProgram, "u_lightPos");
}

//this is what i referred to as a "paint" or "draw" function in my lecture - Cory
void MyGLWidget::paintGL() {
	//Always and only do this at the start of a frame, it wipes the slate clean
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::vec3 temp = cam->calcUpVector(calcCoordinates(),cam->ref);
	//create an identity matrix for the model matrix
	if(flipFlag||mouseFlipped){ //HUGE ISSUES HERE, MUST FIX SO THEY WORK TOGETHER
		//Angela: getting rid of keyboard input later
		temp = -temp; 
		cam->upDirection = -1.0f * (cam->upDirection); 
		//flipFlag = false; 
	}
	viewmat = cam->calcViewMatrix(calcCoordinates(),cam->ref,temp);
	viewmat = (glm::perspective(45.0f,float(width()) / float(height()), 0.1f, 100.0f))*viewmat; 
	glUniformMatrix4fv(u_projMatrixLocation,1,GL_FALSE,&viewmat[0][0]); 
	if(grid){
	createGrid();
	}
	
	if (mesh_load==1){
		testLoader(model);
		//triangleMesh();
	}
	else{
		createCubeFromMesh(model);  
		createRay(model, eRay, rRay); }

	
	if (_boxEnabled){
		drawBox(model,box);	
	}

	if (selectedFace&&selectedFaceFlag) {
		for (int i = 0; i < selectedFace->countNumberOfhalfEdges(); i++) {
			glm::vec3 p1 = selectedFace->getHE(i)->V->coords;
			glm::vec3 p2 = selectedFace->getHE(i + 1)->V->coords;
			glm::vec3 colors = glm::vec3(1,1,1); 
			createRay(model, p1, p2,colors);
		}
	}
	if(selectedVertex && selectedVertexFlag){
		for (int i = 0; i < selectedVertexPoints.size(); i++) {
			glm::vec3 p1 = selectedVertexPoints[i];
			glm::vec3 p2;
			if(i+1 == selectedVertexPoints.size()){
				p2 = selectedVertexPoints[0]; 
			}
			else{
				p2 = selectedVertexPoints[i+1];
			}
			glm::vec3 colors = glm::vec3(1,1,1); 
			createRay(model, p1, p2, colors);
		}
	}
	if(selectedHE && selectedHalfEdgeFlag){
		for (int i = 0; i < selectedHEPoints.size(); i++) {
			glm::vec3 p1 = selectedHEPoints[i];
			glm::vec3 p2;
			if(i+1 == selectedHEPoints.size()){
				p2 = selectedHEPoints[0]; 
			}
			else{
				p2 = selectedHEPoints[i+1];
			}
			glm::vec3 colors = glm::vec3(1,1,1); 
			createRay(model, p1, p2, colors);
		}
		if(selectedHE2Flag){
			for (int i = 0; i < selectedHE2Points.size(); i++) {
			glm::vec3 p1 = selectedHE2Points[i];
			glm::vec3 p2;
			if(i+1 == selectedHE2Points.size()){
				p2 = selectedHE2Points[0]; 
			}
			else{
				p2 = selectedHE2Points[i+1];
			}
			glm::vec3 colors = glm::vec3(1,1,1); 
			createRay(model, p1, p2, colors);
		}
		}
	}
	if(hoveredFace && hoveringFaceFlag){
		for (int i = 0; i < hoveredFace->countNumberOfhalfEdges(); i++) {
			glm::vec3 p1 = hoveredFace->getHE(i)->V->coords;
			glm::vec3 p2 = hoveredFace->getHE(i + 1)->V->coords;
			glm::vec3 colors = glm::vec3(1,0,0); 
			createRay(model, p1, p2, colors);
		}
	}
	if(hoveringHE && hoveringHalfEdgeFlag){
		for (int i = 0; i < hoveringHEPoints.size(); i++) {
			glm::vec3 p1 = hoveringHEPoints[i];
			glm::vec3 p2;
			if(i+1 == hoveringHEPoints.size()){
				p2 = hoveringHEPoints[0]; 
			}
			else{
				p2 = hoveringHEPoints[i+1];
			}
			glm::vec3 colors = glm::vec3(1,0,0); 
			createRay(model, p1, p2, colors);
		}
	}
	if(hoveringVertex && hoveringVertexFlag ){
		for (int i = 0; i < hoveringVertexPoints.size(); i++) {
			glm::vec3 p1 = hoveringVertexPoints[i];
			glm::vec3 p2;
			if(i+1 == hoveringVertexPoints.size()){
				p2 = hoveringVertexPoints[0]; 
			}
			else{
				p2 = hoveringVertexPoints[i+1];
			}
			glm::vec3 colors = glm::vec3(1,0,0); 
			createRay(model, p1, p2, colors);
		}
	}
	
	//for rotate cube, separate from camera	
	if(rotatingFlag){
		model = glm::rotate(model,rotation,glm::vec3(0.0f, 1.0f, 0.0f));
	}
}

void MyGLWidget::setLightPos(QString text){
	QStringList delim = text.split(","); 
	if(delim.size() == 3){
		float x = (delim[0]).toFloat(); 
		float y = (delim[1]).toFloat(); 
		float z = (delim[2]).toFloat(); 

		glm::vec3 pos(x,y,z); 
		light = pos; 

	glUniform3fv(u_lightPosLocation, 1, &light[0]);
	}
}

void MyGLWidget::setRefPoint(QString text){
	QStringList delim = text.split(","); 
	if(delim.size() == 3){
		float x = (delim[0]).toFloat(); 
		float y = (delim[1]).toFloat(); 
		float z = (delim[2]).toFloat(); 

		cam->ref = glm::vec3(x,y,z); 
	}
}

void MyGLWidget::createCube(glm::mat4 model) {

	// See the art of comments? 
	// cube ///////////////////////////////////////////////////////////////////////
	//    v6----- v5
	//   /|      /|
	//  v1------v0|
	//  | |     | |
	//  | |v7---|-|v4
	//  |/      |/
	//  v2------v3	
	
	// vertex coords array, remember the homogeneous representation?
	float vertices[] = {1,1,1,1,  -1,1,1,1,  -1,-1,1,1,  1,-1,1,1,        // v0-v1-v2-v3
                        1,1,1,1,  1,-1,1,1,  1,-1,-1,1,  1,1,-1,1,        // v0-v3-v4-v5
                        1,1,1,1,  1,1,-1,1,  -1,1,-1,1,  -1,1,1,1,        // v0-v5-v6-v1
                        -1,1,1,1,  -1,1,-1,1,  -1,-1,-1,1,  -1,-1,1,1,    // v1-v6-v7-v2
                        -1,-1,-1,1,  1,-1,-1,1,  1,-1,1,1,  -1,-1,1,1,    // v7-v4-v3-v2
                        1,-1,-1,1,  -1,-1,-1,1,  -1,1,-1,1,  1,1,-1,1};   // v4-v7-v6-v5

	// normal array, normal is a vector which has the 4th value zero in homogeneous representation.
	float normals[] = {0,0,1,0,  0,0,1,0,  0,0,1,0,  0,0,1,0,             // v0-v1-v2-v3
                       1,0,0,0,  1,0,0,0,  1,0,0,0, 1,0,0,0,              // v0-v3-v4-v5
                       0,1,0,0,  0,1,0,0,  0,1,0,0, 0,1,0,0,              // v0-v5-v6-v1
                       -1,0,0,0,  -1,0,0,0, -1,0,0,0,  -1,0,0,0,          // v1-v6-v7-v2
                       0,-1,0,0,  0,-1,0,0,  0,-1,0,0,  0,-1,0,0,         // v7-v4-v3-v2
                       0,0,-1,0,  0,0,-1,0,  0,0,-1,0,  0,0,-1,0};        // v4-v7-v6-v5

	// color array, the 4th element is the alpha channel
	float colors[] = {1,1,1,1,  1,1,0,1,  1,0,0,1,  1,0,1,1,              // v0-v1-v2-v3
                      1,1,1,1,  1,0,1,1,  0,0,1,1,  0,1,1,1,              // v0-v3-v4-v5
                      1,1,1,1,  0,1,1,1,  0,1,0,1,  1,1,0,1,              // v0-v5-v6-v1
                      1,1,0,1,  0,1,0,1,  0,0,0,1,  1,0,0,1,              // v1-v6-v7-v2
                      0,0,0,1,  0,0,1,1,  1,0,1,1,  1,0,0,1,              // v7-v4-v3-v2
                      0,0,1,1,  0,0,0,1,  0,1,0,1,  0,1,1,1};             // v4-v7-v6-v5

	// index array
	unsigned int indices[] = {0,1,2,  0,2,3,                             //front			
                                4,5,6,  4,6,7,                             //right
								8,9,10,  8,10,11,                          //top
								12,13,14,  12,14,15,                       //left
								16,17,18,  16,18,19,                       //bottom
								20,21,22,  20,22,23};                      //back
                                
	//now we put the data into the Vertex Buffer Object for the graphics system to use
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 96 * sizeof(float), vertices, GL_STATIC_DRAW); //the square vertices don't need to change, ever,
																				 //while the program runs

	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	//always make sure you are telling OpenGL the right size to make the buffer, color data doesn't have as much data!
	glBufferData(GL_ARRAY_BUFFER, 96 * sizeof(float), colors, GL_STATIC_DRAW);	

	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, 96 * sizeof(float), normals, GL_STATIC_DRAW); //the square normals don't need to change, ever,
																				 //while the program runs
	//activate our three kinds of information
	glEnableVertexAttribArray(positionLocation);
	glEnableVertexAttribArray(colorLocation);
	glEnableVertexAttribArray(normalLocation);
	
	//we're using the vertex data first
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//define how the vertex pointer should work, in our case we're accessing floats 4 at a time with no special pattern
	glVertexAttribPointer(positionLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	//now use color data
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glVertexAttribPointer(colorLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));

	//one more time with the normals
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glVertexAttribPointer(normalLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	//the last thing we need to do is setup our indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	//set the model uniform
	//GL_FALSE is used for not doing transpose operation, because glm has already provided us column major matrices.
	//if the matrices you used is row major, change this parameter to GL_TRUE.
	glUniformMatrix4fv(u_modelMatrixLocation, 1, GL_FALSE, &model[0][0]);

	glUniform3fv(u_lightPosLocation,1,&light[0]);

	//draw the elements
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	
	//shut off the information since we're done drawing
	glDisableVertexAttribArray(positionLocation);
	glDisableVertexAttribArray(colorLocation);
}

void MyGLWidget::createCubeFromMesh(glm::mat4){
	cube->createGL();
	float* vertices = cube->vertGL;

	//now we put the data into the Vertex Buffer Object for the graphics system to use
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	 glBufferData(GL_ARRAY_BUFFER, cube->num*4 * sizeof(float), cube->vertGL, GL_STATIC_DRAW); //the square vertices don't need to change, ever,
                     //while the program runs
	 glBindBuffer(GL_ARRAY_BUFFER, cbo);
	//always make sure you are telling OpenGL the right size to make the buffer, color data doesn't have as much data!
	glBufferData(GL_ARRAY_BUFFER, cube->num*4 * sizeof(float), cube->colorGL, GL_STATIC_DRAW); 

 	

	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, cube->num*4 * sizeof(float), cube->normalGL, GL_STATIC_DRAW); //the square normals don't need to change, ever,
                     //while the program runs
	 //activate our three kinds of information
	 glEnableVertexAttribArray(positionLocation);
	glEnableVertexAttribArray(colorLocation);
	glEnableVertexAttribArray(normalLocation);
 
	//we're using the vertex data first
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//define how the vertex pointer should work, in our case we're accessing floats 4 at a time with no special pattern
	glVertexAttribPointer(positionLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
 
	//now use color data
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glVertexAttribPointer(colorLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));

	//one more time with the normals
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glVertexAttribPointer(normalLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
 

	//the last thing we need to do is setup our indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	 glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube->inNum * sizeof(unsigned int), cube->indicesGL, GL_STATIC_DRAW);

	 //set the model uniform
	//GL_FALSE is used for not doing transpose operation, because glm has already provided us column major matrices.
	//if the matrices you used is row major, change this parameter to GL_TRUE.
	 glUniformMatrix4fv(u_modelMatrixLocation, 1, GL_FALSE, &model[0][0]);


	//draw the elements
	glDrawElements(GL_TRIANGLES, cube->inNum, GL_UNSIGNED_INT, 0);
 
	//shut off the information since we're done drawing
	glDisableVertexAttribArray(positionLocation);
	glDisableVertexAttribArray(colorLocation);
}

void MyGLWidget::createRay(glm::mat4 model, glm::vec3 start, glm::vec3 end){
	glLineWidth(6.0);
	float vertices[] = {start.x, start.y, start.z, 1.0f, end.x, end.y, end.z, 1.0f};
	float normals[] = {2,2,2,0,2,2,2,0};
	float colors[] = {1,1,1,1,1,1,1,1};
	unsigned int indices[] = {0, 1};

	 //now we put the data into the Vertex Buffer Object for the graphics system to use
	 glBindBuffer(GL_ARRAY_BUFFER, vbo);
	 glBufferData(GL_ARRAY_BUFFER, 2*4 * sizeof(float), vertices, GL_STATIC_DRAW); //the square vertices don't need to change, ever,
						 //while the program runs
	 glBindBuffer(GL_ARRAY_BUFFER, cbo);
	 //always make sure you are telling OpenGL the right size to make the buffer, color data doesn't have as much data!
	 glBufferData(GL_ARRAY_BUFFER, 2*4 * sizeof(float), colors, GL_STATIC_DRAW); 

	 glBindBuffer(GL_ARRAY_BUFFER, nbo);
	 glBufferData(GL_ARRAY_BUFFER, 2*4 * sizeof(float), normals, GL_STATIC_DRAW); //the square normals don't need to change, ever,
						 //while the program runs
	 //activate our three kinds of information
	 glEnableVertexAttribArray(positionLocation);
	 glEnableVertexAttribArray(colorLocation);
	 glEnableVertexAttribArray(normalLocation);
 
	 //we're using the vertex data first
	 glBindBuffer(GL_ARRAY_BUFFER, vbo);
	 //define how the vertex pointer should work, in our case we're accessing floats 4 at a time with no special pattern
	 glVertexAttribPointer(positionLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
 
	 //now use color data
	 glBindBuffer(GL_ARRAY_BUFFER, cbo);
	 glVertexAttribPointer(colorLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));

	 //one more time with the normals
	 glBindBuffer(GL_ARRAY_BUFFER, nbo);
	 glVertexAttribPointer(normalLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
 

	 //the last thing we need to do is setup our indices
	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	 glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	 //set the model uniform
	 //GL_FALSE is used for not doing transpose operation, because glm has already provided us column major matrices.
	 //if the matrices you used is row major, change this parameter to GL_TRUE.
	 glUniformMatrix4fv(u_modelMatrixLocation, 1, GL_FALSE, &model[0][0]);

	 //draw the elements
	 glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
 
	 //shut off the information since we're done drawing
	 glDisableVertexAttribArray(positionLocation);
	 glDisableVertexAttribArray(colorLocation);
}

void MyGLWidget::createRay(glm::mat4 model, glm::vec3 start, glm::vec3 end , glm::vec3 col){
	glLineWidth(6.0);
	float vertices[] = {start.x, start.y, start.z, 1.0f, end.x, end.y, end.z, 1.0f};
	float normals[] = {2,2,2,0,2,2,2,0};
	int c1 = col.r; 
	int c2 = col.g; 
	int c3 = col.b; 
	float colors[] = {c1,c2,c3,1,c1,c2,c3,1};
	unsigned int indices[] = {0, 1};

	 //now we put the data into the Vertex Buffer Object for the graphics system to use
	 glBindBuffer(GL_ARRAY_BUFFER, vbo);
	 glBufferData(GL_ARRAY_BUFFER, 2*4 * sizeof(float), vertices, GL_STATIC_DRAW); //the square vertices don't need to change, ever,
						 //while the program runs
	 glBindBuffer(GL_ARRAY_BUFFER, cbo);
	 //always make sure you are telling OpenGL the right size to make the buffer, color data doesn't have as much data!
	 glBufferData(GL_ARRAY_BUFFER, 2*4 * sizeof(float), colors, GL_STATIC_DRAW); 

	 glBindBuffer(GL_ARRAY_BUFFER, nbo);
	 glBufferData(GL_ARRAY_BUFFER, 2*4 * sizeof(float), normals, GL_STATIC_DRAW); //the square normals don't need to change, ever,
						 //while the program runs
	 //activate our three kinds of information
	 glEnableVertexAttribArray(positionLocation);
	 glEnableVertexAttribArray(colorLocation);
	 glEnableVertexAttribArray(normalLocation);
 
	 //we're using the vertex data first
	 glBindBuffer(GL_ARRAY_BUFFER, vbo);
	 //define how the vertex pointer should work, in our case we're accessing floats 4 at a time with no special pattern
	 glVertexAttribPointer(positionLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
 
	 //now use color data
	 glBindBuffer(GL_ARRAY_BUFFER, cbo);
	 glVertexAttribPointer(colorLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));

	 //one more time with the normals
	 glBindBuffer(GL_ARRAY_BUFFER, nbo);
	 glVertexAttribPointer(normalLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
 

	 //the last thing we need to do is setup our indices
	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	 glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	 //set the model uniform
	 //GL_FALSE is used for not doing transpose operation, because glm has already provided us column major matrices.
	 //if the matrices you used is row major, change this parameter to GL_TRUE.
	 glUniformMatrix4fv(u_modelMatrixLocation, 1, GL_FALSE, &model[0][0]);

	 //draw the elements
	 glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
 
	 //shut off the information since we're done drawing
	 glDisableVertexAttribArray(positionLocation);
	 glDisableVertexAttribArray(colorLocation);
}

//This function is called automatically when the widget is resized, including the first "sizing"
void MyGLWidget::resizeGL(int width, int height) {
    //set the viewport, more boilerplate
	glViewport(0, 0, width, height);

	// The current view matrix is calculated by hand/magic... you should come up with your own method to get the view matrix.
	// be ware that those glm matrices are all COLUMN MAJOR.
	glm::mat4 view = glm::mat4(1.015, -0.573, -0.533, -0.530,
		                       0.000, 1.469, -0.533,  -0.530,
							   -0.812, -0.717, -0.667, -0.662,
							   0.000, 0.000, 7.400, 7.550);

	//set the projection matrix here, it only needs to be changed if the screen is resized otherwise it can stay the same
	glUniformMatrix4fv(u_projMatrixLocation, 1, GL_FALSE, &view[0][0]);
}

void MyGLWidget::keyPressEvent(QKeyEvent *e){
	//a good place to process keystrokes
	switch (e->key()){
	case Qt::Key_Shift:
		shiftPressed = !shiftPressed; 
		break; 
	}
	updateGL(); 
}


/*void MyGLWidget::mousePressEvent(QMouseEvent *e){
	 mousePressed = true;
	 x1 = e->x();
	 y1 = e->y(); 

	float x = e->x();
	float y = e->y();
	// change to normalized device coordinates
	x = x / this->width();
	y = 1 - y / this->height();

	// TODO: update the eye position;
	// world coordinate of eye
	glm::vec3 E;//
	E = glm::vec3(cam->eyePos[0], cam->eyePos[1], cam->eyePos[2]);

	// TODO: update the U vector;
	// up vector
	glm::vec3 U;//
	U = glm::vec3(cam->upDirection[0], cam->upDirection[1], cam->upDirection[2]);

	// Viewing vector
	glm::vec3 center = glm::vec3(0,0,0); // assume we are focusing on the origin, if the center moves, it will be different.
	glm::vec3 C = center - E; // implies viewing distance is |C|

	// TODO: fill the two HALF view angles.
	// Field of view half angles: theta and phi
	// theta is the half angle in x plane. Think about why theta is such a weird value here.
	// phi is the half anlge in y plane. phi = 1/2 * the value you used in glPerspective.
	float phi2 = glm::radians(45.0f / 2.0f); 
	float theta2 = phi2 * width() / height();
	
	// Vector A = C x U
	glm::vec3 A = glm::cross(C, U);
	// The REAL up vector B = A x C
	glm::vec3 B = glm::cross(A, C);
	// View Center M = E + C
	glm::vec3 M = E+C;

	// V || B, but on view plane
	glm::vec3 V = B * (1.0f/(glm::length(B)) * (glm::length(C)*tan(phi2)));
	// H || A, but on view plane
	// If you didn't use theta here, you can simply use the ratio between this->width() and this->height() to determine the length of H
	glm::vec3 H = A * (1.0f/(glm::length(A)) * (glm::length(C)*tan(theta2)));

	// Clicking point on the screen. World Coordinate.
	glm::vec3 P = M + (2*x -1)*H + (2*y -1)*V;
	std::cout << "The point is " <<P[0]<<", "<<P[1]<<", "<<P[2]<< std::endl;

	// The ray is: where t goes from 0 to infinity
	// t is float
	float t = 1000.0f; 
	
	glm::vec3 D = (P - E) / (glm::length((P - E)));
	glm::vec3 R = E + t*D;

	eRay = E; 
	rRay = R; 

	float min_t = 100000.0f;
	int min_i = -1;

	for (int i = 0; i < cube->faces.size(); i++) {
		float t2 = cube->faces[i]->calcT(E, P);
		glm::vec3 asdf = E + t2*D;
		bool asdfasdfasd = cube->faces[i]->containsPoint(E + t2*D);
		if (t2 > 0 && t2 < min_t && cube->faces[i]->containsPoint(E + t2*D)) {
			min_t = t2;
			min_i = i;
		}
	}
	cout<< min_i << endl; 
	if (min_i > -1) {
		selectedFace = cube->faces[min_i];
		selectedFaceFlag = true; 
		selectedHalfEdgeFlag = false; 
		selectedVertexFlag = false; 
		emit setFaceRow(min_i); 
	}
	else selectedFace = NULL;

	// TODO:
	// Add your ray mesh intersection code after...
	rRay = E + min_t*D; 

	if (min_i > -1) {
		HalfEdge* start = cube->faces[min_i]->heStart; 
	for(int i =0; i < cube->faces[min_i]->countNumberOfhalfEdges(); i++){
		Vertex* v = start->V;
		vector<glm::vec3> selectedV = calculateVertexPickingPoints(v, cube->faces[min_i]); 
		bool inVertex = checkHoveringSectionHasPoint(selectedV, cube->faces[min_i], E + min_t*D);
		vector<glm::vec3> selectedHEP = calculateHEPickingPoints(start); 
		bool inHE = checkHoveringSectionHasPoint(selectedHEP, cube->faces[min_i], E + min_t*D);
		if (inHE && !inVertex){
			selectedHE = start; 
			selectedHEPoints = selectedHEP; 
			selectedFaceFlag = false; 
			selectedHalfEdgeFlag = true; 
			selectedVertexFlag = false; 
			emit setHERow(findHEID(start)); 
		}
		if(inVertex){
			selectedVertex = v; 
			selectedVertexPoints = selectedV; 
			selectedFaceFlag = false; 
			selectedHalfEdgeFlag = false; 
			selectedVertexFlag = true; 
			cout<<"selected vertex " << selectedVertex->coords.x << " " << selectedVertex->coords.y << " " << selectedVertex->coords.z<<endl; 
			int iTemp = findVertexID(v); 
			emit setVertexRow(findVertexID(v)); 
			break; 
		}			
		start = start->NEXT; 
	}
	}
	else {selectedVertex = NULL;}
}
*/
void MyGLWidget::mousePressEvent(QMouseEvent *e){
	 mousePressed = true;
	 x1 = e->x();
	 y1 = e->y(); 

	float x = e->x();
	float y = e->y();
	// change to normalized device coordinates
	x = x / this->width();
	y = 1 - y / this->height();

	// TODO: update the eye position;
	// world coordinate of eye
	glm::vec3 E;//
	E = glm::vec3(cam->eyePos[0], cam->eyePos[1], cam->eyePos[2]);

	// TODO: update the U vector;
	// up vector
	glm::vec3 U;//
	U = glm::vec3(cam->upDirection[0], cam->upDirection[1], cam->upDirection[2]);

	// Viewing vector
	glm::vec3 center = cam->ref; //glm::vec3(0,0,0); // assume we are focusing on the origin, if the center moves, it will be different.
	glm::vec3 C = center - E; // implies viewing distance is |C|

	// TODO: fill the two HALF view angles.
	// Field of view half angles: theta and phi
	// theta is the half angle in x plane. Think about why theta is such a weird value here.
	// phi is the half anlge in y plane. phi = 1/2 * the value you used in glPerspective.
	float phi2 = glm::radians(45.0f / 2.0f); 
	float theta2 = phi2 * width() / height();
	
	// Vector A = C x U
	glm::vec3 A = glm::cross(C, U);
	// The REAL up vector B = A x C
	glm::vec3 B = glm::cross(A, C);
	// View Center M = E + C
	glm::vec3 M = E+C;

	// V || B, but on view plane
	glm::vec3 V = B * (1.0f/(glm::length(B)) * (glm::length(C)*tan(phi2)));
	// H || A, but on view plane
	// If you didn't use theta here, you can simply use the ratio between this->width() and this->height() to determine the length of H
	glm::vec3 H = A * (1.0f/(glm::length(A)) * (glm::length(C)*tan(theta2)));

	// Clicking point on the screen. World Coordinate.
	glm::vec3 P = M + (2*x -1)*H + (2*y -1)*V;
	std::cout << "The point is " <<P[0]<<", "<<P[1]<<", "<<P[2]<< std::endl;

	// The ray is: where t goes from 0 to infinity
	// t is float
	float t = 1000.0f; 
	
	glm::vec3 D = (P - E) / (glm::length((P - E)));
	glm::vec3 R = E + t*D;

	eRay = E; 
	rRay = R; 

	float min_t = 100000.0f;
	int min_i = -1;

	for (int i = 0; i < cube->faces.size(); i++) {
		if(cube->faces[i]->checkFacePlanar()){
			float t2 = cube->faces[i]->calcT(E, P);
		glm::vec3 asdf = E + t2*D;
		bool asdfasdfasd = cube->faces[i]->containsPoint(E + t2*D);
		if (t2 > 0 && t2 < min_t && cube->faces[i]->containsPoint(E + t2*D)) {
			min_t = t2;
			min_i = i;
		}
		}
		else{
				FaceHE* fTempTemp = cube->faces[i]; 
				for(int a = 1; a < fTempTemp->countNumberOfhalfEdges()-2; a++){
					FaceHE* fTemp = cube->faces[i]; 

					glm::vec3 vector1 = glm::vec3((fTemp->getHE(0))->V->coords - (fTemp->getHE(a+1))->V->coords);
					glm::vec3 vector2 = glm::vec3((fTemp->getHE(a))->V->coords - (fTemp->getHE(0))->V->coords);

					float t2 = fTemp->calcT(E, P, vector1, vector2);
					//fTempTemp->getHE(0)->NEXT = fTempTemp->getHE(0); 
					bool asdfasdf = fTemp->triContainsPoint(E + t2*D,fTemp->getHE(0)->V->coords, fTemp->getHE(a)->V->coords, fTemp->getHE(a+1)->V->coords); 
					if (t2 > 0 && t2 < min_t && asdfasdf) {
						min_t = t2;
						min_i = i;
					}
				}
			//}
		}
	}
	cout<< min_i << endl; 
	if (min_i > -1) {
		selectedFace = cube->faces[min_i];
		selectedFaceFlag = true; 
		if(shiftPressed){
			selectedHalfEdgeFlag = false; 
		}
		else{
			selectedHalfEdgeFlag = false; 
		}
		selectedVertexFlag = false; 
		emit setFaceRow(min_i); 
		emit setVertexRow(-1);
		emit setHERow(-1); 
	}
	else selectedFace = NULL;

	// TODO:
	// Add your ray mesh intersection code after...
	rRay = E + min_t*D; 

	if (min_i > -1) {
		HalfEdge* start = cube->faces[min_i]->heStart; 
	for(int i =0; i < cube->faces[min_i]->countNumberOfhalfEdges(); i++){
		Vertex* v = start->V;
		vector<glm::vec3> selectedV = calculateVertexPickingPoints(v, cube->faces[min_i]); 
		bool inVertex = checkHoveringSectionHasPoint(selectedV, cube->faces[min_i], E + min_t*D);
		vector<glm::vec3> selectedHEP = calculateHEPickingPoints(start); 
		bool inHE = checkHoveringSectionHasPoint(selectedHEP, cube->faces[min_i], E + min_t*D);
		if (inHE && !inVertex){
			
			

			if(shiftPressed){
				selectedHE2 = selectedHE; 
				selectedHEPoints = selectedHE2Points; 
				selectedHE2Points = selectedHEP; 
				selectedHE2Flag = true; 
				emit setSecondHE(); 
				emit setHERow(findHEID(start));
				
			}
			else{
				selectedHEPoints = selectedHEP;
				selectedHE2 = NULL; 
				selectedHE2Points.clear(); 
				emit clearSHE(); 
			}
			selectedHE = start; 
			selectedFaceFlag = false; 
			selectedHalfEdgeFlag = true; 
			selectedVertexFlag = false; 
			emit setHERow(findHEID(start)); 
			emit setFaceRow(-1); 
			emit setVertexRow(-1); 
		}
		if(inVertex){
			selectedVertex = v; 
			selectedVertexPoints = selectedV; 
			selectedFaceFlag = false; 
			selectedHalfEdgeFlag = false;
			selectedHE2Flag = false; 
			selectedVertexFlag = true; 
			selectedHEPoints.clear(); 
			selectedHE2Points.clear(); 
			selectedHE = NULL; 
			selectedHE2 = NULL; 
			cout<<"selected vertex " << selectedVertex->coords.x << " " << selectedVertex->coords.y << " " << selectedVertex->coords.z<<endl; 
			int iTemp = findVertexID(v); 
			emit setVertexRow(findVertexID(v));
			emit setHERow(-1); 
			emit setFaceRow(-1); 
			emit clearSHE(); 
			break; 
		}			
		start = start->NEXT; 
	}
	}
	else {selectedVertex = NULL;}

	if(selectedFaceFlag){
		selectedHEPoints.clear(); 
			selectedHE2Points.clear(); 
			selectedHE2Flag = false; 
			emit clearSHE(); 
			selectedHE2Points.clear(); 
			selectedHE = NULL; 
			selectedHE2 = NULL; 
	}
	min_t = 100000.0f;
	 min_i = -1;
	if(_boxEnabled){
		std::vector<unitCube*> cubes = box->pointCubeList;
		for(int cubeNum = 0; cubeNum <box->pointCubeList.size(); cubeNum++){
			unitCube* currCube = cubes[cubeNum]; 
			for (int i = 0; i < currCube->faces.size(); i++) {
				if(currCube->faces[i]->checkFacePlanar()){
					float t2 = currCube->faces[i]->calcT(E, P);
					glm::vec3 asdf = E + t2*D;
					bool asdfasdfasd = currCube->faces[i]->containsPoint(E + t2*D);
					if (t2 > 0 && t2 < min_t && currCube->faces[i]->containsPoint(E + t2*D)) {
						min_t = t2;
						min_i = cubeNum;
					}
				}
			}
		}
		if (min_i > -1) {
			if(selectedCubeIndex != -1){
				for(int j = 0; j < ((Mesh*)(box->pointCubeList[selectedCubeIndex]))->faces.size(); j++){
					box->pointCubeList[selectedCubeIndex]->faces[j]->colors=glm::vec3(0,1,1); 
				}
			}
			selectedCube = cubes[min_i];
			selectedCubeFlag = true; 
			selectedCubeIndex = min_i; 
			for(int j = 0; j < ((Mesh*)(box->pointCubeList[selectedCubeIndex]))->faces.size(); j++){
				box->pointCubeList[selectedCubeIndex]->faces[j]->colors=glm::vec3(1,1,1); 
			}
			
			selectedFace = NULL;
			selectedVertex = NULL; 
			selectedHE= NULL; 
			selectedHE2 = NULL; 

			selectedVertexPoints.clear(); 
			selectedHEPoints.clear(); 
			selectedHE2Points.clear(); 
			emit clearSHE(); 
			emit setVertexRow(-1);
			emit setHERow(-1); 
			emit setFaceRow(-1); 
		}
		else {
			if(selectedCubeIndex != -1){
				for(int j = 0; j < ((Mesh*)(box->pointCubeList[selectedCubeIndex]))->faces.size(); j++){
					box->pointCubeList[selectedCubeIndex]->faces[j]->colors=glm::vec3(0,1,1); 
				}
			}
			selectedCubeFlag = false; 
			selectedCube = NULL;
			selectedCubeIndex = -1; 
		}
		cout << "selectedCubeFlag "<<selectedCubeFlag<<endl; 
		cout <<"selectedCubeIndex " <<selectedCubeIndex<<endl; 
	}
}

void MyGLWidget::setXBox(int a){
	float xn = (float) a / 5.0f;
	if(selectedCube && selectedCubeFlag && selectedCubeIndex>-1){
		cout <<"selectedCubeIndex " <<selectedCubeIndex<<endl; 
		box->pointCubeList[selectedCubeIndex]->centerPoint.x = xn; 
		float tempa=box->pointCubeList[selectedCubeIndex]->ab;
		unitCube* tempuc=new unitCube(box->pointCubeList[selectedCubeIndex]->centerPoint, tempa);
		box->pointCubeList[selectedCubeIndex]=tempuc;
		cout <<"center moved to "<<box->pointCubeList[selectedCubeIndex]->centerPoint.x <<endl; 
		this->drawBox(model,box); 
	}
	else{
		emit sendSetX(a); 
	}
}

void MyGLWidget::setYBox(int a){
	float yn = (float) a / 5.0f;
	if(selectedCube && selectedCubeFlag && selectedCubeIndex>-1){
		box->pointCubeList[selectedCubeIndex]->centerPoint.y = yn; 
		float tempa=box->pointCubeList[selectedCubeIndex]->ab;
		unitCube* tempuc=new unitCube(box->pointCubeList[selectedCubeIndex]->centerPoint, tempa);
		box->pointCubeList[selectedCubeIndex]=tempuc;
		this->drawBox(model,box); 
	}
	else{
		emit sendSetY(a); 
	}
}

void MyGLWidget::setZBox(int a){
	float zn = (float) a / 5.0f;
	if(selectedCube && selectedCubeFlag && selectedCubeIndex>-1){
		box->pointCubeList[selectedCubeIndex]->centerPoint.z = zn; 
		float tempa=box->pointCubeList[selectedCubeIndex]->ab;
		unitCube* tempuc=new unitCube(box->pointCubeList[selectedCubeIndex]->centerPoint, tempa);
		box->pointCubeList[selectedCubeIndex]=tempuc;
		this->drawBox(model,box); 
	}
	else{
		emit sendSetZ(a); 
	}
}

int MyGLWidget::findHEID(HalfEdge* h){
	vector<HalfEdge*> temp = cube->halfEdges;
	for(int i = 0; i < temp.size(); i++){
		if(temp[i] == h){
			return i; 
		}
	}
	return -1; 
}

int MyGLWidget::findVertexID(Vertex* x){
	vector<Vertex*> temp = cube->vertices;
	for(int i = 0; i < temp.size(); i++){
		if(temp[i] == x){
			return i; 
		}
	}
	return -1; 
}

void MyGLWidget::checkFacePlanarity() {
	for (int i = 0; i < cube->faces.size(); i++) {
		if (!(cube->faces[i]->checkFacePlanar())) {
			doSplitQuadIntoTwoTriangles(cube->faces[i]);
		}
	}
	
}

void MyGLWidget::snapView(){
	if (selectedFace&&selectedFaceFlag) {
		int xCount = 0; 
		int yCount = 0; 
		int zCount = 0; 
		int count = 0; 
		for (int i = 0; i < selectedFace->countNumberOfhalfEdges(); i++) {
			glm::vec3 p1 = selectedFace->getHE(i)->V->coords;
			//glm::vec3 p2 = selectedFace->getHE(i + 1)->V->coords;
			xCount += p1.x; 
			yCount += p1.y; 
			zCount += p1.z; 
			count++; 
		}
		xCount = xCount / count; 
		yCount = yCount / count; 
		zCount = zCount / count; 

		cam->ref = glm::vec3(xCount,yCount,zCount); 

		/*glm::vec3 centroid = glm::vec3(xCount, yCount, zCount); 
		glm::vec3 vertex = cam->ref + (centroid - cam->ref) * (r / glm::length(centroid - cam->ref)); 

		if(vertex.x >= 0){
			theta = (1/DEG2RAD)*acos(vertex.z / r);
		}
		else{
			theta = 3.14159265 - (1/DEG2RAD)*acos(vertex.z / r);
		}
		phi = (1/DEG2RAD)*acos(vertex.z / (r));

		cam->eyePos = glm::vec3(vertex.x,vertex.z,vertex.y); 

		updateGL(); 
		*/

	}
	if(selectedVertex && selectedVertexFlag){
		glm::vec3 p1 = selectedVertex->coords; 
		cam->ref = p1; 
	}
	if(selectedHE && selectedHalfEdgeFlag){
		glm::vec3 p1 = selectedHE->V->coords; 
		glm::vec3 p2 = selectedHE->F->findPrev(selectedHE)->V->coords; 
		glm::vec3 avg = glm::vec3((p1.x+p2.x)/2.0f,(p1.y+p2.y)/2.0f,(p1.z+p2.z)/2.0f); 
		cam->ref = avg ; 
	}
}

void MyGLWidget::triangleMesh(){
	if (mesh_load==1){
		for (int i = 0; i < cube->faces.size(); i++) {
			doSplitQuadIntoTwoTriangles(cube->faces[i]);
		}
	}
}


void MyGLWidget::mouseReleaseEvent(QMouseEvent *e){
	mousePressed = false;
}


/*void MyGLWidget::mouseMoveEvent(QMouseEvent *e){
	if(mousePressed == true){
		int x2 = e->x(); 
		int y2 = e->y(); 
		float oldTheta = theta; 
		if(!mouseFlipped){
			phi = phi - x2+x1; 
			theta = theta + y2-y1;
		}
		else{
			phi = phi + x2-x1; 
			theta = theta+ y2-y1;
		}
		float correction = 0.0f; 
		if(y2-y1>0){
			correction = 2.0f; 
		}
		else if (y2-y1<0){
			correction = -2.0f; 
		}
		if(oldTheta <=theta){
			for(int i = oldTheta; i<=theta; i++){
				if(i % 180 == 0){
					theta = theta + correction;
					mouseFlipped = !mouseFlipped; 
					break;
				}
			}
		}
		else{
			for(int i = theta; i<=oldTheta; i++){
				if(i % 180 == 0){
					theta = theta + correction;
					mouseFlipped = !mouseFlipped; 
					break;
				}
			}
		}
		x1 = x2; 
		y1 = y2; 
		updateGL(); 
	}
	else{
 

	float x = e->x();
	float y = e->y();
	// change to normalized device coordinates
	x = x / this->width();
	y = 1 - y / this->height();

	// update the eye position;
	// world coordinate of eye
	glm::vec3 E;//
	E = glm::vec3(cam->eyePos[0], cam->eyePos[1], cam->eyePos[2]);

	// update the U vector;
	// up vector
	glm::vec3 U;//
	U = glm::vec3(cam->upDirection[0], cam->upDirection[1], cam->upDirection[2]);

	// Viewing vector
	glm::vec3 center = glm::vec3(0,0,0); // assume we are focusing on the origin, if the center moves, it will be different.
	glm::vec3 C = center - E; // implies viewing distance is |C|

	//  fill the two HALF view angles.
	// Field of view half angles: theta and phi
	// theta is the half angle in x plane. Think about why theta is such a weird value here.
	// phi is the half anlge in y plane. phi = 1/2 * the value you used in glPerspective.
	float phi2 = glm::radians(45.0f / 2.0f); 
	float theta2 = phi2 * width() / height();
	
	// Vector A = C x U
	glm::vec3 A = glm::cross(C, U);
	// The REAL up vector B = A x C
	glm::vec3 B = glm::cross(A, C);
	// View Center M = E + C
	glm::vec3 M = E+C;

	// V || B, but on view plane
	glm::vec3 V = B * (1.0f/(glm::length(B)) * (glm::length(C)*tan(phi2)));
	// H || A, but on view plane
	// If you didn't use theta here, you can simply use the ratio between this->width() and this->height() to determine the length of H
	glm::vec3 H = A * (1.0f/(glm::length(A)) * (glm::length(C)*tan(theta2)));

	// Clicking point on the screen. World Coordinate.
	glm::vec3 P = M + (2*x -1)*H + (2*y -1)*V;
	//std::cout << "The point is " <<P[0]<<", "<<P[1]<<", "<<P[2]<< std::endl;

	// The ray is: where t goes from 0 to infinity
	// t is float
	float t = 1000.0f; 
	
	glm::vec3 D = (P - E) / (glm::length((P - E)));
	glm::vec3 R = E + t*D;


	float min_t = 100000.0f;
	int min_i = -1;

	for (int i = 0; i < cube->faces.size(); i++) {
		float t2 = cube->faces[i]->calcT(E, P);

		if (t2 > 0 && t2 < min_t && cube->faces[i]->containsPoint(E + t2*D)) {
			min_t = t2;
			min_i = i;
		}
	}
	if (min_i > -1) {
		hoveredFace = cube->faces[min_i];
		hoveringVertexFlag = false; 
		hoveringHalfEdgeFlag = false; 
		hoveringFaceFlag = true; 
		
		glm::vec3 sent = E + t*D; 


		HalfEdge* start = cube->faces[min_i]->heStart; 
	for(int i =0; i < cube->faces[min_i]->countNumberOfhalfEdges(); i++){
		Vertex* v = start->V;
		vector<glm::vec3> hoveringV = calculateVertexPickingPoints(v, cube->faces[min_i]); 
		bool inVertex = checkHoveringSectionHasPoint(hoveringV, cube->faces[min_i], E + min_t*D);
		vector<glm::vec3> hoveringHEP = calculateHEPickingPoints(start); 
		bool inHE = checkHoveringSectionHasPoint(hoveringHEP, cube->faces[min_i], E + min_t*D);
		if (inHE && !inVertex){
			hoveringHE = start; 
			hoveringHEPoints = hoveringHEP; 
			hoveringFaceFlag = false; 
			hoveringHalfEdgeFlag = true; 
			hoveringVertexFlag = false; 
			cout<< "HE hit"<<endl;  
		}
		if(inVertex){
			hoveringVertex = v; 
			hoveringVertexPoints = hoveringV; 
			hoveringFaceFlag = false; 
			hoveringHalfEdgeFlag = false; 
			hoveringVertexFlag = true; 
			cout<< "vertex hit"<<endl; 
			break; 
		}			
		start = start->NEXT; 
	}
	}
	else {
		hoveredFace = NULL;
		hoveringFaceFlag = false; 
		hoveringVertexFlag = false; 
		hoveringHalfEdgeFlag = false; 
	}
	

	}

}*/

void MyGLWidget::mouseMoveEvent(QMouseEvent *e){
	if(mousePressed == true){
		int x2 = e->x(); 
		int y2 = e->y(); 
		float oldTheta = theta; 
		if(!mouseFlipped){
			phi = phi - x2+x1; 
			theta = theta + y2-y1;
		}
		else{
			phi = phi + x2-x1; 
			theta = theta+ y2-y1;
		}
		float correction = 0.0f; 
		if(y2-y1>0){
			correction = 2.0f; 
		}
		else if (y2-y1<0){
			correction = -2.0f; 
		}
		if(oldTheta <=theta){
			for(int i = oldTheta; i<=theta; i++){
				if(i % 180 == 0){
					theta = theta + correction;
					mouseFlipped = !mouseFlipped; 
					break;
				}
			}
		}
		else{
			for(int i = theta; i<=oldTheta; i++){
				if(i % 180 == 0){
					theta = theta + correction;
					mouseFlipped = !mouseFlipped; 
					break;
				}
			}
		}
		x1 = x2; 
		y1 = y2; 
		updateGL(); 
	}
	else{
 

	float x = e->x();
	float y = e->y();
	// change to normalized device coordinates
	x = x / this->width();
	y = 1 - y / this->height();

	// update the eye position;
	// world coordinate of eye
	glm::vec3 E;//
	E = glm::vec3(cam->eyePos[0], cam->eyePos[1], cam->eyePos[2]);

	// update the U vector;
	// up vector
	glm::vec3 U;//
	U = glm::vec3(cam->upDirection[0], cam->upDirection[1], cam->upDirection[2]);

	// Viewing vector
	glm::vec3 center = cam->ref; //glm::vec3(0,0,0); // assume we are focusing on the origin, if the center moves, it will be different.
	glm::vec3 C = center - E; // implies viewing distance is |C|

	//  fill the two HALF view angles.
	// Field of view half angles: theta and phi
	// theta is the half angle in x plane. Think about why theta is such a weird value here.
	// phi is the half anlge in y plane. phi = 1/2 * the value you used in glPerspective.
	float phi2 = glm::radians(45.0f / 2.0f); 
	float theta2 = phi2 * width() / height();
	
	// Vector A = C x U
	glm::vec3 A = glm::cross(C, U);
	// The REAL up vector B = A x C
	glm::vec3 B = glm::cross(A, C);
	// View Center M = E + C
	glm::vec3 M = E+C;

	// V || B, but on view plane
	glm::vec3 V = B * (1.0f/(glm::length(B)) * (glm::length(C)*tan(phi2)));
	// H || A, but on view plane
	// If you didn't use theta here, you can simply use the ratio between this->width() and this->height() to determine the length of H
	glm::vec3 H = A * (1.0f/(glm::length(A)) * (glm::length(C)*tan(theta2)));

	// Clicking point on the screen. World Coordinate.
	glm::vec3 P = M + (2*x -1)*H + (2*y -1)*V;
	//std::cout << "The point is " <<P[0]<<", "<<P[1]<<", "<<P[2]<< std::endl;

	// The ray is: where t goes from 0 to infinity
	// t is float
	float t = 1000.0f; 
	
	glm::vec3 D = (P - E) / (glm::length((P - E)));
	glm::vec3 R = E + t*D;


	float min_t = 100000.0f;
	int min_i = -1;

	for (int i = 0; i < cube->faces.size(); i++) {
		float t2 = cube->faces[i]->calcT(E, P);

		if (t2 > 0 && t2 < min_t && cube->faces[i]->containsPoint(E + t2*D)) {
			min_t = t2;
			min_i = i;
		}
	}
	if (min_i > -1) {
		hoveredFace = cube->faces[min_i];
		hoveringVertexFlag = false; 
		hoveringHalfEdgeFlag = false; 
		hoveringFaceFlag = true; 
		
		glm::vec3 sent = E + t*D; 


		HalfEdge* start = cube->faces[min_i]->heStart; 
	for(int i =0; i < cube->faces[min_i]->countNumberOfhalfEdges(); i++){
		Vertex* v = start->V;
		vector<glm::vec3> hoveringV = calculateVertexPickingPoints(v, cube->faces[min_i]); 
		bool inVertex = checkHoveringSectionHasPoint(hoveringV, cube->faces[min_i], E + min_t*D);
		vector<glm::vec3> hoveringHEP = calculateHEPickingPoints(start); 
		bool inHE = checkHoveringSectionHasPoint(hoveringHEP, cube->faces[min_i], E + min_t*D);
		if (inHE && !inVertex){
			hoveringHE = start; 
			hoveringHEPoints = hoveringHEP; 
			hoveringFaceFlag = false; 
			hoveringHalfEdgeFlag = true; 
			hoveringVertexFlag = false; 
			cout<< "HE hit"<<endl;  
		}
		if(inVertex){
			hoveringVertex = v; 
			hoveringVertexPoints = hoveringV; 
			hoveringFaceFlag = false; 
			hoveringHalfEdgeFlag = false; 
			hoveringVertexFlag = true; 
			cout<< "vertex hit"<<endl; 
			break; 
		}			
		start = start->NEXT; 
	}
	}
	else {
		hoveredFace = NULL;
		hoveringFaceFlag = false; 
		hoveringVertexFlag = false; 
		hoveringHalfEdgeFlag = false; 
	}
	

	}

}

vector<glm::vec3> MyGLWidget::calculateHEPickingPoints(HalfEdge* h){
	vector<glm::vec3> toReturn; 
	FaceHE* f = h->F; 
	glm::vec3 w = h->V->coords; 
	toReturn.push_back(w); 
	
	 
	HalfEdge* heNext = h->NEXT;
	HalfEdge* hePrev = f->findPrev(h); 
	HalfEdge* hePrevPrev = f->findPrev(hePrev); 
	toReturn.push_back(hePrev->V->coords);

	glm::vec3 AB = h->V->coords - hePrev->V->coords; 
	glm::vec3 AC = hePrevPrev->V->coords - hePrev->V->coords; 
	glm::vec3 BA = h->V->coords - hePrev->V->coords; 
	glm::vec3 BC = hePrevPrev->V->coords - hePrev->V->coords;

	glm::vec3 P = h->V->coords + ((glm::dot(AB,AC) / glm::length(AB)) * AB); 
	glm::vec3 D = hePrev->V->coords + ((glm::dot(BA,BC) / glm::length(BA)) * BA);

	glm::vec3 v = hePrev->V->coords;

	glm::vec3 second ((6.0f*(v.x) + hePrevPrev->V->coords.x)/7.0f,
			(6.0f*(v.y) + hePrevPrev->V->coords.y)/7.0f , (6.0f*(v.z) + hePrevPrev->V->coords.z)/7.0f);
	glm::vec3 fourth ((6.0f*(w.x) + heNext->V->coords.x)/7.0f,
			(6.0f*(w.y) + heNext->V->coords.y)/7.0f , (6.0f*(w.z) + heNext->V->coords.z)/7.0f);

		toReturn.push_back(second); 
		toReturn.push_back(fourth); 
		

	return toReturn;
}

vector<glm::vec3> MyGLWidget::calculateVertexPickingPoints(Vertex* v, FaceHE* f){
	vector<glm::vec3> toReturn; 
	glm::vec3 w = v->coords; 
	toReturn.push_back(w); 
	HalfEdge* hePointing = f->getEdgeThatPointsToV(v); 
	HalfEdge* heNext = hePointing->NEXT;
	HalfEdge* hePrev = f->findPrev(hePointing); 

	glm::vec3 span1 = hePointing->V->coords - heNext->V->coords; 
	glm::vec3 span2 = hePointing->V->coords - hePrev->V->coords;

	glm::mat3x2 planeSpannedMatrix = glm::mat3x2(span1.x, span1.y, span1.z, span2.x, span2.y, span2.z); 
	glm::mat3 projectionMatrix = glm::transpose(planeSpannedMatrix) * planeSpannedMatrix; 
	
	glm::vec3 second ((6.0f*(v->coords.x) + heNext->V->coords.x)/7.0f,
			(6.0f*(v->coords.y) + heNext->V->coords.y)/7.0f , (6.0f*(v->coords.z) + heNext->V->coords.z)/7.0f);
	glm::vec3 fourth ((6.0f*(v->coords.x) + hePrev->V->coords.x)/7.0f,
			(6.0f*(v->coords.y) + hePrev->V->coords.y)/7.0f , (6.0f*(v->coords.z) + hePrev->V->coords.z)/7.0f);
	

		toReturn.push_back(second); 
		toReturn.push_back(fourth); 

	return toReturn;
}

bool MyGLWidget::checkHoveringSectionHasPoint(vector<glm::vec3> points, FaceHE* f, glm::vec3 check){
	if(points.size() == 3){
		bool contains = f->triContainsPoint(check, points[0], points[1], points[2]); 
		return contains; 
	}
	else  if(points.size() == 4){
		bool c1 = f->triContainsPoint(check, points[0], points[1], points[2]); 
		bool c2 = f->triContainsPoint(check, points[0], points[2], points[3]);
		return (c1||c2); 
	}
	
}

void MyGLWidget::redrawOutlines(){
	if(selectedFaceFlag){
		
	}
	else if(selectedVertexFlag){
		selectedVertexPoints = calculateVertexPickingPoints(selectedVertex,selectedFace);
		for (int i = 0; i < selectedVertexPoints.size(); i++) {
			glm::vec3 p1 = selectedVertexPoints[i];
			glm::vec3 p2;
			if(i+1 == selectedVertexPoints.size()){
				p2 = selectedVertexPoints[0]; 
			}
			else{
				p2 = selectedVertexPoints[i+1];
			}
			glm::vec3 colors = glm::vec3(1,1,1); 
			createRay(model, p1, p2, colors);
		}
		emit setVertexRow(selectedVertex->idV); 
	}
	else if(selectedHalfEdgeFlag){

	}
}

void MyGLWidget::wheelEvent(QWheelEvent* e){
	r += e->delta()*0.01; 
	updateGL(); 
}

void MyGLWidget::doUpdateGL(){
	updateGL(); 
}

void MyGLWidget::gotAddVertexToEdge(HalfEdge* h, Vertex* v){
	cube->Mesh::addVertexToEdge(h,v);
	emit sendFaces(&(cube->faces)); 
	emit sendVertices(&(cube->vertices)); 
	emit sendHalfEdges(&(cube->halfEdges)); 
	for(int i = 0; i <cube->faces.size();i++){
		cout<<"NUMofVertex #" << i<<"= "<< cube->faces[i]->countNumberOfhalfEdges()<<endl;;
	    
	}
	cube->createGL();

}

void MyGLWidget::doAddEdgeBetweenTwoFacesShareAVertex(FaceHE* a ,FaceHE* b,HalfEdge* c,HalfEdge* d){
	
	cube->Mesh::addEdgeBetweenTwoFacesShareAVertex(a,b,c,d);
	emit sendFaces(&(cube->faces)); 
	emit sendVertices(&(cube->vertices)); 
	emit sendHalfEdges(&(cube->halfEdges)); 
	cube->createGL();
}

void MyGLWidget::addEdge(){
	if(selectedHE && selectedHE2){
		HalfEdge* firstF = selectedHE;  
		HalfEdge* secondF = selectedHE2; 
		HalfEdge* hF = selectedHE;
		HalfEdge* hS = selectedHE2; 
		HalfEdge* hSStart = secondF;
		if(firstF->V->coords != secondF->V->coords){
			return; 
		}
		int clockwise = 0; 
		int counterclock = 0; 
		while((hF->NEXT->SYM!=NULL || hF->SYM->F->findPrev(hF->SYM)!=NULL) ){ 
			//maybe this		   ^ should be && if delete takes away one face and not the other
			if(hF->NEXT->SYM==hS){
				clockwise++; 
				break;
			}
			if(hF->SYM->F->findPrev(hF->SYM)==hS){
				counterclock++; 
				break; 
			}
		}
		if(clockwise>=counterclock){
			cube->Mesh::addEdgeBetweenTwoFacesShareAVertex(firstF->F,secondF->F,firstF,secondF);
			//emit callAddEdgeBetweenTwoFacesShareAVertex(firstF->F,secondF->F,firstF,secondF);
		}
		else{
			cube->Mesh::addEdgeBetweenTwoFacesShareAVertex(secondF->F,firstF->F,secondF,firstF);
			//emit callAddEdgeBetweenTwoFacesShareAVertex(secondF->F,firstF->F,secondF,firstF);
		}
		emit sendFaces(&(cube->faces)); 
	emit sendVertices(&(cube->vertices)); 
	emit sendHalfEdges(&(cube->halfEdges)); 
	cube->createGL();
	}
	selectedHE = NULL; 
	selectedHE2 = NULL; 
	selectedHEPoints.clear(); 
	selectedHE2Points.clear(); 
	
}


void MyGLWidget::doSplitQuadIntoTwoTriangles(FaceHE* f){
	cube->Mesh::splitQuadIntoTwoTriangles(f); 
	emit sendFaces(&(cube->faces)); 
	emit sendVertices(&(cube->vertices)); 
	emit sendHalfEdges(&(cube->halfEdges)); 
	cube->createGL();
}

void MyGLWidget::doDeleteVertex(HalfEdge* h){
	cube->Mesh::deleteVertex(h); 
	emit sendFaces(&(cube->faces)); 
	emit sendVertices(&(cube->vertices)); 
	emit sendHalfEdges(&(cube->halfEdges)); 
	cube->createGL();
}

//from swiftless.com
char* MyGLWidget::textFileRead(const char* fileName) {
    char* text;
    
    if (fileName != NULL) {
        FILE *file = fopen(fileName, "rt");
        
        if (file != NULL) {
            fseek(file, 0, SEEK_END);
            int count = ftell(file);
            rewind(file);
            
            if (count > 0) {
                text = (char*)malloc(sizeof(char) * (count + 1));
                count = fread(text, sizeof(char), count, file);
                text[count] = '\0';	//cap off the string with a terminal symbol, fixed by Cory
            }
            fclose(file);
        }
    }
    return text;
}

void MyGLWidget::printLinkInfoLog(int prog) 
{
	int infoLogLen = 0;
	int charsWritten = 0;
	GLchar *infoLog;

	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &infoLogLen);

	// should additionally check for OpenGL errors here

	if (infoLogLen > 0)
	{
		infoLog = new GLchar[infoLogLen];
		// error check for fail to allocate memory omitted
		glGetProgramInfoLog(prog,infoLogLen, &charsWritten, infoLog);
		cerr << "InfoLog:" << endl << infoLog << endl;
		delete [] infoLog;
	}
}

void MyGLWidget::printShaderInfoLog(int shader)
{
	int infoLogLen = 0;
	int charsWritten = 0;
	GLchar *infoLog;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

	// should additionally check for OpenGL errors here

	if (infoLogLen > 0)
	{
		infoLog = new GLchar[infoLogLen];
		// error check for fail to allocate memory omitted
		glGetShaderInfoLog(shader,infoLogLen, &charsWritten, infoLog);
		cerr << "InfoLog:" << endl << infoLog << endl;
		delete [] infoLog;
	}

	// should additionally check for OpenGL errors here
}

void MyGLWidget::startCubeRotation(){
	timer->start(17); 
	rotatingFlag = true; 
}

void MyGLWidget::stopCubeRotation(){
	//timer->stop(); 
	rotatingFlag = false; 
}

glm::vec3 MyGLWidget::calcCoordinates(){
	float x =  r*sin((theta)*DEG2RAD)*cos(phi*DEG2RAD);
	float y = r*sin(theta*DEG2RAD)*sin(phi*DEG2RAD);
	float z = r*cos(theta*DEG2RAD);

	return glm::vec3(x,z,y); 
}


void MyGLWidget::newCube(){
  cube = new unitCube();
  box=new Box(cube,boxL,boxM,boxN);
  emit sendFaces(&(cube->faces)); 
  emit sendVertices(&(cube->vertices)); 
  emit sendHalfEdges(&(cube->halfEdges)); 
  cube->createGL();
}

void MyGLWidget::showContextMenu(const QPoint& pos) {
    // for most widgets
    QPoint globalPos = this->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos); 

    QMenu myMenu;
 /*if (mouseW->selectedVertex) {
  myMenu.addAction("Delete Vertex");
  myMenu.addAction("Snap View to Vertex");
 }*/

  if (selectedFace) {
  //myMenu.addAction("Split Face");
  myMenu.addAction("Change Color");
  myMenu.addAction("Snap View");
  //myMenu.addAction("Snap View to Face");
 }
  else{
  myMenu.addAction("Front View");
  myMenu.addAction("Back View");
  myMenu.addAction("Top View");
  myMenu.addAction("Bottom View");
  myMenu.addAction("Right View");
  myMenu.addAction("Left View");
   myMenu.addSeparator();
  myMenu.addAction("Perspective");
  myMenu.addAction("Reset Camera");
  myMenu.addSeparator();
  myMenu.addAction("Show/Hide Grid");
  }

   QAction* selectedItem = myMenu.exec(globalPos);
  
   if(selectedItem){
   if (selectedItem->text() == "Change Color") {
   float red = 0.0f;
   float green = 0.0f;
   float blue = 0.0f;

   QColor color = QColorDialog::getColor(Qt::black, this, "New Face Color", QColorDialog::DontUseNativeDialog);
   if(color.isValid()) {
    QRgb rgb = color.rgb();
    red = (static_cast<float>(qRed(rgb))/255.0f);
    green = (static_cast<float>(qGreen(rgb))/255.0f);
    blue = (static_cast<float>(qBlue(rgb))/255.0f);
    selectedFace->colors = glm::vec3(red, green, blue);
   }
  }
   if (selectedItem->text() == "Snap View") {
	   snapView(); 
   }
    if (selectedItem->text() == "Front View") {
	   frontView(); 
   }
	 if (selectedItem->text() == "Top View") {
	   overheadView(); 
   }
	  if (selectedItem->text() == "Back View") {
	   backView(); 
   }
	   if (selectedItem->text() == "Bottom View") {
	   bottomView(); 
   }
	    if (selectedItem->text() == "Right View") {
	     rightView(); 
   }
		 if (selectedItem->text() == "Left View") {
	     leftView(); 
   }
		 if (selectedItem->text() == "Perspective") {
	     perspectiveView(); 
   }
		 if (selectedItem->text() == "Reset Camera") {
	    resetCamera();
   }
		if (selectedItem->text() == "Show/Hide Grid") {
	    changeGrid();
   }
   }
}

void MyGLWidget::subdivide(){
	/*
	if (mesh_load==1){
		 mesh->subdivideMesh();
		emit sendVertices(&(mesh->vertices));
		emit sendFaces(&(mesh->faces));
		emit sendHalfEdges(&(mesh->halfEdges));
		 mesh->createGL();
	}
	else{*/
     cube->subdivideMesh();
	 emit sendVertices(&(cube->vertices));
     emit sendFaces(&(cube->faces));
     emit sendHalfEdges(&(cube->halfEdges));
	 cube->createGL();
//}
}

void MyGLWidget::saveMesh(){
    QString  fileName = QFileDialog::getSaveFileName(this,
     tr("Save"), "", tr("OBJ (*.obj)"));
	if(!fileName.isEmpty()){
		QByteArray ba = fileName.toLatin1();
		const char* myChar = ba.data();

		if (mesh_load==1){
			mySave* saveOFile=new mySave(cube);
			saveOFile->saveObj(myChar);
		}
		else{
			mySave* saveOFile=new mySave(cube);
			saveOFile->saveObj(myChar);
		
		}


	}
}

void MyGLWidget::loadMesh(){
	QString  fileName = QFileDialog::getOpenFileName(this,
     tr("Open OBJ"), "", tr("OBJ (*.obj)"));
	if(!fileName.isEmpty()){
		QByteArray ba = fileName.toLatin1();
		const char* myChar = ba.data();
		Loader* l=new Loader(myChar);
		int result=l->loadObj();

		cube=l->getMesh();
		cube->createGL();

		box=new Box(cube,boxL,boxM,boxN);

		emit sendVertices(&(cube->vertices));
		emit sendFaces(&(cube->faces));
		emit sendHalfEdges(&(cube->halfEdges));



		mesh_load=1;
	}
} 

void MyGLWidget::callLoadShader(QString filename){
          loadShader(filename);
}

void MyGLWidget::testLoader(glm::mat4 model){

	float* vertices = cube->vertGL;

  //now we put the data into the Vertex Buffer Object for the graphics system to use
 glBindBuffer(GL_ARRAY_BUFFER, vbo);
 glBufferData(GL_ARRAY_BUFFER, cube->num*4 * sizeof(float), cube->vertGL, GL_STATIC_DRAW); //the square vertices don't need to change, ever,
                     //while the program runs
 glBindBuffer(GL_ARRAY_BUFFER, cbo);
 //always make sure you are telling OpenGL the right size to make the buffer, color data doesn't have as much data!
 glBufferData(GL_ARRAY_BUFFER, cube->num*4 * sizeof(float), cube->colorGL, GL_STATIC_DRAW); 

 	

 glBindBuffer(GL_ARRAY_BUFFER, nbo);
 glBufferData(GL_ARRAY_BUFFER, cube->num*4 * sizeof(float), cube->normalGL, GL_STATIC_DRAW); //the square normals don't need to change, ever,
                     //while the program runs
 //activate our three kinds of information
 glEnableVertexAttribArray(positionLocation);
 glEnableVertexAttribArray(colorLocation);
 glEnableVertexAttribArray(normalLocation);
 
 //we're using the vertex data first
 glBindBuffer(GL_ARRAY_BUFFER, vbo);
 //define how the vertex pointer should work, in our case we're accessing floats 4 at a time with no special pattern
 glVertexAttribPointer(positionLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
 
 //now use color data
 glBindBuffer(GL_ARRAY_BUFFER, cbo);
 glVertexAttribPointer(colorLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));

 //one more time with the normals
 glBindBuffer(GL_ARRAY_BUFFER, nbo);
 glVertexAttribPointer(normalLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
 

 //the last thing we need to do is setup our indices
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
 glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube->inNum * sizeof(unsigned int), cube->indicesGL, GL_STATIC_DRAW);

 //set the model uniform
 //GL_FALSE is used for not doing transpose operation, because glm has already provided us column major matrices.
 //if the matrices you used is row major, change this parameter to GL_TRUE.
 glUniformMatrix4fv(u_modelMatrixLocation, 1, GL_FALSE, &model[0][0]);


 //draw the elements
 glDrawElements(GL_TRIANGLES,cube->inNum, GL_UNSIGNED_INT, 0);
 
 //shut off the information since we're done drawing
 glDisableVertexAttribArray(positionLocation);
 glDisableVertexAttribArray(colorLocation);

}

void MyGLWidget::drawPoint(glm::mat4 model, glm::vec3 loc,float a){
	float x,y,z;
	x=loc.x;
	y=loc.y;
	z=loc.z;

	// vertex coords array, remember the homogeneous representation?
	float vertices[] = {x+a,y+a,z+a,1,  x-a,y+a,z+a,1,  x-a,y-a,z+a,1,  x+a,y-a,z+a,1,        // v0-v1-v2-v3
                        x+a,y+a,z+a,1,  x+a,y-a,z+a,1,  x+a,y-a,z-a,1,  x+a,y+a,z-a,1,        // v0-v3-v4-v5
                        x+a,y+a,z+a,1,  x+a,y+a,z-a,1,  x-a,y+a,z-a,1,  x-a,y+a,z+a,1,        // v0-v5-v6-v1
                        x-a,y+a,z+a,1,  x-a,y+a,z-a,1,  x-a,y-a,z-a,1,  x-a,y-a,z+a,1,    // v1-v6-v7-v2
                        x-a,y-a,z-a,1,  x+a,y-a,z-a,1,  x+a,y-a,z+a,1,  x-a,y-a,z+a,1,    // v7-v4-v3-v2
                        x+a,y-a,z-a,1,  x-a,y-a,z-a,1,  x-a,y+a,z-a,1,  x+a,y+a,z-a,1};   // v4-v7-v6-v5

	// normal array, normal is a vector which has the 4th value zero in homogeneous representation.
	float normals[] = {0,0,1,0,  0,0,1,0,  0,0,1,0,  0,0,1,0,             // v0-v1-v2-v3
                       1,0,0,0,  1,0,0,0,  1,0,0,0, 1,0,0,0,              // v0-v3-v4-v5
                       0,1,0,0,  0,1,0,0,  0,1,0,0, 0,1,0,0,              // v0-v5-v6-v1
                       -1,0,0,0,  -1,0,0,0, -1,0,0,0,  -1,0,0,0,          // v1-v6-v7-v2
                       0,-1,0,0,  0,-1,0,0,  0,-1,0,0,  0,-1,0,0,         // v7-v4-v3-v2
                       0,0,-1,0,  0,0,-1,0,  0,0,-1,0,  0,0,-1,0};        // v4-v7-v6-v5

	// color array, the 4th element is the alpha channel
	float colors[] = {0,1,1,1,  0,1,1,1,  0,1,1,1,  0,1,1,1,              // v0-v1-v2-v3
                      0,1,1,1,  0,1,1,1,  0,1,1,1,  0,1,1,1,              // v0-v3-v4-v5
                      0,1,1,1,  0,1,1,1,  0,1,1,1,  0,1,1,1,              // v0-v5-v6-v1
                      0,1,1,1,  0,1,1,1,  0,1,1,1,  0,1,1,1,              // v1-v6-v7-v2
                      0,1,1,1,  0,1,1,1,  0,1,1,1,  0,1,1,1,              // v7-v4-v3-v2
                      0,1,1,1,  0,1,1,1,  0,1,1,1,  0,1,1,1};             // v4-v7-v6-v5

	// index array
	unsigned short indices[] = {0,1,2,  0,2,3,                             //front			
                                4,5,6,  4,6,7,                             //right
								8,9,10,  8,10,11,                          //top
								12,13,14,  12,14,15,                       //left
								16,17,18,  16,18,19,                       //bottom
								20,21,22,  20,22,23};                      //back
                                
	//now we put the data into the Vertex Buffer Object for the graphics system to use
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 96 * sizeof(float), vertices, GL_STATIC_DRAW); //the square vertices don't need to change, ever,
																				 //while the program runs

	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	//always make sure you are telling OpenGL the right size to make the buffer, color data doesn't have as much data!
	glBufferData(GL_ARRAY_BUFFER, 96 * sizeof(float), colors, GL_STATIC_DRAW);	

	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, 96 * sizeof(float), normals, GL_STATIC_DRAW); //the square normals don't need to change, ever,
																				 //while the program runs
	//activate our three kinds of information
	glEnableVertexAttribArray(positionLocation);
	glEnableVertexAttribArray(colorLocation);
	glEnableVertexAttribArray(normalLocation);
	
	//we're using the vertex data first
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//define how the vertex pointer should work, in our case we're accessing floats 4 at a time with no special pattern
	glVertexAttribPointer(positionLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	//now use color data
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glVertexAttribPointer(colorLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));

	//one more time with the normals
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glVertexAttribPointer(normalLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	//the last thing we need to do is setup our indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned short), indices, GL_STATIC_DRAW);

	//set the model uniform
	//GL_FALSE is used for not doing transpose operation, because glm has already provided us column major matrices.
	//if the matrices you used is row major, change this parameter to GL_TRUE.
	glUniformMatrix4fv(u_modelMatrixLocation, 1, GL_FALSE, &model[0][0]);

	glUniform3fv(u_lightPosLocation,1,&light[0]);

	//draw the elements
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
	
	//shut off the information since we're done drawing
	glDisableVertexAttribArray(positionLocation);
	glDisableVertexAttribArray(colorLocation);



}


void MyGLWidget::createCubeFromMesh2(glm::mat4, unitCube* theCube){
	theCube->createGL();
	float* vertices = theCube->vertGL;

	//now we put the data into the Vertex Buffer Object for the graphics system to use
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	 glBufferData(GL_ARRAY_BUFFER, theCube->num*4 * sizeof(float), theCube->vertGL, GL_STATIC_DRAW); //the square vertices don't need to change, ever,
                     //while the program runs
	 glBindBuffer(GL_ARRAY_BUFFER, cbo);
	//always make sure you are telling OpenGL the right size to make the buffer, color data doesn't have as much data!
	glBufferData(GL_ARRAY_BUFFER, theCube->num*4 * sizeof(float), theCube->colorGL, GL_STATIC_DRAW); 

 	

	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, theCube->num*4 * sizeof(float), theCube->normalGL, GL_STATIC_DRAW); //the square normals don't need to change, ever,
                     //while the program runs
	 //activate our three kinds of information
	 glEnableVertexAttribArray(positionLocation);
	glEnableVertexAttribArray(colorLocation);
	glEnableVertexAttribArray(normalLocation);
 
	//we're using the vertex data first
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//define how the vertex pointer should work, in our case we're accessing floats 4 at a time with no special pattern
	glVertexAttribPointer(positionLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
 
	//now use color data
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glVertexAttribPointer(colorLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));

	//one more time with the normals
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glVertexAttribPointer(normalLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
 

	//the last thing we need to do is setup our indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	 glBufferData(GL_ELEMENT_ARRAY_BUFFER, theCube->inNum * sizeof(unsigned int), theCube->indicesGL, GL_STATIC_DRAW);

	 //set the model uniform
	//GL_FALSE is used for not doing transpose operation, because glm has already provided us column major matrices.
	//if the matrices you used is row major, change this parameter to GL_TRUE.
	 glUniformMatrix4fv(u_modelMatrixLocation, 1, GL_FALSE, &model[0][0]);


	//draw the elements
	glDrawElements(GL_TRIANGLES, theCube->inNum, GL_UNSIGNED_INT, 0);
 
	//shut off the information since we're done drawing
	glDisableVertexAttribArray(positionLocation);
	glDisableVertexAttribArray(colorLocation);
}

void MyGLWidget::drawBox(glm::mat4 model, Box* theBox){
	glm::vec3 col=glm::vec3(1,0,0);
	glm::vec3 pstart,pend;
	int size=theBox->ctlpList.size();
	int n=theBox->n;
	int m=theBox->m;
	int l=theBox->l;
	for (int i=0; i<n*m*l;i++){
		int nextX=theBox->getNextX(i);
		int nextY=theBox->getNextY(i);
		int nextZ=theBox->getNextZ(i);
		int wut=1;
		

		drawPoint(model,theBox->ctlpList[i],theBox->c/(theBox->l*10));
		//createCubeFromMesh2(model,theBox->pointCubeList[i]);


		glm::vec3 raycolor=glm::vec3(0.0,1.0,1.0);
		//x
		if (nextX!=-1)
			createRay(model,theBox->ctlpList[i],theBox->ctlpList[nextX],raycolor);
		
		//y
		if (nextY!=-1)
			createRay(model,theBox->ctlpList[i],theBox->ctlpList[nextY],raycolor);
		
		//z
		if (nextZ!=-1)
			createRay(model,theBox->ctlpList[i],theBox->ctlpList[nextZ],raycolor);
	}

}

void MyGLWidget::changeLight(){
  ld->show();
}


void MyGLWidget::showBox(){
	box=new Box(cube,boxL,boxM,boxN);
	_boxEnabled=true;
}

void MyGLWidget::disableBox(){
	_boxEnabled=false;
}

void MyGLWidget::getLValue(int value){
	if ((value>=2)&&(value<=5))
		boxL=value;
}

void MyGLWidget::getMValue(int value){
	if ((value>=2)&&(value<=5))
		boxM=value;
}

void MyGLWidget::getNValue(int value){
	if ((value>=2)&&(value<=5))
		boxN=value;
}

void MyGLWidget::resetCamera(){
	delete cam; 
	cam = new camera(); 
	theta = 90.0f; 
	phi = 45.0f; 
	r = 5; 
	emit resetSavedViews(); 
}

void MyGLWidget::saveUserView(QString n){
	CAMERAS saved; 
	saved.push_back(theta); 
	saved.push_back(phi); 
	saved.push_back(r); 
	saved.push_back(cam->ref.x); 
	saved.push_back(cam->ref.y);
	saved.push_back(cam->ref.z);
	emit addUserCam(saved,n); 
}

void MyGLWidget::userView(CAMERAS c){
	vector<float> a = (vector<float>)c; 
	theta = c[0];
	phi = c[1]; 
	r = c[2]; 
	cam->ref = glm::vec3(c[3],c[4],c[5]);
}

void MyGLWidget::frontView(){
	theta = 90.000005f; 
	phi = 0.00000005f;
}

void MyGLWidget::overheadView(){
	theta = 0.000005f; 
	phi = 0.00000005f;
}

void MyGLWidget::leftView(){
	 theta = 90.00000005f; 
	 phi = 90.0000005f; 
}
	
void MyGLWidget::rightView(){
	theta = -90.00000005f; 
	phi = 90.000000005f; 
}
	
void MyGLWidget::backView(){
	theta = 269.99999999995f; 
	phi = 0.0000000000005f;
}
	
void MyGLWidget::perspectiveView(){
	theta = 45.0f; 
	phi = 45.0f; 
}

void MyGLWidget::bottomView(){
	theta = 180.000000000005f; 
	phi = 0.00000000000005f; 
}

void MyGLWidget::callExtrude(){
	if(selectedFace){
	cube->extrude(selectedFace,distance);
	emit sendVertices(&(cube->vertices));
    emit sendFaces(&(cube->faces));
    emit sendHalfEdges(&(cube->halfEdges));
	cube->createGL();
	}
}


void MyGLWidget::createGrid(){
	glm::vec3 color = glm::vec3(1.0, 1.0, 1.0);
	float w = 2.0;
	createRay(w, model, glm::vec3(-5.0,0.0,-1.0),glm::vec3(5.0,0.0,-1.0),color);
	createRay(w, model, glm::vec3(-5.0,0.0,-2.0),glm::vec3(5.0,0.0,-2.0),color);
	createRay(w, model, glm::vec3(-5.0,0.0,-3.0),glm::vec3(5.0,0.0,-3.0),color);
	createRay(w, model, glm::vec3(-5.0,0.0,-4.0),glm::vec3(5.0,0.0,-4.0),color);
	createRay(w, model, glm::vec3(-5.0,0.0,-5.0),glm::vec3(5.0,0.0,-5.0),color);
	createRay(w, model, glm::vec3(-5.0,0.0, 0.0),glm::vec3(5.0,0.0,0.0),color);
	createRay(w, model, glm::vec3(-5.0,0.0,1.0),glm::vec3(5.0,0.0,1.0),color);
	createRay(w, model, glm::vec3(-5.0,0.0,2.0),glm::vec3(5.0,0.0,2.0),color);
	createRay(w, model, glm::vec3(-5.0,0.0,3.0),glm::vec3(5.0,0.0,3.0),color);
	createRay(w, model, glm::vec3(-5.0,0.0,4.0),glm::vec3(5.0,0.0,4.0),color);
	createRay(w, model, glm::vec3(-5.0,0.0,5.0),glm::vec3(5.0,0.0,5.0),color);


	createRay(w, model, glm::vec3(-1.0,0.0,-5.0),glm::vec3(-1.0,0.0,5.0),color);
	createRay(w, model, glm::vec3(-2.0,0.0,-5.0),glm::vec3(-2.0,0.0,5.0),color);
	createRay(w, model, glm::vec3(-3.0,0.0,-5.0),glm::vec3(-3.0,0.0,5.0),color);
	createRay(w, model, glm::vec3(-4.0,0.0,-5.0),glm::vec3(-4.0,0.0,5.0),color);
	createRay(w, model, glm::vec3(-5.0,0.0,-5.0),glm::vec3(-5.0,0.0,5.0),color);
	createRay(w, model, glm::vec3(0.0,0.0, -5.0),glm::vec3(0.0,0.0,5.0),color);
	createRay(w, model, glm::vec3(1.0,0.0,-5.0),glm::vec3(1.0,0.0,5.0),color);
	createRay(w, model, glm::vec3(2.0,0.0,-5.0),glm::vec3(2.0,0.0,5.0),color);
	createRay(w, model, glm::vec3(3.0,0.0,-5.0),glm::vec3(3.0,0.0,5.0),color);
	createRay(w, model, glm::vec3(4.0,0.0,-5.0),glm::vec3(4.0,0.0,5.0),color);
	createRay(w, model, glm::vec3(5.0,0.0,-5.0),glm::vec3(5.0,0.0,5.0),color);
	
}

void MyGLWidget::changeGrid(){
   grid = !grid;

}

void MyGLWidget::createRay(float w,glm::mat4 model, glm::vec3 start, glm::vec3 end , glm::vec3 col){
	glLineWidth(w);
	float vertices[] = {start.x, start.y, start.z, 1.0f, end.x, end.y, end.z, 1.0f};
	float normals[] = {2,2,2,0,2,2,2,0};
	int c1 = col.r; 
	int c2 = col.g; 
	int c3 = col.b; 
	float colors[] = {c1,c2,c3,1,c1,c2,c3,1};
	unsigned int indices[] = {0, 1};

	 //now we put the data into the Vertex Buffer Object for the graphics system to use
	 glBindBuffer(GL_ARRAY_BUFFER, vbo);
	 glBufferData(GL_ARRAY_BUFFER, 2*4 * sizeof(float), vertices, GL_STATIC_DRAW); //the square vertices don't need to change, ever,
						 //while the program runs
	 glBindBuffer(GL_ARRAY_BUFFER, cbo);
	 //always make sure you are telling OpenGL the right size to make the buffer, color data doesn't have as much data!
	 glBufferData(GL_ARRAY_BUFFER, 2*4 * sizeof(float), colors, GL_STATIC_DRAW); 

	 glBindBuffer(GL_ARRAY_BUFFER, nbo);
	 glBufferData(GL_ARRAY_BUFFER, 2*4 * sizeof(float), normals, GL_STATIC_DRAW); //the square normals don't need to change, ever,
						 //while the program runs
	 //activate our three kinds of information
	 glEnableVertexAttribArray(positionLocation);
	 glEnableVertexAttribArray(colorLocation);
	 glEnableVertexAttribArray(normalLocation);
 
	 //we're using the vertex data first
	 glBindBuffer(GL_ARRAY_BUFFER, vbo);
	 //define how the vertex pointer should work, in our case we're accessing floats 4 at a time with no special pattern
	 glVertexAttribPointer(positionLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
 
	 //now use color data
	 glBindBuffer(GL_ARRAY_BUFFER, cbo);
	 glVertexAttribPointer(colorLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));

	 //one more time with the normals
	 glBindBuffer(GL_ARRAY_BUFFER, nbo);
	 glVertexAttribPointer(normalLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
 

	 //the last thing we need to do is setup our indices
	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	 glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	 //set the model uniform
	 //GL_FALSE is used for not doing transpose operation, because glm has already provided us column major matrices.
	 //if the matrices you used is row major, change this parameter to GL_TRUE.
	 glUniformMatrix4fv(u_modelMatrixLocation, 1, GL_FALSE, &model[0][0]);

	 //draw the elements
	 glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
 
	 //shut off the information since we're done drawing
	 glDisableVertexAttribArray(positionLocation);
	 glDisableVertexAttribArray(colorLocation);
}

void MyGLWidget::setAxisX(){
	currentAxis=1;
}
void MyGLWidget::setAxisY(){
	currentAxis=2;
}
void MyGLWidget::setAxisZ(){
	currentAxis=3;
}


void MyGLWidget::twist(){
	box=box->twist(twistIndex,currentAxis);
	box->deformSolid(box);
	cube=box->mesh;
	cube->createGL();
	
	updateGL(); 
}

void MyGLWidget::taper(){
	box=box->taper(0.3,currentAxis);
	box->deformSolid(box);
	cube=box->mesh;
	cube->createGL();
	
	updateGL(); 
}


void MyGLWidget::bend(){
	box=box->twist(0.3,1);
	box->deformSolid(box);
	cube=box->mesh;
	cube->createGL();
	
	updateGL(); 
}

void MyGLWidget::setDistance(float n){
   distance = n;
}

void MyGLWidget::showEBox(){
   ed->show();
}

void MyGLWidget::showDoc(){
   d->show();
   cout<<"OPEN"<<endl;
}


void MyGLWidget::twistIndexSet(int value){
	twistIndex=value;
}