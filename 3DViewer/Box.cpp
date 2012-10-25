#include "Box.h"

using namespace std;

const int Box::LookUpSize = 100;

Box::Box(Mesh* mesh1, int l1, int m1, int n1){
	mesh=mesh1;
	l=l1;
	m=m1;
	n=n1;
	setUpList();
	setUpPoint();
	for(int i=0; i < LookUpSize; i++) {
			factLookUp[i] = 0;
	}
}

Box::~Box(){

}

void Box::setUpPoint(){
	for (int i=0; i<ctlpList.size();i++){
		unitCube* uc=new unitCube(ctlpList[i],c/(l*10));
		pointCubeList.push_back(uc);
	}
}

glm::vec3 Box::getTransV(glm::vec3 pLocation){
	glm::vec3 v=glm::vec3(0,0,0);

	return v;
}

void Box::setUpList(){
	std::vector<Vertex* > list=mesh->vertices;
	
	if (list.size()>0){

		float min_x=list[0]->coords.x;
		float max_x=list[0]->coords.x;
		float min_y=list[0]->coords.y;
		float max_y=list[0]->coords.y;
		float min_z=list[0]->coords.z;
		float max_z=list[0]->coords.z;


	
		for (int i=0; i<list.size(); i++){
			if (min_x>list[i]->coords.x){
				min_x=list[i]->coords.x;
			}
			if (max_x<list[i]->coords.x){
				max_x=list[i]->coords.x;
			}
			if (min_y>list[i]->coords.y){
				min_y=list[i]->coords.y;
			}
			if (max_y<list[i]->coords.y){
				max_y=list[i]->coords.y;
			}
			if (min_z>list[i]->coords.z){
				min_z=list[i]->coords.z;
			}
			if (max_z<list[i]->coords.z){
				max_z=list[i]->coords.z;
			}	
		}

		min_loc=glm::vec3(min_x,min_y,min_z);
		max_loc=glm::vec3(max_x,max_y,max_z);

		float tempx=min_loc.x;
		float tempy=min_loc.y;
		float tempz=min_loc.z;

		c=max_x-min_x;
		k=max_y-min_y;
		g=max_z-min_z;

		offset_x=c/(l-1);
		offset_y=k/(m-1);
		offset_z=g/(n-1);


		X0 = glm::vec3(min_x,min_y,min_z);
		S = glm::vec3(max_x, min_y, min_z) - X0;
		T = glm::vec3(min_x, max_y, min_z) - X0;
		U = glm::vec3(min_x, min_y, max_z) - X0;


		for (int i1 = 0; i1 < l; i1++)
			for (int j1 = 0; j1 < m; j1++)
				for (int k1 = 0; k1 < n; k1++){
					glm::vec3 tempv = X0 + (i1/((float)l-1)) * S +(j1/((float)m-1)) * T + (k1/((float)n-1)) * U;
					ctlpList.push_back(tempv);
				}


	}


}

int Box::getNextX(int in){
	if (in<m*n*l-m*n)
		return in+m*n;
	else
		return -1;
}

int Box::getNextY(int in){
	
	if (n==5){
	if (((in+1)%(m*n)==0)||((in+1+1)%(n*m)==0)||((in+1+2)%(n*m)==0)||((in+1+3)%(n*m)==0)||((in+1+4)%(n*m)==0))
		return -1;
	else
		return in+n;}

	if (n==4){
	if (((in+1)%(n*m)==0)||((in+1+1)%(n*m)==0)||((in+1+2)%(n*m)==0)||((in+1+3)%(n*m)==0))
		return -1;
	else
		return in+n;}

	if (n==3){
	if (((in+1)%(n*m)==0)||((in+1+1)%(n*m)==0)||((in+1+2)%(n*m)==0))
		return -1;
	else
		return in+n;}

	if (n==2){
	if (((in+1)%(n*m)==0)||((in+1+1)%(n*m)==0))
		return -1;
	else
		return in+n;}

	return in+n;


}

int Box::getNextZ(int in){
	if ((in+1)%n==0)
		return -1;
	else
		return in+1;
}



Box* Box::taper(float index, int axis){
	Box* deBox=new Box(mesh,5,5,5);
	int size=deBox->ctlpList.size();
	int n=deBox->n;
	int m=deBox->m;
	int l=deBox->l;
	for (int i=0; i<n*m*l;i++){
		float z=deBox->ctlpList[i].z;
		float y=deBox->ctlpList[i].y;
		float x=deBox->ctlpList[i].x;

		deBox->ctlpList[i].x*=x;
		deBox->ctlpList[i].y*=x;
		
	}
	return deBox;
}


