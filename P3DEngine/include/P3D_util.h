#pragma once
#include<fstream>
#include <time.h>
#include <memory>
#include <glm\glm.hpp>
/**************************定义数据类型**********************/
typedef unsigned char       BYTE;
typedef unsigned int        uint;  //32 位
typedef glm::ivec2 Size2i;
typedef unsigned int      t_Size;
typedef unsigned short   ushort;  // 16位
/************************************************************/
const float PI = 3.1415926;

#define P3D_DECLARE_SINGLETON(CLASS_NAME)  \
	private:\
	CLASS_NAME(); \
	CLASS_NAME(const CLASS_NAME&); \
	CLASS_NAME& operator= (const CLASS_NAME&);    \
	public:\
	static CLASS_NAME &Instance()

#define P3D_DEFINE_SINGLETON(CLASS_NAME)   \
	CLASS_NAME::CLASS_NAME() {};  \
	CLASS_NAME & CLASS_NAME::Instance(){\
static CLASS_NAME s_instance; \
return s_instance; \
	}

#define PHO_DEFINE_SINGLETON_NO_CTOR(CLASS_NAME)  \
	CLASS_NAME & CLASS_NAME::Instance(){\
	static CLASS_NAME s_instance;   \
	return s_instance;  \
	}


#define INITEERROROUT(P) InitOutOf(P)
#define ERROROUT(P)  ErrorOut(__FILE__,__LINE__,P)
#define ENDERROROUT() EndErrorOut()
#define ZERO_MEM(a) memset(a, 0, sizeof(a))


class ErrorLog{
	P3D_DECLARE_SINGLETON(ErrorLog);
private:
	std::ofstream of;
public:
	void Init(const char*fileName);
	std::ofstream& getOf(){ return of; };
	void End(){ of.close(); }

};


void InitOutOf( const char*);
void ErrorOut( const char*file, int line, const char *neirong);
void GetTime(std::ofstream &);
void EndErrorOut();
void GlfwErrorCallBack(int n, const char* descrption);
bool ReadFile(const char* pFileName, std::string& outFile);
void SaveBMP(const char *fileName, BYTE *buf, int width, int height);

#define GL_INVALID_MATERIAL 0xFFFFFFFF
#define INVALID_OGL_VALUE   0xFFFFFFFF

#define SAFERELEASE(p) if (p) { delete p; p = NULL; }

enum RenderType{
	TEXTURE_TYPE,   //��Ⱦ����
	MODEL_NORMAL_TYPE,    //��Ⱦģ�ͷ���
	WORLD_NORMAL_TYPE,    //��Ⱦ���編��
	MODEL_POSITION_TYPE,  //��Ⱦģ������
	WORLD_POSITION_TYPE,  //��Ⱦ��������

};
enum MaterialType{
	DIFF,
	SPEC,
	REFR,
	EMMI,
	NUM,
};

template<typename T>
void PHO_Clamp(T Tmin, T Tmax, T& var){
	if (var < Tmin)
		var = Tmin;
	else if (var > Tmax)
		var = Tmax;
}
/***********************typedef Ptr***************************************/
class P3DTerrainBlock;
typedef std::shared_ptr<P3DTerrainBlock> P3DTerrainBlockPtr;

class P3DTerrain;
typedef std::shared_ptr<P3DTerrain> P3DTerrainPtr;

class P3DTexture2D;
typedef std::shared_ptr<P3DTexture2D> P3DTexture2DPtr;

class P3DTerrainRender;
typedef std::shared_ptr<P3DTerrainRender> P3DOGLTerrainRender;

class P3DTerrainRenderable;
typedef std::shared_ptr<P3DTerrainRenderable> P3DTerrainRenderablePtr;

class P3DViewPort;
typedef std::shared_ptr< P3DViewPort> P3DViewPortPtr;