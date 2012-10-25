#include "listWrapper.h"

//listWrapper is used for the lists on the GUI (faces, HE, vertices)
listWrapper::listWrapper(){
	faceVecSize=0; 
	vertVecSize=0; 
	edgeVecSize=0; 
	currentRowTemp = -1; 
	secondHE = NULL;
}

listWrapper::listWrapper(QWidget* parent):QListWidget(parent){
	faceVecSize=0; 
	vertVecSize=0; 
	edgeVecSize=0; 
	currentRowTemp = -1; 
	secondHE = NULL;
}

listWrapper::~listWrapper(){

}

//add face to face list
void listWrapper::addFaces(FACES f){
	faceVec = f; 
	faceVecSize = f->size(); 
	clear(); 
	for(int i = 0; i< f->size(); i++){
		addItem(QString("Face %1").arg((*f)[i]->idF)); 
	}
	emit sendNum(f->size());
}

//add vertex to vertex list
void listWrapper::addVertices(VERTICES v){
	vertVec = v; 
	vertVecSize = v->size(); 
	clear(); 
	for(int i = 0; i< v->size(); i++){
		addItem(QString("Vertex %1 -> (%2, %3, %4)").arg((*v)[i]->idV).arg((*v)[i]->coords.x).arg((*v)[i]->coords.y).arg((*v)[i]->coords.z));
	}
	emit sendNum(v->size());
}

//add edge to edges list
void listWrapper::addEdges(EDGES e){
	edgeVec = e; 
	edgeVecSize = e->size(); 
	clear(); 
	for(int i = 0; i< e->size(); i++){
		float x = ((*edgeVec)[i]->V)->coords.x;
		float y = ((*edgeVec)[i]->V)->coords.y;
		float z = ((*edgeVec)[i]->V)->coords.z;
		addItem(QString("Half Edge %1 -> (%2, %3, %4)").arg(i).arg(x).arg(y).arg(z)); 
	}
	emit sendNum(e->size());
}

//set X of a vertex, called when x slider is moved
void listWrapper::setX(int a){
	float xn = (float) a / 5.0f;
	bool b = currentItem();
	int whaa = currentRow(); 
	if(currentItem()||currentRowTemp >=0){
		if(currentItem()){
			int a  = currentRow(); 
			for(int i = 0; i< vertVec->size() ; i++){
				if(a == (*vertVec)[i]->idV){
					(*vertVec)[i]->coords.x = xn; 
					break; 
				}
			}
		}
		else{
			for(int i = 0; i< vertVec->size() ; i++){
				if(currentRowTemp == (*vertVec)[i]->idV){
					(*vertVec)[i]->coords.x = xn; 
					break; 
				}
			}
		}
	}
	cout<<"wth "<<xn<<endl; 
}

//set Y of a vertex, called when y slider is moved
void listWrapper::setY(int a){
	if(currentItem()){
		float yn = (float) a/ 5.0f; 
		(*vertVec)[currentRow()]->coords.y = yn; 
	}
}

//set Z of a vertex, called when z slider is moved
void listWrapper::setZ(int a){
	if(currentItem()){
		float zn = (float) a/ 5.0f; 
		(*vertVec)[currentRow()]->coords.z = zn; 

	}
}

//sets face redness, called when red slider moved
void listWrapper::setRed(int a){
	if(currentItem()){
		float r = (float) a / 255.0f ; 
		(*faceVec)[currentRow()]->colors.r = r; 
	}
}

//sets face green-ness
void listWrapper::setGreen(int a){
	if(currentItem()){
		float r = (float) a / 255.0f ; 
		(*faceVec)[currentRow()]->colors.g = r; 
	}
}

//sets face blue-ness
void listWrapper::setBlue(int a){
	if(currentItem()){
		float r = (float) a / 255.0f ; 
		(*faceVec)[currentRow()]->colors.b = r; 
	}
}

//add vertex into a halfedge must click on a HE
void listWrapper::addVertexIntoEdge(){
	if(currentItem()){
		Vertex* v = new Vertex();
		int count = 0; 
		emit callAddVertexToEdge((*edgeVec)[currentRow()],v);
	}
}

//must add edge by clicking on exactly two edges that point to same vertex
//might want to check this once delete vertex is completely fixed, Ana?
void listWrapper::addEdgeTwoFacesUsingHalfEdges(){
	if(selectedItems().size()==2){
		QList<QListWidgetItem*> temp = selectedItems();
		HalfEdge* firstF = (*edgeVec)[row(temp[0])]; 
		HalfEdge* secondF = (*edgeVec)[row(temp[1])];
		HalfEdge* hF = firstF;
		HalfEdge* hS = secondF; 
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
			emit callAddEdgeBetweenTwoFacesShareAVertex(firstF->F,secondF->F,firstF,secondF);
		}
		else{
			emit callAddEdgeBetweenTwoFacesShareAVertex(secondF->F,firstF->F,secondF,firstF);
		}
	}
	
}

//call split quad
void listWrapper::addSplitQuad(){
	if(currentItem()){
		emit callSplitFace((*faceVec)[currentRow()]);
	}
}

//call delete vertex
void listWrapper::addDeleteVertex(){
	if(currentItem()){
		emit callDeleteVertex((*edgeVec)[currentRow()]);
	}
}

//sets row of item
void listWrapper::setTheRow(int i){
	setCurrentRow(i); 
	cout<<"current item "<<i<<endl; 
	setCurrentItem(item(i));
	bool a = currentItem(); 
	currentRowTemp = i; 
	cout << "current item bool " << currentItem()<<endl; 
}

void listWrapper::testEdge(){
 if(currentItem()){
	 HalfEdge* selected = (*edgeVec)[currentRow()];
    emit sendEdge(selected);
 }
}

void listWrapper::addCam(CAMERAS c,QString n){
	//QString name = QString::fromStdString(n); 
	camStuff.push_back(c); 
	addItem(n); 
	emit sendNum(camStuff.size()); 
}

void listWrapper::gotClickedCam(){
	if(currentItem()){
		CAMERAS c = camStuff[currentRow()]; 
		emit sendCam(c); 
	}
}

void listWrapper::clearSecondHE(){
	secondHE = NULL; 
}
	

void listWrapper::selectSecondHE(){
	if(currentItem()){
		secondHE = (*edgeVec)[currentRow()];
	}
}