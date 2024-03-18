#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 3", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shaders/core.vs", "Shaders/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers

	

	// use with Perspective Projection
	float vertices[] = {

		//Cubo Aztec Gold para el cuerpo y patitas
		-0.5f, -0.5f, 0.5f, 0.7725f, 0.5686f,0.3647f,//Front
		0.5f, -0.5f, 0.5f,  0.7725f, 0.5686f,0.3647f,
		0.5f,  0.5f, 0.5f,  0.7725f, 0.5686f,0.3647f,
		0.5f,  0.5f, 0.5f,  0.7725f, 0.5686f,0.3647f,
		-0.5f,  0.5f, 0.5f, 0.7725f, 0.5686f,0.3647f,
		-0.5f, -0.5f, 0.5f, 0.7725f, 0.5686f,0.3647f,

		-0.5f, -0.5f,-0.5f, 0.7725f, 0.5686f,0.3647f,//Back
		 0.5f, -0.5f,-0.5f, 0.7725f, 0.5686f,0.3647f,
		 0.5f,  0.5f,-0.5f, 0.7725f, 0.5686f,0.3647f,
		 0.5f,  0.5f,-0.5f, 0.7725f, 0.5686f,0.3647f,
		-0.5f,  0.5f,-0.5f, 0.7725f, 0.5686f,0.3647f,
		-0.5f, -0.5f,-0.5f, 0.7725f, 0.5686f,0.3647f,

		 0.5f, -0.5f,  0.5f,  0.7725f, 0.5686f,0.3647f,
		 0.5f, -0.5f, -0.5f,  0.7725f, 0.5686f,0.3647f,
		 0.5f,  0.5f, -0.5f,  0.7725f, 0.5686f,0.3647f,
		 0.5f,  0.5f, -0.5f,  0.7725f, 0.5686f,0.3647f,
		 0.5f,  0.5f,  0.5f,  0.7725f, 0.5686f,0.3647f,
		 0.5f,  -0.5f, 0.5f, 0.7725f, 0.5686f,0.3647f,

		-0.5f,  0.5f,  0.5f,  0.7725f, 0.5686f,0.3647f,
		-0.5f,  0.5f, -0.5f,  0.7725f, 0.5686f,0.3647f,
		-0.5f, -0.5f, -0.5f,  0.7725f, 0.5686f,0.3647f,
		-0.5f, -0.5f, -0.5f,  0.7725f, 0.5686f,0.3647f,
		-0.5f, -0.5f,  0.5f,  0.7725f, 0.5686f,0.3647f,
		-0.5f,  0.5f,  0.5f,  0.7725f, 0.5686f,0.3647f,

		-0.5f, -0.5f, -0.5f, 0.7725f, 0.5686f,0.3647f,
		0.5f, -0.5f, -0.5f,  0.7725f, 0.5686f,0.3647f,
		0.5f, -0.5f,  0.5f,  0.7725f, 0.5686f,0.3647f,
		0.5f, -0.5f,  0.5f,  0.7725f, 0.5686f,0.3647f,
		-0.5f, -0.5f,  0.5f, 0.7725f, 0.5686f,0.3647f,
		-0.5f, -0.5f, -0.5f, 0.7725f, 0.5686f,0.3647f,

		-0.5f,  0.5f, -0.5f, 0.7725f, 0.5686f,0.3647f,
		0.5f,  0.5f, -0.5f,  0.7725f, 0.5686f,0.3647f,
		0.5f,  0.5f,  0.5f,  0.7725f, 0.5686f,0.3647f,
		0.5f,  0.5f,  0.5f,  0.7725f, 0.5686f,0.3647f,
		-0.5f,  0.5f,  0.5f, 0.7725f, 0.5686f,0.3647f,
		-0.5f,  0.5f, -0.5f, 0.7725f, 0.5686f,0.3647f,

		//Cubo Old Lace Pelaje frontal y trasero del cuello
		-2.5f, -2.5f, 2.5f, 0.9882f, 0.9529f,0.8941f,//Front
		2.5f, -2.5f, 2.5f,  0.9882f, 0.9529f,0.8941f,
		2.5f,  2.5f, 2.5f,  0.9882f, 0.9529f,0.8941f,
		2.5f,  2.5f, 2.5f,  0.9882f, 0.9529f,0.8941f,
		-2.5f,  2.5f, 2.5f, 0.9882f, 0.9529f,0.8941f,
		-2.5f, -2.5f, 2.5f, 0.9882f, 0.9529f,0.8941f,

		-2.5f, -2.5f,-2.5f, 0.9882f, 0.9529f,0.8941f,//Back
		 2.5f, -2.5f,-2.5f, 0.9882f, 0.9529f,0.8941f,
		 2.5f,  2.5f,-2.5f, 0.9882f, 0.9529f,0.8941f,
		 2.5f,  2.5f,-2.5f, 0.9882f, 0.9529f,0.8941f,
		-2.5f,  2.5f,-2.5f, 0.9882f, 0.9529f,0.8941f,
		-2.5f, -2.5f,-2.5f, 0.9882f, 0.9529f,0.8941f,

		 2.5f, -2.5f,  2.5f,  0.9882f, 0.9529f,0.8941f,
		 2.5f, -2.5f, -2.5f,  0.9882f, 0.9529f,0.8941f,
		 2.5f,  2.5f, -2.5f,  0.9882f, 0.9529f,0.8941f,
		 2.5f,  2.5f, -2.5f,  0.9882f, 0.9529f,0.8941f,
		 2.5f,  2.5f,  2.5f,  0.9882f, 0.9529f,0.8941f,
		 2.5f,  -2.5f, 2.5f,  0.9882f, 0.9529f,0.8941f,

		-2.5f,  2.5f,  2.5f,  0.9882f, 0.9529f,0.8941f,
		-2.5f,  2.5f, -2.5f,  0.9882f, 0.9529f,0.8941f,
		-2.5f, -2.5f, -2.5f,  0.9882f, 0.9529f,0.8941f,
		-2.5f, -2.5f, -2.5f,  0.9882f, 0.9529f,0.8941f,
		-2.5f, -2.5f,  2.5f,  0.9882f, 0.9529f,0.8941f,
		-2.5f,  2.5f,  2.5f,  0.9882f, 0.9529f,0.8941f,

		-2.5f, -2.5f, -2.5f, 0.9882f, 0.9529f,0.8941f,
		2.5f, -2.5f, -2.5f,  0.9882f, 0.9529f,0.8941f,
		2.5f, -2.5f,  2.5f,  0.9882f, 0.9529f,0.8941f,
		2.5f, -2.5f,  2.5f,  0.9882f, 0.9529f,0.8941f,
		-2.5f, -2.5f,  2.5f, 0.9882f, 0.9529f,0.8941f,
		-2.5f, -2.5f, -2.5f, 0.9882f, 0.9529f,0.8941f,

		-2.5f,  2.5f, -2.5f, 0.9882f, 0.9529f,0.8941f,
		2.5f,  2.5f, -2.5f,  0.9882f, 0.9529f,0.8941f,
		2.5f,  2.5f,  2.5f,  0.9882f, 0.9529f,0.8941f,
		2.5f,  2.5f,  2.5f,  0.9882f, 0.9529f,0.8941f,
		-2.5f,  2.5f,  2.5f, 0.9882f, 0.9529f,0.8941f,
		-2.5f,  2.5f, -2.5f, 0.9882f, 0.9529f,0.8941f,

		//Cubo Dutch White Pelaje laterales del cuello
		-2.5f, -2.5f, 2.5f, 0.9373f, 0.8588f,0.7137f,//Front
		2.5f, -2.5f, 2.5f,  0.9373f, 0.8588f,0.7137f,
		2.5f,  2.5f, 2.5f,  0.9373f, 0.8588f,0.7137f,
		2.5f,  2.5f, 2.5f,  0.9373f, 0.8588f,0.7137f,
		-2.5f,  2.5f, 2.5f, 0.9373f, 0.8588f,0.7137f,
		-2.5f, -2.5f, 2.5f, 0.9373f, 0.8588f,0.7137f,

		-2.5f, -2.5f,-2.5f, 0.9373f, 0.8588f,0.7137f,//Back
		 2.5f, -2.5f,-2.5f, 0.9373f, 0.8588f,0.7137f,
		 2.5f,  2.5f,-2.5f, 0.9373f, 0.8588f,0.7137f,
		 2.5f,  2.5f,-2.5f, 0.9373f, 0.8588f,0.7137f,
		-2.5f,  2.5f,-2.5f, 0.9373f, 0.8588f,0.7137f,
		-2.5f, -2.5f,-2.5f, 0.9373f, 0.8588f, 0.7137f,

		 2.5f, -2.5f,  2.5f, 0.9373f, 0.8588f, 0.7137f,
		 2.5f, -2.5f, -2.5f, 0.9373f, 0.8588f, 0.7137f,
		 2.5f,  2.5f, -2.5f, 0.9373f, 0.8588f, 0.7137f,
		 2.5f,  2.5f, -2.5f, 0.9373f, 0.8588f, 0.7137f,
		 2.5f,  2.5f,  2.5f, 0.9373f, 0.8588f, 0.7137f,
		 2.5f,  -2.5f, 2.5f, 0.9373f, 0.8588f, 0.7137f,

		-2.5f,  2.5f,  2.5f, 0.9373f, 0.8588f, 0.7137f,
		-2.5f,  2.5f, -2.5f, 0.9373f, 0.8588f, 0.7137f,
		-2.5f, -2.5f, -2.5f, 0.9373f, 0.8588f, 0.7137f,
		-2.5f, -2.5f, -2.5f, 0.9373f, 0.8588f, 0.7137f,
		-2.5f, -2.5f,  2.5f, 0.9373f, 0.8588f, 0.7137f,
		-2.5f,  2.5f,  2.5f, 0.9373f, 0.8588f, 0.7137f,

		-2.5f, -2.5f, -2.5f, 0.9373f, 0.8588f, 0.7137f,
		2.5f, -2.5f, -2.5f, 0.9373f, 0.8588f, 0.7137f,
		2.5f, -2.5f,  2.5f, 0.9373f, 0.8588f, 0.7137f,
		2.5f, -2.5f,  2.5f, 0.9373f, 0.8588f, 0.7137f,
		-2.5f, -2.5f,  2.5f, 0.9373f, 0.8588f, 0.7137f,
		-2.5f, -2.5f, -2.5f, 0.9373f, 0.8588f, 0.7137f,

		-2.5f,  2.5f, -2.5f, 0.9373f, 0.8588f, 0.7137f,
		2.5f,  2.5f, -2.5f, 0.9373f, 0.8588f, 0.7137f,
		2.5f,  2.5f,  2.5f, 0.9373f, 0.8588f, 0.7137f,
		2.5f,  2.5f,  2.5f, 0.9373f, 0.8588f, 0.7137f,
		-2.5f,  2.5f,  2.5f, 0.9373f, 0.8588f, 0.7137f,
		-2.5f,  2.5f, -2.5f, 0.9373f, 0.8588f, 0.7137f,

		//color de ojos
			-0.5f, -0.5f, 0.5f, 0.2f, 0.1255f, 0.0667f,//Front
			0.5f, -0.5f, 0.5f, 0.2f, 0.1255f, 0.0667f,
			0.5f, 0.5f, 0.5f, 0.2f, 0.1255f, 0.0667f,
			0.5f, 0.5f, 0.5f, 0.2f, 0.1255f, 0.0667f,
			-0.5f, 0.5f, 0.5f, 0.2f, 0.1255f, 0.0667f,
			-0.5f, -0.5f, 0.5f, 0.2f, 0.1255f, 0.0667f,

			-0.5f, -0.5f, -0.5f, 0.2f, 0.1255f, 0.0667f,//Back
			0.5f, -0.5f, -0.5f, 0.2f, 0.1255f, 0.0667f,
			0.5f, 0.5f, -0.5f, 0.2f, 0.1255f, 0.0667f,
			0.5f, 0.5f, -0.5f, 0.2f, 0.1255f, 0.0667f,
			-0.5f, 0.5f, -0.5f, 0.2f, 0.1255f, 0.0667f,
			-0.5f, -0.5f, -0.5f, 0.2f, 0.1255f, 0.0667f,

			0.5f, -0.5f, 0.5f, 0.2f, 0.1255f, 0.0667f,
			0.5f, -0.5f, -0.5f, 0.2f, 0.1255f, 0.0667f,
			0.5f, 0.5f, -0.5f, 0.2f, 0.1255f, 0.0667f,
			0.5f, 0.5f, -0.5f, 0.2f, 0.1255f, 0.0667f,
			0.5f, 0.5f, 0.5f, 0.2f, 0.1255f, 0.0667f,
			0.5f, -0.5f, 0.5f, 0.2f, 0.1255f, 0.0667f,

			-0.5f, 0.5f, 0.5f, 0.2f, 0.1255f, 0.0667f,
			-0.5f, 0.5f, -0.5f, 0.2f, 0.1255f, 0.0667f,
			-0.5f, -0.5f, -0.5f, 0.2f, 0.1255f, 0.0667f,
			-0.5f, -0.5f, -0.5f, 0.2f, 0.1255f, 0.0667f,
			-0.5f, -0.5f, 0.5f, 0.2f, 0.1255f, 0.0667f,
			-0.5f, 0.5f, 0.5f, 0.2f, 0.1255f, 0.0667f,

			-0.5f, -0.5f, -0.5f, 0.2f, 0.1255f, 0.0667f,
			0.5f, -0.5f, -0.5f, 0.2f, 0.1255f, 0.0667f,
			0.5f, -0.5f, 0.5f, 0.2f, 0.1255f, 0.0667f,
			0.5f, -0.5f, 0.5f, 0.2f, 0.1255f, 0.0667f,
			-0.5f, -0.5f, 0.5f, 0.2f, 0.1255f, 0.0667f,
			-0.5f, -0.5f, -0.5f, 0.2f, 0.1255f, 0.0667f,

			-0.5f, 0.5f, -0.5f, 0.2f, 0.1255f, 0.0667f,
			0.5f, 0.5f, -0.5f, 0.2f, 0.1255f, 0.0667f,
			0.5f, 0.5f, 0.5f, 0.2f, 0.1255f, 0.0667f,
			0.5f, 0.5f, 0.5f, 0.2f, 0.1255f, 0.0667f,
			-0.5f, 0.5f, 0.5f, 0.2f, 0.1255f, 0.0667f,
			-0.5f, 0.5f, -0.5f, 0.2f, 0.1255f, 0.0667f,

			//Color lengua
			-0.5f, -0.5f, 0.5f, 0.851f, 0.5882f, 0.6157f,//Front
			0.5f, -0.5f, 0.5f, 0.851f, 0.5882f, 0.6157f,
			0.5f, 0.5f, 0.5f, 0.851f, 0.5882f, 0.6157f,
			0.5f, 0.5f, 0.5f, 0.851f, 0.5882f, 0.6157f,
			-0.5f, 0.5f, 0.5f, 0.851f, 0.5882f, 0.6157f,
			-0.5f, -0.5f, 0.5f, 0.851f, 0.5882f, 0.6157f,

			-0.5f, -0.5f, -0.5f, 0.851f, 0.5882f, 0.6157f,//Back
			0.5f, -0.5f, -0.5f, 0.851f, 0.5882f, 0.6157f,
			0.5f, 0.5f, -0.5f, 0.851f, 0.5882f, 0.6157f,
			0.5f, 0.5f, -0.5f, 0.851f, 0.5882f, 0.6157f,
			-0.5f, 0.5f, -0.5f, 0.851f, 0.5882f, 0.6157f,
			-0.5f, -0.5f, -0.5f, 0.851f, 0.5882f, 0.6157f,

			0.5f, -0.5f, 0.5f, 0.851f, 0.5882f, 0.6157f,
			0.5f, -0.5f, -0.5f, 0.851f, 0.5882f, 0.6157f,
			0.5f, 0.5f, -0.5f, 0.851f, 0.5882f, 0.6157f,
			0.5f, 0.5f, -0.5f, 0.851f, 0.5882f, 0.6157f,
			0.5f, 0.5f, 0.5f, 0.851f, 0.5882f, 0.6157f,
			0.5f, -0.5f, 0.5f, 0.851f, 0.5882f, 0.6157f,

			-0.5f, 0.5f, 0.5f, 0.851f, 0.5882f, 0.6157f,
			-0.5f, 0.5f, -0.5f, 0.851f, 0.5882f, 0.6157f,
			-0.5f, -0.5f, -0.5f, 0.851f, 0.5882f, 0.6157f,
			-0.5f, -0.5f, -0.5f, 0.851f, 0.5882f, 0.6157f,
			-0.5f, -0.5f, 0.5f, 0.851f, 0.5882f, 0.6157f,
			-0.5f, 0.5f, 0.5f, 0.851f, 0.5882f, 0.6157f,

			-0.5f, -0.5f, -0.5f, 0.851f, 0.5882f, 0.6157f,
			0.5f, -0.5f, -0.5f, 0.851f, 0.5882f, 0.6157f,
			0.5f, -0.5f, 0.5f, 0.851f, 0.5882f, 0.6157f,
			0.5f, -0.5f, 0.5f, 0.851f, 0.5882f, 0.6157f,
			-0.5f, -0.5f, 0.5f, 0.851f, 0.5882f, 0.6157f,
			-0.5f, -0.5f, -0.5f, 0.851f, 0.5882f, 0.6157f,

			-0.5f, 0.5f, -0.5f, 0.851f, 0.5882f, 0.6157f,
			0.5f, 0.5f, -0.5f, 0.851f, 0.5882f, 0.6157f,
			0.5f, 0.5f, 0.5f, 0.851f, 0.5882f, 0.6157f,
			0.5f, 0.5f, 0.5f, 0.851f, 0.5882f, 0.6157f,
			-0.5f, 0.5f, 0.5f, 0.851f, 0.5882f, 0.6157f,
			-0.5f, 0.5f, -0.5f, 0.851f, 0.5882f, 0.6157f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{

		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.149f, 0.9059f, 0.7765f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);

		//Modificamos la matriz de vista por Inputs(window)
		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		glBindVertexArray(VAO);
		//cuerpo de Eevee
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Cara de Eevee
		model = glm::mat4(1);//Reseteo de Matriz borramos las transformadas aplicadas
		model = glm::translate(model, glm::vec3(-0.8f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//orejas de Eevee
		model = glm::mat4(1);//Reseteo de Matriz borramos las transformadas aplicadas
		model = glm::translate(model, glm::vec3(-0.8f, 1.5f, -0.5f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 1.0f));
		model = glm::rotate(model, glm::radians(-35.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::translate(model, glm::vec3(0.0f, -0.7f, 0.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 36);

		model = glm::translate(model, glm::vec3(0.0f, 0.7f, -1.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 36);

		//Colita de Eeeve
		model = glm::mat4(1);//Reseteo de Matriz borramos las transformadas aplicadas
		model = glm::translate(model, glm::vec3(1.2f, 0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
		model = glm::rotate(model, glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Pies de eevee
		model = glm::mat4(1);//Reseteo de Matriz borramos las transformadas aplicadas
		model = glm::translate(model, glm::vec3(0.9f,-0.7f, 0.3f));
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.3f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -8.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::translate(model, glm::vec3(-2.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::translate(model, glm::vec3(0.0f, -0.3f, -0.8f));
		model = glm::scale(model, glm::vec3(1.0f, 0.4f, 0.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 10.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::translate(model, glm::vec3(-2.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//Punta de la colita de Eeeve
		model = glm::mat4(1);//Reseteo de Matriz borramos las transformadas aplicadas
		model = glm::translate(model, glm::vec3(1.45f, 1.2f, 0.0f));
		model = glm::scale(model, glm::vec3(0.22f,-0.1f, 0.2f));
		model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 36);

		//cuello de Eeeve
		model = glm::mat4(1);//Reseteo de Matriz borramos las transformadas aplicadas
		model = glm::translate(model, glm::vec3(-1.25f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);

		model = glm::mat4(1);//Reseteo de Matriz borramos las transformadas aplicadas
		model = glm::translate(model, glm::vec3(-0.9f, 0.2f, 0.7f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.09f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 36);

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -15.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 36);

		model = glm::mat4(1);//Reseteo de Matriz borramos las transformadas aplicadas
		model = glm::translate(model, glm::vec3(-0.3f, 0.6f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.35f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);


		//Ojos de eevee
		model = glm::mat4(1);//Reseteo de Matriz borramos las transformadas aplicadas
		model = glm::translate(model, glm::vec3(-1.3f, 1.1f, -0.25f));
		model = glm::scale(model, glm::vec3(0.2f, 0.3f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 36);

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 2.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 36);

		model = glm::translate(model, glm::vec3(-0.5f, 0.3f, 0.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.06f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -24.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);

		//nariz eevee
		model = glm::mat4(1);//Reseteo de Matriz borramos las transformadas aplicadas
		model = glm::translate(model, glm::vec3(-1.3f, 0.9f, 0.0));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 36);

		//lengua eevee
		model = glm::mat4(1);//Reseteo de Matriz borramos las transformadas aplicadas
		model = glm::translate(model, glm::vec3(-1.3f, 0.7f, 0.0));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 36);

		model = glm::translate(model, glm::vec3(-0.2f, -0.25f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.4f, 0.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 144, 36);

		glBindVertexArray(0);
		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.01f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.01f;
	 if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		 movY += 0.01f;
	 if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		 movY -= 0.01f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.01f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.01f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.1f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.1f;
 }


