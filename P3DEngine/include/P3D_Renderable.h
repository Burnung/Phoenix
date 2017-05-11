#pragma once
#include<vector>
#include<gl\glew.h>
//#include<QtGui\QOpenGLFunctions_4_3_Compatibility>
#include<glm\vec3.hpp>
#include<glm\vec2.hpp>
#include<assimp\Importer.hpp>

#include<assimp\scene.h>
#include <assimp\postprocess.h>
#include <memory>
//#include <QtGui/QOpenGLShaderProgram>
#include"P3D_BaseType.h"
#include"P3D_kdTree.h"

class P3DRenderable{
public:
	enum MODEL_TYPE{
		MODEL_SPHERE,
		MODEL_MESH,
	};
	P3DRenderable() :m_Postion(0.0f, 0.0f, 0.0f){};
	virtual ~P3DRenderable() {};
	virtual void Render(){};
	virtual bool InterSect(P3DRay &ray, P3DObjIntersection &intersection,float &dmin) { return false; };
	void setPos(glm::vec3 pos){ m_Postion = pos; };
	glm::vec3 getPos(){ return m_Postion; }
	MODEL_TYPE m_Type;
private:
	glm::vec3 m_Postion;

};

class P3DSphereRenderable :public P3DRenderable{
public:
	P3DSphereRenderable();
	P3DSphereRenderable(float r, glm::vec3 &pos, P3DMaterial &mat);
	virtual ~P3DSphereRenderable();
	void Init(float r, glm::vec3 &pos, P3DMaterial &mat);
	virtual bool InterSect(P3DRay &ray, P3DObjIntersection &intersection, float &dmin);
	//virtual void Render();
	P3DMaterial* GetMat()const { return m_Mat; }
	float m_Raduis;  //�뾶

private:
	P3DMaterial *m_Mat;
	
};

class P3DMesh {
public:
	P3DMesh(int nVertex, int nIndex) {
		m_index.resize(nVertex);
		m_vertex.resize(nVertex);
	}
	~P3DMesh() {
		m_index.clear();
		m_vertex.clear();
	}
	std::vector<uint> m_index;
	std::vector<Vertex> m_vertex;

	P3DAABB m_AABB;
	int m_MatIndex;
};

class P3DLitModelRenderable :public  P3DRenderable{
public:
	P3DLitModelRenderable();
	virtual ~P3DLitModelRenderable();
	bool LoadFromFile(std::string &FileName, bool kdTree =false);
	virtual void Render();
	virtual bool InterSect(P3DRay &ray, P3DObjIntersection &intersection, float &dmin);
	void SetMaterial(P3DMaterial &Tmat);
	std::vector<Triangle*> & GetTris() { return m_Triangles; };

private:
	std::vector<P3DMaterial*> m_Materials;
	std::vector< P3DMesh*> m_Meshes;
	std::vector<Triangle*> m_Triangles;

	void Clear();
	bool InitFromScene(const aiScene *m_Scene,std::string &filename);
	bool InitEntity(int i, const aiMesh* m_mesh);
	bool InitMaterials(const aiScene *m_Scene, std::string &filename);
	bool BuildTriangles();
	P3DkdTree *m_kdTree;
	bool IskdTree;
	bool IsSameMat;

};
typedef  std::shared_ptr<P3DLitModelRenderable> P3DLitModelRenderablePtr;
