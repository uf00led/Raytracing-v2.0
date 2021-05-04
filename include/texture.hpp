/*
 *
 *  buffer_handling.hpp
 *  Header file for working with the buffer: creating vertex array,
 *  element object array, buffer array.
 *
 */

#pragma once

#include <iostream>
#include <vector>
#include "GL/glew.h"

GLuint LoadCubeMap(std::vector<std::string> cube_faces);
GLuint CreateVAO(const std::vector<GLfloat> & vertex_array, const std::vector<GLuint> & index_array, 
                 const GLint position_type, const GLint vector_dimension, const GLint frequency);
GLuint CreateVAO(const std::vector<GLfloat> & vertex_array, const GLint position_type, 
                 const GLint vector_dimension, const GLint frequency);