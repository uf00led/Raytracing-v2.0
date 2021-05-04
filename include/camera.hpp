/*
 *
 *  camera.hpp
 *  Class for working with camera (keyboard + mouse moving)
 *
 */

#pragma once

#include <iostream>

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.inl"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_projection.inl"

class Camera
{
    private:
        GLFWwindow * camera_window;

        glm::vec2    camera_angles;
        glm::vec3    camera_pos;
        glm::vec3    camera_front, camera_right, camera_up;

        GLint        window_size_x, window_size_y;
        GLfloat      mov_speed, sensitivity, FOV;

        void MouseCallback();
        void KeyboardCallback();

    public:
        Camera()  = delete;
        ~Camera() = default;    

        Camera(GLFWwindow * window, const GLfloat speed, const GLfloat field_of_view, const GLfloat m_sens, const glm::vec3 position) :
               camera_window(window), mov_speed(speed), FOV(field_of_view), sensitivity(m_sens), camera_pos(position)
        {   
            glfwGetWindowSize(camera_window, &window_size_x, &window_size_y);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            camera_angles = glm::vec2(0.0);
        }
        
        void MovCallback();
        glm::mat4 GetViewMatrix();
        glm::mat4 GetProjectionMatrix();
};

void Camera::MouseCallback()
{
    GLdouble x_mouse_pos, y_mouse_pos;
    glfwGetCursorPos(camera_window, &x_mouse_pos, &y_mouse_pos);
    
    glfwSetCursorPos(camera_window, window_size_x / 2, window_size_y / 2);

    camera_angles.x -= (window_size_x / 2 - x_mouse_pos) * sensitivity;
    camera_angles.y += (window_size_y / 2 - y_mouse_pos) * sensitivity;

    std::cout << camera_angles.x << "   " << camera_angles.y << std::endl;

    if (camera_angles.y >  89.0) camera_angles.y =  89.0;
    if (camera_angles.y < -89.0) camera_angles.y = -89.0;

    camera_front = glm::normalize(glm::vec3(cos(glm::radians(camera_angles.x)) * cos(glm::radians(camera_angles.y)),
                                            sin(glm::radians(camera_angles.y)),
                                            sin(glm::radians(camera_angles.x)) * cos(glm::radians(camera_angles.y))));
        
    camera_right = glm::normalize(glm::cross(glm::vec3(0.0, 1.0, 0.0), camera_front));
    camera_up    = glm::normalize(glm::cross(camera_front, camera_right));
}

void Camera::KeyboardCallback()
{
    if (glfwGetKey(camera_window, GLFW_KEY_W)          == GLFW_PRESS) camera_pos += camera_front * mov_speed;
    if (glfwGetKey(camera_window, GLFW_KEY_A)          == GLFW_PRESS) camera_pos += camera_right * mov_speed;
    if (glfwGetKey(camera_window, GLFW_KEY_S)          == GLFW_PRESS) camera_pos -= camera_front * mov_speed;
    if (glfwGetKey(camera_window, GLFW_KEY_D)          == GLFW_PRESS) camera_pos -= camera_right * mov_speed;
            
    if (glfwGetKey(camera_window, GLFW_KEY_SPACE)      == GLFW_PRESS) camera_pos += camera_up    * mov_speed;
    if (glfwGetKey(camera_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) camera_pos -= camera_up    * mov_speed;
}

void Camera::MovCallback()
{
    MouseCallback();
    KeyboardCallback();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return glm::perspective(glm::radians(FOV), (GLfloat)window_size_x / (GLfloat)window_size_y, 0.01f, 100.0f);
}