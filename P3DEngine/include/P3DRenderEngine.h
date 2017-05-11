#pragma once
#include <memory>
#include "P3D_Camera.h"
#include "P3D_ViewPort.h"
#include <map>

typedef 
class P3DRenderEngine {



	void Render();
private:
	P3DViewPortPtr m_ViewPortPtr;
	P3DCameraPtr m_CameraPtr;
};
typedef std::shared_ptr<P3DRenderEngine> P3DRenderEnginePtr;