#include "P3D_util.h"
#include <string>
#include <map>



class P3DTexture2D {
public:
	P3DTexture2D() {};
	~P3DTexture2D() {};
	virtual bool Load(std::string&, uint ) = 0;
	virtual bool Load() = 0;

	virtual void Bind(uint TextureUnit) = 0;
private:
	std::string m_Filename;
	int m_Width;
	int m_Height;
	uint m_TexType;
};
class P3DOGLTexture2D : public P3DTexture2D {
public:
	P3DOGLTexture2D(){};
	~P3DOGLTexture2D(){};

	virtual bool Load(std::string&, uint);
	virtual bool Load();

	virtual void Bind(uint TextureUnit);

private :
	std::string m_Filename;
	int m_Width;
	int m_Height;
	uint m_TexId;
	uint m_TexType;
};
typedef std::shared_ptr<P3DTexture2D> P3DTexture2DPtr;

class P3DTexTureMan {
	P3D_DECLARE_SINGLETON(P3DTexTureMan);
public:
	~P3DTexTureMan();
	P3DTexture2DPtr LoadTexture2D(std::string &FileName);
	P3DTexture2DPtr LoadOGLTexture2D(std::string &FileName);
	typedef std::map<std::string, P3DTexture2DPtr> TexturePtrMap;

private:
	TexturePtrMap m_Texture2DPtrMap;
};