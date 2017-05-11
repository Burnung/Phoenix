#pragma once
#include "P3D_util.h"
#include "P3D_Input.h"
class P3DContex {
	P3D_DECLARE_SINGLETON(P3DContex);

private:
	void LoadCfg();
public:
	P3DInputPtr GetInputPtr() { return m_InputPtr; }
	void Init();
private:
	P3DInputPtr m_InputPtr;
};