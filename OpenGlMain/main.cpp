


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

	auto shaderProgram2 = std::make_shared<ShaderProgram>(PATH + "GL_VERTEX_SHADER_3.txt", PATH + "GL_FRAGMENT_SHADER_3.txt");

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

	shaderProgram2->addTexture_2D_FromFile(std::string(PATH + "t1.jpg").c_str());
	shaderProgram2->addTexture_2D_FromFile(std::string(PATH + "container.jpg" ).c_str());
	
	//GLuint texture;
	//glGenTextures(1, &texture);
	//glBindTexture(GL_TEXTURE_2D, texture);
	//int width, height;
	//std::string s_path = std::string((PATH + "t1.jpg"));
	//const char * path = s_path.c_str();

	//unsigned char* image = SOIL_load_image(s_path.c_str(),&width, &height, 0, SOIL_LOAD_RGB);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//glGenerateMipmap(GL_TEXTURE_2D);
	//SOIL_free_image_data(image);
	//glBindTexture(GL_TEXTURE_2D, 0);


	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(2);


	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	
	while (!w->isExit()) {
		w->lookingEvent();
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram2->use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, shaderProgram2->textures[0]);
		glUniform1i(glGetUniformLocation(shaderProgram2->shaderProgram, "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, shaderProgram2->textures[1]);
		glUniform1i(glGetUniformLocation(shaderProgram2->shaderProgram, "ourTexture2"), 1);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		w->swapBuffers();
	}
	//system("pause");//Чтобы не закрывался.
}