#include "utils/create_shader.hpp"
#include "shaders.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

int main()
{
    if(!glfwInit())
    {
        std::cout << "Failed to init GLFW" << std::endl;
        return 1;
    }
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to create window" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }
    glViewport(0, 0, 800, 600);

    const auto program = create_shader(std::string{vertex_code, sizeof(vertex_code)}, std::string{fragment_code, sizeof(fragment_code)}); 
    
    auto vertices = 
    {
    //   x      y         r     g     b
        0.0f, 0.5f,     1.0f, 0.0f, 0.0f,
        0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
    };

    uint32_t vbo, vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.begin(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float)));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);
    glfwTerminate();

    return 0;
}