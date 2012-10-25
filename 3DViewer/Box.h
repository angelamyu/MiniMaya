#ifndef BOX_H
#define BOX_H


#include "Mesh.h"
#include "unitCube.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
using namespace std;


class Box{
	public:
		int l, m, n;
		Mesh* mesh;
		std::vector<glm::vec3> ctlpList; 
		std::vector<unitCube*> pointCubeList;
		glm::vec3 min_loc,max_loc;
		float offset_x, offset_y, offset_z;
		float c,k,g;

		

		
		glm::vec3 X0, S, T, U;

	private:
		static const int LookUpSize;
		int factLookUp[100];

	public:
		Box(Mesh*, int l, int m, int n);
		~Box();
		glm::vec3 getTransV(glm::vec3 pLocation);
		void setUpPoint();


	public:
		void setUpList();
		int getNextX(int);
		int getNextY(int);
		int getNextZ(int);
		


		Box* taper(float index, int axis);
		Box* twist(float angle, int axis);
		Box* bending(float y, float angle, int axis);

		void deformSolid(Box* deBox);
		void reinitializeBasis(void);

		//math helper method
		int combination(int n, int m);
		int fact(int f);
};


#endif