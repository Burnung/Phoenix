#pragma once

#include"P3D_util.h"
#include<glm\vec3.hpp>
#include"P3D_BaseType.h"
#include"P3D_Math.h"
#define PATHTRACER_USE_GPU   //是否使用GPU加速

class P3DViewPort;
class P3DPahtTracer{
	P3D_DECLARE_SINGLETON(P3DPahtTracer);
public:
	~P3DPahtTracer();

	void Init(P3DViewPort*);
	//void SetViewPort()
	void GoTrace(int samples);
	void SaveRet();

	void Update();

	int GetMaxDepth();

	void Save2BMP(const char* filename );

private:
	P3DViewPort *m_ViewPort;

	BYTE *m_RetBMP;

	int m_WindowWidth;
	int m_WindowHeight;
	glm::vec3 m_CamPos;
	glm::vec3 m_CamTarVec;
	glm::vec3 m_CamYVec;
	glm::vec3 m_CamXVec;

	float m_Width_recp;
	float m_Height_recp;
	float m_FovS;
	float m_Ratio;
	float m_X_Spacing;
	float m_X_Spacing_Half;
	float m_Y_Spacing;
	float m_Y_Spacing_Half;


private:
	void ClearRetBuffer();
	void Clear();
	P3DRay GetRay(int x,int y);
	void WriteColor(glm::vec3 &col, int x, int y);
};
