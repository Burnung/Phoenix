#include "P3D_Terrain.h"
#include <FreeImage.h>
#include "P3D_util.h"
#include <glm\glm.hpp>
#include "P3D_Texture.h"
bool P3DTerrain::LoadTerrain(const std::string& fileName) {
	//使用FreeImage载入高度图
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	fif = FreeImage_GetFileType(fileName.c_str());
	if (fif == FIF_UNKNOWN) {
		ERROROUT("Load Terrian Error,Fomate Error");
		return false;
	}
	FIBITMAP *m_BitMap = nullptr;
	if (FreeImage_FIFSupportsReading(fif))
		m_BitMap = FreeImage_Load(fif,fileName.c_str());
	if (!m_BitMap) {
		ERROROUT("Load Terrain ERROR");
		return false;
	}
	uint bitSize = FreeImage_GetBPP(m_BitMap);
	if (bitSize != 16) {
		m_BitMap = FreeImage_ConvertToUINT16(m_BitMap);  //转为16位深度图
	}
	uint t_width = FreeImage_GetWidth(m_BitMap);
	uint t_height = FreeImage_GetHeight(m_BitMap);  //获得图像大小

	if (t_width % m_BlockSize.x) {
		t_width = t_width / m_BlockSize.x * m_BlockSize.x;
	}
	if (t_height & m_BlockSize.y) {
		t_height = t_height / m_BlockSize.y * m_BlockSize.y;
	}
	//m_TerrainSize = Size2i(t_width, t_height);  //只读取块的整数个大小   先不用块

	m_HeightData.resize(t_height);
	for (auto item : m_HeightData)
		item.resize(t_width);

/*	m_BlockPtrs.resize(t_height / m_BlockSize.y);
	for (auto item : m_BlockPtrs)
		item.resize(t_width / m_BlockSize.x);  // Block大小
	for(int i = 0;i< m_BlockPtrs.size();i++)
		for (int j = 0; j < m_BlockPtrs[i].size(); j++) {
			m_BlockPtrs[i][j] = std::make_shared<P3DTerrainBlock>(m_BlockSize);
			m_BlockPtrs[i][j]->AllocMemory();
			m_BlockPtrs[i][j]->m_LeftDown = glm::ivec2(j * m_BlockSize.x, i * m_BlockSize.y);  //初始化block
		}*/

	BYTE *pByte = FreeImage_GetBits(m_BitMap);  // 获得数据
	uint tPitch = FreeImage_GetPitch(m_BitMap);  // 获得pitch

	// 开始读数据

	for (int i = 0; i < t_height; i++) {
		pByte += tPitch;
		BYTE *nData = pByte;
		for (int j = 0; j < t_width; j++) {
			m_HeightData[i][j] = (float)(*(ushort*)nData);
			nData += 2;
		}
	}
	/*for (int i = 0; i < t_height; i++) {
		pByte += tPitch * i;
		for (int j = 0; j < t_width;) {
			//根据 i j获取块 写入
			int row = i / m_BlockSize.y;
			int col = j / m_BlockSize.x;
			P3DTerrainBlockPtr nowPtr = m_BlockPtrs[row][col];
			int rowIndex = i - row * m_BlockSize.y;
			for (int colIndex = 0; colIndex < m_BlockSize.x; colIndex++){
				nowPtr->m_HeightData[rowIndex][colIndex] = (float)(*(ushort*)pByte);
					pByte += 2;
			}
			j += m_BlockSize.x; 
		}
	}*/

}


Size2i P3DTerrain::GetHeghtDataByPos(const glm::vec3 &pos, float Distance, std::vector<float> &fData, glm::vec2 &CenterPos){
	fData.clear();
	float fDis = Distance / m_Scale;
	float fx = pos.x / m_Scale;
	float fy = pos.y / m_Scale;
	CenterPos = glm::ivec2(floor(fx), floor(fy));
	int minX, minY, maxX, maxY;
	minX = floor(CenterPos.x - fDis) - 1;
	minY = floor(CenterPos.y - fDis) - 1;
	maxX = ceil(CenterPos.x + fDis) + 1;
	maxY = ceil(CenterPos.y + fDis) + 1;
	minX = glm::clamp(minX,0, minX);
	minY = glm::clamp(minY,0, minY);
	maxX = glm::clamp(maxX, maxX, m_TerrainSize.x - 1);
	maxY = glm::clamp(maxY, maxY, m_TerrainSize.y - 1);

	Size2i retSize( maxX - minX + 1, maxY - minY + 1);
	int dataSize = retSize.x * retSize.y;
	fData.resize(dataSize);

	uint index = 0;
	for (int i = minY; i <= maxY; i++)
		for (int j = minX; j <= maxX; j++)
			fData[index++] = m_HeightData[i][j];

	return retSize;

}

/******************************************TerrainRenderable****************************************/
P3DTexture2DPtr P3DTerrainRenderable::GetHeigtTexture(const glm::vec3 &Pos) {
	float Distance = 5000;
	std::vector<float> fData;
	glm::vec2 CenterPos;
	Size2i texSize = m_TerrainPtr->GetHeghtDataByPos(Pos, Distance,fData, CenterPos);
	P3DTexture2DPtr TexPtr = P3DTexTureMan::Instance().CreateTexture2D(texSize.x, texSize.y, GL_R32F, 0, (BYTE*)(&fData[0]));
	return TexPtr;

}
void P3DTerrainRenderable::Release() {

}

/********************************TerrainRender**********************************************/
P3DOGLTerrainRender::~P3DOGLTerrainRender() {
	Release();
}

void P3DOGLTerrainRender::Release() {
	if (m_VAO) {
		glDeleteVertexArrays(1, &m_VAO);
		m_VAO = 0;
	}
}

void P3DOGLTerrainRender::Render(P3DViewPortPtr viewPortPtr) {
	
	P3DTexture2DPtr TexTurePtr = m_TerrainRenderablePtr->GetHeigtTexture()
}