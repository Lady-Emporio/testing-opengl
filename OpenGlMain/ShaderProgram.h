#pragma once

#include "ALL.h"
class ShaderProgram
{
	
public:
	GLuint shaderProgram;
	GLuint texture;
	ShaderProgram();
	ShaderProgram(std::string vertex, std::string fragment);
	~ShaderProgram();
	void LinkProgram();
	void addShader(GLuint shader);
	void addShaderFromFile(GLenum type,std::string path);
	void addTexture_2D_FromFile(std::string path);
	void use();

	
};

