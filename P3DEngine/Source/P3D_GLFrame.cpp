#include"P3D_GLFrame.h"
#include<iostream>
#include<windows.h> 
#include "P3D_Input.h"
#include "P3D_Contex.h"
bool sWithDepth, sWithStencil;//是否使用深度和模板
static GLFWwindow* s_pWindow = nullptr;
static P3DInput *m_Input = nullptr;
int Width, Height;

void InitGLContex(int w, int h, bool WithDepth, bool WithStencil,const char* tittle){

	sWithDepth = WithDepth;
	sWithStencil = WithStencil;
	Width = w;
	Height = h;

	if (!glfwInit()){
		ERROROUT("Inite Glfw Error!");
		exit(1);
	}
	int Major, Minor, Rev;
	glfwGetVersion(&Major, &Minor, &Rev);
	printf("The glfw versiong is %d.%d.%d\n", Major, Minor, Rev);
	glfwSetErrorCallback(GlfwErrorCallBack);
	s_pWindow = glfwCreateWindow(w, h, tittle, nullptr, nullptr);
	if (!s_pWindow){
		ERROROUT("Create Window Error");
		exit(1);
	}
	glfwMakeContextCurrent(s_pWindow);

	//Inite Glew
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		ERROROUT((const char*)glewGetErrorString(res));
		exit(1);
	}
}

void EndRender(){
	glfwSetWindowShouldClose(s_pWindow, 1);
}
void SetInputMode(int a, int b){
	glfwSetInputMode(s_pWindow, a, b);
}
int GetInputMode(int a){
	return glfwGetInputMode(s_pWindow, a);
}
static void keyBoard(GLFWwindow* pWindow, int key, int scancode, int action, int mods){
	m_Input->KeyBoard(key);
}

static void MouseButton(GLFWwindow* pWindow, int Button, int Action, int Mode){
	double px, py;
	glfwGetCursorPos(pWindow, &px, &py);
	m_Input->MouseButton(Button, Action, px,py);
}

static void MouseMove(GLFWwindow* pWindow, double x, double y){
	m_Input->MouseMove(x, y);
}

static void InitCallbacks(){
	glfwSetKeyCallback(s_pWindow, keyBoard);
	glfwSetMouseButtonCallback(s_pWindow, MouseButton);
	glfwSetCursorPosCallback(s_pWindow, MouseMove);
}
void GlfwRun(){

	glViewport(0, 0, Width, Height);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	if (sWithDepth) 
		glEnable(GL_DEPTH_TEST);

	if (sWithStencil)
		glEnable(GL_STENCIL_TEST);

	m_Input = P3DContex::Instance().GetInputPtr().get();
	InitCallbacks();

	while (!glfwWindowShouldClose(s_pWindow)) {

		glfwSwapBuffers(s_pWindow);
		glfwPollEvents();
	}
	glfwDestroyWindow(s_pWindow);
	glfwTerminate();
}

P3DApp::P3DApp(){
	m_frameCount = 0;
	m_frameTime = 0;
	m_fps = 0;

	m_frameTime = m_startTime = GetTickCount();
}

void P3DApp::CalcFPS()
{
	m_frameCount++;

	long long time = GetTickCount();

	if (time - m_frameTime >= 1000) {
		m_frameTime = time;
		m_fps = m_frameCount;
		m_frameCount = 0;
	}
}
void P3DApp::RenderFPS()
{
	char text[32];
	ZERO_MEM(text);
	sprintf_s(text, sizeof(text), "FPS: %d", m_fps);
	glfwSetWindowTitle(s_pWindow, text);
}
float P3DApp::GetRunningTime()
{
	float RunningTime = (float)((double)GetTickCount() - (double)m_startTime) / 1000.0f;
	return RunningTime;
}	
void P3DApp::Run(){
	GlfwRun();
}
void P3DApp::Init{
	P3DContex::Instance().Init();
}
/*
void P3DApp::drawText(const char* text, float x, float y, void* font)
{
	// Save state
	glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glColor3f(.1f, .1f, .1f); // drop shadow
	// Shift shadow one pixel to the lower right.
	glWindowPos2f(x + 1.0f, y - 1.0f);
	int i = 0;
	while (text[i]){
		glfwBitMa(font, text[i]);
		i++;
	}

	glColor3f(.95f, .95f, .95f);        // main text
	glWindowPos2f(x, y);
	for (std::string::const_iterator it = text.begin(); it != text.end(); ++it)
		glutBitmapCharacter(font, *it);

	// Restore state
	glPopAttrib();
}*/