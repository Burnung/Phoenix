#include "P3D_Contex.h"
#include "P3D_GLFrame.h"
P3D_DEFINE_SINGLETON(P3DContex);
const int WINDOWWIDTH = 1600;
const int WINDOWHEIGHT = 1024;
void P3DContex::Init() {
	InitGLContex(WINDOWWIDTH, WINDOWHEIGHT, true, true, "P3DAPP");
	m_InputPtr = std::make_shared<P3DInput>();

}