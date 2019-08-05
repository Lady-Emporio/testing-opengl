#include "ShaderProgram.h"


ShaderProgram::ShaderProgram()
{
	shaderProgram = glCreateProgram();
}

ShaderProgram::ShaderProgram(std::string vertex, std::string fragment)
{
	this->shaderProgram = glCreateProgram();
	addShaderFromFile(GL_VERTEX_SHADER, vertex);
	addShaderFromFile(GL_FRAGMENT_SHADER, fragment);
	this->LinkProgram();
}


ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::LinkProgram()
{
	glLinkProgram(shaderProgram);

	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if(!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		Twilight::Error("ERROR::ShaderProgram::LINK_FAILED\n" , infoLog);
	}
}

void ShaderProgram::addShader(GLuint shader)
{
	glAttachShader(this->shaderProgram, shader);
}

void ShaderProgram::addShaderFromFile(GLenum type, std::string path)
{
		
		std::ifstream file(path);
		if (file.is_open())
		{

			std::string line;
			std::string result = "";
			while (getline(file, line))
			{
				result += line;
				result += '\n';
			}
			file.close();

			
			const char * buffer = result.c_str();


			GLuint shader;
			shader = glCreateShader(type);
			glShaderSource(shader, 1, &buffer, NULL);
			glCompileShader(shader);

			GLint success;
			GLchar infoLog[512];
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 512, NULL, infoLog);
				Twilight::Error("ERROR::SHADER", infoLog);
			}
			this->addShader(shader);
		}
		else {
			Twilight::Error("Cant open:" , path.c_str());
		}
}

void ShaderProgram::addTexture_2D_FromFile(std::string path)
{
	
	GLuint texture;
	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height;
	unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	this->textures.push_back(texture);
}

void ShaderProgram::use()
{
	glUseProgram(this->shaderProgram);
}
