#include <iostream>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "graphics/box.h"
#include "graphics/rectangle.h"
#include "utils/clock.h"
#include "graphics/openglrenderer.h"

#define LOG(x) std::cout << x << std::endl;


class Buffer {

};

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
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    /* Loop until the user closes the window */
      
    glewInit();
	
	VR::OpenGLRenderer renderer;
	VR::utils::Clock clock;

	clock.addListener(&renderer);
	renderer.addRenderable(new VR::Box());
    
    
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