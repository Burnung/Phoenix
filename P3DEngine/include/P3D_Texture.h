#include "P3D_util.h"
#include <string>
#include <gl\glew.h>

class P3DTexture {
public:
	P3DTexture(){};
	P3DTexture(GLenum, std::string&);
	~P3DTexture(){};

	bool Load(GLenum, std::string&);
	bool Load();

	void Bind(GLenum TextureUnit);

private :
	std::string m_Filename;
	int m_Width;
	int m_Height;
	GLuint m_TexId;
	GLenum m_TexType;
};
typedef std::shared_ptr<P3DTexture> P3DTexturePtr;