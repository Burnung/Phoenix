#pragma once
#include<string>
#include<gl\glew.h>
#include<glm\vec3.hpp>
#include<glm\vec2.hpp>
#include<glm\geometric.hpp>
#include"P3D_util.h"

class P3DMaterial;

const float GL_eps = 1e-10;

struct Vertex{

	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 uv;


	Vertex() :pos(glm::vec3(0, 0, 0)), normal(glm::vec3(0,0,-1)),uv(glm::vec2(0,0)){};
	 Vertex(glm::vec3 pos_, glm::vec3 normal_, glm::vec2 uv_) :pos(pos_), normal(glm::normalize(normal_)), uv(uv_)
	{
	}

};
struct P3DRay{
	glm::vec3 m_Origin;
	glm::vec3 m_Dirction;
	P3DRay(glm::vec3 or, glm::vec3 dir) :m_Origin(or), m_Dirction(dir){};
	P3DRay(){
		m_Origin = glm::vec3(0.0f);
		m_Dirction = glm::vec3(0.0f, 0.0f, -1.0f);
	}
};

struct P3DObjIntersection{
	bool m_IsHit;
	float m_Dis;
	P3DMaterial *m_Material;
	Vertex m_Vertex;
	P3DObjIntersection();

	P3DObjIntersection(bool ,Vertex&, P3DMaterial&, float);
	P3DObjIntersection& operator= (P3DObjIntersection&);
};

struct P3DAABB{
	glm::vec3 m_MinPos, m_MaxPos;  //����������С��
	P3DAABB(glm::vec3 &MinPos , glm::vec3& MaxPos) : m_MinPos(MinPos), m_MaxPos(MaxPos){
	};
	P3DAABB(){
		m_MinPos = glm::vec3(0, 0, 0);
		m_MaxPos = glm::vec3(0, 0, 0);
	}
	void ExpandBox(P3DAABB& T_AABB);
	bool Intersect(P3DRay &ray, float &dis,float min);
};

struct P3DSphereBox{
	glm::vec3 m_Center;        //����
	float m_Radius;
	P3DSphereBox(glm::vec3 Center, float radius) :m_Center(Center), m_Radius(radius){};
	P3DSphereBox(){
		m_Center = glm::vec3(0, 0, 0);
		m_Radius = 0;
	}
	bool Intersect(P3DRay &ray, float &dis,float min);
};

struct Triangle{
	Vertex m_p1, m_p2, m_p3;   //
	glm::vec3 m_Normal;        //
	P3DMaterial *m_PMaterial;    //
	int m_id;
	P3DAABB getAABB();
	glm::vec3 getMidPoint();
	void ComputeNormal();
	bool Intersect(P3DRay &ray, float &Dis,float mindis,float &u,float &v);
	void ComVertex(float u, float v, Vertex &ret);//
};
class P3DTexture2D;
class P3DMaterial{
public:
	RenderType m_RenderType;
	MaterialType m_MaterialType;
	float m_Refra;  
	glm::vec3 m_colour;
	glm::vec3 m_emission;

	P3DTexture2D *m_PTexture;
	P3DMaterial(MaterialType MatType = DIFF, RenderType renType = TEXTURE_TYPE);
	P3DMaterial(glm::vec3 &emmision, glm::vec3 &color, MaterialType MatType = DIFF, RenderType renType = TEXTURE_TYPE);
	P3DMaterial(P3DMaterial&);
	P3DMaterial& operator= (P3DMaterial&);
	bool LoadTexture(GLenum, std::string&);

};