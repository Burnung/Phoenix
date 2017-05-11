#include "P3D_GLFrame.h"

class myApp :public GL_CallBack, public P3DApp {
public :

};
int main() {
	myApp *App = new myApp;
	InitGLContex(512, 512, true, false, "test");
	App->Run();
	delete App;
	ENDERROROUT();
}