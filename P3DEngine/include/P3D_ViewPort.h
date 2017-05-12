#pragma once
#include"P3D_util.h"
#include<glm\mat4x4.hpp>
#include<glm\vec3.hpp>

class P3DCamera;

class P3DViewPort{

public:
	P3DViewPort();
	~P3DViewPort();

	void SetNearAndFar(float, float);
	void SetWidth(int);
	void SetHeight(int);
	void SetFovy(float);
	void SetCameraPos(glm::vec3&);
	void SetCameraLookvec(glm::vec3&);
	void SetCameraUpVec(glm::vec3&);
	void InitCamera();

	int GetWidth(){ return m_Width; };
	int GetHeight(){ return m_Height; };
	float GetNear(){ return m_Nearest; };
	float GetFar() { return m_Farthest; };
	float GetFovy() { return m_Fovy; };
	glm::vec3 GetCameraPos();
	glm::vec3 GetCameraLookVec();
	glm::vec3 GetCameraUpVec();

	glm::mat4 GetProMat();
	glm::mat4 GetViewMat();
	glm::mat4 GetProViewMat();

private:
	P3DCameraPtr *m_CameraPtr;
	int m_Width, m_Height;
	float m_Nearest, m_Farthest;
	float m_Fovy;

	bool m_ViewPortChange;

	glm::mat4 m_ProMat;
	glm::mat4 m_ViewMat;
	glm::mat4 m_ProViewMat;

};