Box* Box::twist(float value,int axis){
	float angle;
	Box* deBox=new Box(mesh,l,m,n);
	int size=deBox->ctlpList.size();
	int n=deBox->n;
	int m=deBox->m;
	int l=deBox->l;
	for (int i=0; i<n*m*l;i++){
		float x=deBox->ctlpList[i].x;
		float y=deBox->ctlpList[i].y;
		float z=deBox->ctlpList[i].z;

		angle=value*z;
		deBox->ctlpList[i].x=x*cos(angle)-y*sin(angle);
		deBox->ctlpList[i].y=x*sin(angle)-y*cos(angle);
		
	}
	return deBox;
}

Box* Box::bending(float y, float angle, int axis){
	Box* deBox=new Box(mesh,l,m,n);
	int size=deBox->ctlpList.size();
	int n=deBox->n;
	int m=deBox->m;
	int l=deBox->l;
	for (int i=0; i<n*m*l;i++){
		float x=deBox->ctlpList[i].x;
		float y=deBox->ctlpList[i].y;
		float z=deBox->ctlpList[i].z;

		angle=0.5*z;
		deBox->ctlpList[i].x=x*cos(angle)-y*sin(angle);
		deBox->ctlpList[i].y=x*sin(angle)-y*cos(angle);
		
	}
	return deBox;



}


void Box::reinitializeBasis(void) {
	std::vector<Vertex*> vList=mesh->vertices;

	for (int g=0; g<vList.size();g++){
		vList[g]->basisInitialized=false;
	} 
}

void Box::deformSolid(Box* deBox) {
	int i1, j1, k1;
	float s, t, u;  /* the (s, t, u) bounding box space coords */
	
	glm::vec3 Xnew;
	glm::vec3 Xnew2;
	glm::vec3 Xnew3;

	std::vector<Vertex*> vList=mesh->vertices;


	for (int ind=0; ind<vList.size();ind++){
 
		if (vList[ind]->basisInitialized==false) {
			
			glm::vec3 X;     /* the cartesian coords of the vertex */
	
			// Get this vertex in 3-space
			X.x = vList[ind]->coords.x;
			X.y = vList[ind]->coords.y;
			X.z = vList[ind]->coords.z;

			// Following equations are from Sederberg and Parry, p. 153
			glm::vec3 cha=X-X0;
			glm::vec3 crossTU=glm::cross(T,U);
			glm::vec3 crossSU=glm::cross(S,U);
			glm::vec3 crossST=glm::cross(S,T);
			vList[ind]->s = glm::dot(crossTU,cha) / glm::dot(crossTU ,S);
			vList[ind]->t = glm::dot(crossSU,cha) / glm::dot(crossSU , T);
			vList[ind]->u = glm::dot(crossST , cha) / glm::dot(crossST  , U);
			vList[ind]->basisInitialized = true;

		}

		s = vList[ind]->s;
		t = vList[ind]->t;
		u = vList[ind]->u;
		
		// Here's the kicker, from the same page of S&P

		Xnew=glm::vec3(0,0,0);

		for (i1 = 0; i1 < l; i1++) {
			Xnew2=glm::vec3(0,0,0);

			for (j1 = 0; j1 < m; j1++) {

				Xnew3=glm::vec3(0,0,0);

				for (k1 = 0; k1 < n; k1++) {
					Xnew3 += combination(n-1, k1)*pow((1 - u), (n-1 - k1)) * pow(u, k1) * ctlpList[((i1*l)+j1)*m+k1];
				}

				Xnew2 += combination(m-1, j1)*pow((1 - t),(m-1 - j1)) * pow(t,j1) * Xnew3; 
			}

			Xnew += combination(l-1, i1)*pow((1 - s),(l-1 - i1)) * pow(s,i1) * Xnew2;
		}


		vList[ind]->coords.x = Xnew.x;
		vList[ind]->coords.y = Xnew.y;
		vList[ind]->coords.z = Xnew.z;
  
	} 
	mesh->vertices=vList;
	mesh->createGL();
}

//calculate the combination of (n1, m1)
int Box::combination(int n1, int m1){
	if (n1 < m1) {
		return 1;
	}
	else
	if(n1 >= 0 && m1 >= 0) {
		int result = fact(n1)/(fact(m1)*fact(n1-m1));
		return result;
	}

	
	return 1;
}

//calculate the f1!
int Box::fact(int f1){

	int i;	
	int result;

	if (f1 <= 0) {
		return 1;
	}
	else
	if(f1 >= LookUpSize  || factLookUp[f1] == 0) {
		result = 1;
		for(int i = 2; i <= f1; i++) {
			result *= i;
		}
		factLookUp[f1] = result;
	}
	
	return(factLookUp[f1]);
}