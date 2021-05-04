/*
 *
 *  gl_window.cpp
 *
 */

//C++ pack
#include <iostream>
#include <fstream> 
#include <vector>
#include <sstream>

//OpenGL
#include "GL/glew.h"
#include "GL/gl.h"
#include "GL/glut.h"
#include "GLFW/glfw3.h" 

GLFWwindow * WindowInit(const GLint width, const GLint height, const char * window_title, const GLint msaa_value, const GLint resizable)
{
    if (!glfwInit())
    {
        std::cerr << "\x1b[31merror:\x1b[0m glfwInit()" << std::endl;
        return NULL;
    }

    glfwWindowHint(GLFW_SAMPLES, msaa_value);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, resizable);

    GLFWwindow * window = glfwCreateWindow(width, height, window_title, NULL, NULL);

    if (window == NULL)
    {
        std::cerr << "\x1b[31merror:\x1b[0m Unable to open GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) 
    {
        std::cerr << "\x1b[31merror:\x1b[0m Unable to initialize GLEW" << std::endl;
        return NULL;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    return window;
}

