/*
 *
 *  buffer_handling.cpp
 *
 */

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <vector>
#include "GL/glew.h"
#include "stb_image.h"

GLuint CreateVAO(const std::vector<GLfloat> & vertex_array, const std::vector<GLuint> & index_array, const GLint position_type, const GLint vector_dimension, const GLint frequency)
{
    GLuint vertex_array_object, vertex_buffer_object, element_buffer_object;
 
    glGenVertexArrays(1, &vertex_array_object);
    glGenBuffers(1, &vertex_buffer_object);
    glGenBuffers(1, &element_buffer_object);

    glBindVertexArray(vertex_array_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, vertex_array.size() * sizeof(GLfloat), &vertex_array.front(), frequency);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_array.size() * sizeof(GLfloat), &index_array.front(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(position_type, vector_dimension, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &vertex_buffer_object);
    glDeleteBuffers(1, &element_buffer_object);

    return vertex_array_object;
}

GLuint CreateVAO(const std::vector<GLfloat> & vertex_array, const GLint position_type, const GLint vector_dimension, const GLint frequency)
{
    GLuint vertex_array_object, vertex_buffer_object;
 
    glGenVertexArrays(1, &vertex_array_object);
    glGenBuffers(1, &vertex_buffer_object);

    glBindVertexArray(vertex_array_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, vertex_array.size() * sizeof(GLfloat), &vertex_array.front(), frequency);
    
    glVertexAttribPointer(position_type, vector_dimension, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &vertex_buffer_object);

    return vertex_array_object;
}

// GLuint CreateTexture(const GLchar * image_path)
// {
//     GLuint texture_object;
//     glGenTextures(1, &texture_object);
//     glBindTexture(GL_TEXTURE_2D, texture_object);
    
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_REPEAT);	
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
//     GLint image_width, image_height, nrChannels;
//     unsigned char * image_data = stbi_load(image_path, &image_width, &image_height, &nrChannels, 0);

//     if (image_data)
//     {
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
//         glGenerateMipmap(GL_TEXTURE_2D);
//     }
//     else std::cerr << "\x1b[31m" << "error: " << "\x1b[0m" << "loading texture from " << "\x1b[33m" << image_path << "\x1b[0m" << std::endl;

//     stbi_image_free(image_data);

//     return texture_object;
// }

GLuint LoadCubeMap(std::vector<std::string> cube_faces)
{
    GLuint textureID;
    GLint  img_width, img_height, img_color_channels;
    
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    for (GLuint side_index = 0; side_index < cube_faces.size(); side_index++)
    {
        unsigned char * image_data = stbi_load(cube_faces[side_index].c_str(), 
                                              &img_width, &img_height, &img_color_channels, 0);
 
        if (image_data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + side_index, 0, GL_RGB, 
                         img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);       
            stbi_image_free(image_data);
        }
        else
        {
            std::cerr << "\x1b[31m" << "error: " << "\x1b[0m" << "Cubemap texture failed to load at path: " 
                                    << cube_faces[side_index] << "\nSTB_Reason: " << stbi_failure_reason() << std::endl;
            stbi_image_free(image_data);
        }
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R,     GL_CLAMP_TO_EDGE);

    return textureID;
}