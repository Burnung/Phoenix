#pragma once 
#include"P3D_BaseType.h"
#include<glm\vec3.hpp>
#include<math.h>
#include<vector>

using namespace std;

const int MAX_DEPTH = 25;    
const int MIN_COUNT = 10;    

class P3DkdTree{
	enum AXIS{
		X_AXIS,
		Y_AXIS,
		Z_AXIS
	};
public:
	P3DkdTree();
	~P3DkdTree();
	static P3DkdTree* Build(std::vector<Triangle*>&triangles, int depth);

	bool IsLeaf;
	P3DkdTree *m_PLeftChild;
	P3DkdTree *m_PRightChild;

	vector<Triangle*> m_Triangles;
	P3DAABB m_AABB;     //�ýڵ��İ�Χ�� 

	P3DMaterial *m_Mat;

	int getTriSize();

	int getAxis(vector<Triangle*> tmpTri);
	int getAxis(P3DAABB &tmpAABB,float &Midp);
	bool InterSect(P3DRay& ray,P3DObjIntersection &infersections, float &tmin);
};
typedef  std::shared_ptr<P3DkdTree> P3DkdTreePtr;







