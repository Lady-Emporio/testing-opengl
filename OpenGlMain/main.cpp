


#include "ALL.h"
#include "Window.h"
#include "ShaderProgram.h"
#include <Windows.h>
#include <SOIL/SOIL.h>

int main(int argc, char** argv) {
	std::string PATH = argv[1];

	Window * w = Window::get();

	//std::string pathToShader = PATH + "\GL_FRAGMENT_SHADER_1.txt";


	//auto shaderProgram1 = std::make_shared<ShaderProgram>(); 
	//shaderProgram1->addShaderFromFile(GL_VERTEX_SHADER, PATH + "\GL_VERTEX_SHADER_1.txt" );
	//shaderProgram1->addShaderFromFile(GL_FRAGMENT_SHADER, PATH + "\GL_FRAGMENT_SHADER_1.txt" );
	//shaderProgram1->LinkProgram();

	auto shaderProgram2 = std::make_shared<ShaderProgram>(PATH + "\GL_VERTEX_SHADER_3.txt", PATH + "\GL_FRAGMENT_SHADER_3.txt");

	//GLfloat vertices[] = {
	//		-1.0f, 1.0f, 0.0f,//left top
	//		1.0f, 1.0f, 0.0f, //right top
	//		0.0f, 0.0f, 0.0f, //center center
	//		-1.0f, -1.0f, 0.0f, //left bottom 
	//		1.0f, -1.0f, 0.0f, //right bottom
	//	};
	GLfloat vertices[] = {
		// Позиции          // Цвета             // Текстурные координаты
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Верхний правый
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Нижний правый
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Нижний левый
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Верхний левый
	};
	GLuint indices[] = {	
		3, 1, 0,
		3, 1, 2,
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
	//glVertexAttribPointer(indexArgumentFunctionShader, sizeArgumentFunctionShader, GL_FLOAT, GL_FALSE, stepBetweenAttribs_heEquallySizeKit, offset);
	//glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	std::string s_pathToImage = PATH + "\container.jpg";
	shaderProgram2->addTexture_2D_FromFile(s_pathToImage);

	while (!w->isExit()) {
		w->lookingEvent();

		shaderProgram2->use();

		glBindTexture(GL_TEXTURE_2D, shaderProgram2->texture);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		//glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);

		/*shaderProgram2->use();

		glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(3 * sizeof(GL_UNSIGNED_INT)) );
		glBindVertexArray(0);
*/
		w->swapBuffers();
	}
	//system("pause");//Чтобы не закрывался.
}