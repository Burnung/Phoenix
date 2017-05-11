#pragma once
#include<gl\glew.h>
#include<GLFW\glfw3.h>
#include"P3D_util.h"

class GL_CallBack;
class P3DApp;

void InitGLContex(int w, int h, bool withDepth, bool withStil, const char*);

static void InitCallbacks();
void GlfwRun();
void EndRender();
void SetInputMode(int a, int b);
int GetInputMode(int a);

class P3DApp{
public:
	virtual ~P3DApp(){};

protected:
	P3DApp();

	void CalcFPS();
	void RenderFPS();
	float GetRunningTime();
public:
	void Run();
	virtual void Init();
	//void drawText(const char *text, float x, float y, void* font);

private:
	long long m_frameTime;
	long long m_startTime;
	int m_frameCount;
	int m_fps;

};