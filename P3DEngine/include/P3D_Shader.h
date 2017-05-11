#pragma once
#include<gl\glew.h>
#include"P3D_util.h"
#include<string>

class P3DGlslProgram{

protected:
	GLchar *vertexName ;
	GLchar *geometryName ;
	GLchar *fragmentName ;
	GLenum shaderType ;
	GLuint ShaderProgram ;


public:

	P3DGlslProgram(){vertexName = 0; geometryName = 0; fragmentName =0; ShaderProgram = 0; shaderType = -1;}


	void loadShader(const char *vetexName_=NULL,const char *geometryName_=NULL,
		              const char *fragmentName_=NULL);


	void reload();

	void addShader(std::string s,GLenum id);

	void useShder();

	GLuint getUniform(const char *name);

	void DisUse();

	GLuint getProgram(){ return ShaderProgram; };

};
typedef std::shared_ptr<P3DGlslProgram> P3DGLSLProgramPtr;