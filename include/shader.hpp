/*
 *
 *  shader.hpp
 *  Class for working with shaders (Vertex + Fragment).
 *
 */

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include "GL/glew.h"
#include "glm/glm.hpp"

class Shader
{
    private:
        GLuint program_id;

        std::string FileDataLoader(const char * file_path);
        void ShaderErrChecker(GLuint shader_id);
        void CompileShader(GLuint shader_id, const char * source_pointer);
        void ProgramErrChecker(GLuint shader_id);
        GLuint LinkShader(GLuint vertex_shader_id, GLuint fragment_shader_id);
        GLuint CreateShader(const GLuint shader_type, const GLchar * shader_file_path);

    public:
        Shader(const GLchar * vertex_file_path, const GLchar * fragment_file_path)
        {
            GLuint VertexShaderID   = CreateShader(GL_VERTEX_SHADER, vertex_file_path);
            GLuint FragmentShaderID = CreateShader(GL_FRAGMENT_SHADER, fragment_file_path);
            
            program_id = LinkShader(VertexShaderID, FragmentShaderID);
            
            glDeleteShader(VertexShaderID);
            glDeleteShader(FragmentShaderID);
        }

        void Active();
        
        void SendIntValue  (const GLchar * variable_name, GLint   value);
        void SendFloatValue(const GLchar * variable_name, GLfloat value);
        
        void SendVec2(const GLchar * variable_name, const glm::vec2 & vector);
        void SendVec3(const GLchar * variable_name, const glm::vec3 & vector);
        void SendVec4(const GLchar * variable_name, const glm::vec4 & vector);
        
        void SendMat2(const GLchar * variable_name, const glm::mat2 & matrix);
        void SendMat3(const GLchar * variable_name, const glm::mat3 & matrix);
        void SendMat4(const GLchar * variable_name, const glm::mat4 & matrix);
};

std::string Shader::FileDataLoader(const char * file_path)
{
    std::ifstream file_stream(file_path, std::ios::in);
    std::string buffer = "";

    if (file_stream.is_open()) 
    {
        std::stringstream ss; 
        ss << file_stream.rdbuf();
        buffer = ss.str();
        file_stream.close();
    }
    else
    {
        std::cerr << "\x1b[31m" << "error: " << "\x1b[0m" << "loading file data by path " << "\x1b[33m" << file_path << "\x1b[0m" << std::endl;
    }
    
    return buffer;
}

void Shader::ShaderErrChecker(GLuint shader_id)
{
    GLint compile_status = GL_FALSE;
    int info_log_length  = 0;

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    
    if (info_log_length)
    {
        char * error_message = new char[info_log_length];
        glGetShaderInfoLog(shader_id, info_log_length, NULL, error_message);
        std::cerr << "\x1b[31m" << error_message << " \x1b[0m" << std::endl;
        delete [] error_message;
    }
    
}

void Shader::CompileShader(GLuint shader_id, const char * source_pointer)
{
    glShaderSource(shader_id, GL_TRUE, &source_pointer, NULL);
    glCompileShader(shader_id);
    ShaderErrChecker(shader_id);
}

void Shader::ProgramErrChecker(GLuint shader_id)
{
    GLint compile_status = GL_FALSE;
    int info_log_length  = 0;

    glGetProgramiv(shader_id, GL_COMPILE_STATUS,  &compile_status);
    glGetProgramiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    
    if (info_log_length)
    {
        char * error_message = new char[info_log_length];
        glGetProgramInfoLog(shader_id, info_log_length, NULL, error_message);
        std::cerr << "\x1b[31m" << error_message << " \x1b[0m" << std::endl;
        delete [] error_message;
    }
}

GLuint Shader::LinkShader(GLuint vertex_shader_id, GLuint fragment_shader_id)
{
    GLuint link_program_id = glCreateProgram();
    
    glAttachShader(link_program_id, vertex_shader_id);
    glAttachShader(link_program_id, fragment_shader_id);

    glLinkProgram(link_program_id);
    //ProgramErrChecker(link_program_id);

    return link_program_id;
}

GLuint Shader::CreateShader(const GLuint shader_type, const GLchar * shader_file_path)
{
    GLuint shader_id              = glCreateShader(shader_type);
    std::string shader_filedata   = FileDataLoader(shader_file_path);
    
    CompileShader(shader_id, shader_filedata.c_str());
    return shader_id;
}

void Shader::Active()
{
    glUseProgram(program_id);
}


void Shader::SendIntValue(const GLchar * variable_name, const GLint value)
{
    glUniform1i(glGetUniformLocation(program_id, variable_name), value);
}

void Shader::SendFloatValue(const GLchar * variable_name, const GLfloat value)
{
    glUniform1f(glGetUniformLocation(program_id, variable_name), value);
}
        
void Shader::SendVec2(const GLchar * variable_name, const glm::vec2 & vector)
{
    glUniform2fv(glGetUniformLocation(program_id, variable_name), 1, &vector[0]);
}

void Shader::SendVec3(const GLchar * variable_name, const glm::vec3 & vector)
{
    glUniform3fv(glGetUniformLocation(program_id, variable_name), 1, &vector[0]);
}

void Shader::SendVec4(const GLchar * variable_name, const glm::vec4 & vector)
{
    glUniform4fv(glGetUniformLocation(program_id, variable_name), 1, &vector[0]);
}
        
void Shader::SendMat2(const GLchar * variable_name, const glm::mat2 & matrix)
{
    glUniformMatrix2fv(glGetUniformLocation(program_id, variable_name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::SendMat3(const GLchar * variable_name, const glm::mat3 & matrix)
{
    glUniformMatrix3fv(glGetUniformLocation(program_id, variable_name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::SendMat4(const GLchar * variable_name, const glm::mat4 & matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(program_id, variable_name), 1, GL_FALSE, &matrix[0][0]);
}