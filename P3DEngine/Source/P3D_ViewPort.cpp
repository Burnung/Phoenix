#include"P3D_ViewPort.h"
#include"P3D_Camera.h"
#include<glm/gtc/matrix_transform.hpp>

P3DViewPort::P3DViewPort() :m_Width(512), m_Height(512), m_Nearest(1.0f), m_Farthest(1500.0f),m_Fovy(60.0f), m_Camera(nullptr), m_ViewPortChange(true){
	m_Camera = new P3DCamera(glm::vec3(0, 50, -100), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0),m_Width,m_Height);
}

P3DViewPort::~P3DViewPort(){
	SAFERELEASE(m_Camera);
}

void P3DViewPort::SetHeight(int h){
	m_Height = h;
	m_ViewPortChange = true;
	if (!m_Camera)
		m_Camera = new P3DCamera();
	m_Camera->SetHeithg(h);
}

void P3DViewPort::SetWidth(int w){
	m_Width = w;
	m_ViewPortChange = true;
	if (!m_Camera)
		m_Camera = new P3DCamera();
	m_Camera->SetWidth(w);
}

void P3DViewPort::SetNearAndFar(float n, float f){
	m_Nearest = n;
	m_Farthest = f;
	m_ViewPortChange = true;
}
void P3DViewPort::SetFovy(float f){
	m_Fovy = glm::radians(f);
	m_ViewPortChange = true;
}
void P3DViewPort::SetCameraPos(glm::vec3& p){
	if (!m_Camera)
		m_Camera = new P3DCamera();
	m_Camera->SetPostion(p);
}

void P3DViewPort::SetCameraLookvec(glm::vec3& lv){
	if (!m_Camera)
		m_Camera = new P3DCamera();
	m_Camera->SetLookVec(lv);
}

void P3DViewPort::SetCameraUpVec(glm::vec3& up){
	if (!m_Camera)
		m_Camera = new P3DCamera();
	m_Camera->SetUpVec(up);
}

void P3DViewPort::InitCamera(){
	if (!m_Camera)
		m_Camera = new P3DCamera();
	m_Camera->Init();
}


glm::mat4 P3DViewPort::GetProMat(){
	if (m_ViewPortChange){
		m_ProMat = glm::perspective(glm::radians(m_Fovy), (m_Width * 1.0f) / (m_Height * 1.0f), m_Nearest, m_Farthest);
		m_ViewPortChange = false;
	}
	return m_ProMat;
}

glm::mat4 P3DViewPort::GetViewMat(){
	m_ViewMat = m_Camera->Look();
	return m_Camera->Look();
}

glm::mat4 P3DViewPort::GetProViewMat(){
	mat4 tmpView, tmpProMat;
	tmpView = GetViewMat();
	tmpProMat = GetProMat();
	m_ProViewMat = tmpProMat * tmpView;
	return m_ProViewMat;
}
glm::vec3 P3DViewPort::GetCameraPos(){
	return m_Camera->getPosition();
}
glm::vec3 P3DViewPort::GetCameraLookVec(){
	return m_Camera->GetLookvec();
}
glm::vec3 P3DViewPort::GetCameraUpVec(){
	return m_Camera->GetUpvec();
}