// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );


// Camera
Camera camera( glm::vec3( 0.0f, 0.0f, 3.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

//Constantes para no andar cambiando muchas lineas
const float MAXIMA_TRASLACION = 0.6f;
const float MINIMA_TRASLACION = -0.6f;
const float MAXIMA_ROTACION = 55;
const float MINIMA_ROTACION = -55;
//Variables para controlar la rotacion y traslacion del pez
bool animacion_tile = false;
bool animacion_body = false;
float rot = 0.0f;
float tras_body = 0.0f;



int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Adaptacion,carga de modelos y camara sintetica", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    // Setup and compile our shaders
    Shader shader( "Shaders/modelLoading.vs", "Shaders/modelLoading.frag" );
    
    // Load models
    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    
    Model tileFish((char*)"myfish/tileFish.obj");
    Model bodyFish((char*)"myfish/bodyFish.obj");

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.051f, 0.702f, 0.9451f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model
        glm::mat4 model(1);

        //Pez avanza a lo largo del Eje Z
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, glfwGetTime()));

        //Pez se mueve de arriba hacia abajo
        if (tras_body <= MAXIMA_TRASLACION) {
            // Si tras_body es menor-igual al valor maximo , el pez se mueve hacia arriba
            model = glm::translate(model, glm::vec3(0.0f, tras_body, 0.0f));
        }
        if (tras_body >= MINIMA_TRASLACION) {
            // Si tras_body es mayor-igual al valor maximo , el pez se mueve hacia abajo
            model = glm::translate(model, glm::vec3(0.0f, tras_body, 0.0f));
        }
        
        //Rotamos la cola del pez para su movimiento respecto al eje Y
        model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, glfwGetTime(), 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        tileFish.Draw(shader);

        //Dibujamos el cuerpo del pez.
        model = glm::mat4(1);
        //Pez avanza a lo largo del Eje Z
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, glfwGetTime()));

        if (tras_body <= MAXIMA_TRASLACION) {
            // Si tras_body es menor-igual al valor maximo , el pez se mueve hacia arriba
            model = glm::translate(model, glm::vec3(0.0f, tras_body, 0.0f));
        }
        if (tras_body >= MINIMA_TRASLACION) {
            // Si tras_body es mayor-igual al valor maximo , el pez se mueve hacia abajo
            model = glm::translate(model, glm::vec3(0.0f, tras_body, 0.0f));
        }

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        bodyFish.Draw(shader);
        
        // Swap the buffers
        glfwSwapBuffers( window );
    }
    
    glfwTerminate( );
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }

    //Animación para mover la cola del Pez
    if (animacion_tile) {// Si la animación está activada, incrementa gradualmente el ángulo de rotación hasta 45 grados
        if (rot <= MAXIMA_ROTACION) {
            rot += 0.5f;
        } else {// Si el ángulo alcanza 45 grados, cambia el estado de la animación a false
            animacion_tile = false;
        }
    } else {// Si la animación está desactivada, disminuye gradualmente el ángulo de rotación hasta -45 grados
        if (rot >= MINIMA_ROTACION) {
            rot -= 0.5f;
        } else {// Si el ángulo alcanza -45 grados, cambia el estado de la animación a true
            animacion_tile = true;
        }
    }

    // Animación para subir y bajar el pez
    if (animacion_body) {
        if (tras_body <= MAXIMA_TRASLACION) { //Mientras tras_body sea menor-igual a valormaximo
            tras_body += 0.001f; //Incrementamos tras_body
        } else {// Si tras_body alcanza valor maximo, cambia el estado de la animación a false
            animacion_body = false;
        }
    } else {// Si la animación está desactivada, disminuye gradualmente tras_body
        if (tras_body >=MINIMA_TRASLACION) { //Mientras tras_body sea mayor-igual a valorminimo
            tras_body -= 0.001f;
        } else {// Si tras_body alcanza valor minimo , cambia el estado de la animación a true
            animacion_body = true;
        }
    }
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}

