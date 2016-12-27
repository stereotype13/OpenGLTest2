#include <iostream>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "graphics/box.h"
#include "graphics/rectangle.h"
#include "utils/clock.h"
#include "graphics/openglrenderer.h"

#define LOG(x) std::cout << x << std::endl;

unsigned int windowHeight = 480;
unsigned int windowWidth = 640;

VR::OpenGLRenderer* pRenderer = NULL;
// Callback function to resize the window and set the viewport to the correct size
void resizeWindow(GLFWwindow *window, GLsizei newWidth, GLsizei newHeight)
{
	

	// Keep track of the new width and height of the window
	windowWidth = float(newWidth);
	windowHeight = float(newHeight);

	// Recalculate the projection matrix
	VR::math::mat4 projectionMatrix = VR::math::mat4::Perspective(90.0f, windowWidth / windowHeight, 0.1f, 100.0f);

	// Viewport is the entire window
	glViewport(0, 0, windowWidth, windowHeight);

	if (pRenderer == NULL)
		return;

	pRenderer->setPerspectiveMatrix(projectionMatrix);
}


int main() {

    
    GLFWwindow* window;
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
#ifdef _OS_X_
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    /* Create a windowed mode window and its OpenGL context */

    window = glfwCreateWindow(windowWidth, windowHeight, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    /* Loop until the user closes the window */
      
    glewInit();

	glEnable(GL_TEXTURE_CUBE_MAP);

	glViewport(0, 0, GLsizei(windowWidth), GLsizei(windowHeight));
	
	VR::OpenGLRenderer renderer;
	pRenderer = &renderer;

	glfwSetWindowSizeCallback(window, resizeWindow);

	VR::utils::Clock clock;
	clock.addListener(&renderer);

	//Renderer will free memory on the heap.
	renderer.addRenderable(new VR::Box());
    
	clock.init();
    while (!glfwWindowShouldClose(window))
    {
        
        /* Render here */
		clock.tick();
		
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        
        /* Poll for and process events */
        glfwPollEvents();
    }
    
    
    glfwTerminate();
    return 0;
}