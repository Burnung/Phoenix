#include "P3D_Texture.h"
#include<FreeImage.h>


P3DTexture::P3DTexture(GLenum TexType_, std::string&filename) :m_TexType(TexType_), m_Filename(filename)
{
}

bool P3DTexture::Load(GLenum TexType_, std::string&filename) {
	m_Filename = filename;
	m_TexType = TexType_;
	return Load();
}

void P3DTexture::Bind(GLenum TextureUnit) {
	glActiveTexture(TextureUnit);
	glBindTexture(m_TexType, m_TexId);
}

bool P3DTexture::Load() {

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
	glTexParameterf(m_TexType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(m_TexType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(m_TexType, 0);

	FreeImage_Unload(dib);

	return true;
}