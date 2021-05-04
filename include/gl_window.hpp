/*
 *
 *  gl_window.hpp
 *  Header file for loading window and error handling
 *
 */

#pragma once

#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

GLFWwindow * WindowInit(const GLint width, const GLint height, const char * window_title, const GLint msaa_value, const GLint resizable);