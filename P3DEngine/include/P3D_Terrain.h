#pragma once
#include "P3D_Renderable.h"
#include <string>
#include"P3D_util.h"
#include <vector>
#include "P3D_ViewPort.h"



class P3DTerrainRender {
public:
	virtual ~P3DTerrainRender() {};
	virtual void Render(P3DViewPortPtr) = 0;
	virtual void Release() = 0;

};

class P3DOGLTerrainRender :public P3DTerrainRender{
public:
	P3DOGLTerrainRender() :m_VAO(0) {};
	virtual~P3DOGLTerrainRender();
	virtual void Release();
	virtual void Render(P3DViewPortPtr);

private:
	P3DTerrainRenderablePtr m_TerrainRenderablePtr;
	uint m_VAO;
};

//供渲染使用  只提供渲染数据
class P3DTerrainRenderable :P3DRenderable {

public:
	P3DTerrainRenderable(P3DTerrainPtr TerrainPtr) : m_TerrainPtr(TerrainPtr){}
	P3DTerrainRenderable() : m_TerrainPtr(P3DTerrainPtr(nullptr)) {};
	void Release();
	P3DTexture2DPtr GetHeigtTexture(const glm::vec3 &Pos);
	void SetP3DTerrainPtr(P3DTerrainPtr Tptr);

private:

	P3DTerrainPtr m_TerrainPtr;

	uint m_VAO;

};


class P3DTerrainBlock {
public:
	P3DTerrainBlock() {};
	P3DTerrainBlock(Size2i s) :m_Size(s) {};
	void AllocMemory();
	~P3DTerrainBlock();
	void Release();

private:
	std::vector<std::vector<float>> m_HeightData;
	glm::ivec2 m_LeftDown;  //左下角位置
	Size2i m_Size;      //block大小

	friend class P3DTerrain;
};

//地形数据  供查询使用
class P3DTerrain {

public:
	P3DTerrain();
	~P3DTerrain();
	bool LoadTerrain(const std::string &fileName);
	Size2i GetHeghtDataByPos(const glm::vec3 &pos, float Distance,std::vector<float> &fData,glm::vec2 &CenterPos);


private:
	std::string m_FileName;
	float m_Scale;      //缩放大小  比例尺  
	Size2i m_BlockSize;  
	Size2i m_TerrainSize;  //地形大小 包含的顶点数量
	std::vector < std::vector<P3DTerrainBlockPtr>> m_BlockPtrs;
	std::vector < std::vector<float> > m_HeightData;

};