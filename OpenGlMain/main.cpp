



#include "Window.h"
#include "ShaderProgram.h"
#include <Windows.h>
int main(int argc, char** argv) {
	std::string PATH = argv[1];

	Window * w = Window::get();

	//std::string pathToShader = PATH + "\GL_FRAGMENT_SHADER_1.txt";


	auto shaderProgram1 = std::make_shared<ShaderProgram>(); 
	shaderProgram1->addShaderFromFile(GL_VERTEX_SHADER, PATH + "\GL_VERTEX_SHADER_1.txt" );
	shaderProgram1->addShaderFromFile(GL_FRAGMENT_SHADER, PATH + "\GL_FRAGMENT_SHADER_1.txt" );
	shaderProgram1->LinkProgram();

	auto shaderProgram2 = std::make_shared<ShaderProgram>(PATH + "\GL_VERTEX_SHADER_1.txt", PATH + "\GL_FRAGMENT_SHADER_2.txt");

	GLfloat vertices[] = {
			-1.0f, 1.0f, 0.0f,//left top
			1.0f, 1.0f, 0.0f, //right top
			0.0f, 0.0f, 0.0f, //center center
			-1.0f, -1.0f, 0.0f, //left bottom 
			1.0f, -1.0f, 0.0f, //right bottom
		};
	GLuint indices[] = {	
		2, 0, 1,
		2, 3, 4,
	};
	GLuint VBO, VAO, IBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	int stepBetweenAttribs_heEquallySizeKit = 3 * sizeof(GLfloat);
	auto offset = (GLvoid*)0;
	auto indexArgumentFunctionShader = 0;
	auto sizeArgumentFunctionShader = 3;//if vec3 then 3.
	glVertexAttribPointer(indexArgumentFunctionShader, sizeArgumentFunctionShader, GL_FLOAT, GL_FALSE, stepBetweenAttribs_heEquallySizeKit, offset);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!w->isExit()) {
		w->lookingEvent();

		glUseProgram(shaderProgram1->shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glUseProgram(shaderProgram2->shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(3 * sizeof(GL_UNSIGNED_INT)) );
		glBindVertexArray(0);

		w->swapBuffers();
	}
	//system("pause");//Чтобы не закрывался.
}