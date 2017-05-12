#include "P3D_Texture.h"
#include <gl\glew.h>
#include<FreeImage.h>


P3DOGLTexture2D::~P3DOGLTexture2D() {
	Release();
}
void P3DOGLTexture2D::Release() {
	if (m_TexId) {
		glDeleteTextures(1, &m_TexId);
		m_TexId = 0;
	}
}
bool P3DOGLTexture2D::Load(const std::string&filename ) {
	m_Filename = filename;
	return Load();
}

void P3DOGLTexture2D::Bind(uint TextureUnit) {
	glActiveTexture(TextureUnit);
	glBindTexture(GL_TEXTURE_2D, m_TexId);
}

bool P3DOGLTexture2D::Load() {

	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP *dib(NULL);
	BYTE *bits(NULL);
	m_Width = 0;
	m_Height = 0;

	fif = FreeImage_GetFileType(m_Filename.c_str());
	if (fif == FIF_UNKNOWN)
		return false;
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, m_Filename.c_str());
	if (!dib)
		return false;

	if (!bits || m_Width == 0 || m_Height == 0)
		return false;

	FREE_IMAGE_COLOR_TYPE tColorType = FreeImage_GetColorType(dib);
	m_InnerFormat = GL_RGB8;
	if (tColorType == FIC_RGBALPHA) {
		m_InnerFormat = GL_RGBA8;
		if (FreeImage_GetBPP(dib) != 32)
			dib = FreeImage_ConvertTo32Bits(dib);
	}
	else if (FreeImage_GetBPP(dib) != 24)
		dib = FreeImage_ConvertTo24Bits(dib);

	bits = FreeImage_GetBits(dib);
	m_Width = FreeImage_GetWidth(dib);
	m_Height = FreeImage_GetHeight(dib);
	CreateTexture2D(m_Width, m_Height, m_InnerFormat, 0, bits);

	FreeImage_Unload(dib);

	return true;
}
void P3DOGLTexture2D::GenerateTexFormat(uint InnerFormat) {
	m_InnerFormat = InnerFormat;
	switch (m_InnerFormat) {
	case GL_RGBA8:
		m_OutFormat = GL_RGBA;
		m_OutDateType = GL_UNSIGNED_BYTE;
		break;
	case GL_RGB8:
		m_OutFormat = GL_RGB;
		m_OutDateType = GL_UNSIGNED_BYTE;
	case GL_RGBA32F_ARB:
		m_OutFormat = GL_RGBA;
		m_OutDateType = GL_FLOAT;
		break;
	case GL_RGB32F_ARB:
		m_OutFormat = GL_RGB;
		m_OutDateType = GL_FLOAT;
		break;
	case GL_R32F:
		m_OutFormat = GL_R;
		m_OutDateType = GL_FLOAT;
		break;
	default:
		m_OutFormat = GL_RGBA;
		m_OutDateType = GL_UNSIGNED_BYTE;
	}

}
bool P3DOGLTexture2D::CreateTexture2D(uint w, uint h, uint InnerFormat,uint mipMaps, BYTE *pDate ){
	if (m_TexId)
		return false;
	m_Width = w;
	m_Height = h;
	GenerateTexFormat(InnerFormat);
	glGenTextures(GL_TEXTURE_2D, &m_TexId);
	glBindTexture(GL_TEXTURE_2D, m_TexId);
	m_mipMaps = glm::clamp((int)mipMaps, 0, 7);
	switch (m_OutDateType)
	{
	case GL_UNSIGNED_BYTE:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		break;
	case GL_FLOAT:
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		break;
	default:
		break;
	}
	glTexStorage2D(GL_TEXTURE_2D, m_mipMaps, m_InnerFormat, m_Width, m_Height);
	glTexImage2D(GL_TEXTURE_2D, 0, m_InnerFormat, m_Width, m_Height, 0, m_OutFormat, m_OutDateType, pDate);
	if (m_mipMaps)
		glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,0);
	return true;
}
/**************************************TexMan******************************************/
P3D_DEFINE_SINGLETON(P3DTexTureMan)

P3DTexTureMan::~P3DTexTureMan() {

}
P3DTexture2DPtr P3DTexTureMan::LoadTexture2D(std::string &FileName) {
	if (m_Texture2DPtrMap.find(FileName) != m_Texture2DPtrMap.end())
		return m_Texture2DPtrMap[FileName];
	P3DTexture2DPtr TexPtr = LoadOGLTexture2D(FileName);
	m_Texture2DPtrMap[FileName] = TexPtr;
	return TexPtr;

}
P3DTexture2DPtr P3DTexTureMan::LoadOGLTexture2D(std::string &FileName) {
	P3DTexture2DPtr  tTexptr(new P3DOGLTexture2D);
	if (tTexptr->Load(FileName))
		return tTexptr;
	return P3DTexture2DPtr(nullptr);
}

P3DTexture2DPtr P3DTexTureMan::CreateTexture2D(uint w, uint h, uint InnerFormat,uint mipMaps, BYTE *pDate) {

	P3DTexture2DPtr TexPtr(new P3DOGLTexture2D);
	if (TexPtr->CreateTexture2D(w, h, InnerFormat, mipMaps, pDate))
		return TexPtr;
	return P3DTexture2DPtr(nullptr);


}