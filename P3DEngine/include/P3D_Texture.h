#include "P3D_util.h"
#include <string>
#include <map>



class P3DTexture2D {
public:
	P3DTexture2D() {};
	virtual ~P3DTexture2D() {};
	virtual void Release() = 0;
	virtual bool Load(const std::string&) = 0;
	virtual bool CreateTexture2D(uint w, uint h, uint InnerFormat, uint mipMaps = 0, BYTE *pDate = nullptr) = 0;

	virtual void Bind(uint TextureUnit) = 0;
};

class P3DOGLTexture2D : public P3DTexture2D {
public:
	P3DOGLTexture2D() :m_TexId(0) {};
	virtual ~P3DOGLTexture2D();

	virtual bool Load(const std::string&);
	virtual bool Load();
	virtual bool CreateTexture2D(uint w, uint h, uint InnerFormat, uint mipMaps = 0, BYTE *pDate = nullptr);

	virtual void Bind(uint TextureUnit);

private:
	void GenerateTexFormat(uint InnerFormat);
	virtual void Release();

private:
	std::string m_Filename;
	uint m_Width;
	uint m_Height;
	uint m_InnerFormat;
	uint m_OutFormat;
	uint m_OutDateType;
	uint m_mipMaps;
	uint m_TexId;
};

class P3DTexTureMan {
	P3D_DECLARE_SINGLETON(P3DTexTureMan);
public:
	~P3DTexTureMan();
	P3DTexture2DPtr LoadTexture2D(std::string &FileName);
	P3DTexture2DPtr CreateTexture2D(uint w, uint h, uint InnerFormat, uint MipMaps, BYTE *pDate = nullptr);

	typedef std::map<std::string, P3DTexture2DPtr> TexturePtrMap;
private:
	P3DTexture2DPtr LoadOGLTexture2D(std::string &FileName);

private:
	TexturePtrMap m_Texture2DPtrMap;
};