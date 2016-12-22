#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <cmath>
#include <vector>
#include "math/vec3.h"
#include "math/vec4.h"
#include "math/mat4.h"
#include "math/utils.h"
#include "graphics/box.h"
#include "graphics/rectangle.h"

#define LOG(x) std::cout << x << std::endl;

typedef std::chrono::high_resolution_clock HighResolutionClock;
typedef std::chrono::duration<float, std::milli> milliseconds_type;

std::string loadSource(const std::string& path) {
    FILE* file;
    
    size_t fileLength, readLength;
    file = fopen(path.c_str(), "r");
    if (!file) {
        LOG("Error: Shader source file not found.");
        return 0;
    }
    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0, SEEK_SET);
    std::string buffer(fileLength, 0);
    
    readLength = fread(&buffer[0], 1, fileLength, file);
    buffer[fileLength] = '\0';
    fclose(file);
    
    return buffer;
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
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    /* Loop until the user closes the window */
    
    
    
    //VR::Rectangle rectangle(-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, VR::math::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    VR::Box box;
    
    GLuint VAO;
    GLuint VBO[2];
    
    glewInit();
    
    
    //begin compiling shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexShaderSource = loadSource("/Users/stereotype13/Documents/OpenGLTest/OpenGLTest/OpenGLTest/shaders/vertexShader.vertex");
    const char* vertexShaderSourcCString = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, (const GLchar**)&vertexShaderSourcCString, 0);
    glCompileShader(vertexShader);
    
    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        char* version = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
        printf("Supported GLSL version is %s.\n", version);
        int maxLength;
        
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
        
        char* vertexInfoLog = (char*)malloc(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, vertexInfoLog);
        
        LOG(vertexInfoLog);
        
        free(vertexInfoLog);
        
        return false;
        
    }
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShaderSource = loadSource("/Users/stereotype13/Documents/OpenGLTest/OpenGLTest/OpenGLTest/shaders/fragmentShader.fragment");
    const char* fragmentShaderCString = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentShaderCString, 0);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        int maxLength;
        
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
        
        char* fragmentInfoLog = (char*)malloc(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, fragmentInfoLog);
        
        LOG(fragmentInfoLog);
        
        free(fragmentInfoLog);
        
        return false;
        
    }
    
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    
    //glBindAttribLocation(shaderProgram, 0, "position");
    //glBindAttribLocation(shaderProgram, 1, "color");
    
    glLinkProgram(shaderProgram);
    //end compiling shaders
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(2, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    
    //Allocate enough space on video card for x verticies, each with 3 position and 4 color (total 7) values.
    glBufferData(GL_ARRAY_BUFFER, box.getVertexCount() * 7 * sizeof(float), NULL, GL_STATIC_DRAW);
    
    //position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (GLvoid*)0);
    
    //color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (GLvoid*)((float*)NULL + 3));
    
    //Not the best way, but good enough for now. Want to do it in the same loop.
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, box.getIndexCount() * sizeof(GLuint), NULL, GL_STATIC_DRAW);
    
    std::chrono::time_point<HighResolutionClock> startTimePoint;
    startTimePoint = HighResolutionClock::now();
    float ellapsedTime = 0.0f;
    float totalEllapsedTime = 0.0f;
    
    
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    
    while (!glfwWindowShouldClose(window))
    {
        
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);
        
        
        ellapsedTime = std::chrono::duration_cast<milliseconds_type>(HighResolutionClock::now() - startTimePoint).count() / 1000.0f;
        startTimePoint = HighResolutionClock::now();
        totalEllapsedTime += ellapsedTime;
        if (totalEllapsedTime > 2 * PI)
            totalEllapsedTime -= 2 * PI;
        
        //set the projection matrix
        VR::math::mat4 perspectiveMatrix = VR::math::mat4::Perspective(90.0f, 4.0f/3.0f, 0.1f, 100.0f);
        GLuint perspectiveMatrixID = glGetUniformLocation(shaderProgram, "perspectiveMatrix");
        if (perspectiveMatrixID != -1) {
            glUniformMatrix4fv(perspectiveMatrixID, 1, GL_TRUE, (const float*)&perspectiveMatrix);
        }
        
        //set the view matrix
        VR::math::mat4 viewMatrix = VR::math::mat4::LookAt(VR::math::vec3(0.0f, 0.0f, -1.0f), VR::math::vec3(0.0f, 0.0f, 0.0f), VR::math::vec3(0.0f, 1.0f, 0.0f));
        GLuint viewMatrixID = glGetUniformLocation(shaderProgram, "viewMatrix");
        if (viewMatrixID != -1) {
            glUniformMatrix4fv(viewMatrixID, 1, GL_TRUE, (const float*)&viewMatrix);
        }
        
        //map buffers
        float* vertexBuffer = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        //VR::math::mat4 translationMatrix = VR::math::mat4::Translation(VR::math::vec3(0.5 * std::sin(2 * totalEllapsedTime), 0.0f, 0.0f));
        VR::math::mat4 rotationMatrixX = VR::math::mat4::RotationX(totalEllapsedTime);
        VR::math::mat4 rotationMatrixY = VR::math::mat4::RotationY(totalEllapsedTime);
        int vertexCount = 0;
        for (auto& vertex : box.getVertices()) {
            VR::math::vec3 position = (rotationMatrixY * (rotationMatrixX * vertex->Position));
            
            vertexBuffer[0 + vertexCount] = position[0];
            vertexBuffer[1 + vertexCount] = position[1];
            vertexBuffer[2 + vertexCount] = position[2];
            vertexBuffer[3 + vertexCount] = vertex->Color[0];
            vertexBuffer[4 + vertexCount] = vertex->Color[1];
            vertexBuffer[5 + vertexCount] = vertex->Color[2];
            vertexBuffer[6 + vertexCount] = vertex->Color[3];
            vertexBuffer += 7;
        }
        glUnmapBuffer(GL_ARRAY_BUFFER);
        
        GLuint* indexBuffer = (GLuint*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
        for (auto& index : box.getIndices()) {
            *indexBuffer = index;
            ++indexBuffer;
        }
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
        
        glDrawElements(GL_TRIANGLES, box.getIndexCount(), GL_UNSIGNED_INT, 0);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        
        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glDeleteBuffers(1, &VBO[0]);
    glDeleteBuffers(1, &VBO[1]);
    glDeleteShader(shaderProgram);
    glDeleteVertexArrays(1, &VAO);
    glfwTerminate();
    return 0;
}