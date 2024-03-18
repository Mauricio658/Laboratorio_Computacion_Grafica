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

		//Trapecio
		-0.72f,  0.61f, 0.0f,		0.8431f,0.2824f,0.1059f,  // D  0
		-0.29f,  0.61f, 0.0f,		0.8431f,0.2824f,0.1059f,  // C  1
		-0.89f,  0.2f,  0.0f,		0.8431f,0.2824f,0.1059f,  // A  2
		-0.12f,  0.2f,  0.0f,		0.8431f,0.2824f,0.1059f,  // B  3

		//Rombo
		0.16f,  0.49f, 0.0f,		0.0039f,0.8353f,0.9961f,  // E 4
		0.5f,   0.12f, 0.0f,		0.0039f,0.8353f,0.9961f,  // F 5
		0.5f,   0.84f, 0.0f,		0.0039f,0.8353f,0.9961f,  // H 6
		0.87f,  0.49f, 0.0f,		0.0039f,0.8353f,0.9961f,  // G 7

		//Pentagono
		-0.72f, -0.8f,  0.0f,		1.0f,0.1608f,0.5098f, // J 8
		-0.84f, -0.43f, 0.0f,		1.0f,0.1608f,0.5098f, // I 9
		-0.34f, -0.8f,  0.0f,		1.0f,0.1608f,0.5098f, // K 10
		-0.21f, -0.43f, 0.0f,		1.0f,0.1608f,0.5098f, // L 11
		-0.52f, -0.21f, 0.0f,		1.0f,0.1608f,0.5098f, // M 12

		//Rectangulo
		0.2f,  -0.1f,  0.0f,		0.898f,0.6118f,0.1451f,  //N 13
		0.73f, -0.1f,  0.0f,		0.898f,0.6118f,0.1451f,  //O 14
		0.2f,  -0.95f, 0.0f,		0.898f,0.6118f,0.1451f,  //Q 15
		0.73f, -0.95f, 0.0f,		0.898f,0.6118f,0.1451f,  //P 16

		//Vertices para mostrar los ejes X y Y
		-0.99f, 0.0f,   0.0f,		1.0f,1.0f,1.0f,  // X1 17
		0.99f,  0.0f,   0.0f,		1.0f,1.0f,1.0f,  // X2 18
		0.0f,   -0.99f, 0.0f,		1.0f,1.0f,1.0f,  // Y1 19
		0.0f,   0.99f,  0.0f,		1.0f,1.0f,1.0f,  // Y2 20

	};

	unsigned int indices[] = {  // note that we start from 0!
		0,1,2,   // Mitad Trapecio 
		4,5,6,   //Mitad Rombo
		8,9,10,  //Mitad Pentagono
		13,14,15 //Mitad Triangulo
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

		//Figura 1 Trapecio
		glDrawElements(GL_TRIANGLE_STRIP, 3, GL_UNSIGNED_INT, (GLvoid*)(0 * sizeof(GLfloat)));
		glDrawArrays(GL_LINE_LOOP, 1, 3); //tRABJA CON ARREGLO DE VERTICES
		
		//Figura 2 Rombo
		glDrawElements(GL_TRIANGLE_STRIP, 3, GL_UNSIGNED_INT, (GLvoid*)(3 * sizeof(GLfloat)));
		glDrawArrays(GL_LINE_LOOP, 5, 3);

		//Figura 3 Pentagono
		glDrawElements(GL_TRIANGLE_STRIP, 3, GL_UNSIGNED_INT, (GLvoid*)(6 * sizeof(GLfloat)));
		glDrawArrays(GL_LINE_LOOP, 9, 4);

		//Figura 4 Rectangulo
		glDrawElements(GL_TRIANGLE_STRIP, 3, GL_UNSIGNED_INT, (GLvoid*)(9 * sizeof(GLfloat)));
		glDrawArrays(GL_LINE_LOOP, 14, 3);

		//Lineas de Separación

		glDrawArrays(GL_LINES, 17, 2); //Eje X
		glDrawArrays(GL_LINES, 19, 2); //Eje Y

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