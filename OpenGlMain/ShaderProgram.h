#pragma once

#include "ALL.h"
class ShaderProgram
{
	
public:
	GLuint shaderProgram;
	ShaderProgram();
	ShaderProgram(std::string vertex, std::string fragment);
	~ShaderProgram();
	void LinkProgram();
	void addShader(GLuint shader);
	void addShaderFromFile(GLenum type,std::string path);
};

