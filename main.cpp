#include "include/gl_window.hpp"
#include "include/texture.hpp"
#include "include/shader.hpp"
#include "include/camera.hpp"

unsigned int errors = 0;

void ERROR()
{
    errors++;
    std::cout << "ERROR #" << errors << " oops: " << glGetError() << std::endl;
}

int main()
{
    GLFWwindow * window = WindowInit(1024, 768, "Retracing 3DDD", 4, GL_FALSE);    
    if (window == NULL) return -1;

    std::vector<std::string> cube_faces = 
    {
        "textures/skybox/right.png", 
        "textures/skybox/left.png", 
        "textures/skybox/top.png",
        "textures/skybox/bottom.png",
        "textures/skybox/front.png", 
        "textures/skybox/back.png"
    };

    std::vector<GLfloat> skybox_vertexes = 
    {       
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    Camera main_camera(window, 0.2f, 90.0f, 0.25f, glm::vec3(0.0));
    
    GLuint skybox_vao = CreateVAO(skybox_vertexes, 0, 3, GL_STATIC_DRAW);
    Shader skybox_shader("shaders/skybox/skybox.vs", "shaders/skybox/skybox.fs");
    GLuint skybox_texture = LoadCubeMap(cube_faces);

    ERROR();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window) && (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS))
    {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        main_camera.MovCallback();
        glm::mat4 view_matrix = main_camera.GetViewMatrix();
        glm::mat4 proj_matrix = main_camera.GetProjectionMatrix();
    
        glDepthMask(GL_TRUE);
        skybox_shader.Active();
        skybox_shader.SendMat4("view_matrix",       glm::mat4(glm::mat3(view_matrix)));
        skybox_shader.SendMat4("projection_matrix", proj_matrix);

        glBindVertexArray(skybox_vao);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_texture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthMask(GL_FALSE);
    
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}