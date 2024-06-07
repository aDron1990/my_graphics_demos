#include "Shader.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>

Shader::Shader(const std::string& vertexCode, const std::string& fragmentCode)
{
    auto vertex = compileShader(GL_VERTEX_SHADER, vertexCode);
    auto fragment = compileShader(GL_FRAGMENT_SHADER, fragmentCode);
    program = linkProgram(vertex, fragment);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
uint32_t Shader::compileShader(const int type, const std::string& shaderCode)
{
    int success;
    uint32_t shader = glCreateShader(type);
    const char* shaderCodeCStr = shaderCode.data();
    glShaderSource(shader, 1, &shaderCodeCStr, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        throw std::runtime_error{infoLog};
    }
    return shader;
}

uint32_t Shader::linkProgram(const uint32_t vertex, const uint32_t fragment)
{
    int success;
    uint32_t program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[1024];
        glGetProgramInfoLog(program, 1024, nullptr, infoLog);
        throw std::runtime_error{infoLog};
    }
    return program;
}

Shader::~Shader()
{
    glDeleteProgram(program);
}

Shader::Shader(Shader&& rhs) noexcept
{
    program = rhs.program;
    rhs.program = 0;
}

Shader& Shader::operator=(Shader&& rhs) noexcept
{
    program = rhs.program;
    rhs.program = 0;
    return *this;
}

void Shader::bind() const noexcept
{
    glUseProgram(program);
}

template<>
void Shader::setUniform(const std::string& uniformName, const glm::mat4& uniformValue) noexcept
{
    auto uniformLoc = glGetUniformLocation(program, uniformName.c_str());
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(uniformValue));
}