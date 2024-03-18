#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;

int main() {
	glfwInit();
	//Verificación de compatibilidad
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 1", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);

	//Verificación de errores de creacion  ventana
	if (window == NULL)
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

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	Shader OurShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {

		//Vertices para mostrar los ejes X y Y
		-0.99f, 0.0f,   0.0f,		1.0f,1.0f,1.0f,  // A 0
		0.99f,  0.0f,   0.0f,		1.0f,1.0f,1.0f,  // B 1
		0.0f,   -0.99f, 0.0f,		1.0f,1.0f,1.0f,  // C 2
		0.0f,   0.99f,  0.0f,		1.0f,1.0f,1.0f,  // D 3

		// Vertices para la espada

		-0.55f,0.9f,0.0f,			0.498f,0.1451f,0.898, //H 4
		-0.45f,0.9f,0.0f,			0.498f,0.1451f,0.898, //G 5
		-0.55f,0.8f,0.0f,			0.498f,0.1451f,0.898, //E 6
		-0.45f,0.8f,0.0f,			0.498f,0.1451f,0.898, //K 7

		-0.45f,0.8f,0.0f,			0.898f,0.1451f,0.7725, //K 8
		-0.63f,0.8f,0.0f,			0.898f,0.1451f,0.7725, //I 9
		-0.55f,0.7f,0.0f,			0.898f,0.1451f,0.7725, //J 10
		-0.37f,0.7f,0.0f,			0.898f,0.1451f,0.7725, //L 11

		-0.45f,0.8f,0.0f,			0.9098f,0.8353f,0.1137, //K 12
		-0.37f,0.7f,0.0f,			0.9098f,0.8353f,0.1137, //L 13
		-0.29f,0.8f,0.0f,			0.9098f,0.8353f,0.1137, //N 14

		-0.63f,0.8f,0.0f,			0.9098f,0.4745f,0.1137, //I 15
		-0.71f,0.7f,0.0f,			0.9098f,0.4745f,0.1137, //M 16
		-0.55f,0.7f,0.0f,			0.9098f,0.4745f,0.1137, //J 17

		-0.58f,0.7f,0.0f,			0.5961f,0.9098f,0.1137, //O 18
		-0.42f,0.7f,0.0f,			0.5961f,0.9098f,0.1137, //P 19
		-0.58f,0.5f,0.0f,			0.5961f,0.9098f,0.1137, //Q 20

		-0.42f,0.7f,0.0f,			0.1137f,0.6941f,0.9098, //P 21
		-0.58f,0.5f,0.0f,			0.1137f,0.6941f,0.9098, //Q 22
		-0.42f,0.3f,0.0f,			0.1137f,0.6941f,0.9098, //R 23

		-0.58f,0.5f,0.0f,			0.5647f,0.051f,0.4549, //Q 24
		-0.42f,0.3f,0.0f,			0.5647f,0.051f,0.4549, //R 25
		-0.58f,0.1f,0.0f,			0.5647f,0.051f,0.4549, //S 26

		//vertices para el Corazon
		0.38f,-0.33f,0.0f,			0.1137f,0.6941f,0.9098, //T 27
		0.2f,-0.5f,0.0f,			0.1137f,0.6941f,0.9098, //U 28
		0.57f,-0.5f,0.0f,			0.1137f,0.6941f,0.9098, //V 29

		0.61f,-0.33f,0.0f,			0.9098f,0.4745f,0.1137, //W 30
		0.48f,-0.42f,0.0f,			0.9098f,0.4745f,0.1137, //B1 31
		0.72f,-0.42f,0.0f,			0.9098f,0.4745f,0.1137, //A1 32

		0.48f,-0.42f,0.0f,			0.898f,0.1451f,0.7725, //B1 33
		0.72f,-0.42f,0.0f,			0.898f,0.1451f,0.7725, //A1 34
		0.57f,-0.5f,0.0f,			0.898f,0.1451f,0.7725, //V 35
		0.80f,-0.5f,0.0f,			0.898f,0.1451f,0.7725, //D1 36

		0.80f,-0.5f,0.0f,			0.5647f,0.051f,0.4549, //D1 37
		0.4f,-0.5f,0.0f,			0.5647f,0.051f,0.4549, //C1 38
		0.6f,-0.7f,0.0f,			0.5647f,0.051f,0.4549, //E1 39

		0.2f,-0.5f,0.0f,			0.5961f,0.9098f,0.1137, //U 40
		0.4f,-0.5f,0.0f,			0.5961f,0.9098f,0.1137, //C1 41
		0.4f,-0.7f,0.0f,			0.5961f,0.9098f,0.1137, //G1 42

		0.4f,-0.5f,0.0f,			0.9098f,0.8353f,0.1137, //C1 43
		0.4f,-0.7f,0.0f,			0.9098f,0.8353f,0.1137, //G1 44
		0.5f,-0.6f,0.0f,			0.9098f,0.8353f,0.1137, //H1 45

		0.4f,-0.7f,0.0f,			0.498f,0.1451f,0.898, //G1 46
		0.5f,-0.6f,0.0f,			0.498f,0.1451f,0.898, //H1 47
		0.6f,-0.7f,0.0f,			0.498f,0.1451f,0.898, //E1 48
		0.5f,-0.8f,0.0f,			0.498f,0.1451f,0.898, //J1 49

	};

	unsigned int indices[] = {  // note that we start from 0!
		46,47,48,   // Mitad Trapecio 
		49,48,46
	};


	//Generan los buffers y el arreglo de objetos
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Modo de dibujo estatico

	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Desenlazamos de memoria el VAO



	while (!glfwWindowShouldClose(window))
	{
		// Checa si un eveneto ha sido activado y manda a llamar al callback correspondiente
		glfwPollEvents();
		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Dibujar aquí
		OurShader.Use();
		glBindVertexArray(VAO);
		glPointSize(10);

		 //Figura 1 Espada
		glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
		glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
		glDrawArrays(GL_TRIANGLE_FAN, 12, 3);
		glDrawArrays(GL_TRIANGLE_FAN, 15, 3);
		glDrawArrays(GL_TRIANGLE_FAN, 18, 3);
		glDrawArrays(GL_TRIANGLE_FAN, 21, 3);
		glDrawArrays(GL_TRIANGLE_FAN, 24, 3);
		
		////Figura 2 Corazon
		//                           donde empieza la memoria, # de elemntos a tomar
		glDrawArrays(GL_TRIANGLE_FAN, 27, 3);
		glDrawArrays(GL_TRIANGLE_FAN, 30, 3);
		glDrawArrays(GL_TRIANGLE_STRIP, 33, 4);
		glDrawArrays(GL_TRIANGLE_FAN, 37, 3);
		glDrawArrays(GL_TRIANGLE_FAN, 40, 3);
		glDrawArrays(GL_TRIANGLE_FAN, 43, 3);
		//                        #de datos a tomar              //desde donde inicia la memoria
		glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, (GLvoid*)(0 * sizeof(GLfloat)));
		
		//Lineas de Separación

		glDrawArrays(GL_LINES, 0, 2); //Eje X
		glDrawArrays(GL_LINES, 2, 2); //Eje Y

		glBindVertexArray(0);
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}