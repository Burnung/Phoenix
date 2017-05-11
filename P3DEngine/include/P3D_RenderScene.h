#pragma once
#include"P3D_util.h"
#include"P3D_Renderable.h"
#include"P3D_Camera.h"
#include "P3D_BaseType.h"
#include<vector>
#include<map>

class P3DRenderScene{
	P3D_DECLARE_SINGLETON(P3DRenderScene);
public:
	typedef std::vector<P3DRenderable*> ObjeceVes;
	~P3DRenderScene();
	void addObject(P3DRenderable*);
	bool addModel(std::string &filnema,bool kdTree =false);
	bool addSphereObj(glm::vec3 &Center, float raduis, P3DMaterial&);
	void Render();
	glm::vec3 GoTrace(P3DRay &ray,int depth = 0);
	void RegisterMat(P3DMaterial*);
	int GetMatIndex(P3DMaterial*);
private:
	//Camera m_Camera;
	ObjeceVes m_Objects;
	std::vector<P3DMaterial*> m_MatVec;
	std::map<P3DMaterial*, int> m_MatToIndexMap;
	void clear();
	P3DObjIntersection Intersect(P3DRay &ray);
};

typedef std::shared_ptr < P3DRenderScene> P3DRenderScenePtr;