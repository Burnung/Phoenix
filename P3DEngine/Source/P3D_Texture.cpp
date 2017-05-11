#include "P3D_Texture.h"
#include <gl\glew.h>
#include<FreeImage.h>



bool P3DOGLTexture2D::Load(std::string&filename,uint TexType_ ) {
	m_Filename = filename;
	m_TexType = TexType_;
	return Load();
}

void P3DOGLTexture2D::Bind(uint TextureUnit) {
	glActiveTexture(TextureUnit);
	glBindTexture(m_TexType, m_TexId);
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

	bits = FreeImage_GetBits(dib);
	m_Width = FreeImage_GetWidth(dib);
	m_Height = FreeImage_GetHeight(dib);

	if (!bits || m_Width == 0 || m_Height == 0)
		return false;

	glGenTextures(1, &m_TexId);
	glBindTexture(m_TexType, m_TexId);
	glTexImage2D(m_TexType, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, bits);
	glTexParameteri(m_TexType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(m_TexType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(m_TexType, 0);

	FreeImage_Unload(dib);

	return true;
}

P3DTexture2DPtr P3DTexTureMan::LoadTexture2D(std::string &FileName) {
	if (m_Texture2DPtrMap.find(FileName) != m_Texture2DPtrMap.end())
		return m_Texture2DPtrMap[FileName];
	P3DTexture2DPtr TexPtr = LoadOGLTexture2D(FileName);
	m_Texture2DPtrMap[FileName] = TexPtr;
	return TexPtr;

}
P3DTexture2DPtr LoadOGLTexture2D(std::string &FileName) {
	P3DTexture2DPtr  tTexptr(new P3DOGLTexture2D);
	tTexptr->Load(FileName,GL_TEXTURE_2D);
}